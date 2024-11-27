//! write text file

/** imports */
use std::collections::HashMap;
use std::io::{BufRead, Write};
use std::path::PathBuf;


/** constants */
const PLAINTEXT_FILE: &str = "src/res/Tagore.txt";
const ENCRYPTED_FILE: &str = "src/res/Encrypted.txt";

const MORSE_DATA: [(char, &str); 45] = [
    ('A',	".-"),
    ('B',	"-..."),
    ('C',	"-.-."),
    ('D',	"-.."),
    ('E',	"."),
    ('F',	"..-."),
    ('G',	"--."),
    ('H',	"...."),
    ('I',	".."),
    ('J',	".---"),
    ('K',	"-.-"),
    ('L',	".-.."),
    ('M',	"--"),
    ('N',	"-."),
    ('O',	"---"),
    ('P',	".--."),
    ('Q',	"--.-"),
    ('R',	".-."),
    ('S',	"..."),
    ('T',	"-"),
    ('U',	"..-"),
    ('V',	"...-"),
    ('W',	".--"),
    ('X',	"-..-"),
    ('Y',	"-.--"),
    ('Z',	"--.."),
    ('0',	"-----"),
    ('1',	".----"),
    ('2',	"..---"),
    ('3',	"...--"),
    ('4',	"....-"),
    ('5',	"....."),
    ('6',	"-...."),
    ('7',	"--..."),
    ('8',	"---.."),
    ('9',	"----."),
    ('.',	".-.-.-"),
    (',',	"--..--"),
    (':',	"---..."),
    ('?',	"..--.."),
    ('\'',	".----."),
    ('-',	"-....-"),
    ('\"',	".-..-."),
    (' ',   "  "),
    ('\n',  ".-.-")
];


/// main method: translate character to morse string
pub fn main() -> Result<(), std::io::Error> {
    // dictionary
    let morse_dict: HashMap<char, &str> = HashMap::from(MORSE_DATA);

    // read original text by lines
    let mut original_file_path = std::env::current_dir()?;
    original_file_path.push(PLAINTEXT_FILE);

    let original_file = std::fs::File::open(original_file_path)?;
    let original_text_io = std::io::BufReader::new(original_file);

    // translate by characters
    let mut encrypted_text= String::new();
    for line in original_text_io.lines() {        
        for ch in line?.chars() {
            if let Some(e_ch) = morse_dict.get(&ch.to_ascii_uppercase()) {
                encrypted_text.push_str(e_ch);
            }
        }

        encrypted_text.push('\n');
    }

    // write to file
    let mut encrypted_file_path = std::env::current_dir()?;
    encrypted_file_path.push(ENCRYPTED_FILE);

    let mut encrypted_file = std::fs::File::create(encrypted_file_path)?;
    encrypted_file.write_all(encrypted_text.as_bytes())?;

    Ok(())
}
