#include "NBodySimPM.h"
namespace Compute
{
	#define KM_PER_PARSEC 3.086E+13f
	NBodySimPM::NBodySimPM (uint32_t numStars, float timeStepLength, uint32_t numTimesteps, 
											std::string filePath, SpatialGrid* grid,
											std::shared_ptr<Context> con, std::shared_ptr<Device> device)
		:b_shutdown (false), m_filePath (filePath), m_numStars (numStars), m_timeStepLength(timeStepLength),
		m_numTimesteps (numTimesteps), m_completedTimesteps (0), p_con (con), p_device (device), p_grid(grid),
		m_totalCells(grid->getTotalNumCells()), p_clfft_env(new clfftSetupData()), m_clfft_handle(clfftPlanHandle()) 
	{
		m_densityArr = new float[m_totalCells];
		p_cellArrDim = new size_t[]{(size_t)grid->getNumCellPerDim(), (size_t)grid->getNumCellPerDim (), 
																(size_t)grid->getNumCellPerDim () };
		m_deltaX = new float[m_totalCells];
		m_deltaY = new float[m_totalCells];
		m_deltaZ = new float[m_totalCells];
		m_zero = new float[m_totalCells];
		for ( int i = 0; i < m_totalCells; ++i )
			m_zero[i]=0;
	
	}
	NBodySimPM::~NBodySimPM ()
	{
		shutdown ();
		if ( m_simThread.joinable () )
			m_simThread.join ();
		clfftTeardown();
		delete[] m_densityArr;
		delete[] p_cellArrDim;
		delete[] m_deltaX;
		delete[] m_deltaY;
		delete[] m_deltaZ;
		delete p_clfft_env;
	}

	void NBodySimPM::init ()
	{

		p_cmdq = std::make_shared<CommandQueue> (p_con.get (), p_device.get ());
		p_program = std::unique_ptr<Program> (Program::createProgram ("src/Compute/Kernels/PMgravkernel.cl",
																																	*p_con, *p_device));
		p_kern = std::unique_ptr<Kernel> (Kernel::createKernel (p_program.get (), p_cmdq, "calcDeltaPhi"));
		int err = 0;
		err = clfftInitSetupData(p_clfft_env);
		err = clfftSetup(p_clfft_env);
		p_FFTBufferReal = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBuffer (
																												p_con, p_cmdq, m_totalCells, BufferFlags::Read_Write ));
		p_FFTBufferComplex = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBuffer (
																												p_con, p_cmdq, m_totalCells, BufferFlags::Read_Write));
		p_gradXBufferReal = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBuffer (
																												p_con, p_cmdq, m_totalCells, BufferFlags::Read_Write));
		p_gradXBufferComplex = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBuffer (
																												p_con, p_cmdq, m_totalCells, BufferFlags::Read_Write));
		p_gradYBufferReal = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBuffer (
																												p_con, p_cmdq, m_totalCells, BufferFlags::Read_Write));
		p_gradYBufferComplex = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBuffer (
																												p_con, p_cmdq, m_totalCells, BufferFlags::Read_Write));
		p_gradZBufferReal = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBuffer (
																												p_con, p_cmdq, m_totalCells, BufferFlags::Read_Write));
		p_gradZBufferComplex = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBuffer (
																												p_con, p_cmdq, m_totalCells, BufferFlags::Read_Write));

		p_FFTBuffers = new cl_mem[2];
		
	}

	void NBodySimPM::run ()
	{

		size_t globalWorkSize = m_totalCells;
		size_t localWorkSize = 64;
		float scale = p_grid->getCellDim();
		m_simThread = std::thread ([=]()
		{
			init ();
			float scale_3 = scale * scale * scale;
			std::shared_ptr<IO::StarFileMT> file (IO::StarFileMT::createFile (m_filePath, m_numStars, m_numTimesteps));
			clfftCreateDefaultPlan(&m_clfft_handle, p_con->getCLContext(), m_clfft_dim, p_cellArrDim);
			clfftSetPlanPrecision(m_clfft_handle, CLFFT_SINGLE);
			clfftSetLayout(m_clfft_handle, CLFFT_COMPLEX_PLANAR, CLFFT_COMPLEX_PLANAR);
			clfftSetResultLocation(m_clfft_handle, CLFFT_INPLACE);
			clfftSetPlanScale(m_clfft_handle, CLFFT_FORWARD, scale_3);
			clfftSetPlanScale (m_clfft_handle, CLFFT_BACKWARD,  scale_3/(scale_3 * scale_3));
			clfftBakePlan(m_clfft_handle, 1, p_cmdq->getQueuePtr(), NULL, NULL);
			float cellDim = p_grid->getCellDim ();
		
			for( int i = 0; i < m_numTimesteps; ++i){
				m_visStars = p_grid->getVisibleStars ();
				p_grid->updateSpatialGrid();
				std::vector<float> den = p_grid->getDensityArr();
				std::copy (den.begin(), den.begin() + m_totalCells, m_densityArr);
				p_FFTBufferReal->pushToBuffer(m_densityArr, m_totalCells);
				p_FFTBufferComplex->pushToBuffer(m_zero, m_totalCells);

				p_FFTBuffers[0] = p_FFTBufferReal->getMemBuffer(); 
				p_FFTBuffers[1] = p_FFTBufferComplex->getMemBuffer();
				clfftEnqueueTransform (m_clfft_handle, CLFFT_FORWARD, 1,  p_cmdq->getQueuePtr(), 0, NULL, NULL, 
																p_FFTBuffers, NULL, NULL);
			/*	clfftEnqueueTransform (m_clfft_handle, CLFFT_BACKWARD, 1, p_cmdq->getQueuePtr (), 0, NULL, NULL,
				p_FFTBuffers, NULL, NULL); */
				p_kern->setKernelArg (0, *p_FFTBufferReal);
				p_kern->setKernelArg (1, *p_FFTBufferComplex);

				p_kern->setKernelArg (2, (int)p_cellArrDim[0]);
				p_kern->setKernelArg (3, (int)p_cellArrDim[1]);
				p_kern->setKernelArg (4, (int)p_cellArrDim[2]);

				p_kern->setKernelArg (5, cellDim);
				
				p_kern->setKernelArg (6, *p_gradXBufferReal);
				p_kern->setKernelArg (7, *p_gradXBufferComplex);
				p_kern->setKernelArg (8, *p_gradYBufferReal);
				p_kern->setKernelArg (9, *p_gradYBufferComplex);
				p_kern->setKernelArg (10, *p_gradZBufferReal);
				p_kern->setKernelArg (11, *p_gradZBufferComplex);
				p_kern->runKernel(1, globalWorkSize, localWorkSize);
			

				p_FFTBuffers[0] = p_gradXBufferReal->getMemBuffer ();
				p_FFTBuffers[1] = p_gradXBufferComplex->getMemBuffer ();
				clfftEnqueueTransform (m_clfft_handle, CLFFT_BACKWARD, 1, p_cmdq->getQueuePtr (), 0, NULL, NULL,
																p_FFTBuffers, NULL, NULL);
				
				p_FFTBuffers[0] = p_gradYBufferReal->getMemBuffer ();
				p_FFTBuffers[1] = p_gradYBufferComplex->getMemBuffer ();
				clfftEnqueueTransform (m_clfft_handle, CLFFT_BACKWARD, 1, p_cmdq->getQueuePtr (), 0, NULL, NULL,
																				p_FFTBuffers, NULL, NULL);
				
				p_FFTBuffers[0] = p_gradZBufferReal->getMemBuffer ();
				p_FFTBuffers[1] = p_gradZBufferComplex->getMemBuffer ();
				clfftEnqueueTransform (m_clfft_handle, CLFFT_BACKWARD, 1, p_cmdq->getQueuePtr (), 0, NULL, NULL,
																				p_FFTBuffers, NULL, NULL);
				clFinish(p_cmdq->getQueue());

				p_gradXBufferReal->pullFromBuffer (m_totalCells, m_deltaX);
				p_gradYBufferReal->pullFromBuffer (m_totalCells, m_deltaY);
				p_gradZBufferReal->pullFromBuffer (m_totalCells, m_deltaZ);

				//std::vector<float> debug  = p_gradXBufferComplex->pullFromBuffer (m_totalCells);
				//std::vector<float> debug2 = p_gradYBufferComplex->pullFromBuffer (m_totalCells);
				//std::vector<float> debug3 = p_gradZBufferComplex->pullFromBuffer (m_totalCells);
				//auto debug = p_gradXBufferReal->pullFromBuffer(m_totalCells);
				// Start applying the gradients to the masses in the simulation



				m_visStars = p_grid->getVisibleStars ();
				m_darkStars = p_grid->getDarkStars();
				std::vector<Util::Vec3f> timeStep;
				for ( auto it = m_visStars.begin (); it != m_visStars.end (); ++it )
				{
					//Warning! This assumes that the grid is a cube. If this assumtion is false, another function
					//will need to be used. This also assumes that the grid indexs and the gradient indexs match. 
					Util::Vec3f timeStepStar;
					bool outOfBounds = it->pos.x < 0 || it->pos.x > (p_grid->getCellDim () * p_grid->getNumCellPerDim ()) ||
													   it->pos.y < 0 || it->pos.y > (p_grid->getCellDim () * p_grid->getNumCellPerDim ()) ||
														 it->pos.z < 0 || it->pos.z > (p_grid->getCellDim () * p_grid->getNumCellPerDim ());
					size_t ind = SpatialGrid::computeIndex (*it, p_cellArrDim[0], p_grid->getCellDim ());
					bool inBounds = ind >= 0 && ind < m_totalCells; 
					if(inBounds){ // if it is out of bounds don't update
						//size_t ind = SpatialGrid::computeIndex(*it, p_cellArrDim[0], p_grid->getCellDim ());
						it->pos.x += (it->vel.x * m_timeStepLength)/KM_PER_PARSEC; 
						it->pos.y += (it->vel.y * m_timeStepLength)/KM_PER_PARSEC; 
						it->pos.z += (it->vel.z * m_timeStepLength)/KM_PER_PARSEC; 
						it->pos.x -= (.5 * (m_deltaX[ind] / KM_PER_PARSEC) * m_timeStepLength * m_timeStepLength) / KM_PER_PARSEC;
						it->pos.y -= (.5 * (m_deltaY[ind] / KM_PER_PARSEC) * m_timeStepLength * m_timeStepLength) / KM_PER_PARSEC;
						it->pos.z -= (.5 * (m_deltaZ[ind] / KM_PER_PARSEC) * m_timeStepLength * m_timeStepLength) / KM_PER_PARSEC;
						it->vel.x	-= (m_deltaX[ind] * m_timeStepLength / KM_PER_PARSEC);
						it->vel.y	-= (m_deltaY[ind] * m_timeStepLength / KM_PER_PARSEC);
						it->vel.z -= (m_deltaZ[ind] * m_timeStepLength / KM_PER_PARSEC);
					
					}
					timeStepStar = it->pos;
					timeStep.push_back(timeStepStar);
				}
				p_grid->setVisStars(m_visStars);
				file->writeTimeStep (timeStep);
				for ( auto it = m_darkStars.begin (); it != m_darkStars.end (); ++it )
				{
					//Warning! This assumes that the grid is a cube. If this assumtion is false, another function
					//will need to be used. This also assumes that the grid indexs and the gradient indexs match. 
					bool outOfBounds = it->pos.x < 0 || it->pos.x > (p_grid->getCellDim () * p_grid->getNumCellPerDim ()) ||
						it->pos.y < 0 || it->pos.y > (p_grid->getCellDim () * p_grid->getNumCellPerDim ()) ||
						it->pos.z < 0 || it->pos.z > (p_grid->getCellDim () * p_grid->getNumCellPerDim ());
					if ( !outOfBounds )
					{ // if it is out of bounds don't update
						size_t ind = SpatialGrid::computeIndex (*it, p_cellArrDim[0], p_grid->getCellDim ());
						it->pos.x = it->pos.x + ((it->vel.x * m_timeStepLength) + (.5 * (m_deltaX[ind] / KM_PER_PARSEC) * m_timeStepLength * m_timeStepLength)) / KM_PER_PARSEC;
						it->pos.y = it->pos.y + ((it->vel.y * m_timeStepLength) + (.5 * (m_deltaY[ind] / KM_PER_PARSEC) * m_timeStepLength * m_timeStepLength)) / KM_PER_PARSEC;
						it->pos.z = it->pos.z + ((it->vel.z * m_timeStepLength) + (.5 * (m_deltaZ[ind] / KM_PER_PARSEC) * m_timeStepLength * m_timeStepLength)) / KM_PER_PARSEC;
						it->vel.x = it->vel.x * m_deltaX[ind] * m_timeStepLength / KM_PER_PARSEC;
						it->vel.y = it->vel.y * m_deltaY[ind] * m_timeStepLength / KM_PER_PARSEC;
						it->vel.z = it->vel.z * m_deltaZ[ind] * m_timeStepLength / KM_PER_PARSEC;
					}
				}
				p_grid->setDarkStars (m_darkStars);
				//p_grid->updateSpatialGrid();
				
				incrementTimestepsDone ();
			}
		}
	);
	}
}