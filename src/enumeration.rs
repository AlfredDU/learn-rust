//! enum


/// scalar of RGB color
mod rgb_color {
    pub type RGBTuple = (u8, u8, u8);

    pub const RED: RGBTuple = (255, 0, 0);
    pub const GREEN: RGBTuple = (0, 255, 0);
    pub const BLUE: RGBTuple = (0, 0, 255);
    pub const BLACK: RGBTuple = (0, 0, 0);
    pub const WHITE: RGBTuple = (255, 255, 255);

    pub fn to_string(rgb: RGBTuple) -> String {
        return format!("({}, {}, {})", rgb.0, rgb.1, rgb.2);
    }
}


/// enum of RGB color
enum RGB {
    RED,
    GREEN,
    BLUE,
    BLACK,
    WHITE
}


impl RGB {
    fn val(&self) -> rgb_color::RGBTuple {
        match self {
            &Self::RED => rgb_color::RED,
            &Self::GREEN => rgb_color::GREEN,
            &Self::BLUE => rgb_color::BLUE,
            &Self::WHITE => rgb_color::WHITE,
            &Self::BLACK => rgb_color::BLACK,
            // _ => nil
        }
    }

    fn to_string(&self) -> String {
        return rgb_color::to_string(self.val());
    }
}


/// main method
pub fn main() {
    println!("{}", RGB::BLUE.to_string());
}
