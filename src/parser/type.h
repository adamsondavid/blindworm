#ifndef BLINDWORM_COMPILER_TYPE_H
#define BLINDWORM_COMPILER_TYPE_H

namespace ast {
class ReturnType : public Comparable, public Visitable {
public:
    virtual ~ReturnType() { };
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) = 0;
};

class DataType : public ReturnType {
public:
    virtual ~DataType() { }
};

/****************************************************** Types ****************************************/
class NoneType : public ReturnType {
public:
    virtual ~NoneType() { }
    CN_ACCEPT_METHOD
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getVoidTy(*cg->context);
    };
    virtual bool operator==(const Comparable& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        return true;
    }
};

class BoolType : public DataType {
public:
    virtual ~BoolType() { }
    CN_ACCEPT_METHOD
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt1Ty(*cg->context);
    };
    virtual bool operator==(const Comparable& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        return true;
    }
};

class IntType : public DataType {
public:
    virtual ~IntType() { }
    CN_ACCEPT_METHOD
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt32Ty(*cg->context);
    };
    virtual bool operator==(const Comparable& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        return true;
    }
};

class FloatType : public DataType {
public:
    virtual ~FloatType() { }
    CN_ACCEPT_METHOD
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getFloatTy(*cg->context);
    };
    virtual bool operator==(const Comparable& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        return true;
    }
};

class StrType : public DataType {
public:
    virtual ~StrType() { }
    CN_ACCEPT_METHOD
    virtual llvm::Type* getLlvmType(CodeGenerator* cg) override {
        return llvm::Type::getInt8PtrTy(*cg->context);
    };
    virtual bool operator==(const Comparable& other) const override {
        if (this == &other) return true;
        if (typeid(*this) != typeid(other)) return false;
        return true;
    }
};
}

#endif //BLINDWORM_COMPILER_TYPE_H
