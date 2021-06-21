#ifndef BLINDWORM_COMPILER_BARSER_H
#define BLINDWORM_COMPILER_BARSER_H

#include "abstractparser.h"

class BisonParser : public AbstractParser {
public:
    BisonParser(AbstractLexer* lexer);
    virtual ~BisonParser();
    virtual ast::Program* parse() override;
};

#endif //BLINDWORM_COMPILER_BARSER_H
