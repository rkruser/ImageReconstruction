PATH := /usr/um/gcc-4.7.0/bin:$(PATH)
LD_LIBRARY_PATH := /usr/um/gcc-4.7.0/lib64
LD_RUN_PATH := /usr/um/gcc-4.7.0/lib64
#VPATH =  #Directories searched by make
debug: args = -g -std=c++11 -Wall -Wextra -pedantic -Wvla 
optimize: args = -O3 -std=c++11
# -funroll in optimize?
obj = main.o
inc = -Iimages

# Main targets
.PHONY: debug
.PHONY: optimize
debug: main.exe 
optimize: clean main.exe

# Test targets
main2: main2.cpp
	g++ -o main2.tst main2.cpp
test1: test1.cpp
	g++ -o test1.tst test1.cpp
test2: test2.cpp
	g++ -o test2.tst test2.cpp
test3: test3.cpp
	g++ -o test3.tst test3.cpp

#Dependencies of main targets
main.exe: $(obj)
	g++ -o main.exe $(inc) $(args) $(obj)
main.o: main.cpp defs.h
	g++ -c $(inc) $(args) main.cpp

# Clean results of main targets
.PHONY: clean
clean:
	rm -rf *.o *.exe

# Clean results of test targets
.PHONY: clean2
clean2:
	rm -rf *.tst
