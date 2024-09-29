CXX = g++
CXXFLAGS = -Iinclude -Wall -std=c++11

SRC = src/main.cpp src/RocketStage.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = RocketSimulation

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

clean:
	rm -f $(OBJ) $(TARGET)
