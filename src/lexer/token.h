#ifndef BLINDWORM_COMPILER_TOKEN_H
#define BLINDWORM_COMPILER_TOKEN_H

#include <string>

class Token {
public:
    enum class Type {
        UNKNOWN, END_OF_FILE,
        NATIVE, DEF, ARROW, RETURN,
        IF, ELSE, ELIF, WHILE,
        COLON, COMMA, SEMICOLON,
        LPAREN, RPAREN,
        PLUS, MINUS, MUL, DIV,
        NOT_EQUALS, EQUALS,
        GREATER_THAN, GREATER_EQUALS,
        LESS_THAN, LESS_EQUALS,
        AND, OR, NOT,
        IDENTIFIER,
        NONE, BOOL, INT, FLOAT, STR,
        INT_LITERAL, FLOAT_LITERAL, STR_LITERAL, BOOL_LITERAL,
        ASSIGN
    };
private:
    Token::Type tokenType;
    std::string value;
public:
    Token();
    Token(Token::Type tokenType);
    Token(Token::Type tokenType, std::string value);
    
    /**
     * @brief get the Token-Type
     * 
     * @return Token::Type 
     */
    inline Token::Type getTokenType() {return this->tokenType;}

    /**
     * @brief get the Value, which is stored in the buffer
     * 
     * @return Token::Type 
     */
    inline std::string getValue() {return this->value;}

    static std::string tokenTypeToString(Token::Type tokenType);

    inline bool operator==(const Token &other) const {
        return (this->tokenType == other.tokenType) && (this->value == other.value);
    }

    inline std::string toString() const {
        return "Token(Token::Type::" + Token::tokenTypeToString(this->tokenType) + ", \"" + this->value + "\")";
    }

    friend std::ostream& operator<<(std::ostream& ostream, const Token& token) {
        return ostream << token.toString();
    }
};

#endif //BLINDWORM_COMPILER_TOKEN_H
