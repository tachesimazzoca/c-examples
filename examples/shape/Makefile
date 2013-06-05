CC = gcc
CFLAGS =
LDFLAGS =
INCLUDES =
LIBS = -lm
OBJS = main.o shape.o

TARGET = example-shape

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@rm -f $(TARGET) $(OBJS)

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c $<
