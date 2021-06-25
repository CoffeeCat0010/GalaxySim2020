#pragma once
#include <string>
#include <fstream>
#include "CL/cl.hpp"
#include "glm/glm.hpp"

namespace IO
{
	class StarFile
	{
		struct Header
		{
			uint64_t m_offsetToFirst;
			uint64_t m_numStars;
			uint64_t m_stride;
		};

	private:
		std::string m_path;
		std::shared_ptr<std::fstream> m_stream;
		Header m_header;

	private:
		StarFile (const std::string& path, std::ios_base::openmode mode);
		
	public:
		StarFile (const StarFile& file)
			:m_path(file.getPath()), m_stream(file.getStream()), m_header(file.getHeader()) 
		{};
		~StarFile ()
		{
			m_stream.~shared_ptr();
		};

		std::string getPath () const { return m_path; };
		std::shared_ptr<std::fstream> getStream () const { return m_stream; };
		Header getHeader () const { return m_header; }
		/// <summary>
		/// Creates a new file at path and opens in write mode. If the file
		/// already exists, it will be overwritten.
		/// </summary>
		/// <param name="path">Path of new file</param>
		/// <param name="numStars">Number of stars in the Simulation</param>
		/// <returns>A StarFile object</returns>
		static StarFile* createFile (const std::string& path, uint32_t numStars);
		/// <summary>
		/// Creates a StarFile object that is opened in read mode.
		/// </summary>
		/// <param name="path">Path to file</param>
		/// <returns>A StarFile object</returns>
		static StarFile* readFile (const std::string& path);
		/// <summary>
		/// This writes data to the file. The expected size of the data array is of size m_numStars.
		/// It is up to the user to ensure they are the same;
		/// </summary>
		/// <param name="data">Data to be written to the file</param>
		void writeTimeStep (const cl_float3* data);
		
		/// <summary>
		/// This writes data to the file in sub-time step chunks. It is up to the user to ensure that
		/// the time step data will line up.
		/// </summary>
		/// <param name="data"> Data to be written to the file</param>
		/// <param name="sizeOfArray">The number of elements in the array</param>
		void writeSubTimeStep (const cl_float3* data, size_t sizeOfArray);

		size_t getNumStars () { return m_header.m_numStars; };
		/// <summary>
		/// Attempts to read the number of stars specified by stride/3*float 
		/// </summary>
		/// <param name="data"> Pointer to the buffer to be written to</param>
		/// <param name="numElementsInBuf">Size of the buffer in elements</param>
		/// <returns> The number of elements read</returns>
		void readTimeStep (glm::vec3* data, size_t numElementsInBuf);

	};
}

