CC      = g++
CPPFLAGS= -Wno-deprecated -O3 -c -m64 -std=c++11
LDFLAGS = -O3
SOURCES = temporalChainRank.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE=temporalChainRank

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o : 
	$(CC) $(CPPFLAGS) $< -o $@

rm:
	rm -f *.o

