#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;

//-----------------------------------------------------------------------------
// RecursiveASTVisitor
//-----------------------------------------------------------------------------
class StructPrinter : public RecursiveASTVisitor<StructPrinter> {
public:
    bool VisitRecordDecl(RecordDecl *Declaration) {
        DeclarationName name = Declaration->getDeclName();
        if (name.isEmpty()) return true;

        llvm::outs() << "Struct Name: " << Declaration->getDeclName() << "\n";
        return true;
    }
};


//-----------------------------------------------------------------------------
// ASTConsumer
//-----------------------------------------------------------------------------
class PrintStructASTConsumer : public clang::ASTConsumer {
public:
  void HandleTranslationUnit(clang::ASTContext &Ctx) override {
    StructPrinter visitor;
    visitor.TraverseDecl(Ctx.getTranslationUnitDecl());
  }
};

//-----------------------------------------------------------------------------
// FrontendAction for StructPrinter
//-----------------------------------------------------------------------------
class FindNamedClassAction : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer>
  CreateASTConsumer(clang::CompilerInstance &Compiler,
                    llvm::StringRef InFile) override {
    return std::make_unique<PrintStructASTConsumer>();
  }
  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &args) override {
    return true;
  }
};

//-----------------------------------------------------------------------------
// Registration
//-----------------------------------------------------------------------------
static FrontendPluginRegistry::Add<FindNamedClassAction>
    X(/*Name=*/"print-struct", /*Description=*/"Prints the name and members of a C structure.");
