#include "task_manager.h"

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include <string>
#include <functional>

using namespace std;

TaskManager::TaskManager(size_t chance)
    :_chance(chance)
    , processes(time)
    , processors(processor_count)
    , processor_count(5)
    , time(10'000)
    ,lower_bound(10)
    ,upper_bound(200)
{
    GenerateProcessors();
}

void TaskManager::SetProcessors(const vector<size_t>& processors_value)
{
    size_t min_speed = 100, max_speed = 10;
    for (size_t i = 0; i < processors_value.size(); i++)
    {
        if (processors_value[i] > max_speed)
        {
            max_speed = processors_value[i];
            pos_best_processor = i;
        }
        if (processors_value[i] < min_speed)
        {
            min_speed = processors_value[i];
            pos_worst_processor = i;
        }
        processors[i] = Processor(processors_value[i]);
    }
    GenerateProcesses();
}

void TaskManager::SetProbability(int chance)
{
    _chance = chance;
    GenerateProcesses();
}

void TaskManager::SetRange(size_t lb, size_t ub)
{
    lower_bound = lb;
    upper_bound = ub;
    GenerateProcesses();
}

void TaskManager::GenerateProcessors()
{
    size_t min_speed = 100, max_speed = 10;
    for (size_t i = 0; i < processor_count; i++)
    {
        size_t speed = rand() % 91 + 10;
        
        processors[i] = Processor(speed);
    }
    GenerateProcesses();
}

void TaskManager::GenerateProcesses()
{
    if (processors.size() != 0)
    {
        size_t min_operations = processors[pos_worst_processor].GetSpeed() * lower_bound, 
            max_operations = processors[pos_worst_processor].GetSpeed() * upper_bound;
        for (int i = 0; i < 10'000; i++)
        {
            size_t p = rand() % 100 + 1;
            if (p > _chance)
            {
                processes[i] = { 0, {} };
            }
            else
            {
                size_t count_oparations = rand() % (max_operations - min_operations) + min_operations;
                processes[i] = { count_oparations, processors_combination[rand() % 31] };
            }
        }
    }
    else
    {
        throw exception("procesors doesn't exist");
    }
}

int TaskManager::FIFO()
{
    int i = 0, completed_task_count = 0;
    for (int t = 0; t < time; t++)
    {
        if (processes[i].operation_count != 0)
        {
            size_t pr_type = -1;
            for (const size_t& processor_type : processes[i].processors)
            {
                if (processors[processor_type - 1].isFree() &&
                    (pr_type == -1 || processors[pr_type].GetSpeed() < processors[processor_type - 1].GetSpeed()))
                {
                    pr_type = processor_type - 1;
                }
            }
            if (pr_type != -1)
            {
                processors[pr_type].AddOperations(processes[i].operation_count);
                i++;
            }
        }
        else
        {
            i++;
        }
        for (Processor& processor : processors)
        {
            if (processor.Work())
            {
                completed_task_count++;
            }
        }
    }

    size_t numerator = 0, denominator = 0;
    for (const Processor& processor : processors)
    {
        numerator += processor.GetCompletedOperationCount();
        denominator += processor.GetSpeed();
    }
    denominator *= time;
    fifo_efficiency = numerator * 1.0 / denominator;
    cout << "Efficiency: " << fifo_efficiency << "\n"
        << "completed_task: " << completed_task_count << '\n';
    ResetProcessors();
    return completed_task_count;
}


int TaskManager::ProcessorSchedulerWeak()
{
    int i = 0, completed_task_count = 0;
    vector<vector<size_t>>  processes_queue(processor_count);
    
    pos_worst_processor;
    for (int t = 0; t < time; t++)
    {
        if (processes[i].operation_count != 0 && (!(processes[i].processors.size() == 1) || !(processes[i].processors[0] - 1 == pos_worst_processor)))
        {
            double minimum = -1, pos_min = -1;
            for (int k = 0; k < processor_count; k++)
            {
                if (k != pos_worst_processor && 
                    find(processes[i].processors.begin(), processes[i].processors.end(), k+1) != processes[i].processors.end())
                {

                    double time_in_queue_count = (accumulate(processes_queue[k].begin(), processes_queue[k].end(), 0) + 
                        processors[k].GetOperationCount() + processes[i].operation_count) * 1.0 /
                        processors[k].GetSpeed();
                    if (pos_min == -1 || minimum < time_in_queue_count)
                    {
                        pos_min = k;
                        minimum = time_in_queue_count;
                    }
                }
            }
            if (pos_min != -1)
            {
                processes_queue[pos_min].push_back(processes[i].operation_count);
                i++;
            }
        }
        else
        {
            i++;
        }
        for (int k = 0; k < processor_count; k++)
        {
            if (k != pos_worst_processor && processors[k].isFree() && !processes_queue[k].empty())
            {
                processors[k].AddOperations(processes_queue[k].front());
                processes_queue[k].erase(processes_queue[k].begin());
            }
        }
        for (int k = 0; k < processor_count; k++)
        {
            if (k != pos_worst_processor && processors[k].Work())
            {
                completed_task_count++;
            }
        }
    }
    size_t numerator = 0, denominator = 0;
    for (int k = 0; k < processor_count; k++)
    {
        if (k != pos_worst_processor)
        {
            numerator += processors[k].GetCompletedOperationCount();
        }
        denominator += processors[k].GetSpeed();
    }
    denominator *= time;
    PSW_efficiency = numerator * 1.0 / denominator;
    cout << "Efficiency: " << PSW_efficiency << "\n"
        << "completed_task: " << completed_task_count << '\n';
    ResetProcessors();
    return completed_task_count;
}

int TaskManager::ProcessorSchedulerStrong(size_t work_time, size_t manage_time)
{
    bool is_work = false;
    size_t current_time = 0, pos_queue_begin = 0;
    int i = 0, completed_task_count = 0;

    vector<vector<size_t>>  processes_queue(processor_count);
    for (size_t t = 0; t < time; t++)
    {
        if (current_time < manage_time)
        {
            while (i <= t)
            {
                if (processes[i].operation_count != 0)
                {
                    double minimum = -1, pos_min = -1;
                    for (size_t k = 0; k < processor_count; k++)
                    {
                        if (find(processes[i].processors.begin(), processes[i].processors.end(), k + 1) != processes[i].processors.end())
                        {

                            double time_in_queue_count = (accumulate(processes_queue[k].begin(), processes_queue[k].end(), 0) +
                                processors[k].GetOperationCount() + processes[i].operation_count) * 1.0 /
                                processors[k].GetSpeed();
                            if (pos_min == -1 || minimum < time_in_queue_count)
                            {
                                pos_min = k;
                                minimum = time_in_queue_count;
                            }
                        }
                    }
                    processes_queue[pos_min].push_back(processes[i].operation_count);
                }
                i++;
            }
        }
        for (int k = 0; k < processor_count; k++)
        {
            if ((current_time >= manage_time || k != pos_best_processor) && processors[k].isFree() && !processes_queue[k].empty())
            {
                processors[k].AddOperations(processes_queue[k].front());
                processes_queue[k].erase(processes_queue[k].begin());
            }
        }
        for (int k = 0; k < processor_count; k++)
        {
            if ((current_time >= manage_time || k != pos_best_processor) && processors[k].Work())
            {
                completed_task_count++;
            }
        }
        current_time++;
        if (current_time == manage_time + work_time)
        {
            current_time = 0;
        }
    }
    size_t numerator = 0, denominator = 0;
    for (int k = 0; k < processor_count; k++)
    {
        numerator += processors[k].GetCompletedOperationCount();
        denominator += processors[k].GetSpeed();
    }
    denominator *= time;
    PSS_efficiency = numerator * 1.0 / denominator;
    cout <<"Efficiency: " << PSS_efficiency << "\n"
         <<"completed_task: " << completed_task_count << '\n';
    ResetProcessors();
    return completed_task_count;
}

ostream& operator<<(ostream& os, const TaskManager& tm);

void TaskManager::ResetProcessors()
{
    for (auto& processor : processors)
    {
        processor.reset();
    }
}