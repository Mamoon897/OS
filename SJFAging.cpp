#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

float ATAT;
float AWT;

struct Process {
    string name;
    int arrivalTime;
    int burstTime;
    int age = 2;

    Process(const string& name, int arrivalTime, int burstTime)
        : name(name), arrivalTime(arrivalTime), burstTime(burstTime)
    {}
};

struct Comparator {
    bool operator()(const Process& p1, const Process& p2) {
        if (p1.arrivalTime == p2.arrivalTime)
            return p1.burstTime > p2.burstTime;
        return p1.arrivalTime < p2.arrivalTime;
    }
};

void calculate(const string& name, int at, int bt, int& currentTime) {
    int st = currentTime;
    int ct = st + bt;
    currentTime += bt;

    int tat = ct - at;
    int wt = tat - bt;

    ATAT += tat;
    AWT += wt;
    cout << name << "\t\t" << at << "\t\t" << bt << "\t\t" << st << "\t\t\t" << ct << "\t\t\t" << tat << "\t\t\t" << wt << endl;
}

int main() {
    vector<Process> processes;

    int currentTime = 0;

    cout << "Enter the number of processes: ";
    int n;
    cin >> n;

    cout << "Enter process Arrival & Burst time:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "For Process " << (i + 1) << ":" << endl;
        int arrivalTime, burstTime;
        cin >> arrivalTime >> burstTime;

        processes.push_back(Process("P" + to_string(i + 1), arrivalTime, burstTime));
    }

    sort(processes.begin(), processes.end(), Comparator());

    cout << "PID\t\t" << "Arrival\t\t" << "Burst\t\t" << "Starting\t\t" << "Completion\t\t" << "TurnAround\t\t" << "Waiting" << endl;

    calculate(processes[0].name, processes[0].arrivalTime, processes[0].burstTime, currentTime);
    processes.erase(processes.begin());

    priority_queue<Process, vector<Process>, Comparator> pq;

    for (const Process& process : processes) {
        pq.push(process);
    }

    while (!pq.empty()) {
        Process currentProcess = pq.top();
        pq.pop();

        calculate(currentProcess.name, currentProcess.arrivalTime, currentProcess.burstTime, currentTime);

        while (!pq.empty()) {
            Process nextProcess = pq.top();
            if (nextProcess.arrivalTime <= currentTime) {
                pq.pop();
                pq.push(currentProcess);
                currentProcess = nextProcess;
                calculate(currentProcess.name, currentProcess.arrivalTime, currentProcess.burstTime, currentTime);
            } else {
                break;
            }
        }

        if (currentProcess.burstTime > 0) {
            currentProcess.burstTime--;
            pq.push(currentProcess);
        }
    }

    cout << "Average waiting time: " << AWT / n << endl;
    cout << "Average turnaround time: " << ATAT / n << endl;
    return 0;
}
