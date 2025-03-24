#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

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

struct Task {
    int id;
    int processing_time;
    int release_time;
    int cooling_time;

    std::string to_string() const{
        return "Task ID: " + std::to_string(id) + ", Processing Time: " + std::to_string(processing_time) +
               ", Release Time: " + std::to_string(release_time) + ", Cooling Time: " + std::to_string(cooling_time);
    }
};

class ProblemN {
public:
    ProblemN(std::vector<Task> tasks) {
        this->tasks = tasks;
    }

    void generate_test_instance(std::vector<Task> &tasks) {
        for (int i = 0; i < tasks.size(); i++) {
            tasks[i].id = i + 1;
            tasks[i].processing_time = rand() % 10 + 1; // Random processing time between 1 and 10
            tasks[i].release_time = rand() % 5; // Random release time between 0 and 4
            tasks[i].cooling_time = rand() % 5 + 1; // Random cooling time between 1 and 5
        }
    }

    void print_task_instance() {
        std::cout << "Task ID | Processing Time | Release Time | Cooling Time" << std::endl;
        for (int i = 0; i < tasks.size(); i++) {
            std::cout << tasks[i].to_string() << std::endl;
        }
    }

    int calculate_Cmax() {
        int Cmax = 0;
        int current_time = 0;

        for (int i = 0; i < tasks.size(); i++) {
            if (current_time >= tasks[i].release_time) {
                current_time = tasks[i].release_time;
            }
            current_time += tasks[i].processing_time;
            Cmax = std::max(Cmax, current_time + tasks[i].cooling_time);
        }

        return Cmax;
    }

    void generate_permutations(std::vector<std::vector<Task> > &permutations) {
        std::sort(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            return a.id < b.id;
        });

        do {
            permutations.push_back(tasks);
        } while (std::next_permutation(tasks.begin(), tasks.end(), [](const Task &a, const Task &b) {
            return a.id < b.id;
        }));
    }

private
:
    std::vector<Task> tasks;
};
void print_permutations(const std::vector<std::vector<Task>> &permutations) {
    for (const auto &permutation : permutations) {
        for (const auto &task : permutation) {
            std::cout << task.to_string() << " ";
        }
        std::cout << std::endl;
    }
}
void calculate_Cmax_for_permutations(const std::vector<std::vector<Task>> &permutations) {
    int min_Cmax = std::numeric_limits<int>::max();
    std::vector<Task> best_permutation;

    for (const auto &permutation : permutations) {
        ProblemN problem(permutation);
        int Cmax = problem.calculate_Cmax();
        std::cout << "Cmax: " << Cmax << std::endl;
        if (Cmax < min_Cmax) {
            min_Cmax = Cmax;
            best_permutation = permutation;
        }
    }

    std::cout << "Minimum Cmax: " << min_Cmax << std::endl;
    std::cout << "Best permutation:" << std::endl;
    std::cout << "ID | Processing Time | Release Time | Cooling Time" << std::endl;
    for (const auto &task : best_permutation) {
        std::cout << task.id << "  | " << task.processing_time << "              | "
                  << task.release_time << "            | " << task.cooling_time << std::endl;
    }
}
int main() {
    // Task tasks[10];
    std::vector<Task> pregenerated_tasks = {
        {1, 2, 5, 2},
        {2, 5, 2, 7},
        {3, 1, 3, 1},
        {4, 1, 0, 3},
        {5, 2, 6, 1}
    };
    ProblemN problem(pregenerated_tasks);
    std::vector<std::vector<Task>> permutations = {};
    problem.generate_permutations(permutations);
    print_permutations(permutations);
    std::cout << permutations.size()<<std::endl;
    // generate_test_instance(tasks, 10);
    // print_task_instance(tasks, 10);
    // int Cmax = calculate_Cmax(tasks, 10);
    problem.print_task_instance();
    calculate_Cmax_for_permutations(permutations);
    // int Cmax_for_pregenerated = problem.calculate_Cmax();
    //
    // std::cout << "Cmax for pregenerated: " << Cmax_for_pregenerated << std::endl;
    // std::cout << "Cmax: " << Cmax << std::endl;
}
