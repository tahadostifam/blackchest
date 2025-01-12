; ModuleID = 'main.cy'
source_filename = "main.cy"

@format_str = private unnamed_addr constant [12 x i8] c"Hello World\00", align 1

define i32 @sum(i32 %0, i32 %1) {
entry:
  ret i32 10
}

define i32 @"main\E6U"() {
entry:
  %printf_call = call i32 (ptr, ...) @printf(ptr @format_str)
  ret i32 0
}

declare i32 @printf(ptr, ...)