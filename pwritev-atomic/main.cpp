#include <thread>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <atomic>
#include <sys/uio.h>
#include <cstring>
#include "fcntl.h"

using namespace std;

constexpr int buffer_size = 4 * 1024;
constexpr int num_threads = 8;

int main() {
    int fd = open("test", O_TRUNC | O_CREAT | O_WRONLY);
    void* buffers[num_threads];
    for (int i = 0; i < num_threads; ++i) {
        buffers[i] = malloc(buffer_size);
        memset(buffers[i], i, buffer_size);
    }
    write(fd, buffers[0], buffer_size);
    fsync(fd);
    std::atomic<bool> stop_flag(false);
    new std::thread([&] {
        sleep(3);
        stop_flag = true;
    });
    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back([&](int index) {
            while (true) {
                if (stop_flag) break;
                iovec iov{buffers[index], buffer_size};
                pwritev(fd, &iov, 1, 0);
            }
        }, i);
    }
    for (auto& th : threads) {
        th.join();
    }
}
