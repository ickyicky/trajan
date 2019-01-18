FLAGS  = -std=c++11
SRCS   = simple_graph.cpp main.cpp
OBJS   = $(subst .cpp,.o,$(SRCS))

all: $(OBJS)
	g++ $(OBJS) $(LFLAGS) -o program.x

main.o: main.cpp simple_graph.h
	g++ $(LFLAGS) -c main.cpp

simple_graph.o: simple_graph.cpp simple_graph.h
	g++ $(LFLAGS) -c simple_graph.cpp

clean:
	rm -f *.o *.x
