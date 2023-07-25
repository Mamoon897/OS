import sys

def find_closest_request(requests, head, visited):
    closest = sys.maxsize
    index = -1

    for i in range(len(requests)):
        if not visited[i] and abs(requests[i] - head) < closest:
            closest = abs(requests[i] - head)
            index = i

    return index

def main():
    head = int(input("Enter the initial head position: "))
    n = int(input("Enter the number of disk requests: "))
    requests = []

    print("Enter the disk request queue: ")
    for i in range(n):
        request = int(input())
        requests.append(request)

    visited = [False] * n
    seek = 0

    for i in range(n):
        index = find_closest_request(requests, head, visited)
        visited[index] = True

        print(f"Disk head moves from {head} to {requests[index]} with seek {abs(requests[index] - head)}")
        seek += abs(requests[index] - head)
        head = requests[index]

    print("Total seek time is", seek)
    avg = seek / n
    print("Average seek time is", avg)

if __name__ == "__main__":
    main()
