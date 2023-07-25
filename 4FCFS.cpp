#include <iostream>
#include <vector>
#include <algorithm>

struct Process {
    int processId;
    int arrivalTime;
    int burstTime;
};

bool compareArrivalTime(const Process& p1, const Process& p2) {
    return p1.arrivalTime < p2.arrivalTime;
}

void calculateWaitingTime(std::vector<Process>& processes, std::vector<int>& waitingTimes) {
    int n = processes.size();
    int currentTime = 0;

    for (int i = 0; i < n; i++) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;

        waitingTimes[i] = currentTime - processes[i].arrivalTime;
        currentTime += processes[i].burstTime;
    }
}

void calculateTurnaroundTime(const std::vector<Process>& processes, const std::vector<int>& waitingTimes, std::vector<int>& turnaroundTimes) {
    int n = processes.size();

    for (int i = 0; i < n; i++) {
        turnaroundTimes[i] = processes[i].burstTime + waitingTimes[i];
    }
}

void displayResults(const std::vector<Process>& processes, const std::vector<int>& waitingTimes, const std::vector<int>& turnaroundTimes) {
    int n = processes.size();

    std::cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        std::cout << processes[i].processId << "\t" << processes[i].arrivalTime << "\t\t"
                  << processes[i].burstTime << "\t\t" << waitingTimes[i] << "\t\t" << turnaroundTimes[i] << "\n";
    }
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);
    std::vector<int> waitingTimes(n);
    std::vector<int> turnaroundTimes(n);

    for (int i = 0; i < n; i++) {
        std::cout << "Process " << i + 1 << " - Enter arrival time: ";
        std::cin >> processes[i].arrivalTime;
        std::cout << "Process " << i + 1 << " - Enter burst time: ";
        std::cin >> processes[i].burstTime;
        processes[i].processId = i + 1;
    }

    std::sort(processes.begin(), processes.end(), compareArrivalTime);

    calculateWaitingTime(processes, waitingTimes);
    calculateTurnaroundTime(processes, waitingTimes, turnaroundTimes);
    displayResults(processes, waitingTimes, turnaroundTimes);

    return 0;
}
