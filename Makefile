all: monkeys install

monkeys: monkeys.c
	cc -o monkeys monkeys.c

install: monkeys
	sudo cp monkeys /usr/local/bin

clean:
	rm monkeys

.PHONY: all install clean
