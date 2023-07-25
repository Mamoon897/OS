class Process:
    def __init__(self, processId, arrivalTime, burstTime):
        self.processId = processId
        self.arrivalTime = arrivalTime
        self.burstTime = burstTime


def calculate_waiting_time(processes):
    # Calculate waiting time for each process
    n = len(processes)
    waiting_times = [0] * n
    current_time = 0

    for i in range(n):
        # If the current time is less than the arrival time of the process,
        # set the current time to the arrival time of the process.
        if current_time < processes[i].arrivalTime:
            current_time = processes[i].arrivalTime

        # Calculate the waiting time for the current process.
        waiting_times[i] = current_time - processes[i].arrivalTime
        # Update the current time to include the burst time of the current process.
        current_time += processes[i].burstTime

    return waiting_times


def calculate_turnaround_time(processes, waiting_times):
    # Calculate turnaround time for each process
    turnaround_times = []
    for i in range(len(processes)):
        turnaround_times.append(processes[i].burstTime + waiting_times[i])

    return turnaround_times


def display_results(processes, waiting_times, turnaround_times):
    # Display the results in tabular format
    print("Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time")
    for i in range(len(processes)):
        print(f"{processes[i].processId}\t\t{processes[i].arrivalTime}\t\t{processes[i].burstTime}\t\t{waiting_times[i]}\t\t{turnaround_times[i]}")


def calculate_average_waiting_time(waiting_times):
    # Calculate the average waiting time for all processes
    return sum(waiting_times) / len(waiting_times)


def calculate_average_turnaround_time(turnaround_times):
    # Calculate the average turnaround time for all processes
    return sum(turnaround_times) / len(turnaround_times)


if __name__ == "__main__":
    # Get the number of processes from the user
    n = int(input("Enter the number of processes: "))

    processes = []
    # Get arrival times and burst times for each process from the user
    for i in range(n):
        arrival_time = int(input(f"Process {i + 1} - Enter arrival time: "))
        burst_time = int(input(f"Process {i + 1} - Enter burst time: "))
        processes.append(Process(i + 1, arrival_time, burst_time))

    # Sort processes based on their arrival times
    processes.sort(key=lambda x: x.arrivalTime)

    # Calculate waiting time and turnaround time for each process
    waiting_times = calculate_waiting_time(processes)
    turnaround_times = calculate_turnaround_time(processes, waiting_times)

    # Display the results
    display_results(processes, waiting_times, turnaround_times)

    # Calculate and display the average waiting time and average turnaround time
    avg_waiting_time = calculate_average_waiting_time(waiting_times)
    avg_turnaround_time = calculate_average_turnaround_time(turnaround_times)

    print(f"Average Waiting Time: {avg_waiting_time:.2f}")
    print(f"Average Turnaround Time: {avg_turnaround_time:.2f}")
