#pragma once

#include "Task.hpp"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <chrono>

class BaseProblem {
  public:
    BaseProblem() = default;
    BaseProblem(std::vector<Task> tasks, int maszyny);

    virtual void calculate_heuristic() = 0;

    void print_task_instance();
    int get_cmax();
    std::vector<Task> get_tasks();
    static std::vector<Task> read_tasks_from_file(const std::string &filename);
    static void start_timer();
    static float stop_timer();

    // std::vector<Processor> get_processors() {
    //     return processors;
    // }
  protected:
    std::vector<Task> tasks;
    // std::vector<Processor> processors;
    int maszyny;
    static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;

    int cmax_calcualate(const std::vector<Task> &dp);
  };