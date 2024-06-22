#include <iostream>
#include "codeGenerator.h"
#include "../parser/parser.cpp"

using namespace std;

// CodeGenerator class to generate code from AST
string CodeGenerator::generateCode(const Node& ast) {
    stringstream code;
    code<<"#include <bits/stdc++.h>"<<endl;
    code<<"using namespace std;"<<endl;
    code<<endl;
    code<<"int main() {"<<endl;
    code<<endl;

    for(const Node& child : ast.children){
        generateNodeCode(child, code);
    }

    code<<endl;
    code<<"return 0;"<<endl;
    code<<"}"<<endl;

    return code.str();
}

void CodeGenerator::generateNodeCode(const Node& node, stringstream& code) {
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
        default:
            throw runtime_error("Unknown node type encountered.");
    }
}

void CodeGenerator::generateDeclaration(const Node& node, stringstream& code) {
    string lexType = node.children[1].token.lexeme;
    if(lexType == "Integer"){
        code << "int ";
        generateIdentifier(node.children[0], code);
        code << ";" << endl;
    }
    else if(lexType == "String"){
        code << "string ";
        generateIdentifier(node.children[0], code);
        code << ";" << endl;
    }
    else if(lexType == "Array"){
        string dataType = node.children[2].token.lexeme;
        if(dataType == "Integer"){
            code << "int ";
            generateIdentifier(node.children[0], code);
            code << "[";
            generateIdentifier(node.children[3], code);
            code << "]";
            if(node.children.size() > 4){
                // 2D array
                code << "[";
                generateIdentifier(node.children[4], code);
                code << "]";
            }
            code << ";" << endl;
        }
    }
}

void CodeGenerator::generateFunctionDeclaration(const Node& node, stringstream& code) {
    code << "void " << node.children[0].token.lexeme << "() {" << endl;
    // Generate function body (not implemented in this example)
    code << "    // Function body" << endl;
    code << "}" << endl;
}

void CodeGenerator::generateAssignment(const Node& node, stringstream& code) {
    generateIdentifier(node.children[0], code); 
    code << " ";
    generateIdentifier(node.children[1], code); 
    code << " ";
    generateNodeCode(node.children[2], code);
    code << ";" << endl;
}

void CodeGenerator::generateExpression(const Node& node, stringstream& code) {
    for(const Node& child : node.children){
        generateIdentifier(child, code);
        code << " ";
    }
}

void CodeGenerator::generatePrint(const Node& node, stringstream& code) {
    code << "cout << ";
    for(size_t ind = 0; ind < node.children.size(); ++ind){
        const Node& child = node.children[ind];
        if(child.token.type == TokenType::STRINGVAL){
            code << "\"";
            generateIdentifier(child, code);
            code << "\"";
        }
        else generateIdentifier(child, code);
        if(ind < node.children.size() - 1) code << " << \" \" << ";
    }
    code << " << endl;" << endl;
}

void CodeGenerator::generateIfStatement(const Node& node, stringstream& code) {
    code << "if (";
    generateNodeCode(node.children[0], code);
    code << ") {" << endl;
    // Generate if block (not implemented in this example)
    code << "    // If block" << endl;
    code << "}" << endl;
}

void CodeGenerator::generateForLoop(const Node& node, stringstream& code) {
    code << "for (";
    generateNodeCode(node.children[0], code);
    code << "; ";
    generateNodeCode(node.children[1], code);
    code << "; ";
    generateNodeCode(node.children[2], code);
    code << ") {" << std::endl;
    // Generate for loop body (not implemented in this example)
    code << "    // For loop body" << endl;
    code << "}" << endl;
}

void CodeGenerator::generateWhileLoop(const Node& node, stringstream& code) {
    code << "while (";
    generateNodeCode(node.children[0], code);
    code << ") {" << endl;
    // Generate while loop body (not implemented in this example)
    code << "    // While loop body" << endl;
    code << "}" << endl;
}

void CodeGenerator::generateDoWhileLoop(const Node& node, stringstream& code) {
    code << "do {" << endl;
    // Generate do-while loop body (not implemented in this example)
    code << "    // Do-while loop body" << endl;
    code << "} while (";
    generateNodeCode(node.children[0], code);
    code << ");" << endl;
}

void CodeGenerator::generateIdentifier(const Node& node, stringstream& code) {
    code << node.token.lexeme;
}


// --------------------------------------------------------------------------
// main for unit testing of CodeGenerator

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

//     // Create CodeGenerator instance
//     CodeGenerator generator;

//     // Generate code from AST
//     string generatedCode = generator.generateCode(ast);

//     // Print generated code
//     cout << "Generated code:" << endl;
//     cout << generatedCode << endl;

//     return 0;
// }