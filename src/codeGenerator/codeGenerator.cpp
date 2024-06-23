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

    int level = 1;
    for(const Node& child : ast.children){
        generateNodeCode(child, code, level);
    }

    code<<endl;
    code<<"return 0;"<<endl;
    code<<"}"<<endl;

    return code.str();
}

void CodeGenerator::generateNodeCode(const Node& node, stringstream& code, int level) {
    switch (node.type) {
        case NodeType::DECLARATION:
            generateDeclaration(node, code, level);
            break;
        case NodeType::FUNCTION_DECLARATION:
            generateFunctionDeclaration(node, code, level);
            break;
        case NodeType::ASSIGNMENT:
            generateAssignment(node, code, level);
            break;
        case NodeType::EXPRESSION:
            generateExpression(node, code, level);
            break;
        case NodeType::PRINT:
            generatePrint(node, code, level);
            break;
        case NodeType::IF_STATEMENT:
            generateIfStatement(node, code, level);
            break;
        case NodeType::FOR_LOOP:
            generateForLoop(node, code, level);
            break;
        case NodeType::WHILE_LOOP:
            generateWhileLoop(node, code, level);
            break;
        case NodeType::DO_WHILE_LOOP:
            generateDoWhileLoop(node, code, level);
            break;
        case NodeType::IDENTIFIER:
            generateIdentifier(node, code, level);
            break;
        default:
            throw runtime_error("Unknown node type encountered.");
    }
}

void CodeGenerator::generateDeclaration(const Node& node, stringstream& code, int level) {
    string lexType = node.children[1].token.lexeme;
    indent(code, level); 
    if(lexType == "Integer"){
        code << "int ";
        generateIdentifier(node.children[0], code, level+1);
        code << ";" << endl;
    }
    else if(lexType == "String"){
        code << "string ";
        generateIdentifier(node.children[0], code, level+1);
        code << ";" << endl;
    }
    else if(lexType == "Array"){
        string dataType = node.children[2].token.lexeme;
        if(dataType == "Integer"){
            code << "int ";
            generateIdentifier(node.children[0], code, level+1);
            code << "[";
            generateIdentifier(node.children[3], code, level+1);
            code << "]";
            if(node.children.size() > 4){
                // 2D array
                code << "[";
                generateIdentifier(node.children[4], code, level+1);
                code << "]";
            }
            code << ";" << endl;
        }
    }
}

void CodeGenerator::generateFunctionDeclaration(const Node& node, stringstream& code, int level) {
    code << "void " << node.children[0].token.lexeme << "() {" << endl;
    // Generate function body (not implemented in this example)
    code << "    // Function body" << endl;
    code << "}" << endl;
}

void CodeGenerator::generateAssignment(const Node& node, stringstream& code, int level) {
    indent(code, level); 
    int opertInd = 1;
    if(node.children[1].token.type == TokenType::OPERATOR){
        // single variable
        generateIdentifier(node.children[0], code, level+1);
        opertInd = 1;
    }
    else if(node.children[2].token.type == TokenType::OPERATOR){
        // array variable : arr[i]
        generateIdentifier(node.children[0], code, level+1);
        code<<"["; generateIdentifier(node.children[1], code, level+1); code<<"]";
        opertInd = 2;
    }
    else if(node.children[3].token.type == TokenType::OPERATOR){
        // matrix variable : mat[i][j]
        generateIdentifier(node.children[0], code, level+1);
        code<<"["; generateIdentifier(node.children[1], code, level+1); code<<"]";
        code<<"["; generateIdentifier(node.children[2], code, level+1); code<<"]";
        opertInd = 3;
    }
     
    code << " "; generateIdentifier(node.children[opertInd], code, level+1); code << " ";
    generateNodeCode(node.children[opertInd+1], code, level+1);
    code << ";" << endl;
}

void CodeGenerator::generateExpression(const Node& node, stringstream& code, int level) {
    for(const Node& child : node.children){
        generateIdentifier(child, code, level+1);
        code << " ";
    }
}

void CodeGenerator::generatePrint(const Node& node, stringstream& code, int level) {
    indent(code, level); code << "cout << ";
    for(size_t ind = 0; ind < node.children.size(); ++ind){
        const Node& child = node.children[ind];
        // if(child.token.type == TokenType::STRINGVAL){
        //     code << "\"";
        //     generateIdentifier(child, code, level+1);
        //     code << "\"";
        // }
        // else generateIdentifier(child, code, level+1);
        generateIdentifier(child, code, level+1);
        if(ind < node.children.size() - 1) code << " << \" \" << ";
    }
    code << " << endl;" << endl;
}

void CodeGenerator::generateIfStatement(const Node& node, stringstream& code, int level) {
    indent(code, level); code << "if ( ";
    generateNodeCode(node.children[0], code, level+1);
    code << ") {" << endl;
    Node ifBlock = node.children[1];
    for(Node child : ifBlock.children){
        generateNodeCode(child, code, level+1);
    }
    indent(code, level); code << "}" << endl;
    
    if(node.children.size() > 2){
        indent(code, level); code<<"else {"<<endl;
        Node elseBlock = node.children[2];
        for(Node child : elseBlock.children){
            generateNodeCode(child, code, level+1);
        }
        indent(code, level); code<<"}"<<endl;
        code<<endl;
    }
}

void CodeGenerator::generateForLoop(const Node& node, stringstream& code, int level) {
    Node condition = node.children[0];
    string iterator = condition.children[0].token.lexeme;

    indent(code, level); code << "for (int ";
    generateNodeCode(node.children[0], code, level+1);
    code << "; "<<iterator<<" <= ";
    generateNodeCode(node.children[1], code, level+1);
    code << "; ";
    code <<iterator<<"++) {" << std::endl;

    Node forBlock = node.children[2];
    for(Node child : forBlock.children){
        generateNodeCode(child, code, level+1);
    }

    indent(code, level); code << "}" << endl;
    code<<endl;
}

void CodeGenerator::generateWhileLoop(const Node& node, stringstream& code, int level) {
    indent(code, level); code << "while (";
    generateNodeCode(node.children[0], code, level+1);
    code << ") {" << endl;
    
    Node whileBlock = node.children[1];
    for(Node child : whileBlock.children){
        generateNodeCode(child, code, level+1);
    }

    indent(code, level); code << "}" << endl;
    code<<endl;
}

void CodeGenerator::generateDoWhileLoop(const Node& node, stringstream& code, int level) {
    code << "do {" << endl;
    // Generate do-while loop body (not implemented in this example)
    code << "    // Do-while loop body" << endl;
    code << "} while (";
    generateNodeCode(node.children[0], code, level);
    code << ");" << endl;
}

void CodeGenerator::generateIdentifier(const Node& node, stringstream& code, int level) {
    if(node.token.type == TokenType::STRINGVAL){
        code <<"\""<<node.token.lexeme<<"\"";
    }
    else{
        code << node.token.lexeme;
    }
}

void CodeGenerator::indent(stringstream& code, int level){
    for(int ind=0; ind<level; ind++){
        code<<"\t";
    }
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