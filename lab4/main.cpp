#include <iostream>
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
};
void generate_test_instance(Task tasks[], int n) {
    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        tasks[i].processing_time = rand() % 10 + 1; // Random processing time between 1 and 10
        tasks[i].release_time = rand() % 5; // Random release time between 0 and 4
        tasks[i].cooling_time = rand() % 5 + 1; // Random cooling time between 1 and 5
    }
}
void print_task_instance(Task tasks[], int n) {
    std::cout << "Task ID | Processing Time | Release Time | Cooling Time" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << tasks[i].id << "       | " << tasks[i].processing_time << "              | "
                  << tasks[i].release_time << "            | " << tasks[i].cooling_time << std::endl;
    }
}
int calculate_Cmax(Task tasks[], int n) {
    int Cmax = 0;
    int current_time = 0;

    for (int i = 0; i < n; i++) {
        if (current_time < tasks[i].release_time) {
            current_time = tasks[i].release_time;
        }
        current_time += tasks[i].processing_time;
        Cmax = std::max(Cmax, current_time + tasks[i].cooling_time);
    }

    return Cmax;
}



int main() {
    Task tasks[10];
    Task pregenerated_tasks[5] = {
        {1, 2, 5, 2},
        {2, 5, 2, 7},
        {3, 1, 3, 1},
        {4, 1, 0, 3},
        {5, 2, 6, 1}
    };
    // generate_test_instance(tasks, 10);
    // print_task_instance(tasks, 10);
    // int Cmax = calculate_Cmax(tasks, 10);
    print_task_instance(pregenerated_tasks, 5);
    int Cmax_for_pregenerated = calculate_Cmax(pregenerated_tasks, 5);
    std::cout << "Cmax for pregenerated: "<<Cmax_for_pregenerated << std::endl;
    // std::cout << "Cmax: " << Cmax << std::endl;
}