#include <iostream>
#include <vector>
#include <climits>

struct Process {
    int pid; // Process ID
    int bt; // Burst Time
    int art; // Arrival Time

    Process(int pid, int bt, int art) : pid(pid), bt(bt), art(art) {}
};

// Method to find the waiting time for all processes
void findWaitingTime(const std::vector<Process>& processes, int n, int wt[], int ct[]) {
    int rt[n];

    // Copy the burst time into rt[]
    for (int i = 0; i < n; i++)
        rt[i] = processes[i].bt;

    int complete = 0, t = 0, minm = INT_MAX;
    int shortest = -1, finishTime;
    bool check = false;

    // Process until all processes get completed
    while (complete != n) {
        // Find the process with the minimum remaining time among the processes that have arrived till the current time
        for (int j = 0; j < n; j++) {
            if (processes[j].art <= t && rt[j] < minm && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
                check = true;
            }
        }

        if (!check) {
            t++;
            continue;
        }

        // Reduce the remaining time by one
        rt[shortest]--;

        // Update the minimum remaining time
        minm = rt[shortest];
        if (minm == 0)
            minm = INT_MAX;

        // If a process gets completely executed
        if (rt[shortest] == 0) {
            complete++;
            check = false;

            // Find the finish time of the current process
            finishTime = t + 1;

            // Calculate completion time
            ct[shortest] = finishTime;

            // Calculate waiting time
            wt[shortest] = finishTime - processes[shortest].bt - processes[shortest].art;
            if (wt[shortest] < 0)
                wt[shortest] = 0;
        }

        // Increment time
        t++;
    }
}

// Method to calculate turnaround time
void findTurnaroundTime(const std::vector<Process>& processes, int n, int wt[], int tat[]) {
    // Calculate turnaround time by adding burst time and waiting time
    for (int i = 0; i < n; i++)
        tat[i] = processes[i].bt + wt[i];
}

// Method to calculate average time
void findAverageTime(const std::vector<Process>& processes, int n) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;
    int ct[n];

    // Find waiting time of all processes
    findWaitingTime(processes, n, wt, ct);

    // Find turnaround time for all processes
    findTurnaroundTime(processes, n, wt, tat);

    // Display process details
    std::cout << "Process\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    for (int i = 0; i < n; i++) {
        std::cout << processes[i].pid << "\t" << processes[i].art << "\t" << processes[i].bt << "\t"
                  << ct[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << "\n";

        total_wt += wt[i];
        total_tat += tat[i];
            }

    // Calculate average waiting time and average turnaround time
    float avg_wt = static_cast<float>(total_wt) / n;
    float avg_tat = static_cast<float>(total_tat) / n;

    std::cout << "\nAverage Waiting Time: " << avg_wt << "\n";
    std::cout << "Average Turnaround Time: " << avg_tat << "\n";
}

// Driver Method
int main() {
    std::cout << "Enter the number of processes: ";
    int n;
    std::cin >> n;

    std::vector<Process> processes;

    std::cout << "Enter Arrival Time and Burst Time:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "For process " << (i + 1) << ":\n";

        int arrivalTime, burstTime;
        std::cin >> arrivalTime >> burstTime;

        Process process(i + 1, burstTime, arrivalTime);
        processes.push_back(process);
    }

    findAverageTime(processes, processes.size());

    return 0;
}

