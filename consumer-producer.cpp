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