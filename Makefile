
CXX = g++-13
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra -Wpedantic
TARGET = code
SOURCES = main.cpp

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: clean

