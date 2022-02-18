#pragma once
#include "Corepch.h"
#include "GravMass.h"
#include "Cell.h"

namespace Compute{
	class SpatialGrid
	{

	public:
		explicit SpatialGrid(float cellDim, int64_t numCellsPerDim, std::vector<GravMass>& visStars, std::vector<GravMass>& darkStars);
		~SpatialGrid() = default;

		static size_t computeIndex(GravMass& star, int32_t numCellPerDim, float sizeOfCell);
		void updateSpatialGrid();

		void setVisStars  (std::vector<GravMass>& stars);
		void setDarkStars (std::vector<GravMass>& stars);

		// Getters
		
		std::vector<float> getDensityArr();
		
		/// <summary>
		/// Returns the dimension of each cell in one direction in parsecs. This assumes that cells are cubes!
		/// </summary>
		/// <returns>A float representing the length in one direction</returns>
		inline float getCellDim() const {return m_cellDim;}

		/// <summary>
		/// Returns the vector of visible stars
		/// </summary>
		/// <returns> std::vector containing Compute::GravMass </returns>
		inline std::vector<GravMass> getVisibleStars() {
			updateLock.lock ();
			std::vector<GravMass> res = m_visStarsCurr;
			updateLock.unlock ();
			return res;
		}
		/// <summary>
		/// Returns the vector of dark matter "stars"
		/// </summary>
		/// <returns> std::vector containing Compute::GravMass</returns>
		inline const std::vector<GravMass> getDarkStars () {
			updateLock.lock ();
			std::vector<GravMass> res = m_darkStarsCurr;
			updateLock.unlock ();
			return res;
		}
		/// <summary>
		/// Returns the vector of the spactial grid. May be depricated in future.
		/// </summary>
		/// <returns> std::vector containing Compute::Cell 4</returns>
		inline const std::vector<Cell> getSpatialGrid() { 
			updateLock.lock ();
			std::vector<Cell> res = m_spatialGrid;
			updateLock.unlock ();
			return res;
		}
		/// <summary>
		/// 
		/// </summary>
		/// <returns></returns>
		inline int getNumCellPerDim() const {return m_numCellPerDim;}
		inline int getTotalNumCells() const {return m_numCellPerDim * m_numCellPerDim * m_numCellPerDim;}
	private:
		// This will be the cell size in parsecs. For now all cells, are assumed to be cubes. 
		// This might be something I change in the future.
		float m_cellDim;
		int m_numCellPerDim;

		std::vector<GravMass> m_visStarsCurr;
		std::vector<GravMass> m_darkStarsCurr;

		std::vector<GravMass> m_visStarsUpdated;
		std::vector<GravMass> m_darkStarsUpdated;
		
		std::vector<Cell> m_spatialGrid;

		std::mutex updateLock;
	};
}

