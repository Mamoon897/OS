class Process:
    def __init__(self, pid, arrival_time, burst_time):
        self.id = pid
        self.AT = arrival_time
        self.BT = burst_time
        self.ST = 0
        self.CT = 0
        self.WT = 0
        self.TAT = 0

def compare_AT(p1, p2):
    return p1.AT < p2.AT

def cal_times(work):
    curr_time = 0
    work.sort(key=lambda x: x.AT)

    for i in range(len(work)):
        if curr_time < work[i].AT:
            curr_time = work[i].AT

        sj_index = i
        for j in range(i + 1, len(work)):
            if work[j].AT <= curr_time and work[j].BT < work[sj_index].BT:
                sj_index = j

        work[i], work[sj_index] = work[sj_index], work[i]

        work[i].ST = curr_time
        work[i].CT = curr_time + work[i].BT
        work[i].TAT = work[i].CT - work[i].AT
        work[i].WT = work[i].TAT - work[i].BT

        curr_time = work[i].CT

def display_table(work):
    print("Process\t  ArrivalTime\tBurstTime\tStartTime\tCompletionTime\tWaitingTime\tTAT")
    for p in work:
        print(f"  P{p.id}\t  {p.AT}\t\t{p.BT}\t\t{p.ST}\t\t{p.CT}\t\t{p.WT}\t\t{p.TAT}")

def cal_average_TAT(work):
    sum_TAT = sum(p.TAT for p in work)
    return sum_TAT / len(work)

def cal_average_WT(work):
    sum_WT = sum(p.WT for p in work)
    return sum_WT / len(work)

def cal_throughput(work, total_time):
    n = len(work)
    throughput = n / total_time
    return throughput

def main():
    n = int(input("Enter the number of Processes: "))
    print()

    work = []
    print("Enter the arrival time and burst time for each process:")
    for i in range(n):
        pid = i + 1
        AT = int(input(f"P{pid}  Arrival time: "))
        BT = int(input(f"P{pid}  Burst time: "))
        work.append(Process(pid, AT, BT))

    cal_times(work)
    display_table(work)

    avg_TAT = cal_average_TAT(work)
    print("Average Turnaround Time:", avg_TAT)

    avg_WT = cal_average_WT(work)
    print("Average Waiting Time:", avg_WT)

    total_time = work[-1].CT - work[0].AT
    throughput = cal_throughput(work, total_time)
    print("Throughput:", throughput)

if __name__ == "__main__":
    main()
