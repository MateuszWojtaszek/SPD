#include "BaseProblem.hpp"
#include <limits>
#include "Processor.hpp"

BaseProblem::BaseProblem(std::vector<Task> tasks, int _maszyny) : tasks(tasks),maszyny(_maszyny) {

  for (size_t i = 0; i < _maszyny; i++)
  {
    Processor processor;
    processor.id = i + 1;
    processors.push_back(processor);
  }
}

void BaseProblem::print_task_instance() {
    std::cout << "Task ID | Processing Time" << std::endl;
    for (const auto &proc : processors) {
        std::cout << proc.to_string() << std::endl;
    }
}

int BaseProblem::get_cmax() {
  int Cmax = 0;
  for (size_t i = 0; i < processors.size(); i++)
  {
    auto cm = processors[i].get_cmax();
    if(cm > Cmax)
    {
      Cmax = processors[i].get_cmax();
    } 
  }
  return Cmax;
}

std::vector<Task> BaseProblem::get_tasks() {
    return tasks;
}
// in txt is R, P and Q
std::vector<Task> BaseProblem::read_tasks_from_file(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    int num_tasks;
    file >> num_tasks;
    std::vector<Task> tasks;
    tasks.reserve(num_tasks);

    for (int i = 0; i < num_tasks; ++i) {
        Task task;
        file >> task.processing_time;
        task.id = i + 1;
        tasks.push_back(task);
    }
    return tasks;
}
std::chrono::time_point<std::chrono::high_resolution_clock> BaseProblem::start_time;

void BaseProblem::start_timer() {
    start_time = std::chrono::high_resolution_clock::now();
}

float BaseProblem::stop_timer() {
    auto end_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
    return duration.count() / 1000.0f; // Convert to mseconds
}