CXX      = g++
CXXFLAGS = -std=c++17 -Iinclude
SRC      = src/board.cpp src/food.cpp src/game_controller.cpp src/snake.cpp

all: snake test_unit test_integration

snake: main.cpp $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

test_unit: tests/test_unit.cpp $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

test_integration: tests/test_integration.cpp $(SRC)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f snake test_unit test_integration
