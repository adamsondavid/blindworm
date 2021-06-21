#ifndef BLINDWORM_COMPILER_SYMBOLTABLE_H
#define BLINDWORM_COMPILER_SYMBOLTABLE_H

#include <unordered_map>
#include <stack>
#include <string>
#include "../parser/statement.h"
#include "semanticexception.h"

struct SymbolTableEntry {
    std::string identifier;
    ast::ReturnType* type;
};

class SymbolTable {
private:
    std::stack<std::unordered_map<std::string, SymbolTableEntry>> stack;
    std::unordered_map<std::string, SymbolTableEntry> scope;

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
        if(this->stack.empty())
            throw new SemanticException("No Scope to leave.");
        this->scope = this->stack.top();
        this->stack.pop();
    }

    /**
     * Retrieve entry from the current scope
     * @param name of parameter
     * @return SymbolTableEntry
     * @throws SemanticException on key not found
     */
    SymbolTableEntry get(std::string name){
        try{
            return this->scope.at(name);
        } catch (std::out_of_range& e){
            char buf[128];
            sprintf(buf, "the identifier '%s' was not yet declared", name.c_str());
            throw SemanticException(std::string(buf));
        }
    }

    void put(SymbolTableEntry value){
        this->scope.insert({value.identifier, value});
    }
};

#endif //BLINDWORM_COMPILER_SYMBOLTABLE_H

