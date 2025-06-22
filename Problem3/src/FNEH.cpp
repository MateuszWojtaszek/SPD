// Plik: FNEH.cpp
#include "FNEH.hpp"
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric> // Dla std::accumulate

FNEH::FNEH(std::vector<Task> tasks, int maszyny) : NEH(tasks, maszyny) {}

void FNEH::calculate_heuristic() {
    // Krok 1: Sortowanie zadań - tak jak w NEH
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        long long sum_a = std::accumulate(a.processing_time.begin(), a.processing_time.end(), 0);
        long long sum_b = std::accumulate(b.processing_time.begin(), b.processing_time.end(), 0);
        if (sum_a != sum_b) {
            return sum_a > sum_b;
        }
        return a.id < b.id; // Stabilne sortowanie dla zadań o tej samej sumie
    });

    std::vector<Task> pi; // Permutacja, którą budujemy
    std::vector<std::vector<int>> C_pi; // Macierz Cmax dla permutacji pi

    // Pętla główna - wstawianie kolejnych zadań z posortowanej listy
    for (const auto& task_to_insert : tasks) {
        int best_cmax = std::numeric_limits<int>::max();
        size_t best_pos = 0;

        // Krok 2: Testujemy wstawienie zadania na każdą możliwą pozycję 'q'
        for (size_t q = 0; q <= pi.size(); ++q) {

            // --- POPRAWNA I SZYBKA KALKULACJA CMAX (ZGODNA Z WYKŁADEM) ---
            int current_cmax = 0;
            std::vector<int> C_prev_row(maszyny, 0); // Wiersz Cmax dla zadania i-1

            // Część 1: Obliczenia do miejsca wstawienia (i < q)
            // Używamy istniejącej macierzy C_pi, jeśli nie wstawiamy na początku
            if (q > 0) {
                 C_prev_row = C_pi[q - 1];
            }

            // Część 2: Obliczenia dla wstawianego zadania (i = q)
            std::vector<int> C_current_row(maszyny, 0);
            for (int j = 0; j < maszyny; ++j) {
                int c_prev_machine = (j > 0) ? C_current_row[j - 1] : 0;
                C_current_row[j] = std::max(C_prev_row[j], c_prev_machine) + task_to_insert.processing_time[j];
            }
            C_prev_row = C_current_row;

            // Część 3: Obliczenia dla zadań po miejscu wstawienia (i > q)
            for (size_t i = q; i < pi.size(); ++i) {
                for (int j = 0; j < maszyny; ++j) {
                    int c_prev_machine = (j > 0) ? C_current_row[j - 1] : 0;
                    C_current_row[j] = std::max(C_prev_row[j], c_prev_machine) + pi[i].processing_time[j];
                }
                C_prev_row = C_current_row;
            }

            current_cmax = C_prev_row.back();
            // --- KONIEC KALKULACJI CMAX ---

            // Krok 3: Sprawdź, czy to najlepsza znaleziona pozycja
            if (current_cmax < best_cmax) {
                best_cmax = current_cmax;
                best_pos = q;
            }
        }

        // Krok 4: Wstaw zadanie na stałe na najlepszą pozycję
        pi.insert(pi.begin() + best_pos, task_to_insert);

        // Krok 5: Zaktualizuj główną macierz C_pi dla nowej, dłuższej permutacji 'pi'
        // Ta macierz będzie użyta w następnej iteracji pętli głównej
        C_pi.assign(pi.size(), std::vector<int>(maszyny, 0));
        for (size_t i = 0; i < pi.size(); ++i) {
            for (int j = 0; j < maszyny; ++j) {
                C_pi[i][j] = std::max(i > 0 ? C_pi[i - 1][j] : 0, j > 0 ? C_pi[i][j - 1] : 0) + pi[i].processing_time[j];
            }
        }
    }

    // Zapisz ostateczną permutację
    tasks = pi;
}