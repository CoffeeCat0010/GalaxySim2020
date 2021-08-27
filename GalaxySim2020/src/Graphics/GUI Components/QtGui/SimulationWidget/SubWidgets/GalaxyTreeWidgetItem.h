#pragma once
#include "Corepch.h"
#include <QObject>
#include <QTreeWidgetItem>
#include <QContextMenuEvent>
#include "Generation/GalaxyParams.h"
namespace QUI{
	class GalaxyTreeWidgetItem : public QObject, public QTreeWidgetItem
	{
		Q_OBJECT
	public:
		GalaxyTreeWidgetItem (const QString& text, Physics::GalaxyParams galParams, QTreeWidget* parent );
		GalaxyTreeWidgetItem (Physics::GalaxyParams galParams, QTreeWidget* parent );
		~GalaxyTreeWidgetItem();

		#ifndef QT_NO_CONTEXTMENU
			void contextMenuEvent(QContextMenuEvent* e);
		#endif // !QT_NO_CONTEXTMENU

		//start getters		
		inline const Physics::GalaxyParams getGalaxyParams() const { return m_galaxy;}

	private:
		void setEditableItem(const QString & propName, const QVariant& data, QTreeWidgetItem& item);
	private:

		const static int GalaxyTreeItemType = 1001;
		Physics::GalaxyParams m_galaxy;

		QTreeWidgetItem m_pos;
		//start m_pos sub-items
			QTreeWidgetItem m_xPos;
			QTreeWidgetItem m_yPos;
			QTreeWidgetItem m_zPos;
		//end m_pos sub-items

		QTreeWidgetItem m_rot;
		//Start m_rot sub-items
			QTreeWidgetItem m_xRot;
			QTreeWidgetItem m_yRot;
			QTreeWidgetItem m_zRot;
		//end m_rot sub-items
		
		QTreeWidgetItem m_galaxyDim;
		//Start m_galaxyDim sub-items
			QTreeWidgetItem m_galaxyDiameter;
			QTreeWidgetItem m_galaxyHasCenterMass;
			QTreeWidgetItem m_galaxyCenterMass;
		//end m_galaxyDim sub-items
			QTreeWidgetItem m_galaxyStarProperties;
		//Start m_galaxyStarProperties sub_items
			QTreeWidgetItem m_galaxyNumStars;
			QTreeWidgetItem m_galaxyStarMass;
		//end m_galaxyStarProperties sub_items

		
	};
}
