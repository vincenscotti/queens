CC = g++
CFLAGS += -Wall -std=c++14

SOURCES = $(wildcard *.cpp)
OBJS = $(SOURCES:.cpp=.o)
EXEC = queens

all: $(OBJS)
	$(CC) $(OBJS) -o $(EXEC) $(LDFLAGS) $(CFLAGS)

clean:
	@rm -f $(OBJS) $(EXEC)

%.o: %.cpp
	$(CC) -c $< -o $@ $(CFLAGS)
