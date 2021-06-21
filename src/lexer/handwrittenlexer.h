#ifndef BLINDWORM_COMPILER_LEXER_H
#define BLINDWORM_COMPILER_LEXER_H

#include "abstractlexer.h"
#include <istream>
#include "stdio.h"
#include <string>
#include <ctype.h>
#include "token.h"

class HandwrittenLexer : public AbstractLexer {
private:
    std::istream* inputStream;
    char lastChar;

public:
    HandwrittenLexer(std::istream* inputStream);
    virtual ~HandwrittenLexer() { }

    /**
     * @brief Retrieve the next Token in the inputstream
     * @return Token
     */
    virtual Token next() override;

private:
    /**
     * @brief 'eat' the next char, and set this.lastChar Variable
     * @return char 
     */
    inline char nextChar() {
        this->lastChar = this->inputStream->get();
        return this->lastChar;
    }

    /**
     * @brief peek the next char ot the inputstream
     * @return char 
     */
    inline char peekChar() {
        return this->inputStream->peek();
    }

    /**
     * @brief Evaluate the next chars as a numerical value
     * @return Token(Token::Type::INT_LITERAL || Token::Type::FLOAT_LITERAL)
     */
    Token parseIntOrFloat();

    /**
     * @brief Evaluate the next chars in the inputstream as either a keyword or an identifier
     * @return Token
     */
    Token parseIdentOrKeyword();
};

#endif //BLINDWORM_COMPILER_LEXER_H
