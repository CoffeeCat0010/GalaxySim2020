#pragma once
#include <Corepch.h>

namespace Util
{
	/// <summary>
	/// Checks if the bit at location bitLoc in field is set. The value range for bitLoc is 0-63. If it is higher, then the function will always evaluate false. 
	/// </summary>
	/// <param name="field">The bit field being checked</param>
	/// <param name="bitLoc">The location of the bit being search. Valid values are 0-63.</param>
	/// <returns> True if input field has a bit set at the location given by bitLoc. False otherwise. </returns>
	inline bool bitIsSet (uint64_t field, uint32_t bitLoc)
	{
		const static int maxBit = 63;
		if(bitLoc > maxBit) 
			return false;
		return field & (uint64_t)1 << bitLoc;
	}
	/// <summary>
	/// Returns an int of type int_T with the appropriate bit set. If the bit is not within the range of int_T zero is returned.
	/// </summary>
	/// <typeparam name="int_T">the type of integer requested to be returned. i.e uint32_t, uint64_t, etc.</typeparam>
	/// <param name="bitLoc">the location of the bit being set</param>
	/// <returns>Returns an int of type int_T with the appropriate bit set. If bitLoc is out of range then zero is returned. </returns>
	template< typename int_T>
	inline int_T setBit (uint32_t bitLoc)
	{
		const maxBit = sizeof (int_T) * 8 - 1;
		if(bitLoc > maxBit)
			return 0;
		return (int_T) 1 << bitLoc;
	}
}