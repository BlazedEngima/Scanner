# Simplified C Scanner
This is a scanner/lexical analyzer for the simplified C language written in
C++.

## NFA Design

The NFA was designed taking into consideration of tokens and language of the simplified C language.
![[NFA.png]](https://imgur.com/o9fpEcG)
This is the rough NFA that detects for tokens for the simplified C language. Do note that the NFA is not implemented/present in code. It is only used to guide the creation of the DFA which is used.

## DFA Design

The DFA was designed after getting the rough NFA. 
![[DFA.png]](https://imgur.com/dUNt9E2)
This is what the rough DFA looks like. This DFA is what is implicitly hardcoded into the scanner.

## Scanner Design

A class is used to encapsulate the scanner. It takes the address of a vector in its construction and after scanning, will fill the vector with tokens from the input file.
```Scanner class
class Scanner {
    private:
        std::ifstream in_file; // input file
        std::vector<Token> *out_vector; // pointer to output vector;
        char cur_char; // current character pointer
        std::string char_buffer; // character buffer to analyze tokens

        // Member functions
        Token read_number();
        Token read_string();
        Token read_special_symbol();

    public:
        // Ban copying and assignment
        Scanner(Scanner const &) = delete;
        Scanner & operator=(Scanner const &) = delete;

        // Get scans file and puts token into tokens vector
        void scan();

        // Prints out token vector
        void print();
        void print(std::string out_file);

        // Constructor
        Scanner(std::string file_name, std::vector<Token> *out_vector);

        // Destructor
        ~Scanner();
};
```
The scanner checks character by character following the rough DFA outline before. For read_string(), the scanner will append the read characters into a string buffer first until the next character breaks the grammar for an ID token (does not have a leaving edge from state 1). Then, the scanner will check the scanned string buffer against the reserved words to determine if it is an ID token or a reserved word. A similar mechanism follows for multi-letter special symbols.

## Running

Please run `make all` or `make` to build and compile the scanner.
To run use `./scanner <input_file>` as the running format.
The scanner can accept multiple input files and will print out the result as an output file follow the naming convention `ans1.c1` in the `output/` directory.