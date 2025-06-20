#pragma once
#include <string>
#include <vector>

struct Task {
    int id;
    std::vector<int> processing_time;
    // Holds processing times for each machine in the flowshop
    Task(int id = 0, std::vector<int> rt = {}) : id(id), processing_time(rt) {};

    std::string to_string() const {
        std::string result = "Task ID: " + std::to_string(id) + ", Release Times: ";
        for (const auto &time : processing_time) {
            result += std::to_string(time) + " ";
        }
        return result;
    }
};
