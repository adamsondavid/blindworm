#include <iostream>
#include <fstream>

#include "lexer/handwrittenlexer.h"
#include "lexer/flexlexer.h"

#include "parser/handwrittenparser.h"
#include "parser/bisonparser.h"

#include "semantic/symboltablevisitor.h"
#include "codegen/codegen.h"

int main(int argc, char** argv) {
    std::cout << "Blindworm Compiler (c) 2021: David Niklas Adamson, Maximilian Erren" << std::endl;
    std::cout << "Version 0.1" << std::endl << std::endl;

    if(argc < 2){
        std::cerr << "error: no input file" << std::endl;
        return -1;
    }

    /*** Choose whatever combination of Lexer & Parser you would like to use! ***/
    //std::ifstream inputStream(argv[1]);
    //HandwrittenLexer lexer(&inputStream);
    FlexLexer lexer(fopen(argv[1], "r"));
    HandwrittenParser parser(&lexer);
    //BisonParser parser(&lexer);

    /*** Generate the AST ***/
    ast::Program* program = parser.parse();

    /*** Check for undeclared symbols ***/
    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    /*** Generate LLVM IR and print to .ll output file ***/
    CodeGenerator codeGenerator(argv[1]);
    program->generateCode(&codeGenerator);
    std::string llFile = std::string(argv[1]) + ".ll";
    std::ofstream outputStream(llFile);
    codeGenerator.print(&outputStream);
    outputStream.close();

    /*** Call clang to transform the .ll file into an executable ***/
    std::string clangCommand = "clang -Wno-override-module " + llFile + " -o " + std::string(argv[1]) + ".out";
    std::system(clangCommand.c_str());

    return 0;
}
