# ---- config ----
VCPKG_ROOT := "C:/Users/piper/VS Code/idea-tagger/vcpkg"
TRIPLET    := x64-windows

CXX        := g++
CXXFLAGS   := -std=c++17 -O2 -Wall -Wextra -I$(VCPKG_ROOT)/installed/$(TRIPLET)/include
LDFLAGS    :=

# auto-detect all .cpp files in this directory
SRC := $(wildcard *.cpp)
OBJ := $(SRC:.cpp=.o)
BIN := idea_tagger.exe

# ---- rules ----
all: $(BIN)

$(BIN): $(OBJ)
	$(CXX) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(BIN)
	./$(BIN)

clean:
	-$(RM) $(OBJ) $(BIN)

.PHONY: all run clean
