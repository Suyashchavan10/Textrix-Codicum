#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include "../codeGenerator/codeGenerator.cpp"

using namespace std;

int main() {
    
    // Read the pseudocode from the file
    ifstream inputFile("../pseudocode/pseudocode.txt");
    // ifstream inputFile("../uploads/pseudocode.txt");
    
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
    cout<<"---------------------------  TOKENS GENERATION --------------------------------------"<<endl;
    cout<<endl;
    for (const auto& token : tokens) {
        cout << "Token: " << token.lexeme << "\tType: " << static_cast<int>(token.type) << endl;
    }
    cout<<endl;


    // Create parser instance
    Parser parser(tokens);

    // Parse the tokens to create an AST
    Node ast = parser.parse();

    cout<<"---------------------------  ABSTRACT SYNTAX TREE (AST) GENERATION --------------------------------------"<<endl;
    cout<<endl;
    printAST(ast);
    cout<<endl;

    // Create CodeGenerator instance
    CodeGenerator generator;

    // Generate code from AST
    string generatedCode = generator.generateCode(ast);

    // Print generated code
    cout<<"---------------------------  CODE GENERATION --------------------------------------"<<endl;
    cout<<endl;
    cout << generatedCode << endl;
    cout<<"-----------------------------------------------------------------------------------"<<endl;

    // Write generated code to code.cpp
    // ofstream outputFile("../uploads/code.cpp");
    ofstream outputFile("../uploads/generatedCode.cpp");
    if (!outputFile) {
        cerr << "Failed to open code.cpp for writing" << endl;
        return 1;
    }
    outputFile << generatedCode;
    outputFile.close();

    cout << "PSEUDOCODE IS CONVERTED TO C++ SUCCESSFULLY!" << endl;
    return 0;
}