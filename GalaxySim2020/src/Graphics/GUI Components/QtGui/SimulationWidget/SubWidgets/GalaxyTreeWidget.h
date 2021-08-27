#pragma once
#include "Corepch.h"
#include <QTreeWidget>
#include <QContextMenuEvent>
#include <QMenu>
#include "ui_GalaxyTreeWidget.h"
#include "GalaxyTreeWidgetItem.h"
#include "GalaxyCreationDialog.h"
#include "Generation/GalaxyParams.h"
namespace QUI{ 
	class GalaxyTreeWidget : public QTreeWidget, public Ui::GalaxyTreeWidget
	{
		Q_OBJECT
	public:
		GalaxyTreeWidget(QWidget *parent = Q_NULLPTR);
		~GalaxyTreeWidget();
		std::vector<Physics::GalaxyParams> getGalaxyParams();
	protected:
		#ifndef QT_NO_CONTEXTMENU
			void contextMenuEvent(QContextMenuEvent* e) override;
		#endif // !QT_NO_CONTEXTMENU
	private slots:
		void onAddGalaxyAction();
		void onDialogAccept();
		void onItemDoubleClicked (QTreeWidgetItem* item, int column);
		void onItemValueChanged (QTreeWidgetItem* item, int column);

	private: // Member Variables
		
		std::vector<GalaxyTreeWidgetItem> m_galaxies;
		// Actions
		QAction m_addGalaxyAct;

	};
}
