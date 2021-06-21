#ifndef BLINDWORM_COMPILER_STATEMENT_H
#define BLINDWORM_COMPILER_STATEMENT_H

#include <iostream>
#include "codenode.h"
#include "expression.h"
#include "type.h"

namespace ast {

class Statement : public CodeNode {
public:
    virtual ~Statement() { }
};

/* ========= Loops, Returns, and Conditionals ========= */
class AssignmentStatement : public Statement {
private:
    std::string identifier;
    Expression* value;
public:
    AssignmentStatement(std::string identifier, Expression* value) : identifier(identifier), value(value) { }
    virtual ~AssignmentStatement() {
        delete this->value;
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto var = cg->namedValues.get(identifier);
        return cg->irBuilder->CreateStore(this->value->generateCode(cg), var);
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        this->value->accept(visitor);
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const AssignmentStatement* o = static_cast<const AssignmentStatement*>(&other);
        return this->identifier == o->identifier
            && CMP_AND_DREF_PTR(this->value, o->value);
    }
    std::string getIdentifier(){ return this->identifier; }
};

class VariableDeclarationStatement: public Statement {
private:
    std::string identifier;
    DataType* dataType;
    Expression* value;
public:
    VariableDeclarationStatement(std::string identifier, DataType* dataType, Expression* value) : identifier(identifier), dataType(dataType), value(value) { }
    virtual ~VariableDeclarationStatement() {
        delete this->dataType;
        delete this->value;
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        if(cg->namedValues.get(this->identifier))
            DIE_CODEGEN(std::string("Variable '"+ this->identifier + "' already exists!").c_str())
        llvm::AllocaInst* var = cg->irBuilder->CreateAlloca(this->dataType->getLlvmType(cg), nullptr, this->identifier);
        if(this->value)
            cg->irBuilder->CreateStore(this->value->generateCode(cg), var);
        cg->namedValues.put(this->identifier, var);
        return var;
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        this->dataType->accept(visitor);
        if(this->value) this->value->accept(visitor);
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const VariableDeclarationStatement* o = static_cast<const VariableDeclarationStatement*>(&other);
        return this->identifier == o->identifier
            && CMP_AND_DREF_PTR(this->dataType, o->dataType)
            && CMP_AND_DREF_PTR(this->value, o->value);
    }
    DataType* getDataType() { return this->dataType; }
    std::string getIdentifier() { return this->identifier; }
};

class FunctionType: public DataType {
private:
    ReturnType* returnType;
    std::vector<VariableDeclarationStatement*> formalParameters;
public:
    FunctionType(ReturnType* returnType, std::vector<VariableDeclarationStatement*> formalParameters):
            returnType(returnType), formalParameters(formalParameters) { }
    virtual llvm::FunctionType* getLlvmType(CodeGenerator* cg) override {
        std::vector<llvm::Type*> formal_param_types;
        for(auto fp : this->formalParameters){
            formal_param_types.push_back(fp->getDataType()->getLlvmType(cg));
        }
        return llvm::FunctionType::get(this->returnType->getLlvmType(cg), formal_param_types, false);
    };
    std::vector<VariableDeclarationStatement*> getFormalParameters() {return this->formalParameters;}
    virtual ~FunctionType() {
        delete this->returnType;
        for(VariableDeclarationStatement* fp : this->formalParameters){
            delete fp;
        }
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        this->returnType->accept(visitor);
        for(auto* parameter : this->formalParameters){
            parameter->accept(visitor);
        }
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        const auto* o = static_cast<const FunctionType*>(&other);
        return CMP_AND_DREF_PTR(this->returnType, o->returnType)
               && this->formalParameters.size() == o->formalParameters.size()
               && std::equal(this->formalParameters.begin(), this->formalParameters.end(), o->formalParameters.begin(), o->formalParameters.end(), [](const VariableDeclarationStatement* lhs, const VariableDeclarationStatement* rhs){ return *lhs == *rhs; });
    }
};

class NativeFunctionDefinitionStatement: public Statement {
private:
    std::string identifier;
    FunctionType* functionType;
public:
    NativeFunctionDefinitionStatement(std::string identifier, ReturnType* returnType, std::vector<VariableDeclarationStatement*> formalParameters) :
    identifier(identifier) {
        this->functionType = new FunctionType(returnType, formalParameters);
    }
    virtual ~NativeFunctionDefinitionStatement() {
        delete this->functionType;
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto* function = llvm::Function::Create(this->getFunctionType()->getLlvmType(cg), llvm::Function::ExternalLinkage, this->identifier, cg->compilationUnit);
        return function;
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        this->functionType->accept(visitor);
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const NativeFunctionDefinitionStatement* o = static_cast<const NativeFunctionDefinitionStatement*>(&other);

        return this->identifier == o->identifier
            && CMP_AND_DREF_PTR(this->functionType, o->functionType);
    }

    FunctionType* getFunctionType() { return this->functionType; }
    std::string getIdentifier() { return this->identifier; }
};

class FunctionDefinitionStatement: public NativeFunctionDefinitionStatement {
private:
    std::vector<Statement*> statements;
public:
    FunctionDefinitionStatement(std::string identifier, ReturnType* returnType, std::vector<VariableDeclarationStatement*> formalParameters, std::vector<Statement*> statements) :
    NativeFunctionDefinitionStatement(identifier, returnType, formalParameters), statements(statements) { }
    virtual ~FunctionDefinitionStatement() {
        for(Statement* statement : this->statements){
            delete statement;
        }
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto* functionType = this->getFunctionType()->getLlvmType(cg);
        auto* function = llvm::Function::Create(functionType, llvm::Function::ExternalLinkage, this->getIdentifier(), cg->compilationUnit);

        int index = 0;
        for(auto& arg : function->args()){
            arg.setName(this->getFunctionType()->getFormalParameters().at(index++)->getIdentifier());
        }

        auto* basicBlock = llvm::BasicBlock::Create(*cg->context, this->getIdentifier()+"_body", function);
        cg->irBuilder->SetInsertPoint(basicBlock);
        cg->namedValues.enter();
        for (auto &arg : function->args()) {
            llvm::AllocaInst* alloca = cg->irBuilder->CreateAlloca(arg.getType(), nullptr, arg.getName());
            cg->irBuilder->CreateStore(&arg, alloca);
            cg->namedValues.put(arg.getName().str(), alloca);
        }
        for(auto* statement : this->statements){
            if(!statement->generateCode(cg))
                DIE_CODEGEN("FunctionDefinitionStatement received a nullptr");
        }
        cg->namedValues.leave();
        return function;
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        this->getFunctionType()->accept(visitor);
        for(auto e : this->statements){
            e->accept(visitor);
        }
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const FunctionDefinitionStatement* o = static_cast<const FunctionDefinitionStatement*>(&other);

        return NativeFunctionDefinitionStatement::operator==(other)
            && this->statements.size() == o->statements.size()
            && std::equal(this->statements.begin(), this->statements.end(), o->statements.begin(), o->statements.end(), [](const Statement* lhs, const Statement* rhs){ return *lhs == *rhs; });
    }
};

class ReturnStatement : public Statement {
private:
    Expression* value;
public:
    ReturnStatement(Expression* value) : value(value) { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        if(value)
            return cg->irBuilder->CreateRet(this->value->generateCode(cg));
        return cg->irBuilder->CreateRet(nullptr);
    }
    virtual ~ReturnStatement() {
        delete this->value;
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        if(this->value) this->value->accept(visitor);
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const ReturnStatement* o = static_cast<const ReturnStatement*>(&other);
        return CMP_AND_DREF_PTR(this->value, o->value);
    }
};

class WhileStatement : public Statement {
private:
    Expression* condition;
    std::vector<Statement*> statements;
public:
    WhileStatement(Expression* condition, std::vector<ast::Statement*> statements) : condition(condition), statements(statements) { }
    virtual ~WhileStatement() {
        delete this->condition;
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        llvm::Function* parent = cg->irBuilder->GetInsertBlock()->getParent();

        auto* condBlock = llvm::BasicBlock::Create(*cg->context, "whileCondition", parent);
        cg->irBuilder->CreateBr(condBlock);
        cg->irBuilder->SetInsertPoint(condBlock);

        auto* cond = this->condition->generateCode(cg);
        auto* typeCond = this->condition->getLlvmType(cg);

        if(!cond or !typeCond)
            return nullptr;
        if(typeCond->isFloatingPointTy()) {
            cond = cg->irBuilder->CreateFCmpONE(cond, llvm::ConstantFP::get(*cg->context, llvm::APFloat(0.0f)), "FCmpONE");
        } else if(typeCond->isIntegerTy()) {
            cond = cg -> irBuilder->CreateICmpNE(cond, llvm::ConstantInt::get(llvm::Type::getInt1Ty(*cg->context), 0),"ICmpNE");
        } else {
            DIE_CODEGEN("Could not generate code because condition is no boolean expression")
        }

        auto* thenBlock = llvm::BasicBlock::Create(*cg->context, "whileThen", parent);
        auto* mergeBlock = llvm::BasicBlock::Create(*cg->context, "whileCont", parent);
        cg->irBuilder->CreateCondBr(cond, thenBlock, mergeBlock);

        //Then Block
        cg->irBuilder->SetInsertPoint(thenBlock);
        for (const auto &item : this->statements){
            if(!item->generateCode(cg))
                DIE_CODEGEN("Statement of if, didn't return any llvm code");
        }
        cg->irBuilder->CreateBr(condBlock);

        //Merge Block
        cg->irBuilder->SetInsertPoint(mergeBlock);
        return condBlock;
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        this->condition->accept(visitor);
        for(auto* e : this->statements){
            e->accept(visitor);
        }
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const WhileStatement* o = static_cast<const WhileStatement*>(&other);
        return CMP_AND_DREF_PTR(this->condition, o->condition)
            && this->statements.size() == o->statements.size()
            && std::equal(this->statements.begin(), this->statements.end(), o->statements.begin(), o->statements.end(), [](const Statement* lhs, const Statement* rhs){ return *lhs == *rhs; });
    }
};

class ElifStatement : public Statement {
private:
    Expression* condition;
    std::vector<Statement*> statements;
public:
    ElifStatement(Expression* condition, std::vector<Statement*> statements) : condition(condition), statements(statements) { }
    virtual ~ElifStatement() {
        delete this->condition;
        for(Statement* statement : this->statements){
            delete statement;
        }
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        DIE_CODEGEN("generateCode of ELIF Statement called!")
    };
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        this->condition->accept(visitor);
        for(auto* e : this->statements){
            e->accept(visitor);
        }
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const ElifStatement* o = static_cast<const ElifStatement*>(&other);
        return CMP_AND_DREF_PTR(this->condition, o->condition)
            && this->statements.size() == o->statements.size()
            && std::equal(this->statements.begin(), this->statements.end(), o->statements.begin(), o->statements.end(), [](const Statement* lhs, const Statement* rhs){ return *lhs == *rhs; });
    }
    Expression* getCondition() {return this->condition; }
    std::vector<Statement*> getStatements() { return this->statements; }
};

class ElseStatement : public Statement {
private:
    std::vector<Statement*> statements;
public:
    ElseStatement(std::vector<Statement*> statements) : statements(statements) { }
    virtual ~ElseStatement() {
        for(Statement* statement : this->statements){
            delete statement;
        }
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        llvm::Value* ret = nullptr;
        for (const auto &item : this->statements){
            ret = item->generateCode(cg);
            if(!ret)
                DIE_CODEGEN("Statement of ELSE did not generate any llvm code")
        }
        return ret;
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        for(auto* e : this->statements){
            e->accept(visitor);
        }
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const ElseStatement* o = static_cast<const ElseStatement*>(&other);
        return this->statements.size() == o->statements.size()
            && std::equal(this->statements.begin(), this->statements.end(), o->statements.begin(), o->statements.end(), [](const Statement* lhs, const Statement* rhs){ return CMP_AND_DREF_PTR(lhs, rhs);});
    }
    std::vector<Statement*> getStatements() {
        return this->statements;
    }
};

class IfStatement : public Statement {
private:
    Expression* condition;
    std::vector<Statement*> statements;
    std::vector<ElifStatement*> elifStatements;
    ElseStatement* elseStatement;
    llvm::Value* createCmp(CodeGenerator* cg, llvm::Type* typeCond, llvm::Value* cond){
        if(typeCond->isFloatingPointTy()){
            return cg->irBuilder->CreateFCmpONE(cond, llvm::ConstantFP::get(*cg->context, llvm::APFloat(0.0f)),"FCmpONE");
        }else if(typeCond->isIntegerTy()){
            return cg->irBuilder->CreateICmpNE(cond, llvm::ConstantInt::get(llvm::Type::getInt1Ty(*cg->context), 0),"ICmpNE");
        }else{
            DIE_CODEGEN("Trying to compare something other than Int or Float");
        }
    }
    bool generateElifCode(CodeGenerator *cg, llvm::BasicBlock* mergeBlock){
        for (const auto &elifStmt : this->elifStatements){
            llvm::Function* elif_parent = cg->irBuilder->GetInsertBlock()->getParent(); // any diff ?
            auto* thenB = llvm::BasicBlock::Create(*cg->context, "elifThen", elif_parent);
            auto* elseB = llvm::BasicBlock::Create(*cg->context, "elifElse", elif_parent);
            auto* cond = elifStmt->getCondition()->generateCode(cg);
            auto* condT = elifStmt->getCondition()->getLlvmType(cg);
            if(!cond or !condT){
                DIE_CODEGEN_BOOL("ELIF Cond is wrong.")
            }
            cg->irBuilder->CreateCondBr(this->createCmp(cg, condT, cond), thenB, elseB);
            cg->irBuilder->SetInsertPoint(thenB);
            for (const auto &stmt : elifStmt->getStatements()){
                if(!stmt->generateCode(cg))
                DIE_CODEGEN_BOOL("Statement of elif, didn't return any llvm code")
            }
            cg->irBuilder->CreateBr(mergeBlock);
            cg->irBuilder->SetInsertPoint(elseB);

        }
        return true;
    }
public:
    IfStatement(Expression* condition, std::vector<Statement*> statements, std::vector<ElifStatement*> elifStatements, ElseStatement* elseStatement)
        : condition(condition), statements(statements), elifStatements(elifStatements), elseStatement(elseStatement) { }
    virtual ~IfStatement() {
        delete this->condition;
        for(Statement* statement : this->statements){
            delete statement;
        }
        for(ElifStatement* elifStatement : this->elifStatements){
            delete elifStatement;
        }
        delete this->elseStatement;
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        auto* cond = this->condition->generateCode(cg);
        auto* typeCond = this->condition->getLlvmType(cg);

        if(!cond or !typeCond)
            return nullptr;
        cond = this->createCmp(cg, typeCond, cond);

        llvm::Function* parent = cg->irBuilder->GetInsertBlock()->getParent();
        auto* thenBlock = llvm::BasicBlock::Create(*cg->context, "then", parent);
        auto* elseBlock = llvm::BasicBlock::Create(*cg->context, "else");
        auto* mergeBlock = llvm::BasicBlock::Create(*cg->context, "ifcont");
        cg->irBuilder->CreateCondBr(cond, thenBlock, elseBlock);

        //Then Block
        cg->irBuilder->SetInsertPoint(thenBlock);
        for (const auto &item : this->statements){
            if(!item->generateCode(cg))
                DIE_CODEGEN("Statement of if, didn't return any llvm code");
        }
        cg->irBuilder->CreateBr(mergeBlock);

        //Else Block
        parent->getBasicBlockList().push_back(elseBlock);
        cg->irBuilder->SetInsertPoint(elseBlock);
        //Elifs
        if(!this->elifStatements.empty())
            if(!this->generateElifCode(cg, mergeBlock))
                DIE_CODEGEN("ElifCodeGen failed. See Above.");
        //Back to Else Block
        if(this->elseStatement){
            auto ret = this->elseStatement->generateCode(cg);
            if(!ret)
                DIE_CODEGEN("Else-Statements of if, didn't return any llvm code");
        }
        cg->irBuilder->CreateBr(mergeBlock);

        //Merge Block
        parent->getBasicBlockList().push_back(mergeBlock);
        cg->irBuilder->SetInsertPoint(mergeBlock);
        return thenBlock;
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        for(auto* e : this->statements){
            e->accept(visitor);
        }
        // End visit early, i.e pop Scope...
        visitor->endVisit(this);
        for(auto* e : this->elifStatements){
            e->accept(visitor);
        }
        if(elseStatement) elseStatement->accept(visitor);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const IfStatement* o = static_cast<const IfStatement*>(&other);

        return CMP_AND_DREF_PTR(this->condition, o->condition)
            && CMP_AND_DREF_PTR(this->elseStatement, o->elseStatement)
            && this->statements.size() == o->statements.size()
            && this->elifStatements.size() == o->elifStatements.size()
            && std::equal(this->statements.begin(), this->statements.end(), o->statements.begin(), o->statements.end(), [](const Statement* lhs, const Statement* rhs){ return CMP_AND_DREF_PTR(lhs, rhs); })
            && std::equal(this->elifStatements.begin(), this->elifStatements.end(), o->elifStatements.begin(), o->elifStatements.end(), [](const ElifStatement* lhs, const ElifStatement* rhs){ return CMP_AND_DREF_PTR(lhs, rhs);});
    }
};

class FunctionCallStatement: public Statement {
private:
    FunctionCallExpression* functionCallExpression;
public:
    FunctionCallStatement(FunctionCallExpression* functionCallExpression) : functionCallExpression(functionCallExpression) { }
    virtual ~FunctionCallStatement() {
        delete this->functionCallExpression;
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        return functionCallExpression->generateCode(cg);
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        this->functionCallExpression->accept(visitor);
        visitor->endVisit(this);
    }
    virtual bool operator==(const Comparable& other) const override {
        if(this == &other) return true;
        if(typeid(*this) != typeid(other)) return false;
        const FunctionCallStatement* o = static_cast<const FunctionCallStatement*>(&other);
        return CMP_AND_DREF_PTR(this->functionCallExpression, o->functionCallExpression);
    }
};

}

#endif //BLINDWORM_COMPILER_STATEMENT_H
