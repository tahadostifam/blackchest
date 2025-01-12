use std::sync::{Arc, Mutex};

fn doit() {
    let data = Arc::new(Mutex::new(Box::new("init")));

    change1(data.clone());

    let data_guard = data.lock().unwrap();
    println!("{}", **data_guard);
}

fn change1(data: Arc<Mutex<Box<&str>>>) {
    let mut data_guard = data.lock().unwrap();
    *data_guard = Box::new("changed"); // Change the Box itself
}

fn main() {
    doit(); // Output: changed
}