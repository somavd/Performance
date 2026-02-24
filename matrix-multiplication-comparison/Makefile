CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = matrix_benchmark
TARGET_OPT = matrix_benchmark_opt
SRC_DIR = src
BUILD_DIR = build

.PHONY: all clean benchmark benchmark-opt

all: $(BUILD_DIR) $(TARGET) $(TARGET_OPT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET): $(SRC_DIR)/StrassensVsIterative.cpp
	$(CXX) $(CXXFLAGS) -o $(BUILD_DIR)/$(TARGET) $(SRC_DIR)/StrassensVsIterative.cpp

$(TARGET_OPT): $(SRC_DIR)/StrassensVsIterative.cpp
	$(CXX) $(CXXFLAGS) -O3 -o $(BUILD_DIR)/$(TARGET_OPT) $(SRC_DIR)/StrassensVsIterative.cpp

benchmark: $(TARGET)
	./$(BUILD_DIR)/$(TARGET) > results/benchmark_results.txt

benchmark-opt: $(TARGET_OPT)
	./$(BUILD_DIR)/$(TARGET_OPT) > results/benchmark_results_optimized.txt

clean:
	rm -rf $(BUILD_DIR)
	rm -f results/*.txt

help:
	@echo "Available targets:"
	@echo "  all          - Build both optimized and unoptimized versions"
	@echo "  benchmark    - Run unoptimized benchmark and save results"
	@echo "  benchmark-opt- Run optimized benchmark and save results"
	@echo "  clean        - Remove build artifacts and results"
	@echo "  help         - Show this help message"
