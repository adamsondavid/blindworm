#ifndef BLINDWORM_COMPILER_ABSTRACTLEXER_H
#define BLINDWORM_COMPILER_ABSTRACTLEXER_H

#include "token.h"

class AbstractLexer {
public:
    virtual ~AbstractLexer() { }

    /**
     * @brief Retrieve the next Token in the inputstream
     * @return Token
     */
    virtual Token next() = 0;
};

#endif //BLINDWORM_COMPILER_ABSTRACTLEXER_H
