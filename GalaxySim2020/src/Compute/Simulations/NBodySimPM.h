#pragma once
#include "Corepch.h"
#include "IO/DataFileType/StarFileMT.h"
#include "Compute/CLprim/CLPrim.h"
#include "Utility/Math/MVec.h"
#include "../SimulationObjects/Cell.h"
#include "../SimulationObjects/GravMass.h"
#include "../SimulationObjects/SpatialGrid.h"

#include <clFFT.h>
namespace Compute
{
	class NBodySimPM
{
	private:
		std::thread m_simThread;
		mutable std::mutex m_progressMtx;
		mutable std::mutex m_threadControl;
		bool b_shutdown;

		std::unique_ptr<IO::StarFileMT> p_file;
		std::string m_filePath;

		const uint32_t m_numStars;
		const float m_timeStepLength;
		const uint32_t m_numTimesteps;
		uint32_t m_completedTimesteps;

		//Start OpenCL
		std::shared_ptr<Context> p_con;
		std::shared_ptr<Device> p_device;
		std::unique_ptr<Program> p_program;
		std::unique_ptr<Kernel> p_kern;
		std::shared_ptr<CommandQueue> p_cmdq;

		std::shared_ptr<MemBuffer<float>> p_FFTBufferReal;
		std::shared_ptr<MemBuffer<float>> p_FFTBufferComplex;

		std::shared_ptr<MemBuffer<float>> p_gradXBufferReal;
		std::shared_ptr<MemBuffer<float>> p_gradXBufferComplex;

		std::shared_ptr<MemBuffer<float>> p_gradYBufferReal;
		std::shared_ptr<MemBuffer<float>> p_gradYBufferComplex;

		std::shared_ptr<MemBuffer<float>> p_gradZBufferReal;
		std::shared_ptr<MemBuffer<float>> p_gradZBufferComplex;


		cl_mem* p_FFTBuffers;

		size_t m_totalCells;

		//pointer Members
		SpatialGrid* p_grid;

		//Start Arrays
		float* m_densityArr;
		size_t* p_cellArrDim;

		float* m_deltaX;
		float* m_deltaY;
		float* m_deltaZ;
		float* m_zero;

		std::vector<GravMass> m_visStars;
		std::vector<GravMass> m_darkStars;

		//Start clfft specific data
		clfftSetupData* p_clfft_env;
		clfftPlanHandle m_clfft_handle;
		clfftDim m_clfft_dim = CLFFT_3D;


	public:
		explicit NBodySimPM (uint32_t numStars, float timeStepLength, uint32_t numTimesteps, std::string filePath,
											SpatialGrid* grid, std::shared_ptr<Context> con, std::shared_ptr<Device> device);
		~NBodySimPM ();
		void run ();

		//Start Setters
		inline void shutdown ()
		{
			std::lock_guard<std::mutex> lock (m_threadControl);
			b_shutdown = true;
		}
		//Start getters
		inline const uint32_t getNumTimesteps () const { return m_numTimesteps; }

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
		void init ();
	};
}
