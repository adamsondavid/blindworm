#ifndef BLINDWORM_COMPILER_SYMBOLTABLEVISITOR_H
#define BLINDWORM_COMPILER_SYMBOLTABLEVISITOR_H

#include "../parser/visitor.h"
#include "symboltable.h"

class SymbolTableVisitor : public ast::Visitor {
private:
    SymbolTable table;
public:
    virtual ~SymbolTableVisitor() { }

    virtual void visit(ast::IfStatement* elem) override { this->table.enter(); }
    virtual void endVisit(ast::IfStatement* elem) override { this->table.leave(); }

    virtual void visit(ast::ElifStatement* elem) override { this->table.enter(); }
    virtual void endVisit(ast::ElifStatement* elem) override { this->table.leave(); }

    virtual void visit(ast::ElseStatement* elem) override { this->table.enter(); }
    virtual void endVisit(ast::ElseStatement* elem) override { this->table.leave(); }

    virtual void visit(ast::WhileStatement* elem) override { table.enter(); }
    virtual void endVisit(ast::WhileStatement* elem) override { table.leave(); }

    virtual void visit(ast::FunctionDefinitionStatement* elem) override {
        this->table.put(SymbolTableEntry({elem->getIdentifier(), elem->getFunctionType()}));
        this->table.enter();
    }

    virtual void endVisit(ast::FunctionDefinitionStatement* elem) override {
        this->table.leave();
    }

    virtual void visit(ast::NativeFunctionDefinitionStatement* elem) override {
        this->table.put(SymbolTableEntry({elem->getIdentifier(), elem->getFunctionType()}));
        this->table.enter();
    }

    virtual void endVisit(ast::NativeFunctionDefinitionStatement* elem) override {
        this->table.leave();
    }

    virtual void visit(ast::VariableDeclarationStatement* elem) override {
        this->table.put(SymbolTableEntry({elem->getIdentifier(), elem->getDataType()}));
    }

    virtual void visit(ast::IdentifierExpression* elem) override {
        //Will throw a SemanticException, if no entry was found
        auto entry = this->table.get(elem->getIdentifier());
    }

    virtual void visit(ast::FunctionCallExpression* elem) override {
        //Will throw a SemanticException, if no entry was found
        auto entry = this->table.get(elem->getIdentifier());
    }

    virtual void visit(ast::AssignmentStatement* elem) override {
        //Will throw a SemanticException, if no entry was found
        auto entry = this->table.get(elem->getIdentifier());
    }
};

#endif //BLINDWORM_COMPILER_SYMBOLTABLEVISITOR_H
