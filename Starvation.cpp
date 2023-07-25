#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int priority;
    int tempPriority;
    int startTime;
    int completionTime;
    int waitingTime;
    int turnaroundTime;

    Process(int id, int arrivalTime, int burstTime, int priority)
        : id(id), arrivalTime(arrivalTime), burstTime(burstTime),
          priority(priority), tempPriority(priority),
          startTime(0), completionTime(0),
          waitingTime(0), turnaroundTime(0) {}
};

int main() {
    std::vector<Process> processes;
    int n;

    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::cout << "Enter Arrival, Burst, Priority for each process:\n";
    for (int i = 0; i < n; i++) {
        int arrivalTime, burstTime, priority;
        std::cin >> arrivalTime >> burstTime >> priority;

        Process process(i + 1, arrivalTime, burstTime, priority);
        processes.push_back(process);
    }

    std::sort(processes.begin(), processes.end(),
              [](const Process& p1, const Process& p2) {
                  return p1.arrivalTime < p2.arrivalTime;
              });

    int currentTime = 0;
    int completedProcesses = 0;

    while (completedProcesses < n) {
        Process* selectedProcess = nullptr;
        int highestPriority = std::numeric_limits<int>::max();

        for (Process& process : processes) {
            if (process.arrivalTime <= currentTime && process.priority < highestPriority) {
                highestPriority = process.priority;
                selectedProcess = &process;
            }
        }

        if (selectedProcess == nullptr) {
            currentTime++;
            continue;
        }

        selectedProcess->startTime = currentTime;
        selectedProcess->completionTime = selectedProcess->startTime + selectedProcess->burstTime;
        currentTime = selectedProcess->completionTime;
        selectedProcess->waitingTime = selectedProcess->startTime - selectedProcess->arrivalTime;
        selectedProcess->turnaroundTime = selectedProcess->completionTime - selectedProcess->arrivalTime;

        completedProcesses++;

        for (Process& process : processes) {
            if (process.arrivalTime <= currentTime && &process != selectedProcess) {
                process.priority--;
            }
        }
    }

    float averageWaitingTime = 0.0f;
    float averageTurnaroundTime = 0.0f;

    for (const Process& process : processes) {
        averageWaitingTime += process.waitingTime;
        averageTurnaroundTime += process.turnaroundTime;
    }

    averageWaitingTime /= n;
    averageTurnaroundTime /= n;

    std::cout << "\nProcess\tArrival\tBurst\tPriority\tStart\tCompletion\tWaiting\tTurnaround\n";
   
    for (const Process& process : processes) {
        std::cout << process.id << "\t" << process.arrivalTime << "\t" << process.burstTime << "\t"
                  << process.tempPriority << "\t\t" << process.startTime << "\t\t" << process.completionTime
                  << "\t\t" << process.waitingTime << "\t\t" << process.turnaroundTime << "\n";
    }

    std::cout << "Average Waiting Time: " << averageWaitingTime << std::endl;
    std::cout << "Average Turnaround Time: " << averageTurnaroundTime << std::endl;

    return 0;
}
