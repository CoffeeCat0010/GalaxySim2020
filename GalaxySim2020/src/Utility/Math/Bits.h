#pragma once
#include <Corepch.h>

namespace Util
{
	inline bool bitIsSet (uint64_t number, uint32_t bit)
	{
		const static int maxBit = 63;
		if(bit > maxBit) 
			return false;
		return number & (uint64_t)1 << bit;
	}
	
	template< typename int_T>
	inline int_T setBit (uint32_t bitLoc)
	{
		const maxBit = sizeof (int_T) * 8 - 1;
		if(bitLoc > maxBit)
			return 0;
		return (int_T) 1 << bitLoc;
	}
}