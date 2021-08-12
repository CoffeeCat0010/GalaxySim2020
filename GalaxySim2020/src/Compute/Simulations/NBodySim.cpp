#include "NBodySim.h"
namespace Compute
{
	NBodySim::NBodySim (uint32_t numStars, uint32_t numTimesteps, std::string filePath,
											std::vector<cl_float3>& starPos, std::vector<cl_float3>& starVel,
											std::vector<float>& starMass, std::shared_ptr<Context> con,
											std::shared_ptr<Device> device)
		:b_shutdown(false), m_filePath (filePath), m_numStars (numStars), m_numTimesteps (numTimesteps),
		 m_completedTimesteps(0),p_con(con), p_device(device)
	{
		m_starPosArr = new cl_float3[m_numStars];
		m_starVelArr = new cl_float3[m_numStars];
		m_starMassArr = new float[m_numStars];

		std::copy (starPos.begin  (), starPos.begin  () + m_numStars, m_starPosArr );
		std::copy (starVel.begin  (), starVel.begin  () + m_numStars, m_starVelArr );
		std::copy (starMass.begin (), starMass.begin () + m_numStars, m_starMassArr);
	}
	NBodySim::~NBodySim ()
	{
		shutdown();
		if(m_simThread.joinable())
			m_simThread.join();
		delete[] m_starPosArr;
		delete[] m_starVelArr;
		delete[] m_starMassArr;
	}
	void NBodySim::init ()
	{
			p_cmdq = std::make_shared<CommandQueue> (p_con.get (), p_device.get ());
			p_program = std::unique_ptr<Program> (Program::createProgram ("src/Compute/Kernels/PhysKernel.cl",
																																		*p_con, *p_device));
			p_kern = std::unique_ptr<Kernel> (Kernel::createKernel (p_program.get (), p_cmdq, "calcPos"));

			p_starMassBuffer = std::shared_ptr<MemBuffer<float>> (MemBuffer<float>::createMemBufferWithData (
				p_con, p_cmdq, m_numStars, m_starMassArr,
				BufferFlags::Read_Only | BufferFlags::Copy_Host_Ptr));

			p_starPosInBuffer = std::shared_ptr<MemBuffer<cl_float3>> (MemBuffer<cl_float3>::createMemBufferWithData (
				p_con, p_cmdq, m_numStars, m_starPosArr,
				BufferFlags::Read_Only | BufferFlags::Copy_Host_Ptr));

			p_starVelInBuffer = std::shared_ptr<MemBuffer<cl_float3>> (MemBuffer<cl_float3>::createMemBufferWithData (
				p_con, p_cmdq, m_numStars, m_starVelArr,
				BufferFlags::Read_Write | BufferFlags::Copy_Host_Ptr));
			p_starPosOutBuffer = std::shared_ptr<MemBuffer<cl_float3>> (MemBuffer<cl_float3>::createMemBuffer (
				p_con, p_cmdq, m_numStars,
				BufferFlags::Read_Write));
			//p_starVelOutBuffer = std::shared_ptr<MemBuffer<cl_float3>> (MemBuffer<cl_float3>::createMemBuffer (
				//p_con, p_cmdq, m_numStars,
				//BufferFlags::Read_Write));
			
		
	}
	void NBodySim::run ()
	{
		m_simThread = std::thread([=]() 
		{
			init();

			float softeningFactor = 100.0f;
			float timeStep = 75000 * 3.154e+07; // 75,000 years in seconds 
			std::shared_ptr<IO::StarFileMT> file (IO::StarFileMT::createFile (m_filePath, m_numStars, m_numTimesteps));
			size_t globalWorkSize = m_numStars;
			size_t localWorkSize = 64;
			for ( int i = 0; i < m_numTimesteps; i++ )
			{

				p_kern->setKernelMemBufferArg(0, p_starPosInBuffer.get());
				p_kern->setKernelMemBufferArg(1, p_starMassBuffer.get());
				p_kern->setKernelArg<float>(2, &softeningFactor);
				p_kern->setKernelArg<float>(3, &timeStep);
				p_kern->setKernelMemBufferArg(4, p_starVelInBuffer.get());
				p_kern->setKernelMemBufferArg(5, p_starPosOutBuffer.get());
				//p_kern->setKernelMemBufferArg(6, p_starVelOutBuffer.get ());


				p_kern->runKernel(1, globalWorkSize, localWorkSize);
				clFinish (p_cmdq.get ()->getQueue ());

				std::vector<cl_float3> result = p_starPosOutBuffer->pullFromBuffer(m_numStars);
				file->writeTimeStep (Application::clFloatArrToVec3f (result.data(), m_numStars));
				std::vector<cl_float3> resultVel1 = p_starVelInBuffer->pullFromBuffer(m_numStars);
				p_starPosInBuffer->copyFromBuffer (p_starPosOutBuffer.get (), m_numStars);
				std::copy(resultVel1.begin(), resultVel1.end(), m_starVelArr);
				p_starVelInBuffer->pushToBuffer(m_starVelArr, m_numStars, 0, true);
				//p_starVelInBuffer->copyFromBuffer(p_starVelOutBuffer.get(), m_numStars);
				for ( int i = 0; i < m_numStars; ++i )
				{
					cl_float3 starPos = m_starPosArr[i];
					cl_float3 starVel = m_starVelArr[i];

					if ( starPos.x != starPos.x ||
					starPos.y != starPos.y ||
					starPos.z != starPos.z ||
					starVel.x != starVel.x ||
					starVel.y != starVel.y ||
					starVel.z != starVel.z )
					{
						std::cout << "Something is not a number!" << i << std::endl;
					}
				}
				incrementTimestepsDone();
			}
		}
	);
	}
}

