#pragma once
#include "Corepch.h"
#include <QTreeWidgetItem>

namespace QUI{
	class TreePropertyItem : public QTreeWidgetItem
	{
		Q_OBJECT
	public: //Widget Type IDs
		// This is not an enum to allow for subclassing if necessary
		static const int32_t LineEdit = 1;
		static const int32_t ComboBox = 2;
		static const int32_t SpinnerBox = 3;
		static const int32_t DoubleSpinnerBox = 4;
		
	public:
		explicit TreePropertyItem (QString& name, QVariant& data, QTreeWidgetItem* parent);
		explicit TreePropertyItem (QString& name, QVariant& data, QTreeWidgetItem* parent, 
															 std::function<void()>& onChangedCallback);


		inline void onPropertyChanged() {m_onChangedCallback();}
		//Start Setters
		inline void setOnChangedCallback(std::function<void()> callback) {m_onChangedCallback = callback;}
		//Start Getters
		inline uint32_t getPropertyId() {return m_propertyId;};
	private: // Start Member Variables
		uint32_t m_propertyId;

		uint32_t m_widgetTypeID;

		std::function<void()> m_onChangedCallback;
	};
}
