#include <gtest/gtest.h>
#include <sstream>
#include "../src/lexer/abstractlexer.h"
#include "../src/lexer/handwrittenlexer.h"
#include "../src/lexer/flexlexer.h"

class LexerTests : public ::testing::TestWithParam<std::function<AbstractLexer*(std::string&)>> {

};

INSTANTIATE_TEST_SUITE_P(HandwrittenLexer, LexerTests, testing::Values ([](std::string& input) {
    std::stringstream* stringstream = new std::stringstream();
    *stringstream << input;
    return new HandwrittenLexer(stringstream);
}));

INSTANTIATE_TEST_SUITE_P(FlexLexer, LexerTests, testing::Values ([](std::string& input) {
    return new FlexLexer(fmemopen((void*) input.c_str(), input.size(), "r"));
}));

TEST_P(LexerTests, IntVariable) {
    std::string input = "abc: int = 123;";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "abc"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT_LITERAL, "123"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, FloatVariableZeroPointFive) {
    std::string input = "abc: float = 0.5;";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "abc"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT_LITERAL, "0.5"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, FloatVariablePointFive) {
    std::string input = "abc: float = .5;";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "abc"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT_LITERAL, ".5"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, StrVariableSingleQuotes) {
    std::string input = "abc: str = 'hello';";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "abc"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::STR));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::STR_LITERAL, "hello"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, StrVariableDoubleQuotes) {
    std::string input = "abc: str = \"'hello'\";";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "abc"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::STR));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::STR_LITERAL, "'hello'"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, FunctionDeclaration) {
    std::string input = "def myFunction(number: int) -> int: (return number;)";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::DEF));
    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "myFunction"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::LPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "number"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::RPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ARROW));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::LPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::RETURN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "number"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::RPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, MultipleFunctionDeclaration) {
    std::stringstream stringstream;
    stringstream << "def myFunction(number: int) -> int: (return number;)" << std::endl;
    stringstream << "def myFunction(number:int)->int:(return number;)";
    stringstream << "def myFunction(number: int) -> int: (return number;)";
    std::string input = stringstream.str();

    AbstractLexer* lexer = GetParam()(input);

    for(int i = 0; i < 3; i++){
        EXPECT_EQ(lexer->next(), Token(Token::Type::DEF));
        EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "myFunction"));
        EXPECT_EQ(lexer->next(), Token(Token::Type::LPAREN));
        EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "number"));
        EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
        EXPECT_EQ(lexer->next(), Token(Token::Type::INT));
        EXPECT_EQ(lexer->next(), Token(Token::Type::RPAREN));
        EXPECT_EQ(lexer->next(), Token(Token::Type::ARROW));
        EXPECT_EQ(lexer->next(), Token(Token::Type::INT));
        EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
        EXPECT_EQ(lexer->next(), Token(Token::Type::LPAREN));
        EXPECT_EQ(lexer->next(), Token(Token::Type::RETURN));
        EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "number"));
        EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
        EXPECT_EQ(lexer->next(), Token(Token::Type::RPAREN));
    }
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, SoManyKeywords) {
    std::stringstream stringstream;
    stringstream << " def -> return if else elif while : , ; ";
    stringstream << " = ( ) + - * / != == > >= < <= and or not ";
    stringstream << " myFunction_123 myVariable42 None bool int float str ";
    stringstream << " 123 0.123 .123 \"hello\" 'world' True False Yes No ";
    std::string input = stringstream.str();

    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::DEF));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ARROW));
    EXPECT_EQ(lexer->next(), Token(Token::Type::RETURN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::IF));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ELSE));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ELIF));
    EXPECT_EQ(lexer->next(), Token(Token::Type::WHILE));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COMMA));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));

    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::LPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::RPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::PLUS));
    EXPECT_EQ(lexer->next(), Token(Token::Type::MINUS));
    EXPECT_EQ(lexer->next(), Token(Token::Type::MUL));
    EXPECT_EQ(lexer->next(), Token(Token::Type::DIV));
    EXPECT_EQ(lexer->next(), Token(Token::Type::NOT_EQUALS));
    EXPECT_EQ(lexer->next(), Token(Token::Type::EQUALS));
    EXPECT_EQ(lexer->next(), Token(Token::Type::GREATER_THAN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::GREATER_EQUALS));
    EXPECT_EQ(lexer->next(), Token(Token::Type::LESS_THAN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::LESS_EQUALS));
    EXPECT_EQ(lexer->next(), Token(Token::Type::AND));
    EXPECT_EQ(lexer->next(), Token(Token::Type::OR));
    EXPECT_EQ(lexer->next(), Token(Token::Type::NOT));

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "myFunction_123"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "myVariable42"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::NONE));
    EXPECT_EQ(lexer->next(), Token(Token::Type::BOOL));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::STR));

    EXPECT_EQ(lexer->next(), Token(Token::Type::INT_LITERAL, "123"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT_LITERAL, "0.123"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT_LITERAL, ".123"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::STR_LITERAL, "hello"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::STR_LITERAL, "world"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::BOOL_LITERAL, "True"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::BOOL_LITERAL, "False"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::BOOL_LITERAL, "Yes"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::BOOL_LITERAL, "No"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, IntVariableMathExpressionAddition) {
    std::string input = "abc: int = 1+1;";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "abc"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT_LITERAL, "1"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::PLUS));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT_LITERAL, "1"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, FloatVariableMathExpressionDivision) {
    std::string input = "abc: float = 1.123/.354;";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "abc"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT_LITERAL, "1.123"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::DIV));
    EXPECT_EQ(lexer->next(), Token(Token::Type::FLOAT_LITERAL, ".354"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, IntVariableMathExpressionCompund) {
    std::string input =  "abc: int = (1+1)*(2/2);";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "abc"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ASSIGN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::LPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT_LITERAL, "1"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::PLUS));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT_LITERAL, "1"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::RPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::MUL));
    EXPECT_EQ(lexer->next(), Token(Token::Type::LPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT_LITERAL, "2"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::DIV));
    EXPECT_EQ(lexer->next(), Token(Token::Type::INT_LITERAL, "2"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::RPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::END_OF_FILE));

    delete lexer;
}

TEST_P(LexerTests, NativeFunction) {
    std::string input =  "native def printf(value: str) -> None;";
    AbstractLexer* lexer = GetParam()(input);

    EXPECT_EQ(lexer->next(), Token(Token::Type::NATIVE));
    EXPECT_EQ(lexer->next(), Token(Token::Type::DEF));
    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "printf"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::LPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::IDENTIFIER, "value"));
    EXPECT_EQ(lexer->next(), Token(Token::Type::COLON));
    EXPECT_EQ(lexer->next(), Token(Token::Type::STR));
    EXPECT_EQ(lexer->next(), Token(Token::Type::RPAREN));
    EXPECT_EQ(lexer->next(), Token(Token::Type::ARROW));
    EXPECT_EQ(lexer->next(), Token(Token::Type::NONE));
    EXPECT_EQ(lexer->next(), Token(Token::Type::SEMICOLON));

    delete lexer;
}
