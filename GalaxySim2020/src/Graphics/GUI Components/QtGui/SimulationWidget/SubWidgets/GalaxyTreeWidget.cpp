#include "GalaxyTreeWidget.h"
namespace QUI{
	GalaxyTreeWidget::GalaxyTreeWidget(QWidget *parent)
		: QTreeWidget(parent), m_addGalaxyAct("Add Galaxy")
	{
		setupUi(this);
		connect(&m_addGalaxyAct,&QAction::triggered, this, &GalaxyTreeWidget::onAddGalaxyAction);
		connect(this, &GalaxyTreeWidget::itemDoubleClicked, this, &GalaxyTreeWidget::onItemDoubleClicked);
	}
	
	GalaxyTreeWidget::~GalaxyTreeWidget()
	{
	}

	std::vector<Physics::GalaxyParams> GalaxyTreeWidget::getGalaxyParams ()
	{
		return std::vector<Physics::GalaxyParams> ();
	}
	
	void GalaxyTreeWidget::contextMenuEvent (QContextMenuEvent* e)
	{
		QMenu contextMenu(this);
		contextMenu.addAction(&m_addGalaxyAct);
		contextMenu.exec(e->globalPos());
	}

	void GalaxyTreeWidget::onAddGalaxyAction ()
	{
		GalaxyCreationDialog dialog(this);
		dialog.setModal(true);
		connect(&dialog, &QDialog::accepted, this, &GalaxyTreeWidget::onDialogAccept);
		dialog.exec();
	}
	void GalaxyTreeWidget::onDialogAccept ()
	{
		GalaxyCreationDialog* dialog = qobject_cast<GalaxyCreationDialog*>(sender());
		this->addTopLevelItem(new GalaxyTreeWidgetItem("default", dialog->getGalaxyParams(), this));
		dialog->hide();
		dialog->close();
	}

	void GalaxyTreeWidget::onItemDoubleClicked (QTreeWidgetItem* item, int column)
	{
		if ( item->flags ().testFlag (Qt::ItemIsEditable) )
			this->editItem(item, 1);
	}
	void GalaxyTreeWidget::onItemValueChanged (QTreeWidgetItem* item, int column)
	{}
}