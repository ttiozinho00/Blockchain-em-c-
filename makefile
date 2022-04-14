TARGET_EXEC ?= blockchain

BUILD_DIR ?= ./build
SRC_DIRS ?= ./src
TARGET_DIR ?= ./bin

SRCS := $(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIRS := $(shell find $(SRC_DIRS) -type d) ../../libbitcoin/include
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

LIB_DIRS := -L ../../libbitcoin/lib -lbitcoin -lboost_program_options -lboost_atomic -lboost_regex -lboost_system

CPPFLAGS ?= $(INC_FLAGS) $(LIB_DIRS) -MMD -MP -std=c++14 -O3

$(TARGET_DIR)/$(TARGET_EXEC): $(OBJS)
	$(MKDIR_P) $(dir $@)
	$(CXX) $(OBJS) $(LIB_DIRS) -o $@ $(LDFLAGS)

# c source
$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(dir $@)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# c++ source
$(BUILD_DIR)/%.cpp.o: %.cpp
	$(MKDIR_P) $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


.PHONY: clean

run:
	$(TARGET_DIR)/$(TARGET_EXEC)

clean:
	$(RM) -r $(BUILD_DIR)
	$(RM) -r $(TARGET_DIR)

-include $(DEPS)

MKDIR_P ?= mkdir -p
