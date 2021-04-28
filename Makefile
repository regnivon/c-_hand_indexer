DEFAULT_GOAL := $(BUILD_DIR)/$(TARGET_EXEC)

TARGET_EXEC ?= main

TEST_EXEC ?= runTests

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src

SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

TEST_SRCS := $(shell find ./src ./test -name *.cpp -or -name *.c -or -name *.s)
TEST_OBJS := $(TEST_SRCS:%=$(BUILD_DIR)/%.o)

CXX := g++

INC_DIRS ?= ./inc
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP -std=c++14

LDFLAGS ?= -Llib -lgtest -lgtest_main -lpthread -lindexer

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

$(BUILD_DIR)/$(TEST_EXEC): $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $@ $(LDFLAGS)

# assembly
$(BUILD_DIR)/%.s.o: %.s
	$(MKDIR_P) $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

build_tests:
	docker build -f docker/Dockerfile . -t indexer-tests

run_tests: build_tests
	docker run --rm indexer-tests


.PHONY: clean run_tests

clean:
	$(RM) -r $(BUILD_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
