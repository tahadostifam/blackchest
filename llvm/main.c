#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <llvm-c/Core.h>
#include <llvm-c/ExecutionEngine.h>
#include <llvm-c/Analysis.h>

const char *module_name = "main";
const char *func_name = "my_func";

int main()
{

    LLVMContextRef context = LLVMContextCreate();
    LLVMModuleRef module = LLVMModuleCreateWithNameInContext(module_name, context);
    LLVMBuilderRef builder = LLVMCreateBuilderInContext(context);

    const char *content = "hello world";
    const char *global_var_name = "my_global_var";
    int content_len = strlen(content);

    LLVMValueRef value = LLVMConstStringInContext2(context, content, content_len, 0);
    LLVMTypeRef type = LLVMTypeOf(value);

    LLVMValueRef global_var = LLVMAddGlobal(module, type, global_var_name);
    LLVMSetInitializer(global_var, value);

    LLVMDumpModule(module);

    // Clean Memory
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    return 0;
}
