CXX = g++
CXXFLAGS = -Wall -Iinclude -std=c++20

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