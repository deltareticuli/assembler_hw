#include <pthread.h>
#include <unistd.h>
#include <ctime>
#include <string>
#include <stdexcept>

unsigned int pot = 0; // горшок меда - сначала пустой
unsigned int capacity; // вместимость горшка меда - задается через аргументы командной строки
unsigned int beesNumber; // число пчел - задается через аргументы командной строки
unsigned int iterations; // число итераций - задается через аргументы командной строки

pthread_mutex_t mutex; // мьютекс для условных переменных
pthread_cond_t bees; // условная переменная для блокировки потоков пчел
pthread_cond_t bear; // условная переменная для блокировки потока медведя

clock_t start_time;

const char *USAGE_INFO = "Usage: <path to executable file> <capacity of honey pot 1-65535> <number of bees 1-65535> <number of iterations 1-65535>";

[[noreturn]] void *Bee(void *id) {
    int beeId = *((int *) id);
    while (true) {
        pthread_mutex_lock(&mutex);

        // засыпаем, если горшок меда полон
        while (pot == capacity) {
            pthread_cond_wait(&bees, &mutex);
        }

        // добавляем один глоток меда в горшок
        pot++;

        printf("[%.4f] Bee %d puts 1 sip of honey into the pot (%d/%d).\n",
               ((double) (clock() - start_time) / CLOCKS_PER_SEC),
               beeId, pot, capacity);

        // если горшок меда полон, то будим медведя
        if (pot == capacity) {
            printf("[%.4f] The pot is full. Bee %d wakes up the bear.\n",
                   ((double) (clock() - start_time) / CLOCKS_PER_SEC), beeId);
            pthread_cond_broadcast(&bear);
        }

        // конец критической секции
        pthread_mutex_unlock(&mutex);

        // 2 секунды - время, спустя которое одна пчела соберет и положит очередную порцию меда
        sleep(2);
    }
}

void *Bear(void *id) {
    for (int i = 0; i < iterations; ++i) {
        pthread_mutex_lock(&mutex);

        // засыпаем, пока горшок меда не будет полон
        while (pot != capacity) {
            printf("[%.4f] The bear is sleeping until the pot is full...\n",
                   ((double) (clock() - start_time) / CLOCKS_PER_SEC));
            pthread_cond_wait(&bear, &mutex);
        }

        // медведь съедает весь мед
        pot = 0;

        printf("[%.4f] The bear woke up and ate all the honey.\n",
               ((double) (clock() - start_time) / CLOCKS_PER_SEC));

        printf("[%.4f] The bear fell asleep again. The bees begin to collect honey.\n",
               ((double) (clock() - start_time) / CLOCKS_PER_SEC));

        // конец критической секции
        pthread_mutex_unlock(&mutex);

        // так как горшок меда теперь пуст, нужно разбудить пчел
        pthread_cond_broadcast(&bees);
        sleep(4);
    }
    return nullptr;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf(USAGE_INFO);
        return 0;
    }

    try {
        capacity = static_cast<unsigned int>(std::stoul(argv[1]));
        beesNumber = static_cast<unsigned int>(std::stoul(argv[2]));
        iterations = static_cast<unsigned int>(std::stoul(argv[3]));
    } catch (const std::invalid_argument&) {
        printf(USAGE_INFO);
        return 0;
    }

    if (capacity < 1 || capacity > 65535 || beesNumber < 1 || beesNumber > 65535 || iterations < 1 ||
        iterations > 65535) {
        printf(USAGE_INFO);
        return 0;
    }

    // инициализируем мьютекс и условные переменные
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&bees, nullptr);
    pthread_cond_init(&bear, nullptr);

    start_time = clock();

    // создаем и запускаем производителей - пчел
    pthread_t beeThreads[beesNumber];
    int producers[beesNumber];
    for (int i = 0; i < beesNumber; i++) {
        producers[i] = i + 1;
        pthread_create(&beeThreads[i], nullptr, Bee, (void *) (producers + i));
    }

    // создаем и запускаем потребителя - медведя в главном потоке
    int bearId = 0;
    Bear((void *) &bearId);

    // все итерации - пробуждения медведя прошли, программа завершается.
    printf("Number of iterations exceeded maximum.\n");
    return 0;
}
