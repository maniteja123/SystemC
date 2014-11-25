# Simple Makefile
TARGET = run_me
SYSTEMC = $(SYSTEMC_HOME)
INCDIR = -I. -I$(SYSTEMC)/include
LIBDIR = -L. -L$(SYSTEMC)/lib-linux
LIBS   = -lsystemc -lm

CC     = g++
CFLAGS = -g -Wno-deprecated -Wall

OBJS   = sc_main.o

EXE    = $(TARGET)

all: $(EXE)

$(EXE): $(OBJS)  
	$(CC) $(CFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS) $(LIBS) 2>&1

sc_main.o:	sc_main.cpp module.h
	$(CC) $(CFLAGS) $(INCDIR) -c $<

clean:
	rm -f $(OBJS) $(EXE) *.vcd

