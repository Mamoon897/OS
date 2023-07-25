#include <iostream>

using namespace std;

int main() {
    int NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0;
    float avg_wt, avg_tat;

    cout << "Total number of processes in the system: ";
    cin >> NOP;
    y = NOP;

    int at[NOP], bt[NOP], temp[NOP], ct[NOP];
    int i; 
    for (i = 0; i < NOP; i++) {
        cout << "\nEnter the Arrival and Burst time of Process[" << i + 1 << "]:\n";
        cout << "Arrival time: ";
        cin >> at[i];
        cout << "Burst time: ";
        cin >> bt[i];
        temp[i] = bt[i];
    }

    cout << "Enter the Time Quantum for the process: ";
    cin >> quant;

    cout << "\nProcess  \t\t Arrival Time \t\t Burst Time \t\t TAT \t\t Waiting Time \t\t Completion Time\n";
    for (sum = 0, i = 0; y != 0 ;) {
        if (temp[i] <= quant && temp[i] > 0) {
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        } else if (temp[i] > 0) {
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }
        if (temp[i] == 0 && count == 1) {
            y--;
            ct[i] = sum; // Store the completion time for the process i
            cout << "Process " << i + 1 << "\t\t\t" << at[i] << "\t\t\t" << bt[i] << "\t\t\t" << sum - at[i] << "\t\t\t" << sum - at[i] - bt[i] << "\t\t\t" << ct[i] << "\n";
            
            wt = wt + sum - at[i] - bt[i];
            tat = tat + sum - at[i];
            count = 0;
        }
        if (i == NOP - 1) {
            i = 0;
        } else if (at[i + 1] <= sum) {
            i++;
        } else {
            i = 0;
        }
    }

    avg_wt = static_cast<float>(wt) / NOP;
    avg_tat = static_cast<float>(tat) / NOP;

    cout << "\nAverage Turn Around Time: " << avg_tat << "\n";
    cout << "Average Waiting Time: " << avg_wt << "\n";

    return 0;
}
