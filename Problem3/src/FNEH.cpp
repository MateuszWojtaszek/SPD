#include "FNEH.hpp"
#include "NEH.hpp"

FNEH::FNEH(std::vector<Task> tasks, int maszyny): BaseProblem(tasks, maszyny) {
    std::cout << "FNEH" << std::endl;
}

// Optimized Cmax calculation for FNEH: only updates affected part
int FNEH::fneh_cmax_calculate(const std::vector<Task>& seq, bool remember,bool save) const {
    if (seq.empty()) return 0;
    
    std::vector<std::vector<int>> C(seq.size(), std::vector<int>(maszyny, 0));
    size_t begin_index=0;
    if (remember && !last_completion_times.empty()) {
      C = last_completion_times;
      begin_index = last_completion_times.size();
      C.resize(seq.size(), std::vector<int>(maszyny, 0));
    }
    
    for (size_t i = begin_index; i < seq.size(); ++i) {
      for (int j = 0; j < maszyny; ++j) {
          int proc_time = seq[i].processing_time[j];
          if (i == 0 && j == 0) {
              C[i][j] = proc_time;
          } else if (i == 0) {
              C[i][j] = C[i][j-1] + proc_time;
          } else if (j == 0) {
              C[i][j] = C[i-1][j] + proc_time;
          } else {
              C[i][j] = std::max(C[i-1][j], C[i][j-1]) + proc_time;
          }
      }
    }

    if(save)
      last_completion_times = C;
    return C[seq.size()-1][maszyny-1];
}

void FNEH::calculate_heuristic() {
  if (tasks.empty()) return;
  
  std::vector<Task> sorted_tasks = tasks;
  //sortowansk
  std::sort(sorted_tasks.begin(), sorted_tasks.end(), NEH::compare_total_time);
  
  // dla aktualnej sekwnecji tesetuejmy wsyztkie mozliwosci licząc cmax i jak mamy najmnjesze to bierzemy
  std::vector<Task> best_sequence;
  for (size_t i = 0; i < sorted_tasks.size(); ++i) {
      int min_cmax = -1;
      size_t best_pos = 0;

      std::vector<Task> temp = best_sequence;
      fneh_cmax_calculate(temp, true, true); // Initialize last_completion_times if needed

      for (size_t pos = 0; pos <= best_sequence.size(); ++pos) {
          temp = best_sequence;
          temp.insert(temp.begin() + pos, sorted_tasks[i]);
          int cmax = fneh_cmax_calculate(temp,true, false);
          if (min_cmax == -1 || cmax < min_cmax) {
              min_cmax = cmax;
              best_pos = pos;
          }
      }
      best_sequence.insert(best_sequence.begin() + best_pos, sorted_tasks[i]);
  }
  tasks = best_sequence;    
}
