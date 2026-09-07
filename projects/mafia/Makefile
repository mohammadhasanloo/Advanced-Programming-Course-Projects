CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
LDFLAGS  ?= 

TARGET  := mafia
SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -Isrc -MMD -MP -c $< -o $@

-include $(OBJECTS:.o=.d)

clean:
	rm -rf build $(TARGET)

.PHONY: all clean
