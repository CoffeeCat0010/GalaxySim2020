#include "SpatialGrid.h"
namespace Compute{
  SpatialGrid::SpatialGrid (float cellDim, int64_t numCellsPerDim, std::vector<GravMass>& visStars, std::vector<GravMass>& darkStars)
    :m_cellDim(cellDim), m_numCellPerDim(numCellsPerDim), m_visStarsCurr(std::vector<GravMass>(visStars)),
    m_darkStarsCurr(std::vector<GravMass>(darkStars))
  {
     m_spatialGrid = std::vector<Cell>(numCellsPerDim * numCellsPerDim * numCellsPerDim, Cell(cellDim));
  }
  size_t SpatialGrid::computeIndex (GravMass& star, int32_t numCellPerDim, float sizeOfCell)
  {
    int x = (int)std::ceil (star.pos.x / (sizeOfCell));
    int y = (int)std::ceil (star.pos.y / (sizeOfCell));
    int z = (int)std::ceil (star.pos.z / (sizeOfCell));
    size_t ind = (x ) + (y * numCellPerDim) + (z * numCellPerDim * numCellPerDim);
    return ind;
  }
  void SpatialGrid::updateSpatialGrid ()
  {
    updateLock.lock();
    for ( auto it = m_spatialGrid.begin (); it != m_spatialGrid.end (); ++it )
    {
      it->clearCell();
    }

    for ( int i = 0; i < m_visStarsCurr.size (); ++i )
    {
      GravMass* star = &m_visStarsCurr[i];
      int ind = computeIndex(*star, m_numCellPerDim, m_cellDim);
      bool isValid = ind > 0 && ind < m_spatialGrid.size();
      if(isValid)
        m_spatialGrid[ind].insertMass(*star);
    }
    for ( int i = 0; i < m_darkStarsCurr.size (); ++i )
    {
      GravMass* star = &m_darkStarsCurr[i];
      int ind = computeIndex (*star, m_numCellPerDim, m_cellDim);
      bool isValid = ind > 0 && ind < m_spatialGrid.size ();
      if ( isValid )
        m_spatialGrid[ind].insertMass (*star);
    }
    updateLock.unlock();
  }
  void SpatialGrid::setVisStars (std::vector<GravMass>& stars)
  {
    updateLock.lock();
    std::copy(stars.begin(), stars.end(), m_visStarsCurr.begin());
    updateLock.unlock();
  }
  void SpatialGrid::setDarkStars (std::vector<GravMass>& stars)
  {
    updateLock.lock();
    std::copy (stars.begin (), stars.end (), m_darkStarsCurr.begin ());
    updateLock.unlock();
  }
  std::vector<float> Compute::SpatialGrid::getDensityArr ()
  {
    std::vector<float> ret;
    ret.reserve(m_spatialGrid.size());
    updateLock.lock();
    for ( auto it = m_spatialGrid.begin (); it != m_spatialGrid.end (); ++it )
    {
      ret.push_back(it->getDensity());
    }
    updateLock.unlock();
    return ret;
  }
}
