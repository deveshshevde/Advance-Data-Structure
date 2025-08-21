
/* 

parallel → spawns threads

single / master → one-thread execution

for + reduction → parallel loop summing values

barrier → synchronize threads

atomic → safely update a shared counter

critical → protected section for I/O

sections → different tasks to different threads

task → independent tasks created dynamically

simd → vectorized loop scaling array

*/
#include <stdio.h>
#include <omp.h>

#define N 16

int main() {
    int i, sum = 0;
    int array[N];
    for (i = 0; i < N; i++) array[i] = i + 1;

    printf("Max threads available: %d\n", omp_get_max_threads());

    #pragma omp parallel num_threads(4) shared(array, sum) private(i)
    {
        int tid = omp_get_thread_num();

        // --- single / master ---
        #pragma omp single
        {
            printf("Single thread %d initializing work...\n", tid);
        }

        #pragma omp master
        {
            printf("Master thread %d reporting: team size = %d\n", tid, omp_get_num_threads());
        }

        // --- parallel for with reduction ---
        #pragma omp for reduction(+:sum) schedule(dynamic,2)
        for (i = 0; i < N; i++) {
            printf("Thread %d processing array[%d] = %d\n", tid, i, array[i]);
            sum += array[i];
        }

        // --- barrier ---
        #pragma omp barrier
        if (tid == 0) {
            printf("After loop, partial sum = %d\n", sum);
        }

        // --- atomic update ---
        static int counter = 0;
        #pragma omp atomic
        counter++;
        printf("Thread %d incremented counter to %d\n", tid, counter);

        #pragma omp barrier // just to sync this all !!

        // --- critical section ---
        #pragma omp critical
        {
            printf("Thread %d entering critical section. Counter = %d\n", tid, counter);
        }

        // --- sections ---
        #pragma omp sections
        {
            #pragma omp section
            printf("Thread %d doing Section A\n", tid);

            #pragma omp section
            printf("Thread %d doing Section B\n", tid);
        }

        // --- tasks ---
        #pragma omp single
        {
            #pragma omp task
            printf("Task 1 executed by thread %d\n", omp_get_thread_num());

            #pragma omp task
            printf("Task 2 executed by thread %d\n", omp_get_thread_num());
        }

        // --- SIMD loop ---
        #pragma omp simd
        for (i = 0; i < N; i++) {
            array[i] *= 2;
        }
    }

    printf("Final reduced sum = %d\n", sum);
    printf("Array after SIMD scaling:\n");
    for (i = 0; i < N; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}
