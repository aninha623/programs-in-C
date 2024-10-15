#Makefile for midterm project
#anna andrade
#aandra12
#B4E772

#compiling tags
CC=gcc
CFLAGS= -std=c99 -pedantic -Wall -Wextra -g

#linking
project: project.o image_manip.o ppm_io.o
	$(CC) -o project project.o image_manip.o ppm_io.o

img_cmp: img_cmp.o image_manip.o ppm_io.o
	$(CC) -o img_cmp img_cmp.o image_manip.o ppm_io.o

checkerboard: checkerboard.o image_manip.o ppm_io.o
	$(CC) -o checkerboard project.o image_manip.o ppm_io.o

#compiling project/main execution block
project.o: project.c image_manip.h ppm_io.h
	$(CC) $(CFLAGS) -c project.c 

#compiling functions that are called in project
image_manip.o: image_manip.c image_manip.h ppm_io.h
	$(CC) $(CFLAGS) -c image_manip.c 

#compiling img_cmp
img_cmp.o: img_cmp.c ppm_io.h
	$(CC) $(CFLAGS) -c img_cmp.c

#compiles checkerboard
checkerboard.o: checkerboard.c ppm_io.h
	$(CC) $(CFLAGS) -c checkerboard.c

#compiles ppm_io
ppm_io.o: ppm_io.c ppm_io.h
	$(CC) $(CFLAGS) -c ppm_io.c

#remove intermediate files and executable called test to start anew
clean:
	rm -f *.o project