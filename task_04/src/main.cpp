#include <iostream>
#include <ctime>
#include <functional>
#include <omp.h>

const char USAGE_INFO[] = "Usage: <path to executable file> <array size>";

int find_max(int *array, int size) {
    int v1, v2, res;
    if (size == 1) return array[0];
    int mid = size % 2 == 0 ? size / 2 : size / 2 + 1;
#pragma omp task shared(v1)
    v1 = find_max(array, mid);
#pragma omp task shared(v2)
    v2 = find_max(array + mid, mid);
#pragma omp taskwait 
{
    res = v1 >= v2 ? v1 : v2;
    std::cout << "[Thread " << omp_get_thread_num() << "] Monk (" << v1 << ") is fighting against Monk (" << v2 << "). The winner is " << "Monk (" << res << ")" << std::endl; 
    return res;
}
}


int main(int argc, char *argv[]) {
    uint32_t size;
    int thread_number = omp_get_max_threads();

    if (argc != 2) {
        std::cout << USAGE_INFO << std::endl;
        return 1;
    }

    try {
        size = std::stoul(argv[1]);
    } catch (std::invalid_argument) {
        std::cout << USAGE_INFO << std::endl;
        return 1;
    }

    int *values = new int[size];

    for (int i = 0; i < size; i++) {
        values[i] = i + 1;
    }

    int thread_results[thread_number];

    uint32_t chunk_size = size / thread_number;

#pragma omp parallel
{
    for (int i = 0; i < thread_number; i++) {
        #pragma omp single
        {
            thread_results[i] = find_max(values + i * chunk_size, chunk_size);
        }
    }
}

    int winner = find_max(thread_results, thread_number);
    std::cout << "Monk (" << winner << ") has won the battle!" << std::endl;
}