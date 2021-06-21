#ifndef BLINDWORM_COMPILER_FLEXER_H
#define BLINDWORM_COMPILER_FLEXER_H

#include "abstractlexer.h"

class FlexLexer : public AbstractLexer {
private:
    void* lexer_id;
public:
    FlexLexer(FILE* file);
    virtual ~FlexLexer();
    virtual Token next() override;
};

#endif //BLINDWORM_COMPILER_FLEXER_H
