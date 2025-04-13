//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#ifndef BASEPROBLEM_H
#define BASEPROBLEM_H
#include "Task.h"
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>
class BaseProblem {
public:
    BaseProblem() = default;
    BaseProblem(std::vector<Task> tasks);

    virtual void calculate_heuristic() = 0;

    void print_task_instance();
    int get_cmax();
    std::vector<Task> get_tasks();
    static std::vector<Task> read_tasks_from_file(const std::string &filename);
    static void start_timer();
    static float stop_timer();
protected:
    std::vector<Task> tasks;
    static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

};


#endif //BASEPROBLEM_H
