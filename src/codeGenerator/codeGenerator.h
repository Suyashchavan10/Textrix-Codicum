#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <sstream>
#include "../parser/parser.h" // Make sure to include parser.h to access Node and NodeType

// CodeGenerator class to generate code from AST
class CodeGenerator {
public:
    std::string generateCode(const Node& ast);

private:
    void generateNodeCode(const Node& node, std::stringstream& code);
    void generateDeclaration(const Node& node, std::stringstream& code);
    void generateFunctionDeclaration(const Node& node, std::stringstream& code);
    void generateAssignment(const Node& node, std::stringstream& code);
    void generateExpression(const Node& node, std::stringstream& code);
    void generatePrint(const Node& node, std::stringstream& code);
    void generateIfStatement(const Node& node, std::stringstream& code);
    void generateForLoop(const Node& node, std::stringstream& code);
    void generateWhileLoop(const Node& node, std::stringstream& code);
    void generateDoWhileLoop(const Node& node, std::stringstream& code);
    void generateIdentifier(const Node& node, std::stringstream& code);
};

#endif // CODEGENERATOR_H
