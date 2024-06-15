#include <iostream>
#include <string>
#include <vector>
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
    OPERATOR,
    KEYWORD,
    END_OF_FILE,
};

// Token structure
struct Token {
    TokenType type;
    string lexeme;
    int line;  // optional: to track line numbers
};

// Tokenizer class
class Tokenizer {
private:
    string input;
    size_t currentPos;
    vector<Token> tokens;

public:
    Tokenizer(string input) : input(input), currentPos(0) {}

    // Function to tokenize the input
    vector<Token> tokenize() {
        while (currentPos < input.size()) {
            char currentChar = input[currentPos];

            // Handle whitespace
            if (isspace(currentChar)) {
                currentPos++;
                continue;
            }

            // Handle digits (numbers)
            if (isdigit(currentChar)) {
                tokenizeNumber();
                continue;
            }

            // Handle identifiers (keywords, variable names, function names)
            if (isalpha(currentChar)) {
                tokenizeIdentifier();
                continue;
            }

            // Handle operators and special characters
            if (isOperator(currentChar)) {
                tokenizeOperator();
                continue;
            }

            // Handle strings (quoted text)
            if (currentChar == '"') {
                tokenizeString();
                continue;
            }

            // Handle other cases (like keywords DECLARE, FUNCTION)
            tokenizeOther();
        }

        // Add an end-of-file token
        tokens.push_back({ TokenType::END_OF_FILE, "", -1 });

        return tokens;
    }

private:
    // Helper functions for tokenizing different types of tokens
    void tokenizeNumber() {
        size_t startPos = currentPos;
        while (isdigit(input[currentPos])) {
            currentPos++;
        }
        string numberStr = input.substr(startPos, currentPos - startPos);
        tokens.push_back({ TokenType::NUMBER, numberStr, -1 });
    }

    void tokenizeIdentifier() {
        size_t startPos = currentPos;
        while (isalnum(input[currentPos])) {
            currentPos++;
        }
        string identifier = input.substr(startPos, currentPos - startPos);
        // Check if the identifier matches known keywords
        if (identifier == "DECLARE") {
            tokens.push_back({ TokenType::DECLARE, identifier, -1 });
        } else if (identifier == "FUNCTION") {
            tokens.push_back({ TokenType::FUNCTION, identifier, -1 });
        } else if (identifier == "INTEGER") {
            tokens.push_back({ TokenType::INTEGER, identifier, -1 });
        } else if (identifier == "STRING") {
            tokens.push_back({ TokenType::STRING, identifier, -1 });
        } else if (identifier == "BOOLEAN") {
            tokens.push_back({ TokenType::BOOLEAN, identifier, -1 });
        } else {
            tokens.push_back({ TokenType::IDENTIFIER, identifier, -1 });
        }
    }

    void tokenizeOperator() {
        char currentChar = input[currentPos];
        string op(1, currentChar);  // Convert char to string
        tokens.push_back({ TokenType::OPERATOR, op, -1 });
        currentPos++;
    }

    void tokenizeString() {
        size_t startPos = ++currentPos;  // Skip the opening quote
        while (currentPos < input.size() && input[currentPos] != '"') {
            currentPos++;
        }
        string strLiteral = input.substr(startPos, currentPos - startPos);
        currentPos++;  // Skip the closing quote
        tokens.push_back({ TokenType::STRING, strLiteral, -1 });
    }

    void tokenizeOther() {
        // Handle special cases based on specific pseudocode syntax
        // For example, detect keywords, special characters, etc.
        // In this basic example, it might be simpler to handle within tokenizeIdentifier()
        currentPos++;
    }

    bool isOperator(char c) {
        // Define operators specific to your pseudocode syntax
        // For example: +, -, *, /, :=, >, <, >=, <=, ==, !=, AND, OR, etc.
        return (c == '+' || c == '-' || c == '*' || c == '/' ||
                c == '=' || c == '>' || c == '<' || c == '&' || c == '|');
    }
};

int main() {
    
    // Read the pseudocode from the file
    ifstream inputFile("../pseudocode/pseudocode.txt");
    if (!inputFile) {
        cerr << "Failed to open pseudocode.txt" << endl;
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string pseudocode = buffer.str();

    // Create tokenizer instance
    Tokenizer tokenizer(pseudocode);

    // Tokenize the input
    vector<Token> tokens = tokenizer.tokenize();

    // Print the tokens for verification
    for (const auto& token : tokens) {
        cout << "Token: " << token.lexeme << "\tType: " << static_cast<int>(token.type) << endl;
    }

    return 0;
}
