#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <numeric>
#include <cmath>
#include <iomanip> // Potrzebne do formatowania tabeli

#include "BaseProblem.hpp"
#include "Task.hpp"
#include "Zupelny.hpp"
#include "BandB.hpp"
#include "NEH.hpp" // B&B używa NEH do inicjalizacji

int main() {
    // Ustaw ścieżkę do nowego pliku testowego
    const std::string data_filepath = "/Users/mateuszwojtaszek/CLionProjects/SPD/SPD/Problem3/zupelny_vs_bandb_tests.dat";

    std::ifstream data_file(data_filepath);
    if (!data_file.is_open()) {
        std::cerr << "Błąd: Nie można otworzyć pliku " << data_filepath << std::endl;
        return 1;
    }

    int num_instances;
    data_file >> num_instances;

    // --- Nagłówek Tabeli Wyników ---
    std::cout << "Porównanie algorytmów dokładnych: Przegląd Zupełny vs. Branch and Bound" << std::endl;
    std::cout << std::string(100, '-') << std::endl;
    std::cout << std::left
              << std::setw(12) << "Instancja"
              << std::setw(4)  << "n"
              << std::setw(4)  << "m"
              << std::setw(15) << "Cmax (Zup.)"
              << std::setw(15) << "Czas_Z [ms]"
              << std::setw(15) << "Cmax (B&B)"
              << std::setw(15) << "Czas_B&B [ms]"
              << std::setw(12) << "Błąd abs."
              << std::setw(12) << "Błąd [%]" << std::endl;
    std::cout << std::string(100, '-') << std::endl;

    for (int i = 0; i < num_instances; ++i) {
        int n, m;
        data_file >> n >> m;

        // Wczytywanie zadań z pliku
        std::vector<Task> tasks;
        for (int j = 0; j < n; ++j) {
            std::vector<int> processing_times;
            int machine_idx, processing_time;
            for (int k = 0; k < m; ++k) {
                data_file >> machine_idx >> processing_time;
                processing_times.push_back(processing_time);
            }
            tasks.push_back(Task(j + 1, processing_times));
        }

        // Tworzymy osobne kopie zadań dla każdego algorytmu, aby zapewnić te same warunki startowe
        std::vector<Task> tasks_for_zupelny = tasks;
        std::vector<Task> tasks_for_bandb = tasks;

        // --- Uruchomienie Przeglądu Zupełnego (jako wzorzec optimum) ---
        Zupelny problem_zupelny(tasks_for_zupelny, m);
        problem_zupelny.start_timer();
        problem_zupelny.calculate_heuristic();
        auto time_zupelny = problem_zupelny.stop_timer();
        int optimal_cmax = problem_zupelny.get_cmax(); // Ten wynik to nasze 100% optimum

        // --- Uruchomienie Branch and Bound ---
        BandB problem_bandb(tasks_for_bandb, m);
        problem_bandb.start_timer();
        problem_bandb.calculate_heuristic();
        auto time_bandb = problem_bandb.stop_timer();
        int bandb_cmax = problem_bandb.get_cmax();

        // --- Obliczenie błędów B&B względem Przeglądu Zupełnego ---
        int absolute_error = std::abs(bandb_cmax - optimal_cmax);
        float relative_error = (optimal_cmax > 0) ? (static_cast<float>(absolute_error) / optimal_cmax * 100.0f) : 0.0f;

        // --- Wypisanie wiersza tabeli ---
        std::cout << std::left
                  << std::setw(12) << (i + 1)
                  << std::setw(4)  << n
                  << std::setw(4)  << m
                  << std::setw(15) << optimal_cmax
                  << std::setw(15) << std::fixed << std::setprecision(4) << time_zupelny
                  << std::setw(15) << bandb_cmax
                  << std::setw(15) << time_bandb
                  << std::setw(12) << absolute_error
                  << std::setw(12) << relative_error
                  << std::endl;
    }

    data_file.close();
    std::cout << std::string(100, '-') << std::endl;

    return 0;
}