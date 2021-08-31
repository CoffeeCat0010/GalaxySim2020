#pragma once

#include "Corepch.h"
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QTextEdit>
#include <QStandardItem>
#include <QVariant>

namespace QUI{
	template<class Widget>
	class GravObjItem :public QStandardItem
	{};

	template<>
	class GravObjItem<void> :public QStandardItem
	{
	public:
		const static enum NodeType { Internal, Leaf };
		const static enum EditorType { None, ComboBox, DoubleSpinBox, SpinBox, TextEdit };

		GravObjItem (const QIcon &icon, const QString& text)
			:QStandardItem (icon, text), m_eType (None) {}
		GravObjItem (const QString& text)
			:QStandardItem(text), m_eType (None){}

		int type() { return 1100; }

	private: // Start Member Variables
		NodeType m_nType;
		EditorType m_eType;
	};

	template<>
	class GravObjItem<QComboBox> :public QStandardItem
	{
	public:
		const static enum NodeType { Internal, Leaf };
		const static enum EditorType { None, ComboBox, DoubleSpinBox, SpinBox, TextEdit };

		GravObjItem (const QIcon& icon, const QString& text, QComboBox* editor )
			:QStandardItem (icon, text), m_eType (ComboBox), m_editorDelegate (editor)
		{}
		GravObjItem (const QString& text, QComboBox* editor)
			:QStandardItem (text), m_eType (ComboBox), m_editorDelegate(editor)
		{}
		int type () { return 1101; }

	private: // Start Member Variables
		NodeType m_nType;
		EditorType m_eType;
		QComboBox* m_editorDelegate;
	};

	template<>
	class GravObjItem<QSpinBox> :public QStandardItem
	{
	public:
		const static enum NodeType { Internal, Leaf };
		const static enum EditorType { None, ComboBox, DoubleSpinBox, SpinBox, TextEdit };

		GravObjItem (const QIcon& icon, const QString& text, QSpinBox* editor)
			:QStandardItem (icon, text), m_eType (SpinBox), m_editorDelegate (editor)
		{}
		GravObjItem (const QString& text, QSpinBox* editor)
			:QStandardItem (text), m_eType (SpinBox), m_editorDelegate (editor)
		{}
		int type () { return 1102; }

	private: // Start Member Variables
		NodeType m_nType;
		EditorType m_eType;
		QSpinBox* m_editorDelegate;
	};

	template<>
	class GravObjItem<QDoubleSpinBox> :public QStandardItem
	{
	public:
		const static enum NodeType { Internal, Leaf };
		const static enum EditorType { None, ComboBox, DoubleSpinBox, SpinBox, TextEdit };

		GravObjItem (const QIcon& icon, const QString& text, QDoubleSpinBox* editor)
			:QStandardItem (icon, text), m_eType (DoubleSpinBox), m_editorDelegate (editor)
		{}
		GravObjItem (const QString& text, QDoubleSpinBox* editor)
			:QStandardItem (text), m_eType (DoubleSpinBox), m_editorDelegate (editor)
		{}
		int type () override { return 1103; }

	private: // Start Member Variables
		NodeType m_nType;
		EditorType m_eType;
		QDoubleSpinBox* m_editorDelegate;
	};

	template<>
	class GravObjItem<QTextEdit> :public QStandardItem
	{
	public:
		const static enum NodeType { Internal, Leaf };
		const static enum EditorType { None, ComboBox, DoubleSpinBox, SpinBox, TextEdit };

		GravObjItem (const QIcon& icon, const QString& text, QTextEdit* editor)
			:QStandardItem (icon, text), m_eType (TextEdit), m_editorDelegate (editor)
		{}
		GravObjItem (const QString& text, QTextEdit* editor)
			:QStandardItem (text), m_eType (DoubleSpinBox), m_editorDelegate (editor)
		{}
		int type () override { return 1104; }

	private: // Start Member Variables
		NodeType m_nType;
		EditorType m_eType;
		QTextEdit* m_editorDelegate;
	};
}

