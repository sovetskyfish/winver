#pragma once
#include <stdexcept>
#include <Windows.h>

class RegistryError
	: public std::runtime_error
{
public:
	RegistryError(const char* message, LONG errorCode);
	LONG ErrorCode() const noexcept;
private:
	LONG m_errorCode;
};

