//
// Created by Mateusz Wojtaszek on 31/03/2025.
//

#ifndef SCHRAGE_H
#define SCHRAGE_H
#include "BaseProblem.h"


class Schrage:public BaseProblem {
public:
    explicit Schrage(std::vector<Task> tasks);
    void calculate_heuristic() override;
};



#endif //SCHRAGE_H
