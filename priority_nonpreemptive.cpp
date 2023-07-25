#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int tempBT;
    int priority;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;
    bool completed;

    Process(int id, int arrivalTime, int burstTime, int priority)
        : id(id), arrivalTime(arrivalTime), burstTime(burstTime),
          tempBT(burstTime), priority(priority), startTime(0),
          completionTime(0), waitingTime(0), turnaroundTime(0),
          completed(false) {}
};

bool compareProcesses(const Process& p1, const Process& p2) {
    if (p1.arrivalTime < p2.arrivalTime)
        return true;
    else if (p1.arrivalTime == p2.arrivalTime && p1.priority < p2.priority)
        return true;
    return false;
}

int main() {
    std::vector<Process> processes;

    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::cout << "Enter Arrival, Burst, Priority:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << "For process " << (i + 1) << ":\n";
        int arrivalTime, burstTime, priority;
        std::cin >> arrivalTime >> burstTime >> priority;

        Process process(i + 1, arrivalTime, burstTime, priority);
        processes.push_back(process);
    }

    std::sort(processes.begin(), processes.end(), compareProcesses);

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        Process* selectedProcess = nullptr;
        int highestPriority = INT_MAX;

        for (Process& process : processes) {
            if (process.arrivalTime <= currentTime && !process.completed &&
                process.priority < highestPriority) {
                highestPriority = process.priority;
                selectedProcess = &process;
            }
        }

        if (selectedProcess == nullptr) {
            currentTime++;
            continue;
        }

        selectedProcess->startTime = currentTime;
        selectedProcess->completionTime = selectedProcess->startTime +
                                          selectedProcess->burstTime;
        currentTime += selectedProcess->burstTime;
        selectedProcess->turnaroundTime =
            selectedProcess->completionTime - selectedProcess->arrivalTime;
        selectedProcess->waitingTime =
            selectedProcess->turnaroundTime - selectedProcess->burstTime;
        selectedProcess->completed = true;

        completedProcesses++;
    }

    int averageWaitingTime = 0, averageTurnaroundTime = 0;

    std::cout << "\nProcess\t\tArrival\t\tBurst\t\tPriority\t\tStart\t\tCompletion\t\tWaiting\t\tTurnaround\n";
    std::cout << "--------------------------------------------------------------------------------------------------------------------\n";
    for (const Process& process : processes) {
        averageTurnaroundTime += process.turnaroundTime;
        averageWaitingTime += process.waitingTime;
        std::cout << process.id << "\t\t" << process.arrivalTime << "\t\t" << process.tempBT << "\t\t" << process.priority << "\t\t"
                  << process.startTime << "\t\t" << process.completionTime << "\t\t\t" << process.waitingTime << "\t\t\t" << process.turnaroundTime << "\n";
    }

    std::cout << "Average Waiting Time: " << averageWaitingTime << "\n";
    std::cout << "Average Turnaround Time: "<< averageTurnaroundTime << "\n";

    return 0;
}
