//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#ifndef SORTBYR_H
#define SORTBYR_H
#include "BaseProblem.h"

class SortByR : public BaseProblem {
public:
    SortByR(std::vector<Task> tasks);
    void calculate_heuristic() override;
};
#endif //SORTBYR_H
