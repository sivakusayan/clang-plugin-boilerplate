#include "clang/AST/ASTConsumer.h"
#include "clang/AST/RecursiveASTVisitor.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Frontend/FrontendPluginRegistry.h"
#include "llvm/Support/raw_ostream.h"

using namespace clang;

/**
 * The real bread-and-butter of this plugin. This visitor will walk Clang's AST,
 * and execute the below function for every RecordDecl.
 */
class StructPrinter : public RecursiveASTVisitor<StructPrinter> {
public:
    bool VisitRecordDecl(RecordDecl *Declaration) {
        if (!Declaration->isStruct()) return true;

        DeclarationName name = Declaration->getDeclName();
        if (name.isEmpty()) return true;

        llvm::outs() << "Struct Name: " << Declaration->getDeclName() << "\n";
        return true;
    }
};


/**
 * All of the code below can be considered boilerplate, at least for the sake
 * of this example. We basically create a class that lets Clang know that
 * we care about the AST, and then we invoke our visitor on every generated
 * translation unit.
 */
class PrintStructASTConsumer : public clang::ASTConsumer {
public:
  void HandleTranslationUnit(clang::ASTContext &Ctx) override {
    StructPrinter visitor;
    visitor.TraverseDecl(Ctx.getTranslationUnitDecl());
  }
};

class FindNamedClassAction : public clang::PluginASTAction {
public:
  std::unique_ptr<clang::ASTConsumer> CreateASTConsumer(clang::CompilerInstance &Compiler,
                                                        llvm::StringRef InFile) override {
    return std::make_unique<PrintStructASTConsumer>();
  }
  bool ParseArgs(const CompilerInstance &CI,
                 const std::vector<std::string> &args) override {
    return true;
  }
};

static FrontendPluginRegistry::Add<FindNamedClassAction>
    X(/*Name=*/"print-struct", /*Description=*/"Prints the name and members of a C structure.");
