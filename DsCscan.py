def main():
    queue1 = []
    queue2 = []
    max_range = int(input("Enter the max range of disk: "))
    head = int(input("Enter the initial head position: "))
    n = int(input("Enter the size of the queue request: "))

    print("Enter the queue of disk positions to be read: ")
    for _ in range(n):
        temp = int(input())
        if temp >= head:
            queue1.append(temp)
        else:
            queue2.append(temp)

    queue1.sort()
    queue2.sort()

    queue = queue1 + [max_range] + [0] + queue2
    seek = 0

    for j in range(n + 2):
        diff = abs(queue[j + 1] - queue[j])
        seek += diff
        print(f"Disk head moves from {queue[j]} to {queue[j + 1]} with seek {diff}")

    print("Total seek time is", seek)
    avg = seek / n
    print("Average seek time is", avg)

if __name__ == "__main__":
    main()
