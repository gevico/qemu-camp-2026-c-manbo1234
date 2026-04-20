CC = gcc
CFLAGS = -Wall -I../../include

TARGET := mysed
LIBNAME := mysed
LIB := lib$(LIBNAME).a
OBJDIR ?= ./obj
BINDIR ?= ../../bin
LIB_PATH := $(OBJDIR)/$(LIB)
BIN_PATH := $(BINDIR)/$(TARGET)

LIB_SRCS := mysed.c
LIB_OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(LIB_SRCS))
APP_SRCS := main.c
APP_OBJS := $(patsubst %.c,$(OBJDIR)/%.o,$(APP_SRCS))

all: $(LIB_PATH) $(BIN_PATH)

$(LIB_PATH): $(LIB_OBJS)
	@mkdir -p $(OBJDIR)
	ar rcs $@ $^

$(BIN_PATH): $(APP_OBJS) $(LIB_PATH)
	@mkdir -p $(BINDIR)
	$(CC) $(CFLAGS) -o $@ $(APP_OBJS) -L$(OBJDIR) -l$(LIBNAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	@rm -rf $(OBJDIR)/*.o $(LIB_PATH) $(BIN_PATH)

.PHONY: all clean
