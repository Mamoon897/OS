/*FCFS */
#include <iostream>
#include <vector>
#include <cmath>

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

    int seek = 0;
    std::cout << "Disk head moves from " << head << " to " << requests[0] << " with seek " << std::abs(requests[0] - head) << std::endl;
    seek += std::abs(requests[0] - head);

    for (int i = 1; i < n; i++)
    {
        std::cout << "Disk head moves from " << requests[i - 1] << " to " << requests[i] << " with seek " << std::abs(requests[i] - requests[i - 1]) << std::endl;
        seek += std::abs(requests[i] - requests[i - 1]);
    }

    std::cout << "Total seek time is " << seek << std::endl;
    float avg = static_cast<float>(seek) / n;
    std::cout << "Average seek time is " << avg << std::endl;

    return 0;
}
