#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>

#define BUFFER_SIZE 5

// Buffer & synchronization variables
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

HANDLE empty;           // Semaphore for empty slots
HANDLE full;            // Semaphore for full slots
CRITICAL_SECTION mutex; // Mutex for buffer access

bool is_producer_turn = true; // State variable to control turn

// Function to insert an item into the buffer
void insertItem(int item)
{
    buffer[in] = item;
    in = (in + 1) % BUFFER_SIZE;
    std::cout << "Producer produced: " << item << std::endl;
}

// Function to remove an item from the buffer
int RemoveItem()
{
    int item = buffer[out];
    out = (out + 1) % BUFFER_SIZE;
    std::cout << "Consumer consumed: " << item << std::endl;
    return item;
}

// Producer thread function
DWORD WINAPI producer(LPVOID arg)
{
    int item;
    while (true)
    {
        item = rand() % 100;                  // Generate a random item
        WaitForSingleObject(empty, INFINITE); // Wait for an empty slot
        EnterCriticalSection(&mutex);         // Acquire the mutex lock

        // Check if it's producer's turn
        while (!is_producer_turn)
        {
            LeaveCriticalSection(&mutex); // Release lock and wait
            Sleep(10);
            EnterCriticalSection(&mutex);
        }

        insertItem(item);         // Insert the item into the buffer
        is_producer_turn = false; // Switch turn to consumer

        LeaveCriticalSection(&mutex);    // Release the mutex lock
        ReleaseSemaphore(full, 1, NULL); // Signal that a slot is full
        Sleep(1000 + (rand() % 500));    // Randomized delay for producer
    }
    return 0;
}

// Consumer thread function
DWORD WINAPI consumer(LPVOID arg)
{
    int item;
    while (true)
    {
        WaitForSingleObject(full, INFINITE); // Wait for a full slot
        EnterCriticalSection(&mutex);        // Acquire the mutex lock

        // Check if it's consumer's turn
        while (is_producer_turn)
        {
            LeaveCriticalSection(&mutex); // Release lock and wait
            Sleep(10);
            EnterCriticalSection(&mutex);
        }

        item = RemoveItem();     // Remove the item from the buffer
        is_producer_turn = true; // Switch turn to producer

        LeaveCriticalSection(&mutex);     // Release the mutex lock
        ReleaseSemaphore(empty, 1, NULL); // Signal that a slot is empty
        Sleep(900 + (rand() % 500));      // Randomized delay for consumer
    }
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        std::cerr << "Usage: " << argv[0] << " <sleep_time> <num_producers> <num_consumers>" << std::endl;
        return 1;
    }

    int sleep_time = atoi(argv[1]);
    int num_producers = atoi(argv[2]);
    int num_consumers = atoi(argv[3]);

    // Initialize random seed
    srand(static_cast<unsigned int>(time(NULL)));

    // Initialize semaphores and mutex
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL); // Initialize empty semaphore
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);            // Initialize full semaphore
    InitializeCriticalSection(&mutex);                             // Initialize mutex

    // Create producer threads
    HANDLE producers[num_producers];
    for (int i = 0; i < num_producers; i++)
    {
        producers[i] = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    }

    // Create consumer threads
    HANDLE consumers[num_consumers];
    for (int i = 0; i < num_consumers; i++)
    {
        consumers[i] = CreateThread(NULL, 0, consumer, NULL, 0, NULL);
    }

    // Sleep for the specified time
    Sleep(sleep_time * 1000);

    // Terminate the program
    std::cout << "Terminating the program..." << std::endl;

    // Clean up
    for (int i = 0; i < num_producers; i++)
    {
        CloseHandle(producers[i]);
    }
    for (int i = 0; i < num_consumers; i++)
    {
        CloseHandle(consumers[i]);
    }
    CloseHandle(empty);
    CloseHandle(full);
    DeleteCriticalSection(&mutex);

    return 0;
}