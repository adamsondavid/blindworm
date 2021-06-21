#ifndef BLINDWORM_COMPILER_VISITOR_H
#define BLINDWORM_COMPILER_VISITOR_H

#define VVISIT_FN(e) virtual void visit(e* elem) { }; virtual void endVisit(e* elem) { };

namespace ast {
class Program;
/*** Statement ***/
class AssignmentStatement;
class ElifStatement;
class ElseStatement;
class FunctionCallStatement;
class NativeFunctionDefinitionStatement;
class FunctionDefinitionStatement;
class IfStatement;
class ReturnStatement;
class VariableDeclarationStatement;
class WhileStatement;
/*** Expression ***/
class IdentifierExpression;
class FunctionCallExpression;
//BinaryExpressions
class AdditionExpression;
class AndExpression;
class DivisionExpression;
class EqualsExpression;
class GreaterEqualsExpression;
class GreaterThanExpression;
class LessEqualsExpression;
class LessThanExpression;
class MultiplicationExpression;
class NotEqualsExpression;
class OrExpression;
class SubtractionExpression;
//LiteralExpressions
class BoolLiteralExpression;
class FloatLiteralExpression;
class IntLiteralExpression;
class StrLiteralExpression;
//UnaryExpressions
class NotExpression;
/*** Types ***/
class NoneType;
class BoolType;
class FloatType;
class FunctionType;
class IntType;
class StrType;

class Visitor;
class Visitable {
public:
    virtual void accept(Visitor* visitor) = 0;
};

class Visitor {
public:
    virtual ~Visitor() { }
    /*** Program ***/
    VVISIT_FN(Program)

    /*** Statement ***/
    VVISIT_FN(AssignmentStatement)
    VVISIT_FN(ElifStatement)
    VVISIT_FN(ElseStatement)
    VVISIT_FN(FunctionCallStatement)
    VVISIT_FN(NativeFunctionDefinitionStatement)
    VVISIT_FN(FunctionDefinitionStatement)
    VVISIT_FN(IfStatement)
    VVISIT_FN(ReturnStatement)
    VVISIT_FN(VariableDeclarationStatement)
    VVISIT_FN(WhileStatement)

    /*** Expression ***/
    VVISIT_FN(IdentifierExpression)
    VVISIT_FN(FunctionCallExpression)
    //BinaryExpressions
    VVISIT_FN(AdditionExpression)
    VVISIT_FN(AndExpression)
    VVISIT_FN(DivisionExpression)
    VVISIT_FN(EqualsExpression)
    VVISIT_FN(GreaterEqualsExpression)
    VVISIT_FN(GreaterThanExpression)
    VVISIT_FN(LessEqualsExpression)
    VVISIT_FN(LessThanExpression)
    VVISIT_FN(MultiplicationExpression)
    VVISIT_FN(NotEqualsExpression)
    VVISIT_FN(OrExpression)
    VVISIT_FN(SubtractionExpression)
    //LiteralExpressions
    VVISIT_FN(BoolLiteralExpression)
    VVISIT_FN(FloatLiteralExpression)
    VVISIT_FN(IntLiteralExpression)
    VVISIT_FN(StrLiteralExpression)
    //UnaryExpressions
    VVISIT_FN(NotExpression)

    /*** Types ***/
    VVISIT_FN(NoneType)
    VVISIT_FN(BoolType)
    VVISIT_FN(FloatType)
    VVISIT_FN(FunctionType)
    VVISIT_FN(IntType)
    VVISIT_FN(StrType)
};
}

#endif //BLINDWORM_COMPILER_VISITOR_H
