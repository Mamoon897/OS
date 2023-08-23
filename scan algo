#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    int HeadPosition;
    cout << "Enter the initial head position: ";
    cin >> HeadPosition;
    cin.ignore();

    int n;
    cout << "Enter total number of sequences: ";
    cin >> n;

    vector<int> locations(n);
    vector<int> left;
    vector<int> right;
    vector<int> seekTime;
    int totalSeekTime = 0;
    int SeekTime = 0;

    cout << "Enter the sequence list: ";
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        if (num <= HeadPosition) {
            left.push_back(num);
        } else {
            right.push_back(num);
        }
    }

    string direction;
    cout << "Enter the direction (left or right): ";
    cin >> direction;
    transform(direction.begin(), direction.end(), direction.begin(), ::tolower);

    if (direction == "left") {
        left.push_back(0);
        sort(left.rbegin(), left.rend());
        sort(right.begin(), right.end());

        for (int j = 0; j < left.size(); j++) {
            SeekTime = abs(HeadPosition - left[j]);
            totalSeekTime += SeekTime;
            seekTime.push_back(SeekTime);
            HeadPosition = left[j];
        }

        for (int j = 0; j < right.size(); j++) {
            SeekTime = abs(HeadPosition - right[j]);
            totalSeekTime += SeekTime;
            seekTime.push_back(SeekTime);
            HeadPosition = right[j];
        }

        int k = 0;
        cout << "\nRequest \tSeek Time" << endl;
        for (int i = 0; i < left.size(); i++) {
            cout << left[i] << "\t\t" << seekTime[k] << endl;
            k++;
        }

        cout << "---------Changed Direction---------" << endl;

        for (int i = 0; i < right.size(); i++) {
            cout << right[i] << "\t\t" << seekTime[k] << endl;
            k++;
        }

        cout << "Total Seek Time: " << totalSeekTime << endl;
        cout << "Throughput: " << static_cast<float>(n) / totalSeekTime << endl;

    } else if (direction == "right") {
        right.push_back(200);
        sort(right.begin(), right.end());
        sort(left.rbegin(), left.rend());

        for (int j = 0; j < right.size(); j++) {
            SeekTime = abs(HeadPosition - right[j]);
            totalSeekTime += SeekTime;
            seekTime.push_back(SeekTime);
            HeadPosition = right[j];
        }

        for (int j = 0; j < left.size(); j++) {
            SeekTime = abs(HeadPosition - left[j]);
            totalSeekTime += SeekTime;
            seekTime.push_back(SeekTime);
            HeadPosition = left[j];
        }

        int k = 0;
        cout << "\nRequest \tSeek Time" << endl;
        for (int i = 0; i < right.size(); i++) {
            cout << right[i] << "\t\t" << seekTime[k] << endl;
            k++;
        }

        cout << "---------Changed Direction---------" << endl;

        for (int i = 0; i < left.size(); i++) {
            cout << left[i] << "\t\t" << seekTime[k] << endl;
            k++;
        }

        cout << "Total Seek Time: " << totalSeekTime << endl;
        cout << "Throughput: " << static_cast<float>(n) / totalSeekTime << endl;
    } else {
        cout << "Invalid direction entered. Please choose either 'left' or 'right'." << endl;
        return 0;
    }

    return 0;
}
