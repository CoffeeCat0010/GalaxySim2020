#include "GalaxyItem.h"
#include <QTreeView>
#include <QStyledItemDelegate>

namespace QUI{
	GalaxyItem::GalaxyItem (const QString& name, Physics::GalaxyParams galParams, QAbstractItemView* view)
		:QStandardItem ("Galaxy"), m_galaxy (galParams), m_name(name), p_view(view)
	{
		
		//parent->setSortingEnabled(true);
		this->setData("default", Qt::EditRole);
		this->setChild(0, &m_pos);
		this->setChild(1, &m_rot);
		this->setChild(2, &m_galaxyDim);
		this->setChild(3, &m_galaxyStarProperties);

		m_pos.setText  ("Position");
		m_pos.setEditable (false);

		setEditableItem ("x", m_galaxy.pos.x, m_pos);
		setEditableItem ("y", m_galaxy.pos.y, m_pos);
		setEditableItem ("z", m_galaxy.pos.z, m_pos);
		
		//m_pos.setChild (0, &m_xPos);
		//m_pos.setChild (1, &m_yPos);
		//m_pos.setChild (2, &m_zPos);

		m_rot.setText ("Rotation");
		m_rot.setEditable (false);

		setEditableItem ("x", m_galaxy.rotation.x, m_rot);
		setEditableItem ("y", m_galaxy.rotation.y, m_rot);
		setEditableItem ("z", m_galaxy.rotation.z, m_rot);

		//m_rot.setChild (0, &m_xRot);
		//m_rot.setChild (1, &m_yRot);
		//m_rot.setChild (2, &m_zRot);

	
		m_galaxyDim.setText("Dimensions");
		m_galaxyDim.setEditable (false);

		setEditableItem ("Diameter", m_galaxy.diameter, m_galaxyDim);
		setEditableItem ("Has Center Mass", m_galaxy.hasCenterMass, m_galaxyDim);
		setEditableItem ("Center Mass", m_galaxy.centerMass, m_galaxyDim);
		//m_galaxyDim.setChild (0, &m_galaxyDiameter);
		//m_galaxyDim.setChild (1, &m_galaxyHasCenterMass);
		//m_galaxyDim.setChild (2, &m_galaxyCenterMass);

		m_galaxyStarProperties.setText("Point Mass Properties");
		m_galaxyStarProperties.setEditable(false);
		setEditableItem ("# Point-masses", m_galaxy.numStars, m_galaxyStarProperties);
		setEditableItem ("Point-mass mass", m_galaxy.starMass, m_galaxyStarProperties);
		//m_galaxyStarProperties.setChild (0, &m_galaxyNumStars);
		//m_galaxyStarProperties.setChild (1, &m_galaxyStarMass);

	}
	GalaxyItem::GalaxyItem (Physics::GalaxyParams galParams, QStandardItem* parent)
		:m_galaxy(galParams)
	{
		
	}

	GalaxyItem::~GalaxyItem()
	{
	}

	GalaxyItem* GalaxyItem::clone () const
	{
		return new GalaxyItem(m_name, m_galaxy, p_view);
	}
	
	void GalaxyItem::setEditableItem (const QString& propName, const QVariant& data, QStandardItem& parent)
	{
		QStandardItem* name = new QStandardItem (propName);
		QStandardItem* value = new QStandardItem();
		value->setData(data, Qt::EditRole);
		name->setEditable(false);

		QStandardItemModel* model = parent.model();

		QList<QStandardItem*> columns;
		columns << name << value;
		parent.appendRow(columns);
	}
}
