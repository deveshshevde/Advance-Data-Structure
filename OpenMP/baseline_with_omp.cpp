#include <benchmark/benchmark.h>

#include <random>
#include <vector>

static void baseline(benchmark::State &s) {

  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution dist(0.0f, 1.0f);

  const int num_elements = 1 << 23;
  std::vector<float> v_in;
  std::generate_n(std::back_inserter(v_in), num_elements,[&] { return dist(mt); });

  std::vector<float> v_out(num_elements);

  for (auto _ : s) {
    [[ omp::sequence(directive(parallel), directive(for)) ]]
    for (int i = 0; i < num_elements; i++) {
      v_out[i] = v_in[i] * v_in[i];
    }
  }
}
BENCHMARK(baseline)->Unit(benchmark::kMicrosecond)->UseRealTime();

BENCHMARK_MAIN();