#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include "BaseProblem.h"
#include "SortByR.h"
#include "SortByQ.h"
#include "Permutations.h"

/*************************************************************************
 * n zadań J = {1, 2, 3, 4, 5...n}
 * 1 procesor
 * Pj - czas wykonywania zadania j
 * Rj - termin dostępności zadania j
 * Qj - czas stygnięcia zadania j
 * Cmax - długość szeregowania
 * np:
 * j|Pj|Rj|Qj
 * 1|2 |1 |2
 * 2|5 |2 |7
 * 3|1 |3 |1
 * 4|3 |0 |3
 * 5|2 |6 |2
 * pi = 4,1,3,2,5
 * Czas stygnięcia nie blokuje procesora (wyjmujesz ciasto z piekarnika to piekarnik wolny)
 * Cmax(pi) = 16
 * Cel: zminimalizować Cmax
 * Zadania:
 * 1) wygenreować instancje testową 5 elementową
 * 2) funckje liczącą kryterium
 * 3) sprawdzić działanie na instancji
 * 4) wygenerowanie permuitacji w pożadku lexograficznym dla instancji
 * 5) dla każdej wyliczyć funckje celu i sprawdzić
 * 6) Wczytać instancje testowe z Eportalu, policzyć błąd względny
 **********************************************************************/

int main() {
    std::vector<Task> pregenerated_tasks = {
        {1, 2, 5, 2},
        {2, 5, 2, 7},
        {3, 1, 3, 1},
        {4, 1, 0, 3},
        {5, 2, 6, 1}
    };

    std::vector<Task> tasks = BaseProblem::read_tasks_from_file("/Users/mateuszwojtaszek/CLionProjects/SPD/SPD/lab4/tasks/six.txt");
    //tasks = pregenerated_tasks;
    SortByR problemR(tasks);
    problemR.calculate_heuristic();
    int cmax_for_problemR = problemR.get_cmax();
    // for (const auto &task : tasks) {
    //     std::cout << task.to_string() << std::endl;
    // }
    problemR.print_task_instance();
    std::cout << "Cmax for ProblemR: " << cmax_for_problemR << std::endl;

    std::vector<std::vector<Task>> permutations;
    Permutations perm_problem(tasks);
    BaseProblem::start_timer();
    perm_problem.generate_permutations();
    //perm_problem.print_permutations(permutations);
    std::cout << permutations.size() << std::endl;
    long long elapsed_time = BaseProblem::stop_timer();
    std::cout << "Elapsed time: " << elapsed_time << " ms" << std::endl;


    return 0;
}