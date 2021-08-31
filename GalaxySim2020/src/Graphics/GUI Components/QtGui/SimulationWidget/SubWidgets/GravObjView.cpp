#include "GravObjView.h"
namespace QUI
{
	GravObjView::GravObjView(QWidget *parent)
		: QTreeView(parent), m_addGalaxyAct ("Add Galaxy")
	{
		setupUi(this);
		this->setModel(&model);
		model.insertColumns(0, 2);
		connect (&m_addGalaxyAct, &QAction::triggered, this, &GravObjView::onAddGalaxyAct);
	}
	
	GravObjView::~GravObjView()
	{
	}
	void GravObjView::contextMenuEvent (QContextMenuEvent* e)
	{
		QMenu contextMenu (this);
		contextMenu.addAction (&m_addGalaxyAct);
		contextMenu.exec (e->globalPos ());
	}
	void GravObjView::onAddGalaxyAct ()
	{
		GalaxyItem* test = new GalaxyItem ("default", Physics::GalaxyParams (), this);
		model.insertRow(0, test);
	}
}