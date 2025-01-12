use cc::Build;

fn main() {
    cc::Build::new()
        .file("./my_lib/my_lib.c")
        .compile("my_lib");
}
