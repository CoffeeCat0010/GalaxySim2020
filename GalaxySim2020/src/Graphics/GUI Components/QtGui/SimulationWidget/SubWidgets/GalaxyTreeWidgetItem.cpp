#include "GalaxyTreeWidgetItem.h"

namespace QUI{
	GalaxyTreeWidgetItem::GalaxyTreeWidgetItem (const QString& name, Physics::GalaxyParams galParams, QTreeWidget* parent)
		:QObject(parent), QTreeWidgetItem(parent, GalaxyTreeItemType), m_galaxy (galParams)
	{
		
		parent->setSortingEnabled(true);
		this->setText( 0 , "Galaxy");
		this->setData( 1 , Qt::EditRole , "default");
		this->addChild(&m_pos);
		this->addChild(&m_rot);
		this->addChild(&m_galaxyDim);
		this->addChild(&m_galaxyStarProperties);

		m_pos.setText  (0, "Position");

		setEditableItem ("x", m_galaxy.pos.x, m_xPos);
		setEditableItem ("y", m_galaxy.pos.y, m_yPos);
		setEditableItem ("z", m_galaxy.pos.z, m_zPos);
		
		m_pos.addChildren ({&m_xPos, &m_yPos, &m_zPos});
		
		m_rot.setText (0, "Rotation");

		setEditableItem ("x", m_galaxy.rotation.x, m_xRot);
		setEditableItem ("y", m_galaxy.rotation.y, m_yRot);
		setEditableItem ("z", m_galaxy.rotation.z, m_zRot);

		m_rot.addChildren ({ &m_xRot, &m_yRot, &m_zRot });

	
		m_galaxyDim.setText(0, "Dimensions");

		setEditableItem ("Diameter", m_galaxy.diameter, m_galaxyDiameter);
		setEditableItem ("Has Center Mass", m_galaxy.hasCenterMass, m_galaxyHasCenterMass);
		setEditableItem ("Center Mass", m_galaxy.centerMass, m_galaxyCenterMass);
		m_galaxyDim.addChildren({&m_galaxyDiameter, &m_galaxyHasCenterMass, &m_galaxyCenterMass});

		m_galaxyStarProperties.setText(0, "Point Mass Properties");

		setEditableItem ("# Point-masses", m_galaxy.numStars, m_galaxyNumStars);
		setEditableItem ("Point-mass mass", m_galaxy.starMass, m_galaxyStarMass);
		m_galaxyStarProperties.addChildren({&m_galaxyNumStars, &m_galaxyStarMass});

		parent->sortItems(0, Qt::AscendingOrder);
	}
	GalaxyTreeWidgetItem::GalaxyTreeWidgetItem (Physics::GalaxyParams galParams, QTreeWidget* parent)
		:m_galaxy(galParams)
	{
		
	}

	GalaxyTreeWidgetItem::~GalaxyTreeWidgetItem()
	{
	}
	
	void GalaxyTreeWidgetItem::contextMenuEvent (QContextMenuEvent* e)
	{
	
	}
	void GalaxyTreeWidgetItem::setEditableItem (const QString& propName, const QVariant& data, QTreeWidgetItem& item)
	{
		item.setText (0, propName);
		item.setData (1, Qt::EditRole, data);
		item.setFlags (flags () | Qt::ItemIsEditable);
	}
}
