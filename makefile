all: geometry
helloworld: geometry.c
	gcc -Wall -Werror -o geometry geometry.c
