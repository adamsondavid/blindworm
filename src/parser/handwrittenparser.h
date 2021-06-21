#ifndef BLINDWORM_COMPILER_PARSER_H
#define BLINDWORM_COMPILER_PARSER_H

#include "abstractparser.h"
#include "../lexer/abstractlexer.h"
#include "../lexer/token.h"
#include "program.h"
#include "statement.h"
#include "expression.h"
#include <exception>
#include <string>
#include <vector>

class HandwrittenParser : public AbstractParser {
private:
    Token lookAhead;

public:
    HandwrittenParser(AbstractLexer* lexer);
    virtual ~HandwrittenParser() { }
    virtual ast::Program* parse() override;

private:
    void accept(Token::Type tokenType);
    //* === Productions: @see Grammar === *//
    std::vector<ast::Statement*> statements();
    ast::Statement* statement();
    ast::LiteralExpression* literal();
    ast::ReturnType* returntype();
    ast::DataType* datatype();
    std::vector<ast::VariableDeclarationStatement*> formal_parameters();
    ast::VariableDeclarationStatement* formal_parameter();
    std::vector<ast::Expression*> call_parameters();
    ast::Expression* expression();
    ast::Expression* or_expression();
    ast::Expression* and_expression();
    ast::Expression* not_expression();
    ast::Expression* comparison_expression();
    ast::Expression* arithmetic_expression();
    ast::Expression* term();
    ast::Expression* factor();
    ast::Expression* atom();
    ast::FunctionDefinitionStatement* function_definition();
    ast::NativeFunctionDefinitionStatement* native_function_definition();
    ast::Statement* variable_assignment_OR_variable_declaration_OR_function_call();
    ast::AssignmentStatement* variable_assignment(std::string identifier);
    ast::VariableDeclarationStatement* variable_declaration(std::string identifier);
    ast::FunctionCallExpression* function_call(std::string identifier);
    ast::ReturnStatement* return_statement();
    ast::WhileStatement* while_statement();
    ast::IfStatement* if_statement();
    std::vector<ast::ElifStatement*> elif_statements();
    ast::ElifStatement* elif_statement();
    ast::ElseStatement* else_statement();
};

#endif //BLINDWORM_COMPILER_PARSER_H
