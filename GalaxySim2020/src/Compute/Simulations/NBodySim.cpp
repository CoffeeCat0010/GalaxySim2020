#include "NBodySim.h"
namespace Compute
{
	NBodySim::NBodySim (uint32_t numStars, uint32_t numTimesteps, std::string filePath,
											std::vector<cl_float3>& starPos, std::vector<cl_float3>& starVel,
											std::vector<float>& starMass, std::shared_ptr<Context> con,
											std::shared_ptr<Device> device)
		:b_shutdown (false), m_filePath (filePath), m_numStars (numStars), m_numTimesteps (numTimesteps),
		m_completedTimesteps (0), p_con (con), p_device (device)
	{
		m_starPosArr = new cl_float3[m_numStars];
		m_starVelArr = new cl_float3[m_numStars];
		m_starMassArr = new float[m_numStars];

		std::copy (starPos.begin (), starPos.begin () + m_numStars, m_starPosArr);
		std::copy (starVel.begin (), starVel.begin () + m_numStars, m_starVelArr);
		std::copy (starMass.begin (), starMass.begin () + m_numStars, m_starMassArr);
	}
	NBodySim::~NBodySim ()
	{
		shutdown ();
		if ( m_simThread.joinable () )
			m_simThread.join ();
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
		m_simThread = std::thread ([=]()
		{
			//	init();

			//	float softeningFactor = 100.0f;
			//	float timeStep = 75000 * 3.154e+07; // 75,000 years in seconds 
			//	std::shared_ptr<IO::StarFileMT> file (IO::StarFileMT::createFile (m_filePath, m_numStars, m_numTimesteps));
			//	size_t globalWorkSize = m_numStars;
			//	size_t localWorkSize = 64;
			//	for ( int i = 0; i < m_numTimesteps; i++ )
			//	{

			//		p_kern->setKernelMemBufferArg(0, p_starPosInBuffer.get());
			//		p_kern->setKernelMemBufferArg(1, p_starMassBuffer.get());
			//		p_kern->setKernelArg<float>(2, &softeningFactor);
			//		p_kern->setKernelArg<float>(3, &timeStep);
			//		p_kern->setKernelMemBufferArg(4, p_starVelInBuffer.get());
			//		p_kern->setKernelMemBufferArg(5, p_starPosOutBuffer.get());
			//		//p_kern->setKernelMemBufferArg(6, p_starVelOutBuffer.get ());


			//		p_kern->runKernel(1, globalWorkSize, localWorkSize);
			//		clFinish (p_cmdq.get ()->getQueue ());

			//		std::vector<cl_float3> result = p_starPosOutBuffer->pullFromBuffer(m_numStars);
			//		file->writeTimeStep (Application::clFloatArrToVec3f (result.data(), m_numStars));
			//		std::vector<cl_float3> resultVel1 = p_starVelInBuffer->pullFromBuffer(m_numStars);
			//		//p_starPosInBuffer->copyFromBuffer (p_starPosOutBuffer.get (), m_numStars);
			//		std::copy (result.begin (), result.begin() + m_numStars, m_starPosArr);
			//		std::copy(resultVel1.begin(), resultVel1.begin() + m_numStars, m_starVelArr);
			//		p_starVelInBuffer->pushToBuffer (m_starVelArr, m_numStars, 0, true);
			//		p_starPosInBuffer->pushToBuffer(m_starPosArr, m_numStars, 0, true);
			//		//p_starVelInBuffer->copyFromBuffer(p_starVelOutBuffer.get(), m_numStars);
			//		incrementTimestepsDone();
			//	}
			//}

				cl_context con = p_con->getCLContext ();

				cl_device_id dID = p_device->getId ();

				cl_command_queue clcq = clCreateCommandQueue (con, dID, 0, nullptr);

				//cl_program clProgram = createProgram (con, dID, "src/Compute/Kernels/PhysKernel.cl");
				std::unique_ptr<Compute::Program> program = Compute::Program::createProgramU_Ptr ("src/Compute/Kernels/PhysKernel.cl", con, dID);
				//std::unique_ptr<Compute::Kernel> kern = Compute::Kernel::createKernel (program->getProgramID (), "calcPos");
				cl_kernel kern = clCreateKernel (program->getProgramID (), "calcPos", nullptr);
				cl_int err;
				//cl_kernel kern = clCreateKernel (program->getProgramID(), "calcPos", &err);


				cl_float3* result = new cl_float3[m_numStars];
				cl_float3* resultVelocities = new cl_float3[m_numStars];
				cl_mem buffers[4];

				buffers[0] = clCreateBuffer (con, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof (cl_float3) * m_numStars, m_starPosArr, &err);
				buffers[1] = clCreateBuffer (con, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof (float) * m_numStars, m_starMassArr, &err);
				buffers[2] = clCreateBuffer (con, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof (cl_float3) * m_numStars, m_starVelArr, &err);
				buffers[3] = clCreateBuffer (con, CL_MEM_READ_WRITE, sizeof (cl_float3) * m_numStars, NULL, &err);

				float softeningFactor = 100.0f;
				float timeStep = 75000 * 3.154e+07;
				std::shared_ptr<IO::StarFileMT> file (IO::StarFileMT::createFile (m_filePath, m_numStars, m_numTimesteps));
				for ( int i = 0; i < m_numTimesteps; i++ )
				{
					err = clSetKernelArg (kern/*->getKernel ()*/, 0, sizeof (cl_mem), &buffers[0]);
					err |= clSetKernelArg (kern/*->getKernel ()*/, 1, sizeof (cl_mem), &buffers[1]);
					err |= clSetKernelArg (kern/*->getKernel ()*/, 2, sizeof (float), &softeningFactor);
					err |= clSetKernelArg (kern/*->getKernel ()*/, 3, sizeof (float), &timeStep);
					err |= clSetKernelArg (kern/*->getKernel ()*/, 4, sizeof (cl_mem), &buffers[2]);
					err |= clSetKernelArg (kern/*->getKernel ()*/, 5, sizeof (cl_mem), &buffers[3]);

					if ( err != CL_SUCCESS )
					{
						std::cout << "Couldn't upload kernel args!" << std::endl;
						std::cout << err << std::endl;
					}
					size_t globalWorkSize = m_numStars;
					size_t localWorkSize = 1;

					err = clEnqueueNDRangeKernel (clcq, kern/*->getKernel ()*/, 1, 0, &globalWorkSize, &localWorkSize, 0, NULL, NULL);
					if ( err != CL_SUCCESS )
					{
						std::cout << "Couldn't execute Kernel!" << std::endl;
					}

					err |= clEnqueueReadBuffer (clcq, buffers[3], CL_TRUE, 0, m_numStars * sizeof (cl_float3), result, 0, NULL, NULL);
					err |= clEnqueueReadBuffer (clcq, buffers[2], CL_TRUE, 0, m_numStars * sizeof (cl_float3), resultVelocities, 0, NULL, NULL);

					for ( int j = 0; j < m_numStars; ++j )
					{
						/*std::cout << "Position: " << result[j].x << " " << result[j].y << " " << result[j].z << " "
							<< "Velocities(km/s): " << resultVelocities[j].x << " " << resultVelocities[j].y << " " << resultVelocities[j].z << std::endl;*/
						m_starPosArr[j] = result[j];
						m_starVelArr[j] = resultVelocities[j];
					}
					file->writeTimeStep (Application::clFloatArrToVec3f (result, m_numStars));
					//std::cout << std::endl;
					err |= clEnqueueWriteBuffer (clcq, buffers[0], CL_TRUE, 0, m_numStars * sizeof (cl_float3), m_starPosArr, 0, NULL, NULL);
					err |= clEnqueueWriteBuffer (clcq, buffers[2], CL_TRUE, 0, m_numStars * sizeof (cl_float3), m_starVelArr, 0, NULL, NULL);
					incrementTimestepsDone ();
				}
				//delete file;
				clReleaseMemObject (buffers[0]);
				clReleaseMemObject (buffers[1]);
				clReleaseMemObject (buffers[2]);
				clReleaseMemObject (buffers[3]);
				//clReleaseProgram (clProgram);
				clReleaseCommandQueue (clcq);
			}
		);
	}
}

