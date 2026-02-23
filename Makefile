CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC = src/main.cpp \
      src/Simulation.cpp \
      src/PriorityHeap.cpp \
      src/FIFOQueue.cpp \
	  src/Analytical.cpp

OBJ = $(SRC:.cpp=.o)

main: $(OBJ)
	$(CXX) $(CXXFLAGS) -o main $(OBJ)

src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o main