CC = gcc
CFLAGS = -W
TARGET = math

$(TARGET) : main.o db.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o db.o -lsqlite3

main.o : main.c main.h config.h
	$(CC) $(CFLAGS) -c -o main.o main.c

db.o : db.c db.h config.h
	$(CC) $(CFLAGS) -c -o db.o db.c

clean :
	rm *.o math
