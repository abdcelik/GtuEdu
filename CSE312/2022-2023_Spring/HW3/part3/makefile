CXX		:= g++
CXXFLAGS:= -std=c++11 -Wall -pedantic

SRC		:= $(wildcard src/*.cpp)
INCLUDE	:= -Iinclude
EXEC	:= fileSystemOper

OBJ_DIR	:= obj
OBJ		:= $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(EXEC)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -MMD -o $@

$(EXEC): $(OBJ)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $^

.PHONY: all build clean

build:
	@mkdir -p $(OBJ_DIR)

clean:
	-@rm -rvf $(OBJ_DIR)
	-@rm -rvf $(EXEC)