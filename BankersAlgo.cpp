#include <iostream>
#include <vector>

using namespace std;

const int MAX_PROCESSES = 10;
const int MAX_RESOURCES = 10;

bool isSafe(const vector<vector<int>>& max_resources, const vector<vector<int>>& allocated_resources,
            const vector<int>& available_resources, vector<bool>& completed, int process_count, int resource_count) {
    vector<int> work = available_resources;
    vector<bool> safe_sequence(process_count, false);

    int count = 0;
    while (count < process_count) {
        bool found = false;
        for (int i = 0; i < process_count; ++i) {
            if (!completed[i]) {
                bool can_execute = true;
                for (int j = 0; j < resource_count; ++j) {
                    if (max_resources[i][j] - allocated_resources[i][j] > work[j]) {
                        can_execute = false;
                        break;
                    }
                }

                if (can_execute) {
                    for (int j = 0; j < resource_count; ++j) {
                        work[j] += allocated_resources[i][j];
                    }
                    safe_sequence[count++] = true;
                    completed[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            break;
        }
    }

    return count == process_count;
}

int main() {
    int process_count, resource_count;

    cout << "Enter the number of processes: ";
    cin >> process_count;

    cout << "Enter the number of resources: ";
    cin >> resource_count;

    vector<vector<int>> max_resources(process_count, vector<int>(resource_count));
    vector<vector<int>> allocated_resources(process_count, vector<int>(resource_count));
    vector<int> available_resources(resource_count);
    vector<bool> completed(process_count, false);

    cout << "Enter the maximum resources needed for each process: " << endl;
    for (int i = 0; i < process_count; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < resource_count; ++j) {
            cin >> max_resources[i][j];
        }
    }

    cout << "Enter the allocated resources for each process: " << endl;
    for (int i = 0; i < process_count; ++i) {
        cout << "Process " << i << ": ";
        for (int j = 0; j < resource_count; ++j) {
            cin >> allocated_resources[i][j];
            available_resources[j] -= allocated_resources[i][j];
        }
    }

    cout << "Enter the available resources: ";
    for (int i = 0; i < resource_count; ++i) {
        cin >> available_resources[i];
    }

    if (isSafe(max_resources, allocated_resources, available_resources, completed, process_count, resource_count)) {
        cout << "System is in a safe state. Safe sequence: ";
        for (int i = 0; i < process_count; ++i) {
            cout << "P" << i;
            if (i != process_count - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    } else {
        cout << "System is not in a safe state. Deadlock may occur." << endl;
    }

    return 0;
}
