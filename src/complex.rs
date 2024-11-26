//! complex number


/// use macro to implement precision of complex
macro_rules! complex_define {
    ($num_type:ty) => {
        
        // constants; error tolerance
        const DELTA: $num_type = 0.0001 as $num_type;
        const PI: $num_type = 3.1416 as $num_type;

        /// complex number struct
        struct Complex {
            real: $num_type,
            imag: $num_type
        }

        /// methods of complex struct
        impl Complex {

            /// string representation
            fn to_string(&self) -> String {
                return format!("{} + {} i", self.real, self.imag);
            }

            /// magnitude
            fn abs(&self) -> $num_type {
                return ((self.real * self.real + self.imag * self.imag) as f64).sqrt() as $num_type;
            }

            /// argument angle
            fn arg(&self) -> $num_type {
                if self.real <= DELTA {
                    let _arg: $num_type = PI / (2.0 as $num_type);

                    if self.imag >= (0.0 as $num_type) {
                        return _arg;
                    } else {
                        // cannot apply unary operator `-` to unsigned int type
                        return (0.0 as $num_type) -_arg;
                    }

                } else {
                    return ((self.imag / self.real) as f64).atan() as $num_type;
                }
            }

            /// triangle function representation
            fn to_tri_string(&self) -> String {
                return format!("{} (cos {} + i sin {})", self.abs(), self.arg(), self.arg());
            }
        }        
    };
}


/// Main method: complex number defined by macro
pub fn main() {
    // complex_define!(f32);
    // let c = Complex {
    //     real: 1.0,
    //     imag: 2.0
    // };

    // complex_define!(i32);
    // let c = Complex {
    //     real: 1,
    //     imag: 1
    // };

    complex_define!(u32);
    let c = Complex {
        real: 1,
        imag: 1
    };

    println!("{}", c.to_string());
    println!("{}", c.to_tri_string());
}
