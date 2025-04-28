//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#ifndef TASK_H
#define TASK_H
#include <string>

struct Task {
    int id;
    int processing_time;
    Task(int id = 0, int processing_time = 0) : id(id), processing_time(processing_time) {};

    std::string to_string() const {
        return "ID:"+ std::to_string(id) + ", PT:" + std::to_string(processing_time);
    }
};
#endif //TASK_H
