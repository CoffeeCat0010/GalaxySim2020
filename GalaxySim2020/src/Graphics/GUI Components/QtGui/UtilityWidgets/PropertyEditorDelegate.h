#pragma once

#include <QItemDelegate>

/* Slightly modified version of editor delegate solution found here 
* https://stackoverflow.com/questions/2801959/making-only-one-column-of-a-qtreewidgetitem-editable
* by user336063
*/
namespace Graphics{
	class PropertyEditorDelegate : public QItemDelegate
	{
		Q_OBJECT
	
	public:
		PropertyEditorDelegate(QObject *parent, int editableColumn = 1);
		QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex &index);
	private: 
		int m_editableColumn;
	};
}
