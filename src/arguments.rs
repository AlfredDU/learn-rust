//! Read arguments from shell

// declare modules

// imports
use std::env;
use std::collections::HashMap;


/// Main method: use standard lib to parse arguments.
/// Accept arguments with pattern like "cmd --param0 value0 --param1 value1".
pub fn main() {

    // result
    let mut arguments: HashMap<&str, &String> = HashMap::new();

    // parse arguments
    let argv: Vec<String> = env::args().collect();
    let argc: usize = argv.len();


    if argc % 2 == 0 {
        eprintln!("improper arguments");
        panic!();
    }

    if argc > 1 {
        for _i in (1 .. argc).step_by(2) {
            if let Some(paramter) = argv[_i].strip_prefix("--") {
                arguments.insert(paramter, &argv[_i + 1]);


            } else {
                eprintln!("improper arguments");
                panic!();
            }
        }
    }

    // print the entire HashMap using debug formatting
    println!("{:?}", arguments);
}
