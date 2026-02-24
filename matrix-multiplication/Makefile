# ===== CONFIG =====
CXX = g++
SRC = src/main.cpp
OUT = build/matrix_multiplication

# ===== DEFAULT TARGET =====
all: $(OUT)

# ===== BUILD RULE =====
$(OUT): $(SRC)
	mkdir -p build
	$(CXX) $(SRC) -o $(OUT)

# ===== CLEAN =====
clean:
	rm -rf build
