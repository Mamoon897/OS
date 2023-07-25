/*c scan program */
#include <iostream>
#include <cstdlib> // for abs function

int main()
{
    int queue[20], n, head, i, j, k, seek = 0, max, diff, temp, queue1[20], queue2[20],
        temp1 = 0, temp2 = 0;
    float avg;

    std::cout << "Enter the max range of disk: ";
    std::cin >> max;
    std::cout << "Enter the initial head position: ";
    std::cin >> head;
    std::cout << "Enter the size of the queue request: ";
    std::cin >> n;
    std::cout << "Enter the queue of disk positions to be read: ";
    for (i = 1; i <= n; i++)
    {
        std::cin >> temp;
        if (temp >= head)
        {
            queue1[temp1] = temp;
            temp1++;
        }
        else
        {
            queue2[temp2] = temp;
            temp2++;
        }
    }
    for (i = 0; i < temp1 - 1; i++)
    {
        for (j = i + 1; j < temp1; j++)
        {
            if (queue1[i] > queue1[j])
            {
                temp = queue1[i];
                queue1[i] = queue1[j];
                queue1[j] = temp;
            }
        }
    }
    for (i = 0; i < temp2 - 1; i++)
    {
        for (j = i + 1; j < temp2; j++)
        {
            if (queue2[i] > queue2[j])
            {
                temp = queue2[i];
                queue2[i] = queue2[j];
                queue2[j] = temp;
            }
        }
    }
    for (i = 1, j = 0; j < temp1; i++, j++)
        queue[i] = queue1[j];
    queue[i] = max;
    queue[i + 1] = 0;
    for (i = temp1 + 3, j = 0; j < temp2; i++, j++)
        queue[i] = queue2[j];
    queue[0] = head;
    for (j = 0; j <= n + 1; j++)
    {
        diff = std::abs(queue[j + 1] - queue[j]);
        seek += diff;
        std::cout << "Disk head moves from " << queue[j] << " to " << queue[j + 1] << " with seek " << diff << std::endl;
    }
    std::cout << "Total seek time is " << seek << std::endl;
    avg = seek / static_cast<float>(n);
    std::cout << "Average seek time is " << avg << std::endl;
    return 0;
}

