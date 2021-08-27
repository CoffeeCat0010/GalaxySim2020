#include "TreePropertyItem.h"

namespace QUI
{
	TreePropertyItem::TreePropertyItem (QString& name, QVariant& data, uint32_t propertyId, QTreeWidgetItem* parent)
		:QTreeWidgetItem(parent), m_propertyId(propertyId)
	{
		setText (0, name);
		setData (1, Qt::EditRole, data);
		setFlags (flags () | Qt::ItemIsEditable);
	}
}

