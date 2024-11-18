use std::alloc::{alloc, dealloc, Layout};

fn main() {
    unsafe {
        let l = Layout::new::<i64>();
        let ptr = alloc(l);
        *ptr = 10;

        if !ptr.is_null() {
            println!("{}", *ptr);
        }

        println!("size: {}", l.size());

        dealloc(ptr, l);
    }
}
