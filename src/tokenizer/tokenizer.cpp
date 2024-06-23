#include "tokenizer.h"
// #include <cctype>

vector<Token> Tokenizer::tokenize() {
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
    // tokens.push_back({ TokenType::END_OF_FILE, "", -1 });

    return tokens;
}

void Tokenizer::tokenizeNumber() {
    size_t startPos = currentPos;
    while (isdigit(input[currentPos])) {
        currentPos++;
    }
    string numberStr = input.substr(startPos, currentPos - startPos);
    tokens.push_back({ TokenType::NUMBER, numberStr, -1 });
}

void Tokenizer::tokenizeIdentifier() {
    size_t startPos = currentPos;
    while (isalnum(input[currentPos])) {
        currentPos++;
    }
    string identifier = input.substr(startPos, currentPos - startPos);
    // Check if the identifier matches known keywords
    if (identifier == "Declare") {
        tokens.push_back({ TokenType::DECLARE, identifier, -1 });
    } else if (identifier == "Assign") {
        tokens.push_back({ TokenType::ASSIGN, identifier, -1 });
    } else if (identifier == "Function") {
        tokens.push_back({ TokenType::FUNCTION, identifier, -1 });
    } else if (identifier == "Integer") {
        tokens.push_back({ TokenType::INTEGER, identifier, -1 });
    } else if (identifier == "String") {
        tokens.push_back({ TokenType::STRING, identifier, -1 });
    } else if (identifier == "Boolean") {
        tokens.push_back({ TokenType::BOOLEAN, identifier, -1 });
    } else if (identifier == "As" || identifier == "Of" || identifier == "Then" || identifier == "To" || identifier == "Do") {
        tokens.push_back({ TokenType::KEYWORD, identifier, -1 });
    } else if (identifier == "Array") {
        tokens.push_back({ TokenType::ARRAY, identifier, -1 });
    } else if (identifier == "Read") {
        tokens.push_back({ TokenType::READ, identifier, -1 });
    } else if (identifier == "Print") {
        tokens.push_back({ TokenType::PRINT, identifier, -1 });
    } else if (identifier == "If") {
        tokens.push_back({ TokenType::IF, identifier, -1 });
    } else if (identifier == "Else") {
        tokens.push_back({ TokenType::ELSE, identifier, -1 });
    } else if (identifier == "For") {
        tokens.push_back({ TokenType::FOR, identifier, -1 });
    } else if (identifier == "While") {
        tokens.push_back({ TokenType::WHILE, identifier, -1 });
    } else if (identifier == "End") {
        tokens.push_back({ TokenType::END, identifier, -1 });
    } else {
        tokens.push_back({ TokenType::IDENTIFIER, identifier, -1 });
    }
}

void Tokenizer::tokenizeOperator() {
    char currentChar = input[currentPos];
    string op(1, currentChar);  // Convert char to string
    tokens.push_back({ TokenType::OPERATOR, op, -1 });
    currentPos++;
}

void Tokenizer::tokenizeString() {
    size_t startPos = ++currentPos;  // Skip the opening quote
    while (currentPos < input.size() && input[currentPos] != '"') {
        currentPos++;
    }
    string strLiteral = input.substr(startPos, currentPos - startPos);
    currentPos++;  // Skip the closing quote
    tokens.push_back({ TokenType::STRINGVAL, strLiteral, -1 });
}

void Tokenizer::tokenizeOther() {
    // Handle special cases based on specific pseudocode syntax
    // For example, detect keywords, special characters, etc.
    // In this basic example, it might be simpler to handle within tokenizeIdentifier()
    currentPos++;
}

bool Tokenizer::isOperator(char c) {
    // Define operators specific to your pseudocode syntax
    // For example: +, -, *, /, :=, >, <, >=, <=, ==, !=, AND, OR, etc.
    return (c == '+' || c == '-' || c == '*' || c == '/' ||
            c == '=' || c == '>' || c == '<' || c == '&' || c == '|');
}


// ----------------------------------------------------------------------------------
// main for unit testing


// int main() {
    
//     // Read the pseudocode from the file
//     ifstream inputFile("../pseudocode/pseudocode.txt");
//     if (!inputFile) {
//         cerr << "Failed to open pseudocode.txt" << endl;
//         return 1;
//     }

//     stringstream buffer;
//     buffer << inputFile.rdbuf();
//     string pseudocode = buffer.str();

//     // Create tokenizer instance
//     Tokenizer tokenizer(pseudocode);

//     // Tokenize the input
//     vector<Token> tokens = tokenizer.tokenize();

//     // Print the tokens for verification
//     for (const auto& token : tokens) {
//         cout << "Token: " << token.lexeme << "\tType: " << static_cast<int>(token.type) << endl;
//     }

//     return 0;
// }