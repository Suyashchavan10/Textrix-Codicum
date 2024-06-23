#include "parser.h"
#include "../tokenizer/tokenizer.cpp"
#include <iostream>

using namespace std;

Parser::Parser(vector<Token> tokens) : tokens(tokens), currentPos(0) {
    currentToken = tokens[currentPos];
}

Node Parser::parse() {
    return parseStatements();
}

Node Parser::parseStatements() {
    Node node(NodeType::DECLARATION, currentToken);
    while (currentToken.type != TokenType::END_OF_FILE) {
        node.children.push_back(parseStatement());
    }
    return node;
}

Node Parser::parseStatement() {
    switch (currentToken.type) {
        case TokenType::DECLARE:
            return parseDeclaration();
        case TokenType::FUNCTION:
            return parseFunctionDeclaration();
        case TokenType::ASSIGN:
            return parseAssignment();
        case TokenType::PRINT:
            return parsePrint();
        case TokenType::IF:
            return parseIf();
        case TokenType::FOR:
            return parseFor();
        case TokenType::WHILE:
            return parseWhile();
        default:
            throw runtime_error("Unexpected token: " + currentToken.lexeme);
    }
}

Node Parser::parseDeclaration() {
    Token declareToken = consume(TokenType::DECLARE);
    Token identifierToken = consume(TokenType::IDENTIFIER);
    Token asKeyWord = consume(TokenType::KEYWORD);

    // Consume the type token
    Token typeToken = consume(currentToken.type);
    Node node(NodeType::DECLARATION, declareToken);

    if(typeToken.type == TokenType::ARRAY){
        // 1D array
        node.children.push_back(Node(NodeType::IDENTIFIER, identifierToken));
        node.children.push_back(Node(NodeType::IDENTIFIER, typeToken));

        Token ofKeyWord = consume(TokenType::KEYWORD);
        Token dataTypeToken = consume(currentToken.type);
        Token arraySize = consume(TokenType::NUMBER);

        node.children.push_back(Node(NodeType::IDENTIFIER, dataTypeToken));
        node.children.push_back(Node(NodeType::IDENTIFIER, arraySize));

        if(currentToken.type == TokenType::NUMBER){
            // 2D array
            Token arraySize2 = consume(TokenType::NUMBER);
            node.children.push_back(Node(NodeType::IDENTIFIER, arraySize2));
        }
    }
    else{
        node.children.push_back(Node(NodeType::IDENTIFIER, identifierToken));
        node.children.push_back(Node(NodeType::IDENTIFIER, typeToken)); // Assuming type is also an identifier
    }

    return node;
}

Node Parser::parseFunctionDeclaration() {
    Token token = consume(TokenType::FUNCTION);
    Token identifier = consume(TokenType::IDENTIFIER);
    consume(TokenType::KEYWORD); // assuming FUNCTION is followed by params
    Node node(NodeType::FUNCTION_DECLARATION, token);
    node.children.push_back(Node(NodeType::IDENTIFIER, identifier));
    // parse function body
    return node;
}

Node Parser::parseAssignment(){
    Token assignToken = consume(TokenType::ASSIGN);
    Node node(NodeType::ASSIGNMENT, assignToken);

    while(currentToken.type == TokenType::IDENTIFIER){
        Token identifierToken = consume(TokenType::IDENTIFIER);
        node.children.push_back(Node(NodeType::IDENTIFIER, identifierToken));
    }

    Token opert = consume(TokenType::OPERATOR);
    node.children.push_back(Node(NodeType::IDENTIFIER, opert));

    // Token expr = consume(currentToken.type);
    Node expr = parseExpression();
    node.children.push_back(expr);

    return node;
}

Node Parser::parseExpression(){
    Token exprSt;
    Node node(NodeType::EXPRESSION, exprSt);

    while(currentToken.type==TokenType::IDENTIFIER || currentToken.type==TokenType::OPERATOR || currentToken.type==TokenType::NUMBER || currentToken.type==TokenType::STRINGVAL){
        Token expr = consume(currentToken.type);
        node.children.push_back(Node(NodeType::IDENTIFIER, expr));
    }

    return node;
}

Node Parser::parsePrint(){
    Token printToken = consume(TokenType::PRINT);
    Node node(NodeType::PRINT, printToken);

    while(currentToken.type==TokenType::IDENTIFIER || currentToken.type==TokenType::STRINGVAL || currentToken.type==TokenType::NUMBER){
        Token printId = consume(currentToken.type);
        node.children.push_back(Node(NodeType::IDENTIFIER, printId));
    }

    return node;
}

Node Parser::parseIf(){
    Token ifToken = consume(TokenType::IF);
    Node node(NodeType::IF_STATEMENT, ifToken);

    Node condition = parseExpression();
    node.children.push_back(condition);

    Token thenToken = consume(TokenType::KEYWORD);
    Node ifBlock(NodeType::BLOCK, thenToken);

    while(currentToken.type != TokenType::ELSE && currentToken.type != TokenType::END){
        Node blkStatement = parseStatement();
        ifBlock.children.push_back(blkStatement);
    }
    node.children.push_back(ifBlock);

    if(currentToken.type == TokenType::ELSE){
        Token elseToken = consume(TokenType::ELSE);
        Node elseBlock(NodeType::BLOCK, elseToken);

        while(currentToken.type != TokenType::END){
            Node blkStatement = parseStatement();
            elseBlock.children.push_back(blkStatement);
        }
        node.children.push_back(elseBlock);
    }
    
    Token endToken = consume(TokenType::END);
    Token endIfToken = consume(TokenType::IF);

    return node;
}

Node Parser::parseFor(){
    Token forToken = consume(TokenType::FOR);
    Node node(NodeType::FOR_LOOP, forToken);

    Node stCondition = parseExpression();
    node.children.push_back(stCondition);
    Token toToken = consume(TokenType::KEYWORD);
    Node edCondition = parseExpression();
    node.children.push_back(edCondition);

    Token doToken = consume(TokenType::KEYWORD);
    Node forBlock(NodeType::BLOCK, doToken);

    while(currentToken.type != TokenType::END){
        Node blkStatement = parseStatement();
        forBlock.children.push_back(blkStatement);
    }
    node.children.push_back(forBlock);

    Token endToken = consume(TokenType::END);
    Token endForToken = consume(TokenType::FOR);

    return node;
}

Node Parser::parseWhile(){
    Token whileToken = consume(TokenType::WHILE);
    Node node(NodeType::WHILE_LOOP, whileToken);

    Node condition = parseExpression();
    node.children.push_back(condition);

    Token doToken = consume(TokenType::KEYWORD);
    Node whileBlock(NodeType::BLOCK, doToken);

    while(currentToken.type != TokenType::END){
        Node blkStatement = parseStatement();
        whileBlock.children.push_back(blkStatement);
    }
    node.children.push_back(whileBlock);

    Token endToken = consume(TokenType::END);
    Token endWhileToken = consume(TokenType::WHILE);

    return node;
}

void Parser::release(TokenType expectedType) {
    if (currentToken.type != expectedType) {
        throw runtime_error("Unexpected token: " + currentToken.lexeme);
    }
    currentToken = tokens[--currentPos];
}

Token Parser::consume(TokenType expectedType) {
    if (currentToken.type != expectedType) {
        throw runtime_error("Unexpected token: " + currentToken.lexeme);
    }
    Token token = currentToken;
    currentToken = tokens[++currentPos];
    return token;
}

void printAST(const Node& node, int level) {
    for (int i = 0; i < level; ++i) {
        cout << "  ";
    }

    cout << "Type: ";
    switch (node.type) {
        case NodeType::DECLARATION:
            cout << "DECLARATION";
            break;
        case NodeType::FUNCTION_DECLARATION:
            cout << "FUNCTION_DECLARATION";
            break;
        case NodeType::ASSIGNMENT:
            cout << "ASSIGNMENT";
            break;
        case NodeType::EXPRESSION:
            cout << "EXPRESSION";
            break;
        case NodeType::PRINT:
            cout << "PRINT";
            break;
        case NodeType::IF_STATEMENT:
            cout << "IF_STATEMENT";
            break;
        case NodeType::FOR_LOOP:
            cout << "FOR_LOOP";
            break;
        case NodeType::WHILE_LOOP:
            cout << "WHILE_LOOP";
            break;
        case NodeType::DO_WHILE_LOOP:
            cout << "DO_WHILE_LOOP";
            break;
        case NodeType::IDENTIFIER:
            cout << "IDENTIFIER";
            break;
        case NodeType::BLOCK:
            cout << "BLOCK";
            break;
        // Add cases for other node types as needed
    }

    cout << ", Lexeme: " << node.token.lexeme << ", Line: " << node.token.line << endl;

    for (const auto& child : node.children) {
        printAST(child, level + 1);
    }
}


// --------------------------------------------------------------------------
// main for unit testing of Parser

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

//     // Create parser instance
//     Parser parser(tokens);

//     // Parse the tokens to create an AST
//     Node ast = parser.parse();

//     printAST(ast);

//     return 0;
// }
