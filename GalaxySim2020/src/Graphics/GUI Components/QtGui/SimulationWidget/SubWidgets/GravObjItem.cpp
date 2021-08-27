#include "GravObjItem.h"
#include <QAbstractItemModel>

namespace QUI{
	void GravObjItem::appendChild (GravObjItem* child)
	{
		m_childItems.push_back(std::make_shared<GravObjItem>(child));
	}

	void GravObjItem::appendChild (std::shared_ptr<GravObjItem> child)
	{
		m_childItems.push_back(child);
	}

	std::shared_ptr<GravObjItem> GravObjItem::child (int32_t row)
	{
		if(row < 0 || row >= m_childItems.size())
			return nullptr;
		else
			return m_childItems.at(row);
	}

	QVariant GravObjItem::data (int32_t column) const
	{
		if( column < 0 || column >= m_itemData.size())
			return QVariant();
		else
			return m_itemData.at(column);
	}

	int32_t GravObjItem::row () const
	{
		if ( !p_parent.expired () )
		{
			std::shared_ptr<GravObjItem> l_parent = p_parent.lock();
			auto it = std::find(l_parent.get()->m_childItems.cbegin(), l_parent.get ()->m_childItems.cend (), this);
			return std::distance(l_parent.get ()->m_childItems.cbegin (), it);
		}
	}

}
