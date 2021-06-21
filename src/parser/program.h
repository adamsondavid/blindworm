#ifndef BLINDWORM_COMPILER_PROGRAM_H
#define BLINDWORM_COMPILER_PROGRAM_H

#include <vector>
#include "codenode.h"
#include "statement.h"

namespace ast {
class Program : public CodeNode {
private:
    std::vector<Statement*> statements;
public:
    Program(std::vector<Statement*> statements): statements(statements) { }
    ~Program() {
        for(Statement* statement : this->statements){
            delete statement;
        }
    }
    virtual void accept(Visitor* visitor) override {
        visitor->visit(this);
        for(Statement* statement : this->statements) {
           statement->accept(visitor);
        }
        visitor->endVisit(this);
    }
    virtual llvm::Value* generateCode(CodeGenerator* cg) override {
        for(Statement* statement : this->statements) {
            if(!statement->generateCode(cg))
                DIE_CODEGEN("statement->generateCode received a nullptr")
        }
        return nullptr;
    }
    virtual bool operator==(const Comparable& other) const override {
        const Program* o = static_cast<const Program*>(&other);
        if(this->statements.size() != o->statements.size()) return false;
        for(int i = 0; i < this->statements.size(); i++) {
            if(!(*this->statements.at(i) == *o->statements.at(i))) {
                return false;
            }
        }
        return true;
    }
};
}

#endif //BLINDWORM_COMPILER_PROGRAM_H
