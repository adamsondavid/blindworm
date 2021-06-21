#ifndef BLINDWORM_COMPILER_EXPRESSION_H
#define BLINDWORM_COMPILER_EXPRESSION_H

#include "codenode.h"
#include <vector>
#include <string>

namespace ast{
/* ========================== Base Types: Expression ==========================*/

class Expression : public CodeNode {
public:
    virtual ~Expression() { }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) = 0;
};

class UnaryExpression : public Expression {
protected:
    Expression* child;
public:
    UnaryExpression(Expression* child) : child(child) { }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return child->getLlvmType(cg);
    }
    virtual ~UnaryExpression() {
        delete this->child;
    }
    virtual void accept(Visitor* visitor) override {
        this->child->accept(visitor);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const UnaryExpression* o = static_cast<const UnaryExpression*>(&other);
        return CMP_AND_DREF_PTR(this->child, o->child);
    }
};

class BinaryExpression : public Expression {
protected:
    Expression* left;
    Expression* right;
public:
    BinaryExpression(Expression* left, Expression* right) : left(left), right(right) { }
    virtual ~BinaryExpression() {
        delete this->left;
        delete this->right;
    }
    virtual void accept(Visitor* visitor) override {
        this->left->accept(visitor);
        this->right->accept(visitor);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const BinaryExpression* o = static_cast<const BinaryExpression*>(&other);
        return CMP_AND_DREF_PTR(this->left, o->left) && CMP_AND_DREF_PTR(this->right, o->right);
    }
};

/* ========================== Logical ==========================*/

class NotExpression: public UnaryExpression {
public:
    NotExpression(Expression* child): UnaryExpression(child) { }
    virtual ~NotExpression() { }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        return cg->irBuilder->CreateNot(this->child->generateCode(cg), "notexpr");
    }
    CN_ACCEPT_METHOD_WITH_BASECLASS(UnaryExpression)
};

class OrExpression: public BinaryExpression {
public:
    OrExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        return cg->irBuilder->CreateBinOp(llvm::BinaryOpIntrinsic::Or, left->generateCode(cg), right->generateCode(cg), "orexpr");
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual ~OrExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class AndExpression: public BinaryExpression {
public:
    AndExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        return cg->irBuilder->CreateBinOp(llvm::BinaryOpIntrinsic::And, left->generateCode(cg), right->generateCode(cg), "andexpr");
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual ~AndExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class NotEqualsExpression: public BinaryExpression {
public:
    NotEqualsExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
             return cg->irBuilder->CreateCmp(llvm::CmpInst::FCMP_UNE,left->generateCode(cg), right->generateCode(cg), "noteqexpr");
        return cg->irBuilder->CreateCmp(llvm::CmpInst::ICMP_NE,left->generateCode(cg), right->generateCode(cg), "noteqexpr");
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual ~NotEqualsExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class EqualsExpression: public BinaryExpression {
public:
    EqualsExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateCmp(llvm::CmpInst::FCMP_UEQ,left->generateCode(cg), right->generateCode(cg), "eqexpr");
        return cg->irBuilder->CreateCmp(llvm::CmpInst::ICMP_EQ,left->generateCode(cg), right->generateCode(cg), "eqexpr");
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual ~EqualsExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class GreaterThanExpression: public BinaryExpression {
public:
    GreaterThanExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual ~GreaterThanExpression() { }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateCmp(llvm::CmpInst::FCMP_UGT,left->generateCode(cg), right->generateCode(cg), "gtexpr");
        return cg->irBuilder->CreateCmp(llvm::CmpInst::ICMP_SGT,left->generateCode(cg), right->generateCode(cg), "gtexpr");
    }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class GreaterEqualsExpression: public BinaryExpression {
public:
    GreaterEqualsExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateCmp(llvm::CmpInst::FCMP_UGE,left->generateCode(cg), right->generateCode(cg), "geexpr");
        return cg->irBuilder->CreateCmp(llvm::CmpInst::ICMP_SGE,left->generateCode(cg), right->generateCode(cg), "geexpr");
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual ~GreaterEqualsExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class LessThanExpression: public BinaryExpression {
public:
    LessThanExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateCmp(llvm::CmpInst::FCMP_ULT,left->generateCode(cg), right->generateCode(cg), "ltexpr");
        return cg->irBuilder->CreateCmp(llvm::CmpInst::ICMP_SLT,left->generateCode(cg), right->generateCode(cg), "ltexpr");
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual ~LessThanExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class LessEqualsExpression: public BinaryExpression {
public:
    LessEqualsExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateCmp(llvm::CmpInst::FCMP_ULE,left->generateCode(cg), right->generateCode(cg), "leexpr");
        return cg->irBuilder->CreateCmp(llvm::CmpInst::ICMP_SLE,left->generateCode(cg), right->generateCode(cg), "leexpr");
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    virtual ~LessEqualsExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

/* ========================== Arithmetic ==========================*/

class ArithmeticExpression: public BinaryExpression {
public:
    ArithmeticExpression(Expression* left, Expression* right) : BinaryExpression(left, right) { }
    virtual ~ArithmeticExpression() { }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        llvm::Type* leftType = this->left->getLlvmType(cg);
        llvm::Type* rightType = this->right->getLlvmType(cg);
        if(leftType != rightType)
        DIE_CODEGEN("The Children of the BinaryExpression are not from the same type")
        return leftType;
    }
};

class AdditionExpression: public ArithmeticExpression {
public:
    AdditionExpression(Expression* left, Expression* right) : ArithmeticExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateFAdd(left->generateCode(cg), right->generateCode(cg), "addexpr");
        return cg->irBuilder->CreateAdd(left->generateCode(cg), right->generateCode(cg), "addexpr");
    }
    virtual ~AdditionExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class SubtractionExpression: public ArithmeticExpression {
public:
    SubtractionExpression(Expression* left, Expression* right) : ArithmeticExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateFSub(left->generateCode(cg), right->generateCode(cg), "subexpr");
        return cg->irBuilder->CreateSub(left->generateCode(cg), right->generateCode(cg), "subexpr");
    }
    virtual ~SubtractionExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

class MultiplicationExpression: public ArithmeticExpression {
public:
    MultiplicationExpression(Expression* left, Expression* right) : ArithmeticExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateFMul(left->generateCode(cg), right->generateCode(cg), "mulexpr");
        return cg->irBuilder->CreateMul(left->generateCode(cg), right->generateCode(cg), "mulexpr");
    }
    virtual ~MultiplicationExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)

};

class DivisionExpression: public ArithmeticExpression {
public:
    DivisionExpression(Expression* left, Expression* right) : ArithmeticExpression(left, right) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto type = this->getLlvmType(cg);
        if(!type)
            return nullptr;
        if(type->isFloatingPointTy())
            return cg->irBuilder->CreateFDiv(left->generateCode(cg), right->generateCode(cg), "divexpr");
        return cg->irBuilder->CreateSDiv(left->generateCode(cg), right->generateCode(cg), "divexpr");
    }
    virtual ~DivisionExpression() { }
    CN_ACCEPT_METHOD_WITH_BASECLASS(BinaryExpression)
};

/* ========================== Atom ==========================*/

class IdentifierExpression: public Expression {
private:
    std::string identifier;
public:
    IdentifierExpression(std::string identifier) : identifier(identifier) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto val = cg->namedValues.get(identifier);
        return cg->irBuilder->CreateLoad(val, this->identifier);
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return cg->namedValues.get(this->identifier)->getAllocatedType();
    }
    virtual ~IdentifierExpression() { }
    CN_ACCEPT_METHOD
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const IdentifierExpression* o = static_cast<const IdentifierExpression*>(&other);
        return this->identifier == o->identifier;
    }
    std::string getIdentifier() { return this->identifier; }
};

class FunctionCallExpression: public Expression {
private:
    std::string identifier;
    std::vector<Expression*> parameters;
public:
    FunctionCallExpression(std::string identifier, std::vector<Expression*> parameters) : identifier(identifier), parameters(parameters) { }
    virtual ~FunctionCallExpression() {
        for(Expression* parameter : this->parameters) {
            delete parameter;
        }
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return cg->compilationUnit->getFunction(this->identifier)->getFunctionType()->getReturnType();
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto function = cg->compilationUnit->getFunction(identifier);
        if(!function)
            return nullptr;

        std::vector<llvm::Value*> args;
        for(auto p : parameters){
            args.push_back(p->generateCode(cg));
        }

        if(function->getReturnType() != llvm::Type::getVoidTy(*cg->context)){
            return cg->irBuilder->CreateCall(function, args, "retval");
        }
        return cg->irBuilder->CreateCall(function, args);
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        //Children
        for(Expression* parameter : this->parameters){
            parameter->accept(visitor);
        }
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const FunctionCallExpression* o = static_cast<const FunctionCallExpression*>(&other);
        return this->identifier == o->identifier
               && this->parameters.size() == o->parameters.size()
               && std::equal(this->parameters.begin(), this->parameters.end(), o->parameters.begin(), o->parameters.end(), [](const Expression* lhs, const Expression* rhs){ return CMP_AND_DREF_PTR(lhs, rhs); });
    }
    std::string getIdentifier() { return this->identifier; }
};

class LiteralExpression: public Expression {
public:
    LiteralExpression() { }
    virtual ~LiteralExpression() { }
};

class BoolLiteralExpression: public LiteralExpression {
private:
    bool value;
public:
    BoolLiteralExpression(bool value) : value(value) { }
    virtual ~BoolLiteralExpression() { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        return llvm::ConstantInt::get(llvm::Type::getInt1Ty(*cg->context), (int) this->value, false);
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    }
    CN_ACCEPT_METHOD
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const BoolLiteralExpression* o = static_cast<const BoolLiteralExpression*>(&other);
        return this->value == o->value;
    }
};

class IntLiteralExpression: public LiteralExpression {
private:
    int value;
public:
    IntLiteralExpression(int value) : value(value) { }

    virtual ~IntLiteralExpression() { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        return llvm::ConstantInt::get(llvm::Type::getInt32Ty(*cg->context), this->value, true);
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt32Ty(*cg->context);
    }
    CN_ACCEPT_METHOD
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const IntLiteralExpression* o = static_cast<const IntLiteralExpression*>(&other);
        return this->value == o->value;
    }
};

class FloatLiteralExpression: public LiteralExpression {
private:
    float value;
public:
    FloatLiteralExpression(float value) : value(value) { }
    virtual ~FloatLiteralExpression() { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        return llvm::ConstantFP::get(*cg->context, llvm::APFloat(this->value));
    }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getFloatTy(*cg->context);
    }
    CN_ACCEPT_METHOD
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const FloatLiteralExpression* o = static_cast<const FloatLiteralExpression*>(&other);
        return this->value == o->value;
    }
};

class StrLiteralExpression: public LiteralExpression {
private:
    std::string value;
public:
    StrLiteralExpression(std::string value) : value(value) { }
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt8PtrTy(*cg->context);
    }
    virtual ~StrLiteralExpression() { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        std::string val = this->value;

        this->replace(val, "\\a", "\a");
        this->replace(val, "\\b", "\b");
        this->replace(val, "\\f", "\f");
        this->replace(val, "\\n", "\n");
        this->replace(val, "\\r", "\r");
        this->replace(val, "\\t", "\t");
        this->replace(val, "\\v", "\v");

        return cg->irBuilder->CreateGlobalStringPtr(llvm::StringRef(val), "globalStringVar");
    }
    std::string& replace(std::string& string, std::string find, std::string replace) {
        int pos = string.find(find);
        while(pos != std::string::npos) {
            string.replace(pos, find.length(), replace);
            pos = string.find(find);
        }
        return string;
    }
    CN_ACCEPT_METHOD
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const StrLiteralExpression* o = static_cast<const StrLiteralExpression*>(&other);
        return this->value == o->value;
    }
};
}

#endif //BLINDWORM_COMPILER_EXPRESSION_H
