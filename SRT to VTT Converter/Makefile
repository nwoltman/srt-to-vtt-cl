CXX = g++
CXXFLAGS = -g -std=c++11 -O2 -MMD -I ./include
OBJECTS = Utils.o Converter.o main.o
DEPENDS = $(OBJECTS:.o=.d)
EXEC = ../bin/Mac-OSX/srt-vtt

$(EXEC) : $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXEC)

clean :
	rm -rf $(DEPENDS) $(OBJECTS)

cleanall :
	rm -rf $(DEPENDS) $(OBJECTS) $(EXEC)

-include $(DEPENDS)
