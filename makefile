all: helloworld
helloworld: helloworld.c
	gcc -Wall -Werror -o helloworld helloworld.c
