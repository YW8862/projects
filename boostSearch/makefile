CXX        := g++
CXX_FLAGS  := -lboost_system -lboost_filesystem -std=c++14
SRC_DIR    := src
BUILD_DIR  := build
BIN_DIR    := bin
UTILS_DIR  := utils
INCLUDE_DIR:= include

.PHONY: all clean
all: directories $(BIN_DIR)/parser $(BIN_DIR)/server

# 创建目录
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# 编译 parser
$(BIN_DIR)/parser: $(BUILD_DIR)/parser.o $(BUILD_DIR)/parserOption.o $(BUILD_DIR)/utils.o
	$(CXX) -o $(BIN_DIR)/parser $^ $(CXX_FLAGS)

$(BUILD_DIR)/parser.o: $(SRC_DIR)/parser.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/parserOption.o: $(SRC_DIR)/utils/parserOption.cc
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# 修正后的 utils.o 规则
$(BUILD_DIR)/utils.o: $(SRC_DIR)/$(UTILS_DIR)/utils.cc $(INCLUDE_DIR)/$(UTILS_DIR)/utils.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# 编译 server
$(BIN_DIR)/server: $(BUILD_DIR)/server.o $(BUILD_DIR)/searcher.o $(BUILD_DIR)/index.o $(BUILD_DIR)/utils.o
	$(CXX) -o $@ $^ $(CXX_FLAGS) -ljsoncpp

$(BUILD_DIR)/server.o: $(SRC_DIR)/server.cpp $(INCLUDE_DIR)/searcher.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/index.o: $(SRC_DIR)/$(UTILS_DIR)/index.cc $(INCLUDE_DIR)/$(UTILS_DIR)/utils.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/searcher.o: $(SRC_DIR)/searcher.cc $(INCLUDE_DIR)/$(UTILS_DIR)/index.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# 清理
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
