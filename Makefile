ERR = $(shell which clang++ >/dev/null; echo $$?)
ifeq "$(ERR)" "0"
	CXX ?= clang++
else
	CXX ?= g++
endif
CXXFLAGS = -std=c++11 -O2 -MMD -I ./deps
OBJECTS := src/text_encoding_detect.o src/Utils.o src/Converter.o src/main.o
DEPENDS := $(OBJECTS:.o=.d)
EXEC = srt-vtt
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	BIN_DIR = bin/Mac-OSX
else
	UNAME_M := $(shell uname -m)
	BIN_DIR = bin/$(UNAME_S)/$(UNAME_M)
endif

all: $(EXEC)

$(EXEC): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN_DIR)/$(EXEC)

clean:
	rm -rf $(DEPENDS) $(OBJECTS)

cleanall:
	rm -rf $(DEPENDS) $(OBJECTS) $(BIN_DIR)/$(EXEC)

-include $(DEPENDS)
