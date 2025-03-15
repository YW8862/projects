CXX        := g++
CXX_FLAGS  := -std=c++14
LDFLAGS    := -lboost_system -lboost_filesystem -lpthread -ljsoncpp

SRC_DIR    := src
BUILD_DIR  := build
BIN_DIR    := bin
UTILS_DIR  := utils
INCLUDE_DIR:= include

.PHONY: all clean
all: directories $(BIN_DIR)/parser $(BIN_DIR)/debug $(BIN_DIR)/httpServer

# 创建目录
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)

# 编译 parser 可执行文件
$(BIN_DIR)/parser: $(BUILD_DIR)/parser.o $(BUILD_DIR)/parserOption.o $(BUILD_DIR)/utils.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/parser.o: $(SRC_DIR)/parser.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/parserOption.o: $(SRC_DIR)/$(UTILS_DIR)/parserOption.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/utils.o: $(SRC_DIR)/$(UTILS_DIR)/utils.cpp $(INCLUDE_DIR)/$(UTILS_DIR)/utils.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# 编译 debug 可执行文件
$(BIN_DIR)/debug: $(BUILD_DIR)/debug.o $(BUILD_DIR)/searcher.o $(BUILD_DIR)/index.o $(BUILD_DIR)/utils.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/debug.o: $(SRC_DIR)/debug.cpp $(INCLUDE_DIR)/searcher.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/index.o: $(SRC_DIR)/$(UTILS_DIR)/index.cpp $(INCLUDE_DIR)/$(UTILS_DIR)/index.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/searcher.o: $(SRC_DIR)/searcher.cpp $(INCLUDE_DIR)/$(UTILS_DIR)/index.h
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# 编译 httpServer 可执行文件
$(BIN_DIR)/httpServer: $(BUILD_DIR)/httpServer.o $(BUILD_DIR)/searcher.o $(BUILD_DIR)/index.o $(BUILD_DIR)/utils.o $(BUILD_DIR)/log.o
	$(CXX) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/httpServer.o: $(SRC_DIR)/httpServer.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

$(BUILD_DIR)/log.o: $(SRC_DIR)/$(UTILS_DIR)/log.cpp
	$(CXX) $(CXX_FLAGS) -c $< -o $@

# 清理构建文件
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)
