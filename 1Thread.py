import threading
import queue
import time

bufferSize = 5  
buffer = queue.Queue()  

# Producer function
def producer(id):
    for i in range(1, 11):
        buffer.put(i)
        print(f"Producer {id} produced item: {i}")
        time.sleep(0.2)  

# Consumer function
def consumer(id):
    for i in range(1, 11):
        item = buffer.get()
        print(f"Consumer {id} consumed item: {item}")
        buffer.task_done()
        time.sleep(0.3)  

# Create producer threads
producer_threads = []
for i in range(2):  # Two producer threads
    t = threading.Thread(target=producer, args=(i + 1,))
    producer_threads.append(t)


consumer_threads = []
for i in range(2):  
    t = threading.Thread(target=consumer, args=(i + 1,))
    consumer_threads.append(t)


for t in producer_threads + consumer_threads:
    t.start()


for t in producer_threads + consumer_threads:
    t.join()
