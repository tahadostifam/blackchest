#include <stdio.h>
#include <stdbool.h>
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

    // My func 
    LLVMTypeRef ret_type = LLVMInt32TypeInContext(context);
    LLVMTypeRef a = LLVMInt32TypeInContext(context);
    LLVMTypeRef b = LLVMInt32TypeInContext(context);
    LLVMTypeRef params[] = {a, b};
    LLVMTypeRef func_type = LLVMFunctionType(ret_type, params, 2, false);
    LLVMValueRef func = LLVMAddFunction(module, func_name, func_type);
    LLVMBasicBlockRef entry = LLVMAppendBasicBlockInContext(context, func, "entry");
    LLVMPositionBuilderAtEnd(builder, entry);
    LLVMValueRef val1 = LLVMGetParam(func, 0); // Sum the value of a & b 
    LLVMValueRef val2 = LLVMGetParam(func, 1);
    LLVMValueRef sum = LLVMBuildAdd(builder, val1, val2, "sum"); 
    LLVMBuildRet(builder, sum);

    // Main funnc 
    LLVMTypeRef c = LLVMInt32TypeInContext(context);
    LLVMTypeRef main_func_type = LLVMFunctionType(c, NULL, 0, false);
    LLVMValueRef main_func = LLVMAddFunction(module, "main", main_func_type);

    LLVMBasicBlockRef main_entry = LLVMAppendBasicBlockInContext(context, main_func, "entry");
    LLVMPositionBuilderAtEnd(builder, main_entry);

    // LLVMBuildRet(builder, LLVMConstInt(LLVMInt32Type(), 0, 0));

    // LLVMValueRef result = LLVMfunc(engine, func, 2, args);

    // int result_value = LLVMGenericValueToInt(result, false);
    // printf("result: %d\n", result_value);

    // Verify the function 
    char *err = NULL;
    if (LLVMVerifyModule(module, LLVMAbortProcessAction, &err)) {
        fprintf(stderr, "Error verifying the module: %s\n", err);
        LLVMDisposeMessage(err);
        return -1;
    }

    // LLVMPrintModuleToFile(module, "program.ll", NULL);

    // Clean Memory
    LLVMDisposeBuilder(builder);
    LLVMDisposeModule(module);
    LLVMContextDispose(context);

    return 0;
}
