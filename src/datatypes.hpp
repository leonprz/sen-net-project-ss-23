#pragma once
#ifndef DATATYPES_HPP
#define DATATYPES_HPP

#include <stdint.h>

struct uint24
{
	uint32_t data : 24;

	uint24(uint32_t i)
	{
		data = i & 0xFFFFFF;
	}

	operator uint32_t()
	{
		return data;
	}
};

#endif // DATATYPES_HPP
