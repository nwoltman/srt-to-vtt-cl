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
EXEC_PATH = $(BIN_DIR)/$(EXEC)

.PHONY: test

all: $(EXEC)

$(EXEC): $(OBJECTS)
	mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC_PATH)

clean:
	rm -rf $(DEPENDS) $(OBJECTS)

cleanall:
	rm -rf $(DEPENDS) $(OBJECTS) $(EXEC_PATH)

test:
	./test/test.sh $(EXEC_PATH)

-include $(DEPENDS)
