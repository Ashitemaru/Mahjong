CXX = g++
CXXFLAGS = -Wall -std=c++17

SRC = $(wildcard src/*.cpp)
OBJ = $(addprefix tmp/, $(notdir $(SRC:.cpp=.o)))

TARGET = game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $^ -o $@

tmp/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f tmp/*.o $(TARGET)

.PHONY: all clean