// Example code to demonstrate compiling nested if blocks using libgccjit
#include <stdio.h>
#include <stdlib.h>
#include <libgccjit.h>

int main()
{
    gcc_jit_context *context = gcc_jit_context_acquire();
    if (!context)
    {
        fprintf(stderr, "Failed to create JIT context\n");
        return 1;
    }

    gcc_jit_context_set_int_option(context, GCC_JIT_INT_OPTION_OPTIMIZATION_LEVEL, 3);

    gcc_jit_type *int_type = gcc_jit_context_get_type(context, GCC_JIT_TYPE_INT32_T);

    gcc_jit_function *main_function = gcc_jit_context_new_function(
        context, NULL, GCC_JIT_FUNCTION_EXPORTED, int_type, "main", 0, NULL, 0);

    gcc_jit_block *entry_block = gcc_jit_function_new_block(main_function, "entry");

    // ----------------------------------------------
    gcc_jit_type *array_type = gcc_jit_context_new_array_type(context, NULL, int_type, 3);
    gcc_jit_lvalue *variable_decl = gcc_jit_function_new_local(main_function, NULL, array_type, "my_array");

    gcc_jit_rvalue *item1 = gcc_jit_context_new_rvalue_from_int(context, int_type, 15);
    gcc_jit_rvalue *item2 = gcc_jit_context_new_rvalue_from_int(context, int_type, 20);
    gcc_jit_rvalue *item3 = gcc_jit_context_new_rvalue_from_int(context, int_type, 25);

    gcc_jit_rvalue *array_values[3] = { item1, item2, item3 };
    gcc_jit_rvalue *array =  gcc_jit_context_new_array_constructor(context, NULL, array_type, 3, array_values);

    gcc_jit_block_add_assignment(entry_block, NULL, variable_decl, array);

    // ----------------------------------------------

    // Final block: return 0
    gcc_jit_block_end_with_return(entry_block, NULL, gcc_jit_context_new_rvalue_from_int(context, int_type, 0));

    // Compile the code
    gcc_jit_result *result = gcc_jit_context_compile(context);
    if (!result)
    {
        fprintf(stderr, "Failed to compile JIT code\n");
        gcc_jit_context_release(context);
        return 1;
    }

    // Execute the compiled code
    gcc_jit_context_dump_to_file(context, "./dumped", 1);

    typedef int (*compiled_main_t)(void);
    compiled_main_t compiled_main = (compiled_main_t)gcc_jit_result_get_code(result, "main");
    if (!compiled_main)
    {
        fprintf(stderr, "Failed to retrieve JIT compiled function\n");
        gcc_jit_result_release(result);
        gcc_jit_context_release(context);
        return 1;
    }

    int exit_code = compiled_main();
    printf("Program exited with code %d\n", exit_code);

    // Cleanup
    gcc_jit_result_release(result);
    gcc_jit_context_release(context);

    return 0;
}
