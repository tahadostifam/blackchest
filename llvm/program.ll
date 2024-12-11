; ModuleID = 'main'
source_filename = "main"

define i32 @my_func(i32 %0, i32 %1) {
entry:
  %sum = add i32 %0, %1
  ret i32 %sum
}

define i32 @main() {
entry:
}
