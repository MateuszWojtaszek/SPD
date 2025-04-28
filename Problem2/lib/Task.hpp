//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#ifndef TASK_H
#define TASK_H
#include <string>

struct Task {
    int id;
    int processing_time;

    std::string to_string() const {
        return "Task ID: " + std::to_string(id) + ", Processing Time: " + std::to_string(processing_time);
    }
};
#endif //TASK_H
