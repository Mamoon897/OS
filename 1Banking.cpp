#include <iostream>
#include <vector>

class Bankers {
private:
    std::vector<std::vector<int>> need, allocate, max, available;
    int no_proc, no_res;

    void input() {
        std::cout << "\nNo. of Resources  : ";
        std::cin >> no_res;
        std::cout << "\nNo. of Processes : ";
        std::cin >> no_proc;

        need.resize(no_proc, std::vector<int>(no_res));
        max.resize(no_proc, std::vector<int>(no_res));
        allocate.resize(no_proc, std::vector<int>(no_res));
        available.resize(1, std::vector<int>(no_res));

        /* Input the allocation matrix */
        std::cout << "\nAllocation Matrix : \n";
        for (int i = 0; i < no_proc; i++) {
            for (int j = 0; j < no_res; j++) {
                std::cin >> allocate[i][j];
            }
        }

        /* Input the max matrix */
        std::cout << "\nMaximum resources : \n";
        for (int i = 0; i < no_proc; i++) {
            for (int j = 0; j < no_res; j++) {
                std::cin >> max[i][j];
            }
        }

        /* Input the available matrix */
        std::cout << "\nAvailable resources : \n";
        for (int i = 0; i < no_res; i++) {
            std::cin >> available[0][i];
        }
    }

    /* Calculate the need matrix */
    void find_need() {
        for (int i = 0; i < no_proc; i++) {
            for (int j = 0; j < no_res; j++) {
                need[i][j] = max[i][j] - allocate[i][j];
            }
        }
    }

    /* Check if all resources for a process can be allocated */
    bool check_resource_allocation(int row) {
        for (int i = 0; i < no_res; i++) {
            if (available[0][i] < need[row][i]) {
                return false;
            }
        }
        return true;
    }

public:
    void is_Safe() {
        int j = 0;

        input();
        find_need();

        std::vector<bool> done(no_proc, false);

        while (j < no_proc) {
            bool allocated = false;

            for (int i = 0; i < no_proc; i++) {
                if (!done[i] && check_resource_allocation(i)) {
                    for (int k = 0; k < no_res; k++) {
                        available[0][k] = available[0][k] - need[i][k] + max[i][k];
                    }

                    std::cout << "\nAllocated Process : " << i << std::endl;
                    allocated = done[i] = true;
                    j++;
                }
            }

            if (!allocated) {
                break;
            }
        }

        if (j == no_proc) {
            std::cout << "\nSafely Allocated\n";
        } else {
            std::cout << "\nAll processes can't be allocated safely\n";
        }
    }
};

int main() {
    Bankers bankers;
    bankers.is_Safe();
    return 0;
}
