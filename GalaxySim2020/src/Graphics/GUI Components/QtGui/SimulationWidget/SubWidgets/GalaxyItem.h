#pragma once
#include "Corepch.h"
#include <QObject>
#include <QStandardItem>
#include <QContextMenuEvent>
#include <QAbstractItemView>
#include "Generation/GalaxyParams.h"
namespace QUI{
	class GalaxyItem : public QStandardItem
	{
	public:
		GalaxyItem (const QString& text, Physics::GalaxyParams galParams, QAbstractItemView* view);
		GalaxyItem (Physics::GalaxyParams galParams, QStandardItem* parent );
		~GalaxyItem();

		virtual GalaxyItem* clone() const override;

		//start getters		
		inline const Physics::GalaxyParams getGalaxyParams() const { return m_galaxy;}

	private:
		void setEditableItem(const QString & propName, const QVariant& data, QStandardItem& item);
	private:

		const static int GalaxyTreeItemType = 1001;
		Physics::GalaxyParams m_galaxy;
		QString m_name;
		QAbstractItemView* p_view;

		QStandardItem m_pos;
		//start m_pos sub-items
			QStandardItem m_xPos;
			QStandardItem m_yPos;
			QStandardItem m_zPos;
		//end m_pos sub-items

		QStandardItem m_rot;
		//Start m_rot sub-items
			QStandardItem m_xRot;
			QStandardItem m_yRot;
			QStandardItem m_zRot;
		//end m_rot sub-items
		
		QStandardItem m_galaxyDim;
		//Start m_galaxyDim sub-items
			QStandardItem m_galaxyDiameter;
			QStandardItem m_galaxyHasCenterMass;
			QStandardItem m_galaxyCenterMass;
		//end m_galaxyDim sub-items
			QStandardItem m_galaxyStarProperties;
		//Start m_galaxyStarProperties sub_items
			QStandardItem m_galaxyNumStars;
			QStandardItem m_galaxyStarMass;
		//end m_galaxyStarProperties sub_items

		
	};
}
