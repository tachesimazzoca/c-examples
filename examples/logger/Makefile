CC = gcc
CFLAGS =
LDFLAGS =
INCLUDES =
LIBS =
OBJS = main.o

TARGET = example-logger

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@rm -f $(TARGET) $(OBJS)

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c $<

main.o: logger/inline.h logger/macro.h
