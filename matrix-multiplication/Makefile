# ===== CONFIG =====
CXX = g++
CXXFLAGS = -O3 -march=native -flto -std=c++17
SRC = src/main.cpp
OUT = build/matrix_multiplication_opt_ikj_loop_order

# ===== DEFAULT TARGET =====
all: $(OUT)

# ===== BUILD RULE =====
$(OUT): $(SRC)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT)

# ===== CLEAN =====
clean:
	rm -rf build
