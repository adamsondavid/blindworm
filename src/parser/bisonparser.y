%{
    #include "bisonparser.h"
    #include "../lexer/token.h"
    #include <string>
    #include <exception>

    // Room for improvement: replace with a std::variant
    struct value_t {
        std::string token_value;
        ast::Program* program;
        std::vector<ast::Statement*> statements;
        ast::Statement* statement;
        ast::LiteralExpression* literal_expression;
        ast::ReturnType* returntype;
        ast::DataType* datatype;
        std::vector<ast::VariableDeclarationStatement*> variable_declaration_statements;
        ast::VariableDeclarationStatement* variable_declaration_statement;
        std::vector<ast::Expression*> expressions;
        ast::Expression* expression;
        ast::FunctionDefinitionStatement* function_definition_statement;
        ast::NativeFunctionDefinitionStatement* native_function_definition_statement;
        ast::AssignmentStatement* assignment_statement;
        ast::FunctionCallExpression* function_call_expression;
        ast::ReturnStatement* return_statement;
        ast::WhileStatement* while_statement;
        ast::IfStatement* if_statement;
        std::vector<ast::ElifStatement*> elif_statements;
        ast::ElifStatement* elif_statement;
        ast::ElseStatement* else_statement;
    };
    #define YYSTYPE value_t

    int yylex(YYSTYPE* lvalp, AbstractLexer* lexer);
    int yyerror(AbstractLexer* lexer, ast::Program** program, const char* msg);
%}

%output                                     "bisonparser.cpp"
%define                                     api.pure

%lex-param                                  { AbstractLexer* lexer }
%parse-param                                { AbstractLexer* lexer }
%parse-param                                { ast::Program** program }

%token                                      NATIVE
%token                                      DEF
%token                                      ARROW
%token                                      RETURN
%token                                      IF
%token                                      ELSE
%token                                      ELIF
%token                                      WHILE
%token                                      COLON
%token                                      COMMA
%token                                      SEMICOLON
%token                                      LPAREN
%token                                      RPAREN
%token                                      PLUS
%token                                      MINUS
%token                                      MUL
%token                                      DIV
%token                                      NOT_EQUALS
%token                                      EQUALS
%token                                      GREATER_THAN
%token                                      GREATER_EQUALS
%token                                      LESS_THAN
%token                                      LESS_EQUALS
%token                                      AND
%token                                      OR
%token                                      NOT
%token  <token_value>                       IDENTIFIER
%token                                      NONE
%token                                      BOOL
%token                                      INT
%token                                      FLOAT
%token                                      STR
%token  <token_value>                       INT_LITERAL
%token  <token_value>                       FLOAT_LITERAL
%token  <token_value>                       STR_LITERAL
%token  <token_value>                       BOOL_LITERAL
%token                                      ASSIGN

%type   <program>                           program
%type   <statements>                        statements
%type   <statement>                         statement
%type   <literal_expression>                literal
%type   <returntype>                        returntype
%type   <datatype>                          datatype
%type   <variable_declaration_statements>   formal_parameters
%type   <variable_declaration_statement>    formal_parameter
%type   <expressions>                       call_parameters
%type   <expression>                        expression
%type   <expression>                        or_expression
%type   <expression>                        and_expression
%type   <expression>                        not_expression
%type   <expression>                        comparison_expression
%type   <expression>                        arithmetic_expression
%type   <expression>                        term
%type   <expression>                        factor
%type   <expression>                        atom
%type   <function_definition_statement>     function_definition
%type   <native_function_definition_statement>  native_function_definition
%type   <assignment_statement>              variable_assignment
%type   <variable_declaration_statement>    variable_declaration
%type   <function_call_expression>          function_call
%type   <return_statement>                  return_statement
%type   <while_statement>                   while_statement
%type   <if_statement>                      if_statement
%type   <elif_statements>                   elif_statements
%type   <elif_statement>                    elif_statement
%type   <else_statement>                    else_statement

%%

program: statements YYEOF                                               { *program = new ast::Program($1); }

statements: statement statements                                        { $2.insert($2.begin(), $1); $$ = $2; }
    |                                                                   { $$ = std::vector<ast::Statement*>(); }

statement: function_definition                                          { $$ = $1; }
    | native_function_definition                                        { $$ = $1; }
    | variable_assignment                                               { $$ = $1; }
    | variable_declaration                                              { $$ = $1; }
    | function_call SEMICOLON                                           { $$ = new ast::FunctionCallStatement($1); }
    | return_statement                                                  { $$ = $1; }
    | while_statement                                                   { $$ = $1; }
    | if_statement                                                      { $$ = $1; }
    |                                                                   { $$ = NO_STMT; }

literal: BOOL_LITERAL                                                   { $$ = new ast::BoolLiteralExpression($1 == "True" || $1 == "On"); }
    | INT_LITERAL                                                       { $$ = new ast::IntLiteralExpression(std::stoi($1)); }
    | FLOAT_LITERAL                                                     { $$ = new ast::FloatLiteralExpression(std::stof($1)); }
    | STR_LITERAL                                                       { $$ = new ast::StrLiteralExpression($1); }

returntype: datatype                                                    { $$ = $1; }
    | NONE                                                              { $$ = new ast::NoneType(); }

datatype: BOOL                                                          { $$ = new ast::BoolType(); }
    | INT                                                               { $$ = new ast::IntType(); }
    | FLOAT                                                             { $$ = new ast::FloatType(); }
    | STR                                                               { $$ = new ast::StrType(); }

formal_parameters: formal_parameter COMMA formal_parameters             { $3.insert($3.begin(), $1); $$ = $3; }
    | formal_parameter                                                  { $$ = std::vector<ast::VariableDeclarationStatement*>{$1}; }
    |                                                                   { $$ = std::vector<ast::VariableDeclarationStatement*>(); }

formal_parameter: IDENTIFIER COLON datatype                             { $$ = new ast::VariableDeclarationStatement($1, $3, NO_EXPR); }
    | IDENTIFIER COLON datatype ASSIGN literal                          { $$ = new ast::VariableDeclarationStatement($1, $3, $5); }
    |                                                                   { $$ = nullptr; }

call_parameters: expression                                             { $$ = std::vector<ast::Expression*>{$1}; }
    | expression COMMA call_parameters                                  { $3.insert($3.begin(), $1); $$ = $3; }
    |                                                                   { $$ = std::vector<ast::Expression*>(); }

expression: or_expression                                               { $$ = $1; }

or_expression: and_expression OR or_expression                          { $$ = new ast::OrExpression($1, $3); }
    | and_expression                                                    { $$ = $1; }

and_expression: not_expression AND and_expression                       { $$ = new ast::AndExpression($1, $3); }
    | not_expression                                                    { $$ = $1; }

not_expression: NOT not_expression                                      { $$ = new ast::NotExpression($2); }
    | comparison_expression                                             { $$ = $1; }

comparison_expression: arithmetic_expression NOT_EQUALS comparison_expression   { $$ = new ast::NotEqualsExpression($1, $3); }
    | arithmetic_expression EQUALS comparison_expression                { $$ = new ast::EqualsExpression($1, $3); }
    | arithmetic_expression GREATER_THAN comparison_expression          { $$ = new ast::GreaterThanExpression($1, $3); }
    | arithmetic_expression GREATER_EQUALS comparison_expression        { $$ = new ast::GreaterEqualsExpression($1, $3); }
    | arithmetic_expression LESS_THAN comparison_expression             { $$ = new ast::LessThanExpression($1, $3); }
    | arithmetic_expression LESS_EQUALS comparison_expression           { $$ = new ast::LessEqualsExpression($1, $3); }
    | arithmetic_expression                                             { $$ = $1; }

arithmetic_expression: term PLUS arithmetic_expression                  { $$ = new ast::AdditionExpression($1, $3); }
    | term MINUS arithmetic_expression                                  { $$ = new ast::SubtractionExpression($1, $3); }
    | term                                                              { $$ = $1; }

term: factor MUL term                                                   { $$ = new ast::MultiplicationExpression($1, $3); }
    | factor DIV term                                                   { $$ = new ast::DivisionExpression($1, $3); }
    | factor                                                            { $$ = $1; }

factor: MINUS atom                                                      { $$ = new ast::MultiplicationExpression(new ast::IntLiteralExpression(-1), $2); }
    | atom                                                              { $$ = $1; }

atom: literal                                                           { $$ = $1; }
    | IDENTIFIER                                                        { $$ = new ast::IdentifierExpression($1); }
    | function_call                                                     { $$ = $1; }
    | LPAREN expression RPAREN                                          { $$ = $2; }

function_definition: DEF IDENTIFIER LPAREN formal_parameters RPAREN ARROW returntype COLON LPAREN statements RPAREN { $$ = new ast::FunctionDefinitionStatement($2, $7, $4, $10);}

native_function_definition: NATIVE DEF IDENTIFIER LPAREN formal_parameters RPAREN ARROW returntype SEMICOLON { $$ = new ast::NativeFunctionDefinitionStatement($3, $8, $5); }

variable_assignment: IDENTIFIER ASSIGN expression SEMICOLON             { $$ = new ast::AssignmentStatement($1, $3); }

variable_declaration: IDENTIFIER COLON datatype ASSIGN expression SEMICOLON { $$ = new ast::VariableDeclarationStatement($1, $3, $5); }
    | IDENTIFIER COLON datatype SEMICOLON                               { $$ = new ast::VariableDeclarationStatement($1, $3, NO_EXPR); }

function_call: IDENTIFIER LPAREN call_parameters RPAREN                 { $$ = new ast::FunctionCallExpression($1, $3); }

return_statement: RETURN expression SEMICOLON                           { $$ = new ast::ReturnStatement($2); }
    | RETURN SEMICOLON                                                  { $$ = new ast::ReturnStatement(NO_EXPR); }

while_statement: WHILE LPAREN expression RPAREN COLON LPAREN statements RPAREN  { $$ = new ast::WhileStatement($3, $7); }

if_statement: IF LPAREN expression RPAREN COLON LPAREN statements RPAREN elif_statements else_statement { $$ = new ast::IfStatement($3, $7, $9, $10); }

elif_statements: elif_statement elif_statements                         { $2.insert($2.begin(), $1); $$ = $2; }
    |                                                                   { $$ = std::vector<ast::ElifStatement*>(); }

elif_statement: ELIF LPAREN expression RPAREN COLON LPAREN statements RPAREN    { $$ = new ast::ElifStatement($3, $7); }
    |                                                                   { $$ = NO_STMT; }

else_statement: ELSE COLON LPAREN statements RPAREN                     { $$ = new ast::ElseStatement($4); }
    |                                                                   { $$ = NO_STMT; }

%%

int toBisonToken(Token::Type t) {
    if(Token::Type::UNKNOWN == t)           return YYUNDEF;
    if(Token::Type::END_OF_FILE == t)       return YYEOF;
    if(Token::Type::NATIVE == t)            return NATIVE;
    if(Token::Type::DEF == t)               return DEF;
    if(Token::Type::ARROW == t)             return ARROW;
    if(Token::Type::RETURN == t)            return RETURN;
    if(Token::Type::IF == t)                return IF;
    if(Token::Type::ELSE == t)              return ELSE;
    if(Token::Type::ELIF == t)              return ELIF;
    if(Token::Type::WHILE == t)             return WHILE;
    if(Token::Type::COLON == t)             return COLON;
    if(Token::Type::COMMA == t)             return COMMA;
    if(Token::Type::SEMICOLON == t)         return SEMICOLON;
    if(Token::Type::LPAREN == t)            return LPAREN;
    if(Token::Type::RPAREN == t)            return RPAREN;
    if(Token::Type::PLUS == t)              return PLUS;
    if(Token::Type::MINUS == t)             return MINUS;
    if(Token::Type::MUL == t)               return MUL;
    if(Token::Type::DIV == t)               return DIV;
    if(Token::Type::NOT_EQUALS == t)        return NOT_EQUALS;
    if(Token::Type::EQUALS == t)            return EQUALS;
    if(Token::Type::GREATER_THAN == t)      return GREATER_THAN;
    if(Token::Type::GREATER_EQUALS == t)    return GREATER_EQUALS;
    if(Token::Type::LESS_THAN == t)         return LESS_THAN;
    if(Token::Type::LESS_EQUALS == t)       return LESS_EQUALS;
    if(Token::Type::AND == t)               return AND;
    if(Token::Type::OR == t)                return OR;
    if(Token::Type::NOT == t)               return NOT;
    if(Token::Type::IDENTIFIER == t)        return IDENTIFIER;
    if(Token::Type::NONE == t)              return NONE;
    if(Token::Type::BOOL == t)              return BOOL;
    if(Token::Type::INT == t)               return INT;
    if(Token::Type::FLOAT == t)             return FLOAT;
    if(Token::Type::STR == t)               return STR;
    if(Token::Type::INT_LITERAL == t)       return INT_LITERAL;
    if(Token::Type::FLOAT_LITERAL == t)     return FLOAT_LITERAL;
    if(Token::Type::STR_LITERAL == t)       return STR_LITERAL;
    if(Token::Type::BOOL_LITERAL == t)      return BOOL_LITERAL;
    if(Token::Type::ASSIGN == t)            return ASSIGN;
    return YYUNDEF;
}

int yylex(YYSTYPE* lvalp, AbstractLexer* lexer) {
    Token token = lexer->next();
    lvalp->token_value = token.getValue();
    return toBisonToken(token.getTokenType());
}

int yyerror(AbstractLexer* lexer, ast::Program** program, const char* msg) {
    throw std::runtime_error(msg);
    return 0;
}

BisonParser::BisonParser(AbstractLexer *lexer) : AbstractParser(lexer) { }

BisonParser::~BisonParser() { }

ast::Program* BisonParser::parse() {
    ast::Program* program = nullptr;
    yyparse(this->lexer, &program);
    return program;
}
