macro_rules! my_macro {
    ($arg1:expr $(, $variadic:expr)?) => {
        println!("Arg1: {}", $arg1);
        $(println!("Optional Arg2: {}", $variadic);)?
    };
}

fn main() {
    my_macro!(20); // Valid
}