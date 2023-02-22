#include <iostream>
#include <vector>

#include <pthread.h>

int a = 0;

void* TBC1(void*)
{
    int& b = a;
    b += 10;
    return NULL;
}

void* TBC2(void*)
{
    int& b = a;
    b += 10;
    return NULL;
}

int main() 
{
    pthread_t thread_1, thread_2;

    pthread_create(&thread_1, NULL, TBC1, NULL);
    pthread_create(&thread_2, NULL, TBC2, NULL);

    std::cout << ::a;

    return 0;
}
