#pragma once
#include <iostream>
#include <array>
#include <deque>
#include <stack>
#include<windows.h>


using namespace std;

class Task {
public:

	void clear_info();
	void work(int count);
	void work1(int count);
	void work2(int count);

	void add_tasks(const array<int, 8>& task, int n);
	void add_tasks1(const array<int, 8>& task, int n);
	void add_tasks2(const array<int, 8>& task1, const array<int, 8>& task2, int n);

	void add_task(const array<int, 8>& task);
	void add_task1(const array<int, 8>& task);

	void show_conveyor();
	
private:
		
	array<int, 8> task_info = {0, 1, 2, 1, 2, 0, 0, 1};
	array<int, 8> task2_info = { 0, 1, 0, 1, 0, 1, 1, 1 };
	int milliseconds = 100;
	size_t current_task_stage = 0;
	struct ConveyorInfo {
		size_t work_time = 0;
		double efficiency = 0;
	};
	size_t task_count;
	deque<array<bool, 3>> conv;
	array<ConveyorInfo, 3> conveyor_info;
	stack<array<int, 8>> tasks;
};

