#include "conveyor.h"

using namespace std;

void Task::clear_info()
{
	for (int i = 0; i < conveyor_info.size(); i++)
	{
		conveyor_info[i].work_time = 0;
	}
}
void Task::work(int count)
{
	clear_info();
	int i = 0;
	add_tasks(task_info, count);
	show_conveyor();
	Sleep(milliseconds);
	while (!conv.empty())
	{

		auto& conv_begin = conv.front();
		for (int j = 0; j < 3; j++)
		{
			conveyor_info[j].work_time += static_cast<int>(conv_begin[j]);
		}
		conv.pop_front();
		i++;
		system("cls");
		show_conveyor();
		cout << i << " itteration\n";
		for (int j = 0; j < 3; j++)
		{
			cout << j + 1 << " con: " << conveyor_info[j].work_time << " " << static_cast<double>(conveyor_info[j].work_time) / static_cast<double>(i) << "\n";
		}
		Sleep(milliseconds);
	}
	cout << "successively itterations: " << count * 8 << "\n";
}
void Task::work1(int count)
{
	clear_info();
	int i = 0;
	add_tasks1(task_info, count);
	show_conveyor();
	Sleep(milliseconds);
	while (!conv.empty())
	{

		auto& conv_begin = conv.front();
		for (int j = 0; j < 3; j++)
		{
			conveyor_info[j].work_time += static_cast<int>(conv_begin[j]);
		}
		conv.pop_front();
		i++;
		system("cls");
		show_conveyor();
		cout << i << " itteration\n";
		for (int j = 0; j < 3; j++)
		{
			cout << j + 1 << " con: " << conveyor_info[j].work_time << " " << static_cast<double>(conveyor_info[j].work_time) / static_cast<double>(i) << "\n";
		}
		Sleep(milliseconds);
	}
	cout << "successively itterations: " << count * 8 << "\n";
}
void Task::work2(int count)
{
	clear_info();
	int i = 0;
	add_tasks2(task_info, task2_info, count);
	show_conveyor();
	Sleep(milliseconds);
	while (!conv.empty())
	{

		auto& conv_begin = conv.front();
		for (int j = 0; j < 3; j++)
		{
			conveyor_info[j].work_time += static_cast<int>(conv_begin[j]);
		}
		conv.pop_front();
		i++;
		system("cls");
		show_conveyor();
		cout << i << " itteration\n";
		for (int j = 0; j < 3; j++)
		{
			cout << j + 1 << " con: " << conveyor_info[j].work_time << " " << static_cast<double>(conveyor_info[j].work_time) / static_cast<double>(i) << "\n";
		}
		Sleep(milliseconds);
	}
	cout << "successively itterations: " << count * 8 << "\n";
}

void Task::add_tasks(const array<int, 8>& task, int n)
{
	for (int i = 0; i < n; i++)
	{
		add_task(task);
	}
}
void Task::add_tasks1(const array<int, 8>& task, int n)
{
	add_task(task);
	for (int i = 1; i < n; i++)
	{
		add_task1(task);
	}
}
void Task::add_tasks2(const array<int, 8>& task1, const array<int, 8>& task2, int n)
{
	for (int i = 0; i < n; i++)
	{
		int chance = rand() % 2;
		if (chance == 0)
		{
			add_task(task1);
		}
		else
		{
			add_task(task2);
		}
	}
}
void Task::add_task(const array<int, 8>& task)
{
	bool is_can_insert = false;
	int current_pos = 0;
	int i = 0;
	while (i < 8)
	{
		if (i + current_pos >= conv.size())
		{
			break;
		}
		if (conv[i + current_pos][task[i]])
		{
			i = -1;
			current_pos++;
		}
		i++;
	}

	for (int i = 0; i < 8; i++)
	{
		if (i + current_pos >= conv.size())
		{
			conv.push_back({ false, false, false });
		}
		conv[i + current_pos][task[i]] = true;
	}
}

void Task::add_task1(const array<int, 8>& task)
{
	bool is_can_insert = false;
	int current_pos = 7;
	int i = 0;
	while (i < 8)
	{
		if (i + current_pos >= conv.size())
		{
			break;
		}
		if (conv[i + current_pos][task[i]])
		{
			i = -1;
			current_pos++;
		}
		i++;
	}

	for (int i = 0; i < 8; i++)
	{
		if (i + current_pos >= conv.size())
		{
			conv.push_back({ false, false, false });
		}
		conv[i + current_pos][task[i]] = true;
	}
}

void Task::show_conveyor()
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 30; i++)
		{
			if (i >= conv.size())
			{
				cout << "0 ";
			}
			else
			{
				cout << static_cast<int>(conv[i][j]) << " ";
			}
		}
		cout << "\n";
	}
}