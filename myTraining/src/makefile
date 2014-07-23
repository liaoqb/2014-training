CC=g++
CFLAGS=-c -Wall -std=c++11
LDFLAGS=-lpthread
SOURCES=Date.cpp User.cpp Meeting.cpp Storage.cpp AgendaService.cpp AgendaUI.cpp Agenda.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=a.out

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm *.o $(EXECUTABLE)
