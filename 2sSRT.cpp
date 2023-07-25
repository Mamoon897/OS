#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;

    Process(int id, int arrivalTime, int burstTime)
        : id(id), arrivalTime(arrivalTime), burstTime(burstTime), remainingTime(burstTime),
          startTime(0), completionTime(0), waitingTime(0), turnaroundTime(0) {}
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

bool compareRemainingTime(const Process& p1, const Process& p2) {
    return p1.remainingTime < p2.remainingTime;
}

void SRTF(std::vector<Process>& processes) {
    int n = processes.size();
    std::vector<bool> completed(n, false);
    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < n) {
        int shortestIndex = -1;
        int shortestTime = std::numeric_limits<int>::max();

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestTime) {
                shortestIndex = i;
                shortestTime = processes[i].remainingTime;
            }
        }

        if (shortestIndex == -1) {
            currentTime++;
            continue;
        }

        if (processes[shortestIndex].remainingTime == processes[shortestIndex].burstTime) {
            processes[shortestIndex].startTime = currentTime;
        }

        processes[shortestIndex].remainingTime--;
        currentTime++;

        if (processes[shortestIndex].remainingTime == 0) {
            completed[shortestIndex] = true;
            completedCount++;
            processes[shortestIndex].completionTime = currentTime;
            processes[shortestIndex].turnaroundTime = processes[shortestIndex].completionTime - processes[shortestIndex].arrivalTime;
            processes[shortestIndex].waitingTime = processes[shortestIndex].turnaroundTime - processes[shortestIndex].burstTime;

            cout << "Process \t Start Time\t Completion time\t waiting time\t Turnaround Time " <<endl
                      << processes[shortestIndex].id << ":\t "
                      <<  processes[shortestIndex].startTime<<"\t"
                      <<  processes[shortestIndex].completionTime<<"\t"
                      << processes[shortestIndex].waitingTime<<"\t"
                      << processes[shortestIndex].turnaroundTime << endl;
        }
    }
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes;
    int id, arrivalTime, burstTime;

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter the arrival time and burst time for process " << i + 1 << ": ";
        std::cin >> arrivalTime >> burstTime;
        processes.emplace_back(i + 1, arrivalTime, burstTime);
    }

    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    std::cout << "\nShortest Remaining Time First (SRTF) scheduling:\n";
    SRTF(processes);

    return 0;
}
