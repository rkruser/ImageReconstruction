include config.mk
VPATH = src:include:images:test #Directories searched by make
args = -g -std=c++11 -Wall -Wextra -pedantic -Wvla 
optimize: args = -O3 -std=c++11
# -funroll in optimize?
obj = main.o read.o naivenn.o makeSparse.o
inc = -Iimages -Iinclude

# Main targets
.PHONY: debug
.PHONY: optimize
debug: main.exe 
optimize: clean main.exe

#Test targets
test1: test1.cpp naivenn.h
	echo $@
	g++ -o test1.test $(args) $(inc) $< 
# $< provides name of first argument in its proper directory
test2:  test2.cpp defs.h
	g++ -o test2.test $(args) $(inc) $<
test3: test3.cpp defs.h sor.h
	g++ -o test3.test $(args) $(inc) $<
.PHONY: cleanTest
cleanTest:
	rm -f *.test test*.o

#Dependencies of main targets
main.exe: $(obj)
	g++ -o main.exe $(inc) $(args) $^
#  $^ lists all the prerequisites
main.o: main.cpp defs.h read.h naivenn.h makeSparse.h
	g++ -c $(inc) $(args) $<
read.o: read.cpp read.h defs.h 
	g++ -c $(inc) $(args) $<
naivenn.o: naivenn.cpp naivenn.h defs.h 
	g++ -c $(inc) $(args) $<
makeSparse.o: makeSparse.cpp defs.h makeSparse.h 
	g++ -c $(inc) $(args) $<

# Clean results of main targets
.PHONY: clean
clean:
	rm -f *.o *.exe

