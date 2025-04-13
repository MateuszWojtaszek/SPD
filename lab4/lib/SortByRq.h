//
// Created by Mateusz Wojtaszek on 13/04/2025.
//

#ifndef SORTBYRQ_H
#define SORTBYRQ_H
#include "BaseProblem.h"

class SortByRq : public BaseProblem {
public:
    explicit SortByRq(std::vector<Task> tasks);
    void calculate_heuristic() override;
};

#endif // SORTBYRQ_H