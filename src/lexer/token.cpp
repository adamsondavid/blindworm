#include "token.h"

Token::Token() : Token(Token::Type::UNKNOWN) { }

Token::Token(Token::Type tokenType) : Token(tokenType, "") { }

Token::Token(Token::Type tokenType, std::string value) : tokenType(tokenType), value(value) { }


/**
 * @brief retrieve the string-value of the current type
 * 
 * @return std::string 
 */
std::string Token::tokenTypeToString(Token::Type tokenType) {
    switch (tokenType) {
        case Type::UNKNOWN:
            return "UNKNOWN";
        case Type::END_OF_FILE:
            return "END_OF_FILE";
        case Type::NATIVE:
            return "NATIVE";
        case Type::DEF:
            return "DEF";
        case Type::ARROW:
            return "ARROW";
        case Type::RETURN:
            return "RETURN";
        case Type::IF:
            return "IF";
        case Type::ELSE:
            return "ELSE";
        case Type::ELIF:
            return "ELIF";
        case Type::WHILE:
            return "WHILE";
        case Type::COLON:
            return "COLON";
        case Type::COMMA:
            return "COMMA";
        case Type::SEMICOLON:
            return "SEMICOLON";
        case Type::LPAREN:
            return "LPAREN";
        case Type::RPAREN:
            return "RPAREN";
        case Type::PLUS:
            return "PLUS";
        case Type::MINUS:
            return "MINUS";
        case Type::MUL:
            return "MUL";
        case Type::DIV:
            return "DIV";
        case Type::NOT_EQUALS:
            return "NOT_EQUALS";
        case Type::EQUALS:
            return "EQUALS";
        case Type::GREATER_THAN:
            return "GREATER_THAN";
        case Type::GREATER_EQUALS:
            return "GREATER_EQUALS";
        case Type::LESS_THAN:
            return "LESS_THAN";
        case Type::LESS_EQUALS:
            return "LESS_EQUALS";
        case Type::AND:
            return "AND";
        case Type::OR:
            return "OR";
        case Type::NOT:
            return "NOT";
        case Type::IDENTIFIER:
            return "IDENTIFIER";
        case Type::NONE:
            return "NONE";
        case Type::BOOL:
            return "BOOL";
        case Type::INT:
            return "INT";
        case Type::FLOAT:
            return "FLOAT";
        case Type::STR:
            return "STR";
        case Type::INT_LITERAL:
            return "INT_LITERAL";
        case Type::FLOAT_LITERAL:
            return "FLOAT_LITERAL";
        case Type::STR_LITERAL:
            return "STR_LITERAL";
        case Type::BOOL_LITERAL:
            return "BOOL_LITERAL";
        case Type::ASSIGN:
            return "ASSIGN";
        default:
            return "NO_TO_STRING_FOUND";
    }
}
