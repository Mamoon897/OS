import threading
import time

# Function to be executed by the thread
def print_numbers():
    for i in range(1, 6):
        print(f"Thread 1: {i}")
        time.sleep(1)

def print_letters():
    for letter in 'ABCDE':
        print(f"Thread 2: {letter}")
        time.sleep(1)

# Create two threads
thread1 = threading.Thread(target=print_numbers)
thread2 = threading.Thread(target=print_letters)

# Start the threads
thread1.start()
thread2.start()

# Wait for both threads to finish
thread1.join()
thread2.join()

print("Both threads have finished.")
