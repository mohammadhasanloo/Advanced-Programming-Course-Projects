CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

# SDL2 lives in a different place on every platform; sdl2-config knows where.
# The prefix include is needed as well because the sources ask for <SDL2/SDL.h>
# while sdl2-config points straight at the SDL2 directory itself.
SDL_PREFIX := $(shell sdl2-config --prefix 2>/dev/null)
SDL_CFLAGS := $(shell sdl2-config --cflags 2>/dev/null) $(if $(SDL_PREFIX),-I$(SDL_PREFIX)/include)
SDL_LIBS   := $(shell sdl2-config --libs 2>/dev/null || echo -lSDL2)

TARGET  := soccer-stars
SOURCES := $(shell find src -name '*.cpp')
OBJECTS := $(SOURCES:src/%.cpp=build/%.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ $(SDL_LIBS) -lSDL2_image -lSDL2_ttf -lSDL2_mixer $(LDFLAGS) -o $@

build/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) $(SDL_CFLAGS) -Isrc -MMD -MP -c $< -o $@

-include $(OBJECTS:.o=.d)

clean:
	rm -rf build $(TARGET)

.PHONY: all clean
