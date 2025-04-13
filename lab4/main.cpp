#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <limits>
#include "BaseProblem.h"
#include "SortByR.h"
#include "SortByQ.h"
#include "Permutations.h"
#include "Schrage.h"
#include "SchrageDiv.h"
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
// gnatowski pwr Cariela


#include <iostream>
#include <vector>
#include "SchrageDiv.h"

#include <iostream>
#include <vector>
#include "SortByRq.h"

int main() {
    const std::string base_path = "/home/lemonx/it/pwr/SPD/lab4/tasks/SCHRAGE";
    const std::string extension = ".DAT";

    for (int i = 1; i <= 9; ++i) {
        std::string filepath = base_path + std::to_string(i) + extension;
        std::cout << "==== INSTANCJA: " << i << " ====" << std::endl;

        try {
            // Wczytaj zadania
            std::vector<Task> tasks = BaseProblem::read_tasks_from_file(filepath);
            int num_tasks = static_cast<int>(tasks.size());

            // Uruchom algorytm Schrage’a
            SchrageDiv problem(tasks);
            problem.start_timer();
            problem.calculate_heuristic();
            int Cmax = problem.get_thsis_Cmax();
            float time = problem.stop_timer();

            // Wypisz wynik
            std::cout << "Liczba zadań: " << num_tasks << std::endl;
            std::cout << "Cmax: " << Cmax << " | Czas działania: " << time << "ms" << std::endl << std::endl;

        } catch (const std::exception &e) {
            std::cerr << "Błąd przy przetwarzaniu pliku " << filepath << ": " << e.what() << std::endl;
        }
    }

    return 0;
}