#include <iostream>
#include <ctime>
#include <functional>
#include <omp.h>

const char USAGE_INFO[] = "Usage: <path to executable file> <monastery size>";

class Monk {
public:
    int energy{0};
    int monastery{0};
    Monk() {}
    explicit Monk(int i, int m) : energy(i), monastery(m) {}
};

Monk find_max(Monk *array, int size) {
    Monk m1, m2, res;
    if (size == 1) return array[0];
    int mid = size % 2 == 0 ? size / 2 : size / 2 + 1;
#pragma omp task shared(m1)
    m1 = find_max(array, mid);
#pragma omp task shared(m2)
    m2 = find_max(array + mid, mid);
#pragma omp taskwait 
{
    res = m1.energy >= m2.energy ? m1 : m2;
    std::cout << "[Thread " << omp_get_thread_num() << "]";
    std::cout << " Monk (" << m1.energy << ") from " << (m1.monastery == 0 ? "Guan-Yin" : "Guan-Yang");
    std::cout << " is fighting against Monk (" << m2.energy << ") from " << (m2.monastery == 0 ? "Guan-Yin" : "Guan-Yang");
    std::cout << ". The winner is Monk (" << res.energy << ") from " << (res.monastery == 0 ? "Guan-Yin." : "Guan-Yang.") << std::endl;
    return res;
}
}


int main(int argc, char *argv[]) {
    uint32_t size;
    int thread_number = omp_get_max_threads();
    srand(time(0));

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

    Monk *values = new Monk[size*2];

    for (int i = 0; i < size*2; i++) {
        values[i] = Monk(0 + rand() % 100, i % 2);
    }

    Monk thread_results[thread_number];

    uint32_t chunk_size = size * 2 / thread_number;

#pragma omp parallel
{
    for (int i = 0; i < thread_number; i++) {
        #pragma omp single
        {
            thread_results[i] = find_max(values + i * chunk_size, chunk_size);
        }
    }
}

    Monk winner = find_max(thread_results, thread_number);
    std::cout << (winner.monastery == 0 ? "Guan-Yin" : "Guan-Yang") << " has won the battle!" << std::endl;
}