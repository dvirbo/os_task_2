CC = gcc
FLAGS= -Wall -Werror -g

all: signals
run: signals
	./$^
signals: signals.c
	$(CC)  signals.c -o signals

clean:
	rm signals