use llvm_sys::core::*;

fn main() {
    unsafe {
        let context = LLVMContextCreate();
        let module = LLVMModuleCreateWithNameInContext("my_module".as_ptr() as *const i8, context);

        unsafe {
            let content = "StringContent";
            let content_i8 = content.as_ptr() as *const i8;
            let string_value = LLVMConstStringInContext(context, content_i8, content.len() as u32, 0);

            LLVMAddGlobal(module, LLVMTypeOf(string_value), "my_var".as_ptr() as *const i8);
        }

        LLVMDumpModule(module);
        LLVMDisposeModule(module);
        LLVMContextDispose(context);
    }
}
