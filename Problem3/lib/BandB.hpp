// Plik: BandB.hpp
#pragma once

#include "BaseProblem.hpp"
#include "Task.hpp"
#include <vector>
#include <string>

class BandB : public BaseProblem {
public:
    // Konstruktor, wywołuje konstruktor klasy bazowej
    BandB(std::vector<Task> tasks, int maszyny);

    // Główna funkcja uruchamiająca algorytm
    void calculate_heuristic() override;

private:
    // Prywatne atrybuty do przechowywania najlepszego znalezionego rozwiązania
    int upper_bound; // Najlepszy Cmax znaleziony do tej pory (nasze UB)
    std::vector<Task> best_permutation_so_far; // Najlepsza permutacja znaleziona do tej pory

    // Rekurencyjna funkcja implementująca strategię "najpierw w głąb" (DFS)
    void branch(std::vector<Task>& current_permutation, std::vector<Task>& unscheduled_tasks);

    // Funkcja obliczająca dolne ograniczenie (LB) dla danego węzła drzewa
    int calculate_lower_bound(const std::vector<Task>& partial_permutation, const std::vector<Task>& unscheduled_tasks);
};