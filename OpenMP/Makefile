CXX = clang++
CXXFLAGS = -std=c++17 -O2 -I/opt/homebrew/include 
LDFLAGS = -L/opt/homebrew/lib -lbenchmark -lpthread

OMP_CXX = /opt/homebrew/opt/llvm/bin/clang++
OMP_FLAGS = -std=c++17 -O2 -fopenmp -I/opt/homebrew/include
OMP_LDFLAGS = -L/opt/homebrew/lib -lbenchmark -lpthread -L/opt/homebrew/opt/llvm/lib -fopenmp

TARGETS = baseline_seq baseline_omp

all: $(TARGETS)

baseline_seq: baseline.cpp
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

baseline_omp: baseline_with_omp.cpp
	$(OMP_CXX) $(OMP_FLAGS) $< -o $@ $(OMP_LDFLAGS)

run: all
	./baseline_seq
	./baseline_omp

clean:
	rm -f $(TARGETS)
