#pragma once
#include "Corepch.h"
#include "IO/DataFileType/StarFileMT.h"
#include "Compute/CLprim/CLPrim.h"
#include "Utility/Math/MVec.h"
namespace Compute
{
	class NBodySim
	{
	private:
		std::thread m_simThread;
		mutable std::mutex m_progressMtx;
		mutable std::mutex m_threadControl;
		bool b_shutdown; 

		std::unique_ptr<IO::StarFileMT> p_file;
		std::string m_filePath;

		const uint32_t m_numStars;
		const uint32_t m_numTimesteps;
		uint32_t m_completedTimesteps;

		//Start OpenCL
		std::shared_ptr<Context> p_con;
		std::shared_ptr<Device> p_device;
		std::unique_ptr<Program> p_program;
		std::unique_ptr<Kernel> p_kern;
		std::shared_ptr<CommandQueue> p_cmdq;

		std::shared_ptr<MemBuffer<float>> p_starMassBuffer;

		std::shared_ptr<MemBuffer<cl_float3>> p_starPosInBuffer;
		std::shared_ptr<MemBuffer<cl_float3>> p_starVelInBuffer;

		std::shared_ptr<MemBuffer<cl_float3>> p_starPosOutBuffer;
		std::shared_ptr<MemBuffer<cl_float3>> p_starVelOutBuffer;

		//Start Arrays
		cl_float3* m_starPosArr;
		cl_float3* m_starVelArr;
		float* m_starMassArr;

	public:
		explicit NBodySim (uint32_t numStars, uint32_t numTimesteps, std::string filePath,
											std::vector<cl_float3>& starPos, std::vector<cl_float3>& starVel,
											std::vector<float>& starMass, std::shared_ptr<Context> con, 
											std::shared_ptr<Device> device);
		~NBodySim();
		void run();

		//Start Setters
		inline void shutdown ()
		{
			std::lock_guard<std::mutex> lock (m_threadControl);
			b_shutdown = true;
		}
		//Start getters
		inline const uint32_t getNumTimesteps() const {return m_numTimesteps;}

		inline void incrementTimestepsDone ()
		{
			std::lock_guard<std::mutex> lock (m_progressMtx);
			m_completedTimesteps++;
		}

		inline const uint32_t getTimestepsDone () const
		{
			std::lock_guard<std::mutex> lock (m_progressMtx);
			return m_completedTimesteps;
		}
		inline const bool isShutdown () const
		{
			std::lock_guard<std::mutex> lock (m_threadControl);
			return b_shutdown;
		}
	private:
		void init();
	};
}

