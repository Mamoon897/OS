/*SSTF*/
#include <iostream>
#include <vector>
#include <cmath>
#include <limits>

int findClosestRequest(const std::vector<int>& requests, int head, const std::vector<bool>& visited)
{
    int closest = std::numeric_limits<int>::max();
    int index = -1;

    for (int i = 0; i < requests.size(); i++)
    {
        if (!visited[i] && std::abs(requests[i] - head) < closest)
        {
            closest = std::abs(requests[i] - head);
            index = i;
        }
    }

    return index;
}

int main()
{
    int head;
    int n;
    std::vector<int> requests;

    std::cout << "Enter the initial head position: ";
    std::cin >> head;

    std::cout << "Enter the number of disk requests: ";
    std::cin >> n;

    std::cout << "Enter the disk request queue: ";
    for (int i = 0; i < n; i++)
    {
        int request;
        std::cin >> request;
        requests.push_back(request);
    }

    std::vector<bool> visited(n, false);
    int seek = 0;

    for (int i = 0; i < n; i++)
    {
        int index = findClosestRequest(requests, head, visited);
        visited[index] = true;

        std::cout << "Disk head moves from " << head << " to " << requests[index] << " with seek " << std::abs(requests[index] - head) << std::endl;
        seek += std::abs(requests[index] - head);
        head = requests[index];
    }

    std::cout << "Total seek time is " << seek << std::endl;
    float avg = static_cast<float>(seek) / n;
    std::cout << "Average seek time is " << avg << std::endl;

    return 0;
}
