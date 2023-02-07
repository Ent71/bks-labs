#pragma once

#include <vector>
#include <iostream>

using namespace std;

struct Process
{
	size_t operation_count;
	vector<size_t> processors;
};

class Processor
{
public:
	Processor();
	Processor(const size_t& speed);
	Processor& operator=(const Processor& other);
	size_t GetSpeed() const;
	void AddOperations(const size_t& operations);
	bool Work();
	bool isFree() const;
	size_t GetCompletedOperationCount() const;
	size_t GetOperationCount() const;
	void reset();
	friend ostream& operator<<(ostream& os, const Processor& pr)
	{
		os << "Power: " << pr._operation_per_ms;
		return os;
	}
private:
	size_t _operation_per_ms;
	size_t operation_count;
	size_t completed_operation_count;

};
