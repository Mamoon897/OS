
def main():
    head = int(input("Enter the initial head position: "))
    n = int(input("Enter the number of disk requests: "))
    requests = []

    print("Enter the disk request queue: ")
    for i in range(n):
        request = int(input())
        requests.append(request)

    seek = 0
    print(f"Disk head moves from {head} to {requests[0]} with seek {abs(requests[0] - head)}")
    seek += abs(requests[0] - head)

    for i in range(1, n):
        print(f"Disk head moves from {requests[i - 1]} to {requests[i]} with seek {abs(requests[i] - requests[i - 1])}")
        seek += abs(requests[i] - requests[i - 1])

    print("Total seek time is", seek)
    avg = seek / n
    print("Average seek time is", avg)

if __name__ == "__main__":
    main()
