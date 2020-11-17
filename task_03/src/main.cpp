#include <iostream>
#include <thread>
#include <ctime>

const char USAGE_INFO[] = "Usage: <path to executable file> <array size> <min value> <max value> <threads number>";

int find_max(int *array, int size) {
    if (size == 1) return array[0];
    int mid = size % 2 == 0 ? size / 2 : size / 2 + 1;
    int v1 = find_max(array, mid);
    int v2 = find_max(array + mid, mid);
    return v1 >= v2 ? v1 : v2;
}

void find_thread(int *array, int size, int &thread_result) {
    thread_result = find_max(array, size);
}

int main(int argc, char *argv[]) {
    uint32_t size, thread_number, min, max;

    if (argc != 5) {
        std::cout << USAGE_INFO << std::endl;
        return 1;
    }

    try {
        size = std::stoul(argv[1]);
        min = std::stoi(argv[2]);
        max = std::stoi(argv[3]);
        thread_number = std::stoi(argv[4]);
    } catch (std::invalid_argument) {
        std::cout << USAGE_INFO << std::endl;
        return 1;
    }

    int* values = new int[size];

    for (int i = 0; i < size; i++) {
        values[i] = rand() % (max - min + 1) + min;
    }

    std::thread *threads[thread_number];
    int thread_results[thread_number];

    clock_t start_time = clock();

    uint32_t chunk_size = size / thread_number;
    for (int i = 0; i < thread_number; i++) {
        threads[i] = new std::thread{find_thread, values + i * chunk_size, chunk_size, std::ref(thread_results[i])};
    }

    for (int i = 0; i < thread_number; i++) {
        threads[i]->join();
        delete threads[i];
    }

    std::cout << "Maximum value = " << find_max(thread_results, thread_number) << std::endl;
    clock_t end_time = clock();
    std::cout << "Time = " << end_time - start_time << "\n";
}