#ifndef BLINDWORM_COMPILER_CODENODE_H
#define BLINDWORM_COMPILER_CODENODE_H

#include <iostream>
#include "comparable.h"
#include "visitor.h"
#include "../codegen/codegen.h"

#define NO_STMT nullptr
#define NO_EXPR nullptr

#define DIE_CODEGEN(msg) { std::cerr << msg << std::endl; return nullptr; }
#define DIE_CODEGEN_BOOL(msg) { std::cerr << msg << std::endl; return false; }
#define CN_ACCEPT_METHOD_WITH_BASECLASS(base)           \
    virtual void accept(Visitor* visitor) override {    \
        visitor->visit(this);                           \
        base::accept(visitor);                          \
        visitor->endVisit(this);                        \
    }

#define CN_ACCEPT_METHOD                                \
    virtual void accept(Visitor* visitor) override {    \
        visitor->visit(this);                           \
        visitor->endVisit(this);                        \
    }

namespace ast {
class CodeNode : public Comparable, public Visitable {
public:
    virtual ~CodeNode() { }
    virtual llvm::Value* generateCode(CodeGenerator* cg) = 0;
};
}

#endif //BLINDWORM_COMPILER_CODENODE_H
