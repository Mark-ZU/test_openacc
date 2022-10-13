CXX := g++
FLAG := -O3

ALL: COMPILE

COMPILE: mul_origin mul_acc

mul_origin: mul.cpp
	$(CXX) mul.cpp $(FLAG) -o mul_origin
mul_acc: mul.cpp
	$(CXX) -fopenacc -fcf-protection=none -fopt-info-optimized-omp mul.cpp $(FLAG) -o mul_acc

clean:
	rm -rf mul_origin mul_acc

test: COMPILE
	./mul_origin
	./mul_acc

# -foffload=nvptx-none="-fcf-protection=none" 