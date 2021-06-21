#ifndef BLINDWORM_COMPILER_CODEGEN_H
#define BLINDWORM_COMPILER_CODEGEN_H

#include <unordered_map>
#include <stack>
#include <string>
#include <ostream>

#include "llvm/Support/raw_os_ostream.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

// TODO: fix scopes!
class LLVMSymbolTable {
private:
    std::stack<std::unordered_map<std::string, llvm::AllocaInst*>> stack;
    std::unordered_map<std::string, llvm::AllocaInst*> scope;
public:
    /**
     * Enter new Scope
     */
    void enter() {
        this->stack.push(this->scope);
    }

    /**
    * Leave current scope
     * @throws SemanticException if no scope to leave
    */
    void leave() {
        this->scope = this->stack.top();
        this->stack.pop();
    }

    /**
     * Retrieve entry from the current scope
     * @param name of parameter
     * @return SymbolTableEntry
     * @throws SemanticException on key not found
     */
    llvm::AllocaInst* get(std::string name){
        try{
            return this->scope.at(name);
        } catch (std::out_of_range& e){
            return nullptr;
        }
    }

    void put(std::string identifier, llvm::AllocaInst* value){
        this->scope.insert({identifier, value});
    }
};

struct CodeGenerator {
    llvm::LLVMContext* context;
    llvm::Module* compilationUnit;
    llvm::IRBuilder<>* irBuilder;
    LLVMSymbolTable namedValues;

    CodeGenerator(std::string compilationUnit) {
        this->context = new llvm::LLVMContext();
        this->compilationUnit = new llvm::Module(compilationUnit, *this->context);
        this->irBuilder = new llvm::IRBuilder<>(*this->context);
    }

    ~CodeGenerator() {
        delete this->compilationUnit;
        delete this->context;
    }

    void print(std::ostream* ostream) {
        llvm::raw_os_ostream llvmOstream(*ostream);
        this->compilationUnit->print(llvmOstream, nullptr);
    }
};

#endif //BLINDWORM_COMPILER_CODEGEN_H
