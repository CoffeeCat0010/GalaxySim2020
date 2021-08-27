#include "PropertyEditorDelegate.h"

namespace Graphics{
	PropertyEditorDelegate::PropertyEditorDelegate(QObject *parent, int editablecolumn)
		: QItemDelegate(parent), m_editableColumn(editablecolumn)
	{
	}
	
	QWidget* Graphics::PropertyEditorDelegate::createEditor (QWidget* parent, const QStyleOptionViewItem& option, const QModelIndex& index)
	{
		if(index.column() == m_editableColumn && (index.flags() & Qt::ItemIsEditable))
			return QItemDelegate::createEditor(parent, option, index);
		return nullptr;
	}
}
