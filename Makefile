PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64
#VPATH =  #Directories searched by make
args = -g -std=c++11 -Wall -Wextra -pedantic -Wvla 
optimize: args = -O3 -std=c++11
# -funroll in optimize?
obj = main.o read.o naivenn.o makeSparse.o
inc = -Iimages

# Main targets
.PHONY: debug
.PHONY: optimize
debug: main.exe 
optimize: clean main.exe

#Test targets
test: test.cpp defs.h
	g++ -o test.test $(args) $(inc) test.cpp
.PHONY: cleanTest
cleanTest:
	rm -rf *.test

#Dependencies of main targets
main.exe: $(obj)
	g++ -o main.exe $(inc) $(args) $(obj)
main.o: main.cpp defs.h read.h naivenn.h makeSparse.h
	g++ -c $(inc) $(args) main.cpp
read.o: read.h defs.h read.cpp
	g++ -c $(inc) $(args) read.cpp
naivenn.o: naivenn.h defs.h naivenn.cpp
	g++ -c $(inc) $(args) naivenn.cpp
makeSparse.o: defs.h makeSparse.h makeSparse.cpp
	g++ -c $(inc) $(args) makeSparse.cpp

# Clean results of main targets
.PHONY: clean
clean:
	rm -rf *.o *.exe

