all: dirinfo.o
	gcc -o dirinfo dirinfo.c
main.o: dirinfo.c
	gcc -c dirinfo.c
run:
	./dirinfo
