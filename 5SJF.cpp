#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    int id,AT,BT,ST,CT,WT,TAT;
};

bool compareAT(const Process& p1, const Process& p2) {
    return p1.AT < p2.AT;
}

void calTimes(vector<Process>& work,int n) {
    int currTime = 0;

    sort(work.begin(), work.end(), compareAT);

    for (int i = 0; i < n; i++) {
        if (currTime < work[i].AT){
           currTime = work[i].AT; 
        }

        int sjIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (work[j].AT <= currTime && work[j].BT < work[sjIndex].BT)
                sjIndex = j;
        }

        swap(work[i], work[sjIndex]);

        work[i].ST = currTime;
        work[i].CT = currTime + work[i].BT;
        work[i].TAT = work[i].CT - work[i].AT;
        work[i].WT = work[i].TAT - work[i].BT;

        currTime = work[i].CT;
    }
}

void displayTable(const vector<Process>& work) {
    cout << "Process\t  ArrivalTime\tBurstTime\tStartTime\tCompletionTime\tWaitingTime\tTAT\n";
    
    for (const auto& p : work) {
        cout<<"  P" << p.id <<" \t  " << p.AT << "\t\t"
            << p.BT << "\t\t" << p.ST << "\t\t"
            << p.CT << "\t\t" << p.WT << "\t\t"
            << p.TAT << endl;
    }
}

double calAverageTAT(const vector<Process>& work, int n) {
    double sumTAT = 0.0;

    for (const auto& process : work) {
        sumTAT += process.TAT;
    }

    return sumTAT / n;
}

double calAverageWT(const vector<Process>& work, int n) {
    double sumWT = 0.0;

    for (const auto& process : work) {
        sumWT += process.WT;
    }

    return sumWT / n;
}

double calThroughput(const vector<Process>& work, int totalTime) {
    int n = work.size();
    double throughput = static_cast<double>(n) / totalTime;

    return throughput;
}


int main() {
    int n;
    cout << "Enter the number of Processes: ";
    cin >> n;
    cout << endl;
    vector<Process> work(n);
    cout << "Enter the arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        work[i].id = i + 1;
        cout << "P" << work[i].id << "  Arrival time: ";
        cin >> work[i].AT;
        cout << "P" << work[i].id << "  Burst time: ";
        cin >> work[i].BT;
    }

    calTimes(work,n);
    displayTable(work);

    double avgTAT = calAverageTAT(work,n);
    cout << "Average Turnaround Time: " << avgTAT << endl;

    double avgWT = calAverageWT(work,n);
    cout << "Average Waiting Time: " << avgWT << endl;

    int totalTime = work[n - 1].CT - work[0].AT;
   /* double throughput = calThroughput(work, totalTime);
    cout << "Throughput: " << throughput << endl;*/

    return 0;
}
