#pragma once

#include "Corepch.h"
#include <QTreeView>
#include <QAction>
#include <QContextMenuEvent>
#include <QMenu>
#include <QStandardItemModel>
#include "GalaxyItem.h"
#include "ui_GravObjView.h"


namespace QUI{
	class GravObjView : public QTreeView, public Ui::GravObjView
	{
		Q_OBJECT
	
	public:
		GravObjView(QWidget *parent = Q_NULLPTR);
		~GravObjView();
	
	protected:
		#ifndef QT_NO_CONTEXTMENU
		void contextMenuEvent (QContextMenuEvent* e) override;
		#endif // !QT_NO_CONTEXTMENU
	private slots:
		void onAddGalaxyAct();
	private: //Start Member Variables
		// Actions
		QAction m_addGalaxyAct;

		//Model
		QStandardItemModel model;
	};
}