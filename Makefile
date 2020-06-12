all: lexer

CFLAGS := -Wall

lexer: lexer.o token.o
	$(CC) -o $@ $^

lexer.o: lexer.c
	$(CC) $(CFLAGS) -o $@ -c $<

token.o: token.c list.h
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f *.o tags lexer
