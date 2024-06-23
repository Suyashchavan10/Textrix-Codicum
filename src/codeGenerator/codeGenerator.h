#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <sstream>
#include "../parser/parser.h" // Make sure to include parser.h to access Node and NodeType

// CodeGenerator class to generate code from AST
class CodeGenerator {
public:
    std::string generateCode(const Node& ast);

private:
    void generateNodeCode(const Node& node, std::stringstream& code, int level);
    void generateDeclaration(const Node& node, std::stringstream& code, int level);
    void generateFunctionDeclaration(const Node& node, std::stringstream& code, int level);
    void generateAssignment(const Node& node, std::stringstream& code, int level);
    void generateExpression(const Node& node, std::stringstream& code, int level);
    void generatePrint(const Node& node, std::stringstream& code, int level);
    void generateIfStatement(const Node& node, std::stringstream& code, int level);
    void generateForLoop(const Node& node, std::stringstream& code, int level);
    void generateWhileLoop(const Node& node, std::stringstream& code, int level);
    void generateDoWhileLoop(const Node& node, std::stringstream& code, int level);
    void generateIdentifier(const Node& node, std::stringstream& code, int level);
    void indent(std::stringstream& code, int level);
};

#endif // CODEGENERATOR_H
