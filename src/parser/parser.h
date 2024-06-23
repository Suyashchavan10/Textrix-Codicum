#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <stdexcept>
#include "../tokenizer/tokenizer.h"  // Make sure this file contains the definition for the Token structure and TokenType enum

// AST Node Types
enum class NodeType {
    DECLARATION,
    FUNCTION_DECLARATION,
    ASSIGNMENT,
    EXPRESSION,
    PRINT,
    READ,
    IF_STATEMENT,
    FOR_LOOP,
    WHILE_LOOP,
    DO_WHILE_LOOP,
    IDENTIFIER,
    BLOCK
    // Add other necessary node types
};

// AST Node structure
struct Node {
    NodeType type;
    std::vector<Node> children;
    Token token;

    Node(NodeType type, Token token) : type(type), token(token) {}
};

// Parser class
class Parser {
private:
    std::vector<Token> tokens;
    size_t currentPos;
    Token currentToken;

public:
    Parser(std::vector<Token> tokens);

    // Function to parse the tokens and build the AST
    Node parse();

private:
    Node parseStatements();
    Node parseStatement();
    Node parseDeclaration();
    Node parseFunctionDeclaration();
    Node parseAssignment();
    Node parseExpression();
    Node parsePrint();
    Node parseIf();
    Node parseFor();
    Node parseWhile();

    void release(TokenType expectedType);
    Token consume(TokenType expectedType);
};

// Function to print the AST
void printAST(const Node& node, int level = 0);

#endif // PARSER_H
