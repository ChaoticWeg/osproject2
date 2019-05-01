#!/usr/bin/env make

CC=g++ --std=c++11
CFLAGS=-Werror -Wall

INCDIR=./include
LIBDIR=./lib
SRCDIR=./src

.PHONY: dirs all clean

all: clean dirs main

main: $(LIBDIR)/libprocess.so $(SRCDIR)/memory.cpp $(SRCDIR)/cpu.cpp $(SRCDIR)/runqueue.cpp $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -I$(INCDIR) -L$(LIBDIR) -lprocess -o $@ $(SRCDIR)/cpu.cpp $(SRCDIR)/runqueue.cpp $(SRCDIR)/memory.cpp $(SRCDIR)/main.cpp

$(LIBDIR)/libprocess.so: $(SRCDIR)/process.cpp
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

dirs:
	-@mkdir -p lib

clean:
	-@rm -rf $(LIBDIR)
	-@rm -f main
	-@make dirs
