CXX 		:= g++
CXX_FLAGS 	:= -lboost_system -lboost_filesystem -std=c++14
SRC_DIR 	:= src
BUILD_DIR 	:= build
BIN_DIR		:= bin

.PHONY: all clean
all: directories $(BIN_DIR)/parser 

# 创建依赖文件和目标文件目录
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# 编译目标文件
$(BIN_DIR)/parser: $(BUILD_DIR)/parser.o $(BUILD_DIR)/parserOption.o
	$(CXX) -o $(BIN_DIR)/parser $(BUILD_DIR)/parser.o $(BUILD_DIR)/parserOption.o $(CXX_FLAGS)

# 编译依赖文件
$(BUILD_DIR)/parser.o: $(SRC_DIR)/parser.cpp
	$(CXX) -o $@ $^ -c $(CXX_FLAGS)

$(BUILD_DIR)/parserOption.o: $(SRC_DIR)/parserOption.cc
	$(CXX) -o $@ $^ -c $(CXX_FLAGS)

# 清除文件及所在目录
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)