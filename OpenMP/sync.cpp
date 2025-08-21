#include <cassert>

int main() {
    const int num_iterations = 1 << 20;
    const int num_threads = 8;
    const int iterations_per_thread = num_iterations / num_threads;

    int sink = 0;

    #pragma omp parallel num_threads(8)
    {
        for(int i = 0; i < iterations_per_thread; i++) {
            #pragma omp critical
            sink++;
        }

    }
    assert(sink == num_iterations);
    return 0;
}