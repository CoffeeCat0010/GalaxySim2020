#include "GravObjView.h"
namespace QUI
{
	GravObjView::GravObjView(QWidget *parent)
		: QTreeView(parent), m_addGalaxyAct ("Add Galaxy")
	{
		setupUi(this);
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
}