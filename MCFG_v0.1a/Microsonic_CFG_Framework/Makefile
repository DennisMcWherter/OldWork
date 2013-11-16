# Makefile created by Microsonic Development
# for Microsonic Configuration Parser Framework
#

CC=g++
OBJS=Microsonic_CFG_Framework.o
CFLAGS=-Wall

Microsonic_CFG_Framework.o:
	$(CC) -c $(CFLAGS) Microsonic_CFG_Framework.cpp
all: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) MCFG_Example.cpp -o MCFG_Example
clean:
	rm -rf *.o
	rm -rf MCFG_Example
