#include <gtest/gtest.h>
#include "../src/lexer/abstractlexer.h"
#include "../src/parser/abstractparser.h"
#include "../src/parser/handwrittenparser.h"
#include "../src/parser/bisonparser.h"
#include "../src/semantic/symboltablevisitor.h"
#include <queue>
#include <vector>

class LexerMock : public AbstractLexer {
private:
    std::queue<Token> tokens;
public:
    LexerMock(std::queue<Token> tokens) : tokens(tokens) { }
    virtual ~LexerMock() { }
    virtual Token next() override {
        if(!this->tokens.empty()){
            Token token = this->tokens.front();
            this->tokens.pop();
            return token;
        }
        return Token(Token::Type::END_OF_FILE);
    }
};

class ParserTests : public ::testing::TestWithParam<std::function<AbstractParser*(AbstractLexer*)>> {

};

INSTANTIATE_TEST_SUITE_P(HandwrittenParser, ParserTests, testing::Values ([](AbstractLexer* lexer) {
    return new HandwrittenParser(lexer);
}));

INSTANTIATE_TEST_SUITE_P(BisonParser, ParserTests, testing::Values ([](AbstractLexer* lexer) {
    return new BisonParser(lexer);
}));

/**
 * Testcase: myvar = 42.0;
 */
TEST_P(ParserTests, VariableAssignementFloatSimple) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "myvar"),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::FLOAT_LITERAL, "42.0"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::AssignmentStatement("myvar", new ast::FloatLiteralExpression(42.0))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_THROW(program->accept(&symbolTableVisitor), SemanticException);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: abc: int = 42;
 */
TEST_P(ParserTests, VariableDeclarationSimple) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::COLON),
        Token(Token::Type::INT),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::INT_LITERAL, "42"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("abc", new ast::IntType(), new ast::IntLiteralExpression(42))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: abc: int = 47 - 5;
 */
TEST_P(ParserTests, VariableDeclarationSimpleSubstraction) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::COLON),
        Token(Token::Type::INT),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::INT_LITERAL, "47"),
        Token(Token::Type::MINUS),
        Token(Token::Type::INT_LITERAL, "5"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("abc", new ast::IntType(),
                  new ast::SubtractionExpression(new ast::IntLiteralExpression(47), new ast::IntLiteralExpression(5)))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: abc: int = -someNumber;
 */
TEST_P(ParserTests, VariableDeclarationSimpleNegative) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::COLON),
        Token(Token::Type::INT),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::MINUS),
        Token(Token::Type::IDENTIFIER, "someNumber"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("abc", new ast::IntType(),
                  new ast::MultiplicationExpression(new ast::IntLiteralExpression(-1), new ast::IdentifierExpression("someNumber")))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_THROW(program->accept(&symbolTableVisitor), SemanticException);

    delete expected;
    delete program;
    delete parser;
}


/**
 * Testcase: myStr: str = "strrr";
 */
TEST_P(ParserTests, VariableDeclarationStringType) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "myStr"),
        Token(Token::Type::COLON),
        Token(Token::Type::STR),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::STR_LITERAL, "strrr"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("myStr", new ast::StrType(),
            new ast::StrLiteralExpression("strrr"))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}


/**
 * Testcase: myFloaty: float = 0.0000001f";
 */
TEST_P(ParserTests, VariableDeclarationFloatTypeWithf) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "myFloaty"),
        Token(Token::Type::COLON),
        Token(Token::Type::FLOAT),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::FLOAT_LITERAL, "0.0000001f"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("myFloaty", new ast::FloatType(),
            new ast::FloatLiteralExpression(0.0000001f))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}


/**
 * Testcase: if(True):()
 */
TEST_P(ParserTests, IfStatementSimple) {
    std::queue<Token> tokens({
        Token(Token::Type::IF),
        Token(Token::Type::LPAREN),
        Token(Token::Type::BOOL_LITERAL, "True"),
        Token(Token::Type::RPAREN),
        Token(Token::Type::COLON),
        Token(Token::Type::LPAREN),
        Token(Token::Type::RPAREN),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::IfStatement(new ast::BoolLiteralExpression(true), std::vector<ast::Statement*>(), std::vector<ast::ElifStatement*>(), NO_STMT),
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: if(True):(return 0.7;)
 */
TEST_P(ParserTests, IfStatementWithReturn) {
    std::queue<Token> tokens({
        Token(Token::Type::IF),
        Token(Token::Type::LPAREN),
        Token(Token::Type::BOOL_LITERAL, "True"),
        Token(Token::Type::RPAREN),
        Token(Token::Type::COLON),
        Token(Token::Type::LPAREN),
        Token(Token::Type::RETURN),
        Token(Token::Type::FLOAT_LITERAL, "0.7"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::RPAREN),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::IfStatement(new ast::BoolLiteralExpression("True"),
                            std::vector<ast::Statement*>({
                                new ast::ReturnStatement(new ast::FloatLiteralExpression(0.7))
                            }),
                          std::vector<ast::ElifStatement*>(), NO_STMT)
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: age: int = getAge();
 */
TEST_P(ParserTests, VariableDeclarationByFunctionCall) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "age"),
        Token(Token::Type::COLON),
        Token(Token::Type::INT),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::IDENTIFIER, "getAge"),
        Token(Token::Type::LPAREN),
        Token(Token::Type::RPAREN),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("age", new ast::IntType(),
            new ast::FunctionCallExpression("getAge", std::vector<ast::Expression*>()))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_THROW(program->accept(&symbolTableVisitor), SemanticException);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: age: int = getAge(abc);
 */
TEST_P(ParserTests, VariableDeclarationByFunctionCallWithArgs) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "age"),
        Token(Token::Type::COLON),
        Token(Token::Type::INT),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::IDENTIFIER, "getAge"),
        Token(Token::Type::LPAREN),
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::RPAREN),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("age", new ast::IntType(),
            new ast::FunctionCallExpression("getAge", std::vector<ast::Expression*>({
                        new ast::IdentifierExpression("abc")
                  })))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_THROW(program->accept(&symbolTableVisitor), SemanticException);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: abc: int = 2 + 3 * 4 + 5;
 */
TEST_P(ParserTests, MultiplicationAndAddition) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::COLON),
        Token(Token::Type::INT),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::INT_LITERAL, "2"),
        Token(Token::Type::PLUS),
        Token(Token::Type::INT_LITERAL, "3"),
        Token(Token::Type::MUL),
        Token(Token::Type::INT_LITERAL, "4"),
        Token(Token::Type::PLUS),
        Token(Token::Type::INT_LITERAL, "5"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("abc", new ast::IntType(), new ast::AdditionExpression(
                new ast::IntLiteralExpression(2),
                new ast::AdditionExpression(
                        new ast::MultiplicationExpression(new ast::IntLiteralExpression(3), new ast::IntLiteralExpression(4)),
                        new ast::IntLiteralExpression(5))))}));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: def print(valueToPrint: str = "hello world") -> None: ( extern_print(valueToPrint); )
 */
TEST_P(ParserTests, FunctionDeclaration) {
    std::queue<Token> tokens({
        Token(Token::Type::DEF),
        Token(Token::Type::IDENTIFIER, "print"),
        Token(Token::Type::LPAREN),
        Token(Token::Type::IDENTIFIER, "valueToPrint"),
        Token(Token::Type::COLON),
        Token(Token::Type::STR),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::STR_LITERAL, "hello world"),
        Token(Token::Type::RPAREN),
        Token(Token::Type::ARROW),
        Token(Token::Type::NONE),
        Token(Token::Type::COLON),
        Token(Token::Type::LPAREN),
        Token(Token::Type::IDENTIFIER, "extern_print"),
        Token(Token::Type::LPAREN),
        Token(Token::Type::IDENTIFIER, "valueToPrint"),
        Token(Token::Type::RPAREN),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::RPAREN),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::FunctionDefinitionStatement("print", new ast::NoneType(), std::vector<ast::VariableDeclarationStatement*>({
            new ast::VariableDeclarationStatement("valueToPrint", new ast::StrType(), new ast::StrLiteralExpression("hello world"))
        }), std::vector<ast::Statement*>({
            new ast::FunctionCallStatement(new ast::FunctionCallExpression("extern_print", std::vector<ast::Expression*>({
                new ast::IdentifierExpression("valueToPrint")
            })))
        }))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_THROW(program->accept(&symbolTableVisitor), SemanticException);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: def do() -> None: ()
 */
TEST_P(ParserTests, FunctionDeclarationNoParams) {
    std::queue<Token> tokens({
        Token(Token::Type::DEF),
        Token(Token::Type::IDENTIFIER, "do"),
        Token(Token::Type::LPAREN),
        Token(Token::Type::RPAREN),
        Token(Token::Type::ARROW),
        Token(Token::Type::NONE),
        Token(Token::Type::COLON),
        Token(Token::Type::LPAREN),
        Token(Token::Type::RPAREN),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::FunctionDefinitionStatement(
            "do",
            new ast::NoneType(),
            std::vector<ast::VariableDeclarationStatement*>(),
            std::vector<ast::Statement*>()
        )
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: def xyz(value: str = "hello world") -> None: ( value = ""; )
 */
TEST_P(ParserTests, FunctionDeclarationValidSemantic) {
    std::queue<Token> tokens({
        Token(Token::Type::DEF),
        Token(Token::Type::IDENTIFIER, "xyz"),
        Token(Token::Type::LPAREN),
        Token(Token::Type::IDENTIFIER, "value"),
        Token(Token::Type::COLON),
        Token(Token::Type::STR),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::STR_LITERAL, "hello world"),
        Token(Token::Type::RPAREN),
        Token(Token::Type::ARROW),
        Token(Token::Type::NONE),
        Token(Token::Type::COLON),
        Token(Token::Type::LPAREN),
        Token(Token::Type::IDENTIFIER, "value"),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::STR_LITERAL, ""),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::RPAREN),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::FunctionDefinitionStatement("xyz", new ast::NoneType(), std::vector<ast::VariableDeclarationStatement*>({
            new ast::VariableDeclarationStatement("value", new ast::StrType(), new ast::StrLiteralExpression("hello world"))
        }), std::vector<ast::Statement*>({
            new ast::AssignmentStatement("value", new ast::StrLiteralExpression(""))
        }))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_NO_THROW(program->accept(&symbolTableVisitor));

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: def xyz() -> None: (return;)
 */
TEST_P(ParserTests, FunctionDeclarationReturnVoid) {
    std::queue<Token> tokens({
        Token(Token::Type::DEF),
        Token(Token::Type::IDENTIFIER, "xyz"),
        Token(Token::Type::LPAREN),
        Token(Token::Type::RPAREN),
        Token(Token::Type::ARROW),
        Token(Token::Type::NONE),
        Token(Token::Type::COLON),
        Token(Token::Type::LPAREN),
        Token(Token::Type::RETURN),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::RPAREN),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::FunctionDefinitionStatement(
            "xyz",
            new ast::NoneType(),
            std::vector<ast::VariableDeclarationStatement*>(),
            std::vector<ast::Statement*>({new ast::ReturnStatement(NO_EXPR)})
        )
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: print("hello", "world");
 */
TEST_P(ParserTests, FunctionCallTwoParameters) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "print"),
        Token(Token::Type::LPAREN),
        Token(Token::Type::STR_LITERAL, "hello"),
        Token(Token::Type::COMMA),
        Token(Token::Type::STR_LITERAL, "world"),
        Token(Token::Type::RPAREN),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::FunctionCallStatement(
                new ast::FunctionCallExpression("print", std::vector<ast::Expression*>({
                    new ast::StrLiteralExpression("hello"),
                    new ast::StrLiteralExpression("world")
        })))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_THROW(program->accept(&symbolTableVisitor), SemanticException);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: print((1+2),((1+7)*4));
 */
TEST_P(ParserTests, FunctionCallNestedParameters) {
    std::queue<Token> tokens({
         Token(Token::Type::IDENTIFIER, "print"),
         Token(Token::Type::LPAREN),
         //Arg1
         Token(Token::Type::LPAREN),
         Token(Token::Type::INT_LITERAL,"1"),
         Token(Token::Type::PLUS),
         Token(Token::Type::INT_LITERAL,"2"),
         Token(Token::Type::RPAREN),
         Token(Token::Type::COMMA),
         //Arg2
         Token(Token::Type::LPAREN),

         Token(Token::Type::LPAREN),
         Token(Token::Type::INT_LITERAL,"1"),
         Token(Token::Type::PLUS),
         Token(Token::Type::INT_LITERAL,"7"),
         Token(Token::Type::RPAREN),

         Token(Token::Type::MUL),
         Token(Token::Type::INT_LITERAL, "4"),
         Token(Token::Type::RPAREN),

         Token(Token::Type::RPAREN),
         Token(Token::Type::SEMICOLON),
         Token(Token::Type::END_OF_FILE)
     });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    auto function_args = std::vector<ast::Expression*>({
    new ast::AdditionExpression(
    new ast::IntLiteralExpression(1),
    new ast::IntLiteralExpression(2)),
    new ast::MultiplicationExpression(
    new ast::AdditionExpression(
    new ast::IntLiteralExpression(1),
        new ast::IntLiteralExpression(7)),
        new ast::IntLiteralExpression(4))
    });

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::FunctionCallStatement(new ast::FunctionCallExpression("print", function_args))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_THROW(program->accept(&symbolTableVisitor), SemanticException);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: abc: bool = 42 == 42;
 */
TEST_P(ParserTests, BooleanEqualsExpression) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::COLON),
        Token(Token::Type::BOOL),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::INT_LITERAL, "42"),
        Token(Token::Type::EQUALS),
        Token(Token::Type::INT_LITERAL, "42"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("abc", new ast::BoolType(), new ast::EqualsExpression(
            new ast::IntLiteralExpression(42), new ast::IntLiteralExpression(42)
        ))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: abc: bool = True and False;
 */
TEST_P(ParserTests, BooleanAndExpression) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::COLON),
        Token(Token::Type::BOOL),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::BOOL_LITERAL, "True"),
        Token(Token::Type::AND),
        Token(Token::Type::BOOL_LITERAL, "False"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("abc", new ast::BoolType(), new ast::AndExpression(
            new ast::BoolLiteralExpression(true), new ast::BoolLiteralExpression(false)
        ))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: abc: bool = True or False;
 */
TEST_P(ParserTests, BooleanOrExpression) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::COLON),
        Token(Token::Type::BOOL),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::BOOL_LITERAL, "True"),
        Token(Token::Type::OR),
        Token(Token::Type::BOOL_LITERAL, "False"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("abc", new ast::BoolType(), new ast::OrExpression(
            new ast::BoolLiteralExpression(true), new ast::BoolLiteralExpression(false)
        ))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: abc: bool = not False;
 */
TEST_P(ParserTests, BooleanNotExpression) {
    std::queue<Token> tokens({
        Token(Token::Type::IDENTIFIER, "abc"),
        Token(Token::Type::COLON),
        Token(Token::Type::BOOL),
        Token(Token::Type::ASSIGN),
        Token(Token::Type::NOT),
        Token(Token::Type::BOOL_LITERAL, "False"),
        Token(Token::Type::SEMICOLON),
        Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::VariableDeclarationStatement("abc", new ast::BoolType(), new ast::NotExpression(
            new ast::BoolLiteralExpression(false)
        ))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);
    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: Simple  While Loop
 * while(True):(exclaim("it's true!";))
 */
TEST_P(ParserTests, SimpleWhileLoop) {
    std::queue<Token> tokens({
         Token(Token::Type::WHILE),
         Token(Token::Type::LPAREN),
         Token(Token::Type::BOOL_LITERAL, "True"),
         Token(Token::Type::RPAREN),
         Token(Token::Type::COLON),
         Token(Token::Type::LPAREN),
         Token(Token::Type::IDENTIFIER, "exclaim"),
         Token(Token::Type::LPAREN),
         Token(Token::Type::STR_LITERAL, "it's true!"),
         Token(Token::Type::RPAREN),
         Token(Token::Type::SEMICOLON),
         Token(Token::Type::RPAREN),
         Token(Token::Type::END_OF_FILE)
                             });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);
    auto m_params = std::vector<ast::Expression*>({new ast::StrLiteralExpression("it's true!")});
    auto m_stmts = std::vector<ast::Statement*>({new ast::FunctionCallStatement(new ast::FunctionCallExpression("exclaim", m_params))});
    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::WhileStatement(new ast::BoolLiteralExpression(true), m_stmts)
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    EXPECT_THROW(program->accept(&symbolTableVisitor), SemanticException);
    delete expected;
    delete program;
    delete parser;
}

/**
 * Testcase: Native Function Definition
 * native def printf(value: str) -> None;
 * printf("hello world!");
 */
TEST_P(ParserTests, NativeFunction) {
    std::queue<Token> tokens({
         Token(Token::Type::NATIVE),
         Token(Token::Type::DEF),
         Token(Token::Type::IDENTIFIER, "printf"),
         Token(Token::Type::LPAREN),
         Token(Token::Type::IDENTIFIER, "value"),
         Token(Token::Type::COLON),
         Token(Token::Type::STR),
         Token(Token::Type::RPAREN),
         Token(Token::Type::ARROW),
         Token(Token::Type::NONE),
         Token(Token::Type::SEMICOLON),

         Token(Token::Type::IDENTIFIER, "printf"),
         Token(Token::Type::LPAREN),
         Token(Token::Type::STR_LITERAL, "hello world!"),
         Token(Token::Type::RPAREN),
         Token(Token::Type::SEMICOLON),
         Token(Token::Type::END_OF_FILE)
    });
    LexerMock lexerMock(tokens);
    AbstractParser* parser = GetParam()(&lexerMock);

    ast::Program* expected = new ast::Program(std::vector<ast::Statement*>({
        new ast::NativeFunctionDefinitionStatement(
            "printf",
            new ast::NoneType(),
            std::vector<ast::VariableDeclarationStatement*>{
                new ast::VariableDeclarationStatement("value", new ast::StrType(), NO_EXPR)}),
        new ast::FunctionCallStatement(
            new ast::FunctionCallExpression("printf", std::vector<ast::Expression*>({
                new ast::StrLiteralExpression("hello world!")
        })))
    }));

    ast::Program* program = parser->parse();
    EXPECT_EQ(*expected, *program);

    SymbolTableVisitor symbolTableVisitor;
    program->accept(&symbolTableVisitor);

    delete expected;
    delete program;
    delete parser;
}
