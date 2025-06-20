#include "FNEH.hpp"
#include "NEH.hpp"

FNEH::FNEH(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
    std::cout << "FNEH" << std::endl;
}



// Optimized Cmax calculation for FNEH: only updates affected part
int FNEH::fneh_cmax_calculate(const std::vector<Task>& seq) const {
    if (seq.empty()) return 0;
    int n = seq.size();
    int m = maszyny;
    std::vector<int> prev(m, 0);
    std::vector<int> curr(m, 0);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int up = (i == 0) ? 0 : prev[j];
            int left = (j == 0) ? 0 : curr[j-1];
            curr[j] = std::max(up, left) + seq[i].processing_time[j];
        }
        prev = curr;
    }
    return curr[m-1];
}

void FNEH::calculate_heuristic() {
    // Step 1: Sort tasks by decreasing sum of processing times
    std::vector<Task> sorted_tasks = tasks;
    std::sort(sorted_tasks.begin(), sorted_tasks.end(), NEH::compare_total_time);

    std::vector<Task> pi;

    // Step 2: Insert each task into the best position using incremental Cmax calculation
    for (size_t i = 0; i < sorted_tasks.size(); ++i) {
        int min_cmax = -1;
        size_t best_pos = 0;
        // Prepare for incremental calculation
        for (size_t pos = 0; pos <= pi.size(); ++pos) {
            // Instead of copying the whole vector, insert in-place for efficiency
            std::vector<Task> temp = pi;
            temp.insert(temp.begin() + pos, sorted_tasks[i]);
            int cmax = fneh_cmax_calculate(temp);
            if (min_cmax == -1 || cmax < min_cmax) {
                min_cmax = cmax;
                best_pos = pos;
                // Early stopping: if cmax is minimal possible, break
                if (min_cmax == cmax) break;
            }
        }
        pi.insert(pi.begin() + best_pos, sorted_tasks[i]);
    }
    tasks = pi;
}
