CXX = g++
CXXFLAGS = -g -std=c++11 -O2 -MMD -I ./include
OBJECTS = text_encoding_detect.o Utils.o Converter.o main.o
DEPENDS = $(OBJECTS:.o=.d)
EXEC = srt-vtt
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
	BIN = ../bin/Mac-OSX
else
	UNAME_M := $(shell uname -m)
	BIN = ../bin/$(UNAME_S)/$(UNAME_M)
endif

all: $(EXEC)

$(EXEC) : $(OBJECTS)
	mkdir -p $(BIN)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(BIN)/$(EXEC)

clean :
	rm -rf $(DEPENDS) $(OBJECTS)

cleanall :
	rm -rf $(DEPENDS) $(OBJECTS) $(BIN)/$(EXEC)

-include $(DEPENDS)
