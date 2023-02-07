#include "proccesor.h"

using namespace std;

Processor::Processor()
	: _operation_per_ms(0)
	, operation_count(0)
	, completed_operation_count(0) {}

Processor::Processor(const size_t& speed)
	: _operation_per_ms(speed)
	, operation_count(0)
	, completed_operation_count(0){}

size_t Processor::GetSpeed() const
{
	return _operation_per_ms;
}

Processor& Processor::operator=(const Processor& other)
{
	this->_operation_per_ms = other.GetSpeed();
	return *this;
}

void Processor::AddOperations(const size_t& operations)
{
	operation_count += operations;
}

bool Processor::Work()
{
	if (operation_count == 0)
	{
		return false;
	}
	if (operation_count <= _operation_per_ms)
	{
		operation_count = 0;
		completed_operation_count += operation_count;
		return true;
	}
	else
	{
		completed_operation_count += _operation_per_ms;
		operation_count -= _operation_per_ms;
		return false;
	}
}

bool Processor::isFree() const
{
	return operation_count == 0;
}

size_t Processor::GetCompletedOperationCount() const
{
	return completed_operation_count;
}

size_t Processor::GetOperationCount() const
{
	return operation_count;
}

void Processor::reset()
{
	operation_count = 0;
	completed_operation_count = 0;
}
