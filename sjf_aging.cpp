#include <iostream>
#include <vector>
#include <algorithm>

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

// sort based on arrival time
struct ArrivalComparator {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.arrivalTime < p2.arrivalTime;
    }
};

// sort based on burst time
struct BurstComparator {
    bool operator()(const Process& p1, const Process& p2) {
        return p1.burstTime < p2.burstTime;
    }
};

void calculate(const string& name, int at, int bt, int& currentTime) {
    int st = currentTime;
    int ct = st + bt;
    currentTime += bt;

    int tat = ct - at;
    int wt = tat - bt;

  ATAT+=tat;
  AWT+=wt;
    cout << name << "\t\t" << at << "\t\t" << bt << "\t\t" << st << "\t\t\t" << ct << "\t\t\t" << tat << "\t\t\t" << wt << endl;
}

int main() {
    vector<Process> processes;
    vector<Process> temp;

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

    // sort based on arrival time
    sort(processes.begin(), processes.end(), ArrivalComparator());

    cout << "PID\t\t" << "Arrival\t\t" << "Burst\t\t" << "Starting\t\t" << "Completion\t\t" << "TurnAround\t\t" << "Waiting" << endl;

    // calculate 1st process
    calculate(processes[0].name, processes[0].arrivalTime, processes[0].burstTime, currentTime);

    processes.erase(processes.begin());

    while (!processes.empty() || !temp.empty()) {
        // add processes which have arrived into the temporary list
        if (!processes.empty()) {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrivalTime <= currentTime) {
                    temp.push_back(processes[i]);
                    processes.erase(processes.begin() + i);
                    i--;
                }
            }
        }

        if (!processes.empty()) {
            for (int i = 0; i < processes.size(); i++) {
                if (processes[i].arrivalTime <= currentTime) {
                    temp.push_back(processes[i]);
                    processes.erase(processes.begin() + i);
                    i--;
                }
            }
        }

        // sort based on burst time
        sort(temp.begin(), temp.end(), BurstComparator());

        bool flag = false;

        for (int i = 0; i < temp.size(); i++) {
            if (temp[i].age == 0) {
                flag = true;
                calculate(temp[i].name, temp[i].arrivalTime, temp[i].burstTime, currentTime);
                                temp.erase(temp.begin() + i);
                i--;
            } else {
                flag = false;
            }
        }

        if (!flag) {
            calculate(temp[0].name, temp[0].arrivalTime, temp[0].burstTime, currentTime);
            for (Process& p : temp) {
                p.age -= 1;
            }
            temp.erase(temp.begin());
            flag = false;
        }
    }
    
    cout<<"Average waiting time:"<<AWT/n<<endl;
    cout<<"Average turnaround time:"<<ATAT/n<<endl;
    return 0;
}

