#include "uint64Validator.h"

namespace Util{
	uint64Validator::uint64Validator(QObject *parent)
		:m_bottom(0), m_top(std::numeric_limits<quint64>::max()), QValidator(parent)
	{
		
	}
	uint64Validator::uint64Validator (quint64 bottom, quint64 top, QObject* parent)
		: m_bottom (bottom), m_top (top), QValidator (parent)
	{}
	
	uint64Validator::~uint64Validator()
	{

	}
	QValidator::State uint64Validator::validate (QString & input, int& pos) const
	{
		// Based on code from https://forum.qt.io/topic/115662/qintvalidator-for-unsigned-long-values/3
		bool convertOk = false;
		quint64 inputNum = input.toULongLong(&convertOk);
		if ( !convertOk && !input.isEmpty())
			return QValidator::Invalid;
		if ( inputNum < m_bottom || input.isEmpty ())
			return QValidator::Intermediate;
		if ( inputNum > m_top )
			return QValidator::Invalid;
		else  
			return QValidator::Acceptable;
	}
}
