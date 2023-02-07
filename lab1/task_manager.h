#pragma once
#include "proccesor.h"

#include <vector>

using namespace std;

class TaskManager
{
public:
    TaskManager(size_t chance);
    void GenerateProcessors();
    void SetProcessors(const vector<size_t>& processors_value);
    void GenerateProcesses();
    void SetProbability(int chance);
    void SetRange(size_t lb, size_t ub);
    int FIFO();
    int ProcessorSchedulerWeak();
    int ProcessorSchedulerStrong(size_t work_time, size_t manage_time);
    void ResetProcessors();
    friend ostream& operator<<(ostream& os, const TaskManager& tm)
    {
        os << "Probability: " << tm._chance << "\n";
        for (size_t i = 0; i < tm.processors.size(); i++)
        {
            cout << "processor " << i << " " << tm.processors[i] << "\n";
        }
        return os;
    }
private:
    const vector<vector<size_t>> processors_combination =
    { {1,2,3,4,5},{2,3,4,5},{1,3,4,5},{1,2,4,5},{1,2,3,5},{1,2,3,4},{1,2,3},
    {1,2,3},{1,2,5},{1,3,4},{1,3,5},{1,4,5},{2,3,4},{2,3,5},
    {2,4,5},{3,4,5},{1,2},{1,3},{1,4},{1,5},{2,3},
    {2,4},{2,5},{3,4},{3,5},{4,5},{1},{2},{3},{4},{5} };
    const size_t processor_count, time;
    vector<Process> processes;
    vector<Processor> processors;
    int pos_worst_processor = 0, pos_best_processor = 0;
    size_t _chance = 50;
    double fifo_efficiency, PSW_efficiency, PSS_efficiency;
    size_t lower_bound, upper_bound;
};