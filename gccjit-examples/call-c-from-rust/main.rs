use std::ffi::CString;

fn main() {
    let fmt = "Hello from Rust!";
    let fmt_str = CString::new(fmt).unwrap();

    unsafe { sample(fmt_str.as_ptr()) };
}

extern "C" {
    fn sample(fmt: *const i8);
}
