PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64
VPATH = src:include:images:test #Directories searched by make
args = -g -std=c++11 -Wall -Wextra -pedantic -Wvla 
optimize: args = -O3 -std=c++11
# -funroll in optimize?
obj = main.o read.o naivenn.o makeSparse.o
inc = -Iimages -Iinclude
srcpath = src
testpath = test

# Main targets
.PHONY: debug
.PHONY: optimize
debug: main.exe 
optimize: clean main.exe

#Test targets
test: test.cpp naivenn.h
	g++ -o test.test $(args) $(inc) $(testpath)/test.cpp
test2:  test2.cpp defs.h
	g++ -o test2.test $(args) $(inc) $(testpath)/test2.cpp
test3: test3.cpp defs.h sor.h
	g++ -o test3.test $(args) $(inc) $(testpath)/test3.cpp
.PHONY: cleanTest
cleanTest:
	rm -f *.test test*.o

#Dependencies of main targets
main.exe: $(obj)
	g++ -o main.exe $(inc) $(args) $(obj)
main.o: main.cpp defs.h read.h naivenn.h makeSparse.h
	g++ -c $(inc) $(args) $(srcpath)/main.cpp
read.o: read.h defs.h read.cpp
	g++ -c $(inc) $(args) $(srcpath)/read.cpp
naivenn.o: naivenn.h defs.h naivenn.cpp
	g++ -c $(inc) $(args) $(srcpath)/naivenn.cpp
makeSparse.o: defs.h makeSparse.h makeSparse.cpp
	g++ -c $(inc) $(args) $(srcpath)/makeSparse.cpp

# Clean results of main targets
.PHONY: clean
clean:
	rm -f *.o *.exe

