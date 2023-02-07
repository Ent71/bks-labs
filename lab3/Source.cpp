#include <iostream>
#include "conveyor.h"

using namespace std;

int main()
{
	//5, 6
	/*1 0 0 0 0 1 1 0
	  0 1 0 1 0 0 0 1
	  0 0 1 0 1 0 0 0
	  
	  1 0 1 0 1 0 0 0
	  0 1 0 1 0 1 1 1
	  0 0 0 0 0 0 0 0*/

	Task t;
	
	int query;
	int task_count = 10;
	bool is_work = true;
	while (is_work)
	{
		cout << "1. greedy:\n"
			<< "2. not gready\n"
			<< "3. second task\n"
			<< "4. choose task count\n"
			<< "5. exit\n";
		cin >> query;
		string tmp;
		switch (query)
		{
		case 1:
			system("cls"); 
			t.work(task_count);
			cin >> tmp;
			break;
		case 2:
			system("cls");
			t.work1(task_count);
			cin >> tmp;
			break;
		case 3:
			system("cls");
			t.work2(task_count);
			cin >> tmp;
			break;
		case 4:
			system("cls");
			cout << "Enter task count:\n";
			cin >> task_count;
			break;
		case 5:
			is_work = false;
			break;
		}
		system("cls");
	}
	return 0;
}