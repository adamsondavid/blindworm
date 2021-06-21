#ifndef BLINDWORM_COMPILER_ABSTRACTPARSER_H
#define BLINDWORM_COMPILER_ABSTRACTPARSER_H

#include "../lexer/abstractlexer.h"
#include "program.h"

class AbstractParser {
protected:
    AbstractLexer* lexer;

public:
    AbstractParser(AbstractLexer* lexer) : lexer(lexer) { }
    virtual ~AbstractParser() { }
    virtual ast::Program* parse() = 0;
};

#endif //BLINDWORM_COMPILER_ABSTRACTPARSER_H
