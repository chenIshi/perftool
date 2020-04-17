CC = g++
INC_LIB = /usr/local/include
CFLAGS = -fpermissive
EXEC = prime

ALL: EXEC
	

# g++ -I/usr/local/include -O0 -fpermissive prime_sieve-64.c perftool.cpp /usr/local/lib/libpapi.a -o prime
EXEC: prime_sieve-64.c perftool.cpp /usr/local/lib/libpapi.a
	$(CC) -I$(INC_LIB) $(CFLAGS) $< -o $@


.PHONY : clean

clean:
	rm $(EXEC) *.o
