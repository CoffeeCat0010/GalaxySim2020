#pragma once

#include <QAbstractItemModel>

namespace QUI{
	class GravObjItemModel : public QAbstractItemModel
	{
		Q_OBJECT
	
	public:
		GravObjItemModel(QObject *parent);
	};
}