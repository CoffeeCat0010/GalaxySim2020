#pragma once
#include "Corepch.h"
#include <QStandardItem>
#include <QList>

namespace QUI{
	class PropertyItem
	{
	public:
		const static enum EditorType {None, LineEdit, ComboBox, SpinBox, DoubleSpinBox };
		const static enum EditorSettingRole {LineEditMaxLength = Qt::UserRole + 1, LineEditValidator = Qt::UserRole + 2,
																				 ComboxBoxItems = Qt::UserRole + 3, SpinBoxMin = Qt::UserRole + 4, 
																				 SpinBoxMax = Qt::UserRole + 5, SpinBoxStepSize = Qt::UserRole + 6, 
																				 SpinBoxSuffix = Qt::UserRole + 7};
		explicit PropertyItem(const QString& name, const QVariant& value, EditorType type);

		//Setters
		void setEditorSettings(EditorSettingRole role, const QVariant& setting);
		//Getters
		inline QList<QStandardItem*> getColumns() const {return m_columns;}
		inline QString getName() const {return m_name;}
		inline QVariant getValue() const {return m_value;}
		inline EditorType getEditorType() const {return m_editorType; }
	private: // Member Variables
		QList<QStandardItem*> m_columns;
		QString m_name;
		QVariant m_value;
		EditorType m_editorType;
	};
}

