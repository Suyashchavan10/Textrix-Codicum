#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Token types enumeration
enum class TokenType {
    DECLARE,
    FUNCTION,
    INTEGER,
    STRING,
    BOOLEAN,
    IDENTIFIER,
    NUMBER,
    STRINGVAL,
    OPERATOR,
    KEYWORD,
    ARRAY,
    ASSIGN,
    READ,
    PRINT,
    IF,
    ELSE,
    END,
    FOR,
    WHILE,
    END_OF_FILE,
};

// Token structure
struct Token {
    TokenType type;
    string lexeme;
    int line;  // optional: to track line numbers

    // Token(TokenType type, const string& lexeme, int line) : type(type), lexeme(lexeme), line(line) {}
};

// Tokenizer class
class Tokenizer {
private:
    string input;
    size_t currentPos;
    vector<Token> tokens;

    void tokenizeNumber();
    void tokenizeIdentifier();
    void tokenizeOperator();
    void tokenizeString();
    void tokenizeOther();
    bool isOperator(char c);

public:
    Tokenizer(string input) : input(input), currentPos(0) {};

    // Function to tokenize the input
    vector<Token> tokenize();
};

#endif // TOKENIZER_H
