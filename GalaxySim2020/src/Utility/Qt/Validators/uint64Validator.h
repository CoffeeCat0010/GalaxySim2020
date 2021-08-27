#pragma once

#include <QValidator>
namespace Util{
class uint64Validator : public QValidator
	{
		Q_OBJECT
	
	public:
		explicit uint64Validator (QObject* parent = nullptr);
		explicit uint64Validator(quint64 bottom, quint64 top, QObject *parent = nullptr);
		~uint64Validator();
		
		// Start Getters
		inline const quint64 getTop () const { return m_top; }
		inline const quint64 getBottom () const { return m_bottom; }

		// Start Setters
		inline void setTop (quint64 top) { m_top = top; }
		inline void setBottom (quint64 bottom) {m_bottom = bottom;}
		inline void setRange (quint64 bottom, quint64 top) 
			{
				m_bottom = bottom;
				m_top = top;
			}

		//Overrides
		QValidator::State validate(QString &input, int& pos) const override;
	private: //Member Variables
		quint64 m_bottom, m_top;
	};
}