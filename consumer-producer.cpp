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

        insertItem(item);        // Insert the item into the buffer
        is_producer_turn = false; // Switch turn to consumer

        LeaveCriticalSection(&mutex);    // Release the mutex lock
        ReleaseSemaphore(full, 1, NULL); // Signal that a slot is full
        Sleep(1000 + (rand() % 500));    // Randomized delay for producer
    }
    return 0;
}