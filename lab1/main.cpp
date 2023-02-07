#include "proccesor.h"
#include "task_manager.h"

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <memory>

using namespace std;

void menu_inter() {
    cout << "1. Task-1 (FIFO)" << '\n';
    cout << "2. Task-2 (the weakest unit as scheduler)" << '\n';
    cout << "3. Task-3 (the strongest unit as scheduler)" << '\n';
    cout << "4. Set the probality" << '\n';
    cout << "5. Set the range of task difficulty" << '\n';
    cout << "6. Set units power" << '\n';
    cout << "7. Print Units power" << '\n';
    cout << "8. Exit" << '\n';
}

int main()
{
    TaskManager manager(70);
    bool is_exit = false;
    size_t probability = 70, lower_bound = 10, upper_bound = 200;
    vector<size_t> values(5);
    while (!is_exit) {
        system("cls");
        menu_inter();
        int request;
        cin >> request;
        switch (request) {
        case 1:
            system("cls");
            cout << "FIFO:\n";
            manager.FIFO();
            system("pause");
            break;
        case 2:
            system("cls");
            cout << "Weak Scheduler:\n";
            manager.ProcessorSchedulerWeak();
            system("pause");
            break;
        case 3:
            system("cls");
            cout << "Strong Scheduler::\n";
            int work_time, schedule_time;
            cout << "Set work time: ";
            cin >> work_time;
            cout << "Set schedule time: ";
            cin >> schedule_time;
            manager.ProcessorSchedulerStrong(work_time, schedule_time);
            system("pause");
            break;
        case 4:
            system("cls");
            cout << "Set probability: ";
            cin >> probability;
            manager.SetProbability(probability);
            break;
        case 5:
            system("cls");
            cout << "Lower bound: ";
            cin >> lower_bound;
            cout << "Upper bound: ";
            cin >> upper_bound;
            manager.SetRange(lower_bound, upper_bound);
            break;
        case 6:
            system("cls");
            
            for (size_t& v : values) {
                cout << "Enter unit power: ";
                cin >> v;
            }
            manager.SetProcessors(values);
            break;
        case 7:
            system("cls");
            cout << manager;
            system("pause");
            break;
        case 8:
            is_exit = true;
            break;
        }
    }
}

