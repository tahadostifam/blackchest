#include <llvm-c/Types.h>
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

    LLVMTypeRef int_type = LLVMInt32TypeInContext(context);


    // Sample function 
    LLVMTypeRef param_types[] = {};

    LLVMTypeRef func = LLVMFunctionType(int_type, param_types, 0, 0);
    LLVMValueRef callee = LLVMAddFunction(module, "sample", func);
    LLVMBasicBlockRef entry_block = LLVMAppendBasicBlockInContext(context, callee, "entry");
    LLVMPositionBuilderAtEnd(builder, entry_block);

    LLVMValueRef ret_value = LLVMConstInt(int_type, 10, 0);
    LLVMBuildRet(builder, ret_value);
    // Sample function end

    
    LLVMTypeRef function_type = LLVMFunctionType(int_type, NULL, 0, 0); // No arguments
    LLVMValueRef main_function = LLVMAddFunction(module, "main", function_type);
    LLVMBasicBlockRef entry_block2 = LLVMAppendBasicBlockInContext(context, main_function, "entry");
    LLVMPositionBuilderAtEnd(builder, entry_block2);
    LLVMValueRef sample_loaded = LLVMGetNamedFunction(module, "sample");
    LLVMTypeRef int_type2 = LLVMInt32TypeInContext(context);

    LLVMBuildCall2(builder, func, callee, NULL, 0, NULL);

    // -------------------------

    // -------------------------

    // Create a constant integer value (return 0)
    LLVMValueRef return_value = LLVMConstInt(int_type, 0, 0);

    // Create a return instruction
    LLVMBuildRet(builder, return_value);

    char *error = NULL;
    LLVMVerifyModule(module, LLVMAbortProcessAction, &error);

    LLVMDumpModule(module);

    return 0;
}
