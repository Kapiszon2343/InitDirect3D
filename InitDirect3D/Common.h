#pragma once

#include <windows.h>
#include <stdexcept>

void ThrowIfFailed(HRESULT result)
{
	if (result != S_OK)
	{
		throw std::runtime_error("failed");
	}
}