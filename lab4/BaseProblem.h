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

class BaseProblem {
public:
    BaseProblem() = default;
    BaseProblem(std::vector<Task> tasks);

    virtual void calculate_heuristic() = 0;

    void print_task_instance();
    int get_cmax();
    std::vector<Task> get_tasks();
    void read_tasks_from_file(const std::string &filename);

protected:
    std::vector<Task> tasks;
};


#endif //BASEPROBLEM_H
