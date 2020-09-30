TARGET = test.exe
OBJS = main.o  
CC = g++
CFLAGS = -c -Wall -g -std=c++11
LFLAGS = -Wall -g
#CFLAGS = -c -Wall -O3 -DNDEBUG -std=c++11
#LFLAGS = -Wall  -O3 -DNDEBUG

$(TARGET): $(OBJS)
	$(CC) $(LFLAGS)  $(OBJS) -o $(TARGET)

main.o: main.cpp  gd.h gd.cpp
	$(CC) $(CFLAGS) main.cpp gd.cpp


.PHONY: clean
clean:
	rm -f  $(OBJS) $(TARGET) 

.PHONY: cleanObject
cleanObject:
	rm -f  $(OBJS)

