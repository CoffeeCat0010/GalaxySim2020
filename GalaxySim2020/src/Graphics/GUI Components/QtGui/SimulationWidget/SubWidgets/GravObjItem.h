#pragma once

#include "Corepch.h"
#include <QVariant>

namespace QUI{
	class GravObjItem
	{
		const static enum NodeType {Internal, Leaf};
		explicit GravObjItem(const std::vector<QVariant>& data, std::weak_ptr<GravObjItem> parent)
		:m_itemData(data), p_parent(parent){};

		void appendChild (GravObjItem* child);
		void appendChild (std::shared_ptr<GravObjItem> child);
		
		std::shared_ptr<GravObjItem> child(int32_t row);
		inline int32_t childCount() const { return m_childItems.size();}
		inline int32_t columnCount() const {return m_itemData.size(); }
		QVariant data(int32_t column) const;
		int32_t row() const;

		inline std::weak_ptr<GravObjItem> parentItem() {return p_parent;}

	private: // Start Member Variables
		std::vector<std::shared_ptr<GravObjItem>> m_childItems;
		std::vector<QVariant> m_itemData;

		//NodeType m_nodeType;

		std::weak_ptr<GravObjItem> p_parent;
	};
}

