#include "handwrittenlexer.h"

HandwrittenLexer::HandwrittenLexer(std::istream *inputStream): inputStream(inputStream), lastChar(' ') { }

Token HandwrittenLexer::next() {
    while(isspace(this->nextChar())) { }
    if('(' == this->lastChar) return Token(Token::Type::LPAREN);
    if(')' == this->lastChar) return Token(Token::Type::RPAREN);
    if('+' == this->lastChar) return Token(Token::Type::PLUS);
    if('*' == this->lastChar) return Token(Token::Type::MUL); // NO **
    if('/' == this->lastChar) return Token(Token::Type::DIV);
    if(',' == this->lastChar) return Token(Token::Type::COMMA);
    if(':' == this->lastChar) return Token(Token::Type::COLON);
    if(';' == this->lastChar) return Token(Token::Type::SEMICOLON);
    if('-' == this->lastChar) {
        if ('>' == this->peekChar()) {
            this->nextChar();
            return Token(Token::Type::ARROW);
        }
        return Token(Token::Type::MINUS);
    }
    if('>' == this->lastChar) {
        if('=' == this->peekChar()) {
            this->nextChar();
            return Token(Token::Type::GREATER_EQUALS);
        }
        return Token(Token::Type::GREATER_THAN);
    }
    if('<' == this->lastChar) {
        if('=' == this->peekChar()) {
            this->nextChar();
            return Token(Token::Type::LESS_EQUALS);
        }
        return Token(Token::Type::LESS_THAN);
    }
    if('=' == this->lastChar) {
        if('=' == this->peekChar()) {
            this->nextChar();
            return Token(Token::Type::EQUALS);
        }
        return Token(Token::Type::ASSIGN);
    }
    if('!' == this->lastChar) {
        if('=' == this->peekChar()) {
            this->nextChar();
            return Token(Token::Type::NOT_EQUALS);
        }
    }
    if('"' == this->lastChar || '\'' == this->lastChar) {
        char quote = this->lastChar;
        std::string buffer;
        for(this->nextChar(); this->lastChar != quote; this->nextChar()){
            buffer += this->lastChar;
        }
        return Token(Token::Type::STR_LITERAL, buffer);
    }
    if(isdigit(this->lastChar) || '.' == this->lastChar) { // Int or float literal
        return parseIntOrFloat();
    }
    if(isalpha(this->lastChar)) {
        return parseIdentOrKeyword();
    }
    if(EOF == this->lastChar) {
        return Token(Token::Type::END_OF_FILE);
    }
    return Token(Token::Type::UNKNOWN);
}

Token HandwrittenLexer::parseIntOrFloat(){
    std::string buffer;
    buffer += this->lastChar;
    while(isdigit(this->peekChar()) || '.' == this->peekChar()) {
        buffer += this->nextChar();
    }
    //TODO: maybe set a flag, or the return type in a variable
    if(buffer.find('.') == std::string::npos) {
        return Token(Token::Type::INT_LITERAL, buffer);
    }

    return Token(Token::Type::FLOAT_LITERAL, buffer);
}

Token HandwrittenLexer::parseIdentOrKeyword() {
    std::string buffer;

    buffer += this->lastChar;
    while(isalnum(this->peekChar()) || isdigit(this->peekChar()) || '_' == this->peekChar()) {
        buffer += this->nextChar();
    }

    if("native" == buffer) return Token(Token::Type::NATIVE);
    if("def" == buffer) return Token(Token::Type::DEF);
    if("return" == buffer) return Token(Token::Type::RETURN);
    if("if" == buffer) return Token(Token::Type::IF);
    if("else" == buffer) return Token(Token::Type::ELSE);
    if("elif" == buffer) return Token(Token::Type::ELIF);
    if("while" == buffer) return Token(Token::Type::WHILE);
    if("and" == buffer) return Token(Token::Type::AND);
    if("or" == buffer) return Token(Token::Type::OR);
    if("not" == buffer) return Token(Token::Type::NOT);
    if("None" == buffer) return Token(Token::Type::NONE);
    if("bool" == buffer) return Token(Token::Type::BOOL);
    if("int" == buffer) return Token(Token::Type::INT);
    if("float" == buffer) return Token(Token::Type::FLOAT);
    if("str" == buffer) return Token(Token::Type::STR);

    if("True" == buffer || "False" == buffer || "Yes" == buffer || "No" == buffer)
        return Token(Token::Type::BOOL_LITERAL, buffer);

    return Token(Token::Type::IDENTIFIER, buffer);
}
