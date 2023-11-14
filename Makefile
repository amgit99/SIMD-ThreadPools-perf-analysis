# Directories
EXEC_DIR = ./bin

# Compiler flags
CXX = g++-13
CXXFLAGS = -std=c++20 -Ofast

# Source files and corresponding object files
SRC := $(wildcard *.cpp)
EXECS := $(patsubst %.cpp, $(EXEC_DIR)/%, $(SRC))

# ****************************************************
# Targets needed to bring the executable up to date

all: $(EXECS)

$(EXEC_DIR)/% : %.cpp
	$(CXX) $(CXXFLAGS) -o ./$@ $<

clean: 
	rm -f ./bin/*