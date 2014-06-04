CC = gcc
CFLAGS =
LDFLAGS =
INCLUDES =
LIBS = -lz
OBJS = main.o

TARGET = example-zip

all: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	@rm -f $(TARGET) $(OBJS)

.c.o:
	@$(CC) $(CFLAGS) $(INCLUDES) -c $<
