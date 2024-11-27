//! read text file

/** imports */
use std::io::BufRead;


/** constants */
const TEXT_FILENAME: &str = "src/res/GNU通用公共许可协议3.0.txt";


/// read by lines
fn read_by_lines() -> Result<Vec<String>, std::io::Error> {
    // get file path to be read
    let mut text_file_path = std::env::current_dir()?;
    text_file_path.push(TEXT_FILENAME);

    println!("File path: {}", text_file_path.display());

    // open the file
    let text_file = std::fs::File::open(text_file_path)?;
    let text_io = std::io::BufReader::new(text_file);

    // read by lines
    let mut lines: Vec<String> = Vec::new();
    for line in text_io.lines() {
        lines.push(line?);
    }

    Ok(lines)
}


/// read all
fn read_all() -> Result<String, std::io::Error> {
    // get file path to be read
    let mut text_file_path = std::env::current_dir()?;
    text_file_path.push(TEXT_FILENAME);

    println!("File path: {}", text_file_path.display());

    // read all
    let text_content = std::fs::read_to_string(text_file_path)?;

    Ok(text_content)
}


/// main method
pub fn main() {
    // read all
    // println!("{}", read_all().unwrap());

    // read lines
    println!("{}", read_by_lines().unwrap().join("\n"));
}
