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
    STRINGVAL,
    OPERATOR,
    KEYWORD,
    ARRAY,
    ASSIGN,
    READ,
    PRINT,
    END_OF_FILE,
};

// Token structure
struct Token {
    TokenType type;
    string lexeme;
    int line;  // optional: to track line numbers
};

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
    IDENTIFIER
    // Add other necessary node types
};

// AST Node structure
struct Node {
    NodeType type;
    vector<Node> children;
    Token token;

    Node(NodeType type, Token token) : type(type), token(token) {}
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
        if (identifier == "Declare") {
            tokens.push_back({ TokenType::DECLARE, identifier, -1 });
        } else if (identifier == "Assign") {
            tokens.push_back({ TokenType::ASSIGN, identifier, -1 });
        } else if (identifier == "Function") {
            tokens.push_back({ TokenType::FUNCTION, identifier, -1 });
        }   else if (identifier == "Integer") {
            tokens.push_back({ TokenType::INTEGER, identifier, -1 });
        } else if (identifier == "String") {
            tokens.push_back({ TokenType::STRING, identifier, -1 });
        } else if (identifier == "Boolean") {
            tokens.push_back({ TokenType::BOOLEAN, identifier, -1 });
        } else if (identifier == "As" || identifier == "Of") {
            tokens.push_back({ TokenType::KEYWORD, identifier, -1 });
        } else if (identifier == "Array") {
            tokens.push_back({ TokenType::ARRAY, identifier, -1 });
        } else if (identifier == "Read") {
            tokens.push_back({ TokenType::READ, identifier, -1 });
        } else if (identifier == "Print") {
            tokens.push_back({ TokenType::PRINT, identifier, -1 });
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
        tokens.push_back({ TokenType::STRINGVAL, strLiteral, -1 });
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

// Parser class
class Parser {
private:
    vector<Token> tokens;
    size_t currentPos;
    Token currentToken;

public:
    Parser(vector<Token> tokens) : tokens(tokens), currentPos(0) {
        currentToken = tokens[currentPos];
    }

    // Function to parse the tokens and build the AST
    Node parse() {
        return parseStatements();
    }

private:
    Node parseStatements() {
        Node node(NodeType::DECLARATION, currentToken);
        while (currentToken.type != TokenType::END_OF_FILE) {
            node.children.push_back(parseStatement());
        }
        return node;
    }

    Node parseStatement() {
        switch (currentToken.type) {
            case TokenType::DECLARE:
                return parseDeclaration();
            case TokenType::FUNCTION:
                return parseFunctionDeclaration();
            case TokenType::ASSIGN:
                return parseAssignment();
            case TokenType::PRINT:
                return parsePrint();
            default:
                throw runtime_error("Unexpected token: " + currentToken.lexeme);
        }
    }

    Node parseDeclaration() {
        Token declareToken = consume(TokenType::DECLARE);
        Token identifierToken = consume(TokenType::IDENTIFIER);
        Token asKeyWord = consume(TokenType::KEYWORD);

        // Consume the type token
        Token typeToken = consume(currentToken.type);
        Node node(NodeType::DECLARATION, declareToken);

        if(typeToken.type == TokenType::ARRAY){
            // cout<<"array"<<endl;
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


    Node parseFunctionDeclaration() {
        Token token = consume(TokenType::FUNCTION);
        Token identifier = consume(TokenType::IDENTIFIER);
        consume(TokenType::KEYWORD); // assuming FUNCTION is followed by params
        Node node(NodeType::FUNCTION_DECLARATION, token);
        node.children.push_back(Node(NodeType::IDENTIFIER, identifier));
        // parse function body
        return node;
    }

    Node parseAssignment(){
        Token assignToken = consume(TokenType::ASSIGN);
        Node node(NodeType::ASSIGNMENT, assignToken);

        Token identifierToken = consume(TokenType::IDENTIFIER);
        Token opert = consume(TokenType::OPERATOR);
        node.children.push_back(Node(NodeType::IDENTIFIER, identifierToken));
        node.children.push_back(Node(NodeType::IDENTIFIER, opert));

        // Token expr = consume(currentToken.type);
        Node expr = parseExpression();
        node.children.push_back(expr);

        return node;
    }

    Node parseExpression(){
        Token exprSt;
        Node node(NodeType::EXPRESSION, exprSt);

        Token expr = consume(currentToken.type);
        while(expr.type==TokenType::IDENTIFIER || expr.type==TokenType::OPERATOR || expr.type==TokenType::NUMBER){
            node.children.push_back(Node(NodeType::IDENTIFIER, expr));
            expr = consume(currentToken.type);
        }

        // if(currentToken.type == TokenType::END_OF_FILE) return node;
        release(currentToken.type);
        return node;
    }

    Node parsePrint(){
        Token printToken = consume(TokenType::PRINT);
        Node node(NodeType::PRINT, printToken);

        while(currentToken.type==TokenType::IDENTIFIER || currentToken.type==TokenType::STRINGVAL || currentToken.type==TokenType::NUMBER){
            Token printId = consume(currentToken.type);
            node.children.push_back(Node(NodeType::IDENTIFIER, printId));
        }

        return node;
    }

    // Helper functions for releasing tokens
    void release(TokenType expectedType) {
        if (currentToken.type != expectedType) {
            throw runtime_error("Unexpected token: " + currentToken.lexeme);
        }
        // Token token = currentToken;
        currentToken = tokens[--currentPos];
        // return token;
        return;
    }

    // Helper functions for consuming tokens
    Token consume(TokenType expectedType) {
        if (currentToken.type != expectedType) {
            throw runtime_error("Unexpected token: " + currentToken.lexeme);
        }
        Token token = currentToken;
        currentToken = tokens[++currentPos];
        return token;
    }

};

// Function to print the AST
void printAST(const Node& node, int level = 0) {
    // Print current node
    for (int i = 0; i < level; ++i) {
        cout << "  "; // Indentation for readability
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
        // Add cases for other node types as needed
    }

    cout << ", Lexeme: " << node.token.lexeme << ", Line: " << node.token.line << endl;

    // Recursively print children
    for (const auto& child : node.children) {
        printAST(child, level + 1);
    }
}


// CodeGenerator class to generate code from AST
class CodeGenerator {
public:
    string generateCode(const Node& ast) {
        stringstream code;
        for(Node child : ast.children){
            generateNodeCode(child, code);
        }
        return code.str();
    }

private:
    void generateNodeCode(const Node& node, stringstream& code) {
        switch (node.type) {
            case NodeType::DECLARATION:
                generateDeclaration(node, code);
                break;
            case NodeType::FUNCTION_DECLARATION:
                generateFunctionDeclaration(node, code);
                break;
            case NodeType::ASSIGNMENT:
                generateAssignment(node, code);
                break;
            case NodeType::EXPRESSION:
                generateExpression(node, code);
                break;
            case NodeType::PRINT:
                generatePrint(node, code);
                break;
            case NodeType::IF_STATEMENT:
                generateIfStatement(node, code);
                break;
            case NodeType::FOR_LOOP:
                generateForLoop(node, code);
                break;
            case NodeType::WHILE_LOOP:
                generateWhileLoop(node, code);
                break;
            case NodeType::DO_WHILE_LOOP:
                generateDoWhileLoop(node, code);
                break;
            case NodeType::IDENTIFIER:
                generateIdentifier(node, code);
                break;
            // Handle other node types as needed
            default:
                throw runtime_error("Unknown node type encountered.");
        }
    }

    void generateDeclaration(const Node& node, stringstream& code) {
        // code << "Declare " << node.children[0].token.lexeme << " As " << node.children[1].token.lexeme << ";" << endl;
        string lexType = node.children[1].token.lexeme;
        if(lexType == "Integer"){
            code<<"int ";
            generateIdentifier(node.children[0], code);
            code<<";"<<endl;
        }
        else if(lexType == "String"){
            code<<"string ";
            generateIdentifier(node.children[0], code);
            code<<";"<<endl;
        }
        else if(lexType == "Array"){
            string dataType = node.children[2].token.lexeme;
            if(dataType == "Integer"){
                code<<"int ";
                generateIdentifier(node.children[0], code);
                code<<"[";
                generateIdentifier(node.children[3], code);
                code<<"]";
                if(node.children.size() > 4){
                    // 2D array
                    code<<"[";
                    generateIdentifier(node.children[4], code);
                    code<<"]";
                }
                code<<";"<<endl;
            }
        }
    }

    void generateFunctionDeclaration(const Node& node, stringstream& code) {
        code << "Function " << node.children[0].token.lexeme << "() {" << endl;
        // Generate function body (not implemented in this example)
        code << "    // Function body" << endl;
        code << "}" << endl;
    }

    void generateAssignment(const Node& node, stringstream& code) {
        generateIdentifier(node.children[0], code); 
        code <<" ";
        generateIdentifier(node.children[1], code); 
        code<<" ";
        generateNodeCode(node.children[2], code);
        code << ";" << endl;
    }

    void generateExpression(const Node& node, stringstream& code) {
        for(Node child : node.children){
            generateIdentifier(child, code);
            code<<" ";
        }
    }

    void generatePrint(const Node& node, stringstream& code) {
        code<<"cout << ";
        for(int ind=0; ind<node.children.size(); ind++){
            Node child = node.children[ind];
            if(child.token.type == TokenType::STRINGVAL){
                code<<"\"";
                generateIdentifier(child, code);
                code<<"\"";
            }
            else generateIdentifier(child, code);
            code<<" << ";
            if(ind < node.children.size()-1)code<<"\" \" << ";
        }
        code<<"endl;"<<endl;
    }

    void generateIfStatement(const Node& node, stringstream& code) {
        code << "If (";
        generateNodeCode(node.children[0], code);
        code << ") {" << endl;
        // Generate if block (not implemented in this example)
        code << "    // If block" << endl;
        code << "}" << endl;
    }

    void generateForLoop(const Node& node, stringstream& code) {
        code << "For (";
        generateNodeCode(node.children[0], code);
        code << "; ";
        generateNodeCode(node.children[1], code);
        code << "; ";
        generateNodeCode(node.children[2], code);
        code << ") {" << endl;
        // Generate for loop body (not implemented in this example)
        code << "    // For loop body" << endl;
        code << "}" << endl;
    }

    void generateWhileLoop(const Node& node, stringstream& code) {
        code << "While (";
        generateNodeCode(node.children[0], code);
        code << ") {" << endl;
        // Generate while loop body (not implemented in this example)
        code << "    // While loop body" << endl;
        code << "}" << endl;
    }

    void generateDoWhileLoop(const Node& node, stringstream& code) {
        code << "Do {" << endl;
        // Generate do-while loop body (not implemented in this example)
        code << "    // Do-while loop body" << endl;
        code << "} While (";
        generateNodeCode(node.children[0], code);
        code << ");" << endl;
    }

    void generateIdentifier(const Node& node, stringstream& code) {
        code << node.token.lexeme;
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

    // Create parser instance
    Parser parser(tokens);

    // Parse the tokens to create an AST
    Node ast = parser.parse();

    printAST(ast);

    // Create CodeGenerator instance
    CodeGenerator generator;

    // Generate code from AST
    string generatedCode = generator.generateCode(ast);

    // Print generated code
    cout << "Generated code:" << endl;
    cout << generatedCode << endl;


    return 0;
}
