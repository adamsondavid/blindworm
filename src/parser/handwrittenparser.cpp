#include "handwrittenparser.h"

HandwrittenParser::HandwrittenParser(AbstractLexer* lexer) : AbstractParser(lexer) {
    this->lookAhead = this->lexer->next();
}

void HandwrittenParser::accept(Token::Type tokenType) {
    if(this->lookAhead.getTokenType() == tokenType){
        this->lookAhead = this->lexer->next();
    } else {
        throw std::runtime_error("expected " + Token::tokenTypeToString(tokenType) + " but got " + Token::tokenTypeToString(this->lookAhead.getTokenType()));
    }
}

ast::Program* HandwrittenParser::parse() {
    ast::Program* program = new ast::Program(this->statements());
    this->accept(Token::Type::END_OF_FILE);
    return program;
}

std::vector<ast::Statement*> HandwrittenParser::statements() {
    ast::Statement* statement = this->statement();
    if(statement == NO_STMT){
        return std::vector<ast::Statement*>();
    }
    std::vector<ast::Statement*> statements = this->statements();
    statements.insert(statements.begin(), statement);
    return statements;
}

ast::Statement* HandwrittenParser::statement() {
    Token::Type tokenType = this->lookAhead.getTokenType();
    std::string tokenValue = this->lookAhead.getValue();

    if(tokenType == Token::Type::DEF){
        return this->function_definition();
    }
    if(tokenType == Token::Type::NATIVE){
        return this->native_function_definition();
    }
    if(tokenType == Token::Type::IDENTIFIER){
        return this->variable_assignment_OR_variable_declaration_OR_function_call();
    }
    if(tokenType == Token::Type::RETURN){
        return this->return_statement();
    }
    if(tokenType == Token::Type::WHILE){
        return this->while_statement();
    }
    if(tokenType == Token::Type::IF){
        return  this->if_statement();
    }

    return NO_STMT;
}

ast::LiteralExpression* HandwrittenParser::literal() {
    Token::Type tokenType = this->lookAhead.getTokenType();
    std::string tokenValue = this->lookAhead.getValue();

    if(tokenType == Token::Type::BOOL_LITERAL) {
        this->accept(Token::Type::BOOL_LITERAL);
        return new ast::BoolLiteralExpression(tokenValue == "True" || tokenValue == "On");
    }
    if(tokenType == Token::Type::INT_LITERAL){
        this->accept(Token::Type::INT_LITERAL);
        return new ast::IntLiteralExpression(std::stoi(tokenValue));
    }
    if(tokenType == Token::Type::FLOAT_LITERAL){
        this->accept(Token::Type::FLOAT_LITERAL);
        return new ast::FloatLiteralExpression(std::stof(tokenValue));
    }
    if(tokenType == Token::Type::STR_LITERAL){
        this->accept(Token::Type::STR_LITERAL);
        return new ast::StrLiteralExpression(tokenValue);
    }

    throw std::runtime_error("expected any kind of literal but got " + Token::tokenTypeToString(this->lookAhead.getTokenType()));
}

ast::ReturnType *HandwrittenParser::returntype() {
    if(this->lookAhead.getTokenType() == Token::Type::NONE){
        this->accept(Token::Type::NONE);
        return new ast::NoneType();
    }

    return this->datatype();
}

ast::DataType *HandwrittenParser::datatype() {
    Token::Type tokenType = this->lookAhead.getTokenType();

    if(tokenType == Token::Type::BOOL){
        this->accept(Token::Type::BOOL);
        return new ast::BoolType();
    }
    if(tokenType == Token::Type::INT){
        this->accept(Token::Type::INT);
        return new ast::IntType();
    }
    if(tokenType == Token::Type::FLOAT){
        this->accept(Token::Type::FLOAT);
        return new ast::FloatType();
    }
    if(tokenType == Token::Type::STR){
        this->accept(Token::Type::STR);
        return new ast::StrType();
    }

    throw std::runtime_error("expected BOOL, INT, FLOAT or STR but got " + Token::tokenTypeToString(tokenType));
}

/**
 * formal_parameters:
 *
 *   | formal_parameter COMMA formal_parameters
 *
 *   | formal_parameter
 *
 *   | ε
 */
std::vector<ast::VariableDeclarationStatement*> HandwrittenParser::formal_parameters() {
    auto parameter = this->formal_parameter();

    if(parameter == nullptr)
        return std::vector<ast::VariableDeclarationStatement*>();

    //Was it a single formal_parameter ? (== not followed by comma)
    if(this->lookAhead.getTokenType() != Token::Type::COMMA)
        return std::vector<ast::VariableDeclarationStatement*>{parameter};

    this->accept(Token::Type::COMMA);

    auto parameters = this->formal_parameters();
    parameters.insert(parameters.begin(), parameter);
    return parameters;
}

/**
 * formal_parameter:
 *
 *   | IDENTIFIER COLON datatype
 *
 *   | IDENTIFIER COLON datatype ASSIGN literal
 */
ast::VariableDeclarationStatement* HandwrittenParser::formal_parameter() {
    if(this->lookAhead.getTokenType() != Token::Type::IDENTIFIER)
        return nullptr;
    std::string identifier = this->lookAhead.getValue();
    ast::LiteralExpression* value = NO_EXPR;

    this->accept(Token::Type::IDENTIFIER);
    this->accept(Token::Type::COLON);
    ast::DataType* dataType = this->datatype();

    if(this->lookAhead.getTokenType() == Token::Type::ASSIGN){
        this->accept(Token::Type::ASSIGN);
        value = this->literal();
    }
    return new ast::VariableDeclarationStatement(identifier, dataType, value);
}

/**
 * call_parameters:
 *
 *   | expression COMMA call_parameters
 *
 *   | expression
 *
 *   | ε
 *
 */
std::vector<ast::Expression*> HandwrittenParser::call_parameters() {
    Token::Type tokenType = this->lookAhead.getTokenType();

    if(tokenType == Token::Type::NOT
    || tokenType == Token::Type::MINUS
    || tokenType == Token::Type::BOOL_LITERAL
    || tokenType == Token::Type::INT_LITERAL
    || tokenType == Token::Type::FLOAT_LITERAL
    || tokenType == Token::Type::STR_LITERAL
    || tokenType == Token::Type::IDENTIFIER
    || tokenType == Token::Type::LPAREN){
        ast::Expression* expression = this->expression();
        if(this->lookAhead.getTokenType() != Token::Type::COMMA)
            return std::vector<ast::Expression*>{expression};
        this->accept(Token::Type::COMMA);
        std::vector<ast::Expression*> callParameters = this->call_parameters();
        callParameters.insert(callParameters.begin(), expression);
        return callParameters;
    }

    return std::vector<ast::Expression*>();
}

ast::Expression* HandwrittenParser::expression() {
    return this->or_expression();
}

ast::Expression* HandwrittenParser::or_expression() {
    ast::Expression* expression = this->and_expression();
    if(this->lookAhead.getTokenType() == Token::Type::OR){
        this->accept(Token::Type::OR);
        return new ast::OrExpression(expression, this->or_expression());
    }
    return expression;
}

ast::Expression* HandwrittenParser::and_expression() {
    ast::Expression* expression = this->not_expression();
    if(this->lookAhead.getTokenType() == Token::Type::AND){
        this->accept(Token::Type::AND);
        return new ast::AndExpression(expression, this->and_expression());
    }
    return expression;
}

ast::Expression* HandwrittenParser::not_expression() {
    if(this->lookAhead.getTokenType() == Token::Type::NOT){
        this->accept(Token::Type::NOT);
        return new ast::NotExpression(this->not_expression());
    }
    return this->comparison_expression();
}

ast::Expression* HandwrittenParser::comparison_expression() {
    ast::Expression* expression = this->arithmetic_expression();

    Token::Type tokenType = this->lookAhead.getTokenType();
    std::string tokenValue = this->lookAhead.getValue();

    if(tokenType == Token::Type::NOT_EQUALS){
        this->accept(Token::Type::NOT_EQUALS);
        return new ast::NotEqualsExpression(expression, this->comparison_expression());
    }
    if(tokenType == Token::Type::EQUALS){
        this->accept(Token::Type::EQUALS);
        return new ast::EqualsExpression(expression, this->comparison_expression());
    }
    if(tokenType == Token::Type::GREATER_THAN){
        this->accept(Token::Type::GREATER_THAN);
        return new ast::GreaterThanExpression(expression, this->comparison_expression());
    }
    if(tokenType == Token::Type::GREATER_EQUALS){
        this->accept(Token::Type::GREATER_EQUALS);
        return new ast::GreaterEqualsExpression(expression, this->comparison_expression());
    }
    if(tokenType == Token::Type::LESS_THAN){
        this->accept(Token::Type::LESS_THAN);
        return new ast::LessThanExpression(expression, this->comparison_expression());
    }
    if(tokenType == Token::Type::LESS_EQUALS){
        this->accept(Token::Type::LESS_EQUALS);
        return new ast::LessEqualsExpression(expression, this->comparison_expression());
    }

    return expression;
}

ast::Expression* HandwrittenParser::arithmetic_expression() {
    ast::Expression* expression = this->term();

    Token::Type tokenType = this->lookAhead.getTokenType();
    std::string tokenValue = this->lookAhead.getValue();

    if(tokenType == Token::Type::PLUS){
        this->accept(Token::Type::PLUS);
        return new ast::AdditionExpression(expression, this->arithmetic_expression());
    }
    if(tokenType == Token::Type::MINUS){
        this->accept(Token::Type::MINUS);
        return new ast::SubtractionExpression(expression, this->arithmetic_expression());
    }

    return expression;
}

ast::Expression* HandwrittenParser::term() {
    ast::Expression* expression = this->factor();

    Token::Type tokenType = this->lookAhead.getTokenType();
    std::string tokenValue = this->lookAhead.getValue();

    if(tokenType == Token::Type::MUL){
        this->accept(Token::Type::MUL);
        return new ast::MultiplicationExpression(expression, this->term());
    }
    if(tokenType == Token::Type::DIV){
        this->accept(Token::Type::DIV);
        return new ast::DivisionExpression(expression, this->term());
    }

    return expression;
}

ast::Expression* HandwrittenParser::factor() {
    Token::Type tokenType = this->lookAhead.getTokenType();
    std::string tokenValue = this->lookAhead.getValue();

    if(tokenType == Token::Type::MINUS){
        this->accept(Token::Type::MINUS);
        return new ast::MultiplicationExpression(new ast::IntLiteralExpression(-1), this->atom());
    }

    return this->atom();
}

ast::Expression* HandwrittenParser::atom() {
    Token::Type tokenType = this->lookAhead.getTokenType();
    std::string tokenValue = this->lookAhead.getValue();

    if(tokenType == Token::Type::BOOL_LITERAL
       || tokenType == Token::Type::INT_LITERAL
       || tokenType == Token::Type::FLOAT_LITERAL
       || tokenType == Token::Type::STR_LITERAL){
        return this->literal();
    }
    if(tokenType == Token::Type::IDENTIFIER){
        this->accept(Token::Type::IDENTIFIER);

        if(this->lookAhead == Token::Type::LPAREN){
            return this->function_call(tokenValue);
        }

        return new ast::IdentifierExpression(tokenValue);
    }
    if(tokenType == Token::Type::LPAREN){
        this->accept(Token::Type::LPAREN);
        ast::Expression* expression = this->expression();
        this->accept(Token::Type::RPAREN);

        return expression;
    }

    throw std::runtime_error("expected any kind of literal, IDENTIFIER or LPAREN but got " + Token::tokenTypeToString(tokenType));
}

ast::FunctionDefinitionStatement* HandwrittenParser::function_definition() {
    this->accept(Token::Type::DEF);
    std::string identifier = this->lookAhead.getValue();
    this->accept(Token::Type::IDENTIFIER);
    this->accept(Token::Type::LPAREN);
    std::vector<ast::VariableDeclarationStatement*> formalParameters = this->formal_parameters();
    this->accept(Token::Type::RPAREN);
    this->accept(Token::Type::ARROW);
    ast::ReturnType* returnType = this->returntype();
    this->accept(Token::Type::COLON);
    this->accept(Token::Type::LPAREN);
    std::vector<ast::Statement*> statements = this->statements();
    this->accept(Token::Type::RPAREN);

    return new ast::FunctionDefinitionStatement(identifier, returnType, formalParameters, statements);
}

ast::NativeFunctionDefinitionStatement* HandwrittenParser::native_function_definition() {
    this->accept(Token::Type::NATIVE);
    this->accept(Token::Type::DEF);
    std::string identifier = this->lookAhead.getValue();
    this->accept(Token::Type::IDENTIFIER);
    this->accept(Token::Type::LPAREN);
    std::vector<ast::VariableDeclarationStatement*> formalParameters = this->formal_parameters();
    this->accept(Token::Type::RPAREN);
    this->accept(Token::Type::ARROW);
    ast::ReturnType* returnType = this->returntype();
    this->accept(Token::Type::SEMICOLON);

    return new ast::NativeFunctionDefinitionStatement(identifier, returnType, formalParameters);
}

ast::Statement* HandwrittenParser::variable_assignment_OR_variable_declaration_OR_function_call() {
    std::string id = this->lookAhead.getValue();
    this->accept(Token::Type::IDENTIFIER);

    Token::Type tokenType = this->lookAhead.getTokenType();

    if(tokenType == Token::Type::ASSIGN){
        return this->variable_assignment(id);
    }
    if(tokenType == Token::Type::COLON){
        return this->variable_declaration(id);
    }
    if(tokenType == Token::Type::LPAREN){
        ast::FunctionCallExpression* functionCall = this->function_call(id);
        this->accept(Token::Type::SEMICOLON);
        return new ast::FunctionCallStatement(functionCall);
    }

    throw std::runtime_error("expected ASSIGN or COLON or LPAREN but got " + Token::tokenTypeToString(tokenType));
}

ast::AssignmentStatement* HandwrittenParser::variable_assignment(std::string identifier) {
    this->accept(Token::Type::ASSIGN);
    ast::Expression* expression = this->expression();
    this->accept(Token::Type::SEMICOLON);

    return new ast::AssignmentStatement(identifier, expression);
}

ast::VariableDeclarationStatement* HandwrittenParser::variable_declaration(std::string identifier) {
    this->accept(Token::Type::COLON);
    ast::DataType* dataType = this->datatype();

    Token::Type tokenType = this->lookAhead.getTokenType();
    std::string tokenValue = this->lookAhead.getValue();

    if(tokenType == Token::Type::ASSIGN){
        this->accept(Token::Type::ASSIGN);
        ast::Expression* expression = this->expression();
        this->accept(Token::Type::SEMICOLON);
        return new ast::VariableDeclarationStatement(identifier, dataType, expression);
    }
    if(tokenType == Token::Type::SEMICOLON){
        this->accept(Token::Type::SEMICOLON);
        return new ast::VariableDeclarationStatement(identifier, dataType, NO_EXPR);
    }

    throw std::runtime_error("expected ASSIGN or SEMICOLON but got " + Token::tokenTypeToString(tokenType));
}

ast::FunctionCallExpression* HandwrittenParser::function_call(std::string identifier) {
    this->accept(Token::Type::LPAREN);
    std::vector<ast::Expression*> callParameters = this->call_parameters();
    this->accept(Token::Type::RPAREN);

    return new ast::FunctionCallExpression(identifier, callParameters);
}

ast::ReturnStatement* HandwrittenParser::return_statement() {
    this->accept(Token::Type::RETURN);

    if(this->lookAhead.getTokenType() == Token::Type::SEMICOLON){
        this->accept(Token::Type::SEMICOLON);
        return new ast::ReturnStatement(NO_EXPR);
    }

    ast::Expression* expression = this->expression();
    this->accept(Token::Type::SEMICOLON);

    return new ast::ReturnStatement(expression);
}

ast::WhileStatement* HandwrittenParser::while_statement() {
    this->accept(Token::Type::WHILE);
    this->accept(Token::Type::LPAREN);
    ast::Expression* condition = this->expression();
    this->accept(Token::Type::RPAREN);
    this->accept(Token::Type::COLON);
    this->accept(Token::Type::LPAREN);
    std::vector<ast::Statement*> statements = this->statements();
    this->accept(Token::Type::RPAREN);

    return new ast::WhileStatement(condition, statements);
}

ast::IfStatement* HandwrittenParser::if_statement() {
    this->accept(Token::Type::IF);
    this->accept(Token::Type::LPAREN);
    ast::Expression* condition = this->expression();
    this->accept(Token::Type::RPAREN);
    this->accept(Token::Type::COLON);
    this->accept(Token::Type::LPAREN);
    std::vector<ast::Statement*> statements = this->statements();
    this->accept(Token::Type::RPAREN);
    std::vector<ast::ElifStatement*> elifStatements = this->elif_statements();
    ast::ElseStatement* elseStatement = this->else_statement();

    return new ast::IfStatement(condition, statements, elifStatements, elseStatement);
}

/**
 * elif_statements:
 *
 *   | elif_statement elif_statements
 *
 *   | ε
 *
 */
std::vector<ast::ElifStatement*> HandwrittenParser::elif_statements() {
    auto elif_stmt = this->elif_statement();
    if(elif_stmt == NO_STMT)
        return std::vector<ast::ElifStatement*>();

    std::vector<ast::ElifStatement*> elif_stmts = this->elif_statements();
    elif_stmts.insert(elif_stmts.begin(), elif_stmt);
    return elif_stmts;
}

ast::ElifStatement* HandwrittenParser::elif_statement() {
    if(this->lookAhead.getTokenType() == Token::Type::ELIF){
        this->accept(Token::Type::ELIF);
        this->accept(Token::Type::LPAREN);
        ast::Expression* condition = this->expression();
        this->accept(Token::Type::RPAREN);
        this->accept(Token::Type::COLON);
        this->accept(Token::Type::LPAREN);
        std::vector<ast::Statement*> statements = this->statements();
        this->accept(Token::Type::RPAREN);

        return new ast::ElifStatement(condition, statements);
    }
    return NO_STMT;
}

ast::ElseStatement* HandwrittenParser::else_statement() {
    if(this->lookAhead.getTokenType() == Token::Type::ELSE){
        this->accept(Token::Type::ELSE);
        this->accept(Token::Type::COLON);
        this->accept(Token::Type::LPAREN);
        std::vector<ast::Statement*> statements = this->statements();
        this->accept(Token::Type::RPAREN);

        return new ast::ElseStatement(statements);
    }
    return NO_STMT;
}
