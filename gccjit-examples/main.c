// Example code to demonstrate compiling nested if blocks using libgccjit
#include <stdio.h>
#include <stdlib.h>
#include <libgccjit.h>

int main() {
    gcc_jit_context *context = gcc_jit_context_acquire();
    if (!context) {
        fprintf(stderr, "Failed to create JIT context\n");
        return 1;
    }

    gcc_jit_context_set_int_option(context, GCC_JIT_INT_OPTION_OPTIMIZATION_LEVEL, 3);

    gcc_jit_type *int_type = gcc_jit_context_get_type(context, GCC_JIT_TYPE_INT32_T);
    gcc_jit_function *main_function = gcc_jit_context_new_function(
        context, NULL, GCC_JIT_FUNCTION_EXPORTED, int_type, "main", 0, NULL, 0);

    gcc_jit_block *entry_block = gcc_jit_function_new_block(main_function, "entry");

    // Define constants for comparisons
    gcc_jit_rvalue *const_1 = gcc_jit_context_new_rvalue_from_int(context, int_type, 1);
    gcc_jit_rvalue *const_2 = gcc_jit_context_new_rvalue_from_int(context, int_type, 2);
    gcc_jit_rvalue *const_10 = gcc_jit_context_new_rvalue_from_int(context, int_type, 10);
    gcc_jit_rvalue *const_3 = gcc_jit_context_new_rvalue_from_int(context, int_type, 3);
    gcc_jit_rvalue *const_4 = gcc_jit_context_new_rvalue_from_int(context, int_type, 4);

    // Create the nested if structure
    gcc_jit_block *true_block_1 = gcc_jit_function_new_block(main_function, "true_block_1");
    gcc_jit_block *false_block_1 = gcc_jit_function_new_block(main_function, "false_block_1");
    gcc_jit_block *true_block_2 = gcc_jit_function_new_block(main_function, "true_block_2");
    gcc_jit_block *false_block_2 = gcc_jit_function_new_block(main_function, "false_block_2");
    gcc_jit_block *final_block = gcc_jit_function_new_block(main_function, "final_block");

    // First condition: if (1 < 2)
    gcc_jit_rvalue *condition_1 = gcc_jit_context_new_comparison(
        context, NULL, GCC_JIT_COMPARISON_LT, const_1, const_2);
    gcc_jit_block_end_with_conditional(entry_block, NULL, condition_1, true_block_1, false_block_1);

    // Inside true_block_1: if (10 == 10)
    gcc_jit_rvalue *condition_2 = gcc_jit_context_new_comparison(
        context, NULL, GCC_JIT_COMPARISON_EQ, const_10, const_10);
    gcc_jit_block_end_with_conditional(true_block_1, NULL, condition_2, true_block_2, false_block_2);

    // End both branches of nested if
    gcc_jit_block_end_with_jump(true_block_2, NULL, final_block);
    gcc_jit_block_end_with_jump(false_block_2, NULL, final_block);

    // In false_block_1: else if (3 < 4)
    gcc_jit_rvalue *condition_3 = gcc_jit_context_new_comparison(
        context, NULL, GCC_JIT_COMPARISON_LT, const_3, const_4);
    gcc_jit_block_end_with_conditional(false_block_1, NULL, condition_3, true_block_2, final_block);

    // Final block: return 0
    gcc_jit_block_end_with_return(final_block, NULL, gcc_jit_context_new_rvalue_from_int(context, int_type, 0));

    // Compile the code
    gcc_jit_result *result = gcc_jit_context_compile(context);
    if (!result) {
        fprintf(stderr, "Failed to compile JIT code\n");
        gcc_jit_context_release(context);
        return 1;
    }

    // Execute the compiled code
    gcc_jit_context_dump_to_file(context, "./dumped", 1);

    typedef int (*compiled_main_t)(void);
    compiled_main_t compiled_main = (compiled_main_t)gcc_jit_result_get_code(result, "main");
    if (!compiled_main) {
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
