main:
	cc ./main.c -lLLVM -o ./program;

gen_llvm:
	clang -S -lLLVM -emit-llvm -o sample.ll ./sample.c 

run_llvm:
	clang -o sample ./sample.ll -lpthread -lc 

c_to_llvm:
	make gen_llvm;
	make run_llvm;