PROGNAME = disko
TARGET ?= linux

CXX = g++
CXXFLAGS = 

LD = g++
LDFLAGS =

BUILD_DIR = build
SRC_DIR = src
INC_DIR = $(SRC_DIR)/include

CXXSRCS = $(wildcard $(SRC_DIR)/*.cpp)
CXXSRCS_SUBS = $(wildcard $(SRC_DIR)/*/*.cpp)
CXXSRCS_PLATFORM = $(wildcard $(SRC_DIR)/platform/$(TARGET)/*.cpp)

CXXOBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/cpp/%.o, $(CXXSRCS))
CXXOBJS += $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/cpp/%.o, $(CXXSRCS_SUBS))
CXXOBJS += $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/cpp/%.o, $(CXXSRCS_PLATFORM))

.PHONY: run

run: link

link: $(CXXOBJS)
	@printf "Linking\n"
	$(LD) \
	$(LDFLAGS) \
	-o $(BUILD_DIR)/$(PROGNAME) $^ \
	-lgcc \
	-lstdc++
	
$(BUILD_DIR)/cpp/%.o: $(SRC_DIR)/%.cpp
	@printf "Compiling $^\n"
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $^ -I$(INC_DIR)


clean:
	rm -rf $(BUILD_DIR)/**