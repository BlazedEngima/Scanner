all:
	g++ main.cpp util/scanner.cpp -o scanner

test:
	g++ test.cpp util/scanner.cpp util/parser.cpp -o test

clean:
	rm scanner test