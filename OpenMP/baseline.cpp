#include <benchmark/benchmark.h>
#include <random>
#include <vector>

static void baseline(benchmark::State &s) {
  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_real_distribution<float> dist(0.0f, 1.0f);

  const int num_elements = 1 << 23;
  std::vector<float> v_in(num_elements);
  std::generate(v_in.begin(), v_in.end(), [&] { return dist(mt); });

  std::vector<float> v_out(num_elements);

  for (auto _ : s) {
    for (int i = 0; i < num_elements; i++) {
      benchmark::DoNotOptimize(v_out[i] = v_in[i] * v_in[i]); /* Please compiler dont throw this line away :) */
    benchmark::ClobberMemory();
  }
}
}

BENCHMARK(baseline)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();