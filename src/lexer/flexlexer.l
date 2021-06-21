%{
    #include "flexlexer.h"
    #include "token.h"
    #include <string>

    #define YY_DECL Token bwyylex(void* yyscanner)
%}

%option reentrant noyywrap
%option outfile="flexlexer.cpp"
%option prefix="bwyy"

delim                               [ \t\n]
ws                                  {delim}+

%%

{ws}                                {/* do nothing */}
"native"                            { return Token(Token::Type::NATIVE); }
"def"                               { return Token(Token::Type::DEF); }
"->"                                { return Token(Token::Type::ARROW); }
"return"                            { return Token(Token::Type::RETURN); }
"if"                                { return Token(Token::Type::IF); }
"else"                              { return Token(Token::Type::ELSE); }
"elif"                              { return Token(Token::Type::ELIF); }
"while"                             { return Token(Token::Type::WHILE); }
":"                                 { return Token(Token::Type::COLON); }
","                                 { return Token(Token::Type::COMMA); }
";"                                 { return Token(Token::Type::SEMICOLON); }
"("                                 { return Token(Token::Type::LPAREN); }
")"                                 { return Token(Token::Type::RPAREN); }
"+"                                 { return Token(Token::Type::PLUS); }
"-"                                 { return Token(Token::Type::MINUS); }
"*"                                 { return Token(Token::Type::MUL); }
"/"                                 { return Token(Token::Type::DIV); }
"!="                                { return Token(Token::Type::NOT_EQUALS); }
"=="                                { return Token(Token::Type::EQUALS); }
">"                                 { return Token(Token::Type::GREATER_THAN); }
">="                                { return Token(Token::Type::GREATER_EQUALS); }
"<"                                 { return Token(Token::Type::LESS_THAN); }
"<="                                { return Token(Token::Type::LESS_EQUALS); }
"and"                               { return Token(Token::Type::AND); }
"or"                                { return Token(Token::Type::OR); }
"not"                               { return Token(Token::Type::NOT); }
"None"                              { return Token(Token::Type::NONE); }
"bool"                              { return Token(Token::Type::BOOL); }
"int"                               { return Token(Token::Type::INT); }
"float"                             { return Token(Token::Type::FLOAT); }
"str"                               { return Token(Token::Type::STR); }
"True"|"False"|"Yes"|"No"           { return Token(Token::Type::BOOL_LITERAL, yytext); }
[0-9]+                              { return Token(Token::Type::INT_LITERAL, yytext); }
([0-9]*[\.])?[0-9]+                 { return Token(Token::Type::FLOAT_LITERAL, yytext); }
(\"(.*?)\")|('(.*?)')               { yytext = yytext + 1; yytext[strlen(yytext)-1] = 0; return Token(Token::Type::STR_LITERAL, yytext); }
[a-zA-z_][a-zA-Z0-9_]*              { return Token(Token::Type::IDENTIFIER, yytext); }
"="                                 { return Token(Token::Type::ASSIGN); }
.                                   { return Token(Token::Type::UNKNOWN, yytext); }
<<EOF>>                             { return Token(Token::Type::END_OF_FILE); }

%%

FlexLexer::FlexLexer(FILE *file) {
    bwyylex_init(&this->lexer_id);
    bwyyset_in(file, this->lexer_id);
}

FlexLexer::~FlexLexer() {
    bwyylex_destroy(this->lexer_id);
}

Token FlexLexer::next() {
    return bwyylex(this->lexer_id);
}
