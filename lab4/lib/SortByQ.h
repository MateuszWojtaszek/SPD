//
// Created by Mateusz Wojtaszek on 30/03/2025.
//

#ifndef SORTBYQ_H
#define SORTBYQ_H
#include "BaseProblem.h"
class SortByQ : public BaseProblem {
public:
    SortByQ(std::vector<Task> tasks);
    void calculate_heuristic() override;
};

#endif //SORTBYQ_H
