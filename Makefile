all: compile

compile: lcs.cpp
	g++ lcs.cpp -o lcs

run: lcs
	./lcs input.txt output.txt
clean: lcs
	rm lcs
