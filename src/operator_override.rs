//! override operators


/** imports */
use std::ops::{Add, Sub, Mul, Div};
use std::cmp::PartialEq;


/// Finite field (math concept) based on certain prime number.
struct FiniteFieldElement<const IDENTITY: i64> {
    val: i64
}


/// plus operator
impl<const IDENTITY: i64> Add for FiniteFieldElement<IDENTITY> {
    type Output = FiniteFieldElement<IDENTITY>;

    fn add(self, other: FiniteFieldElement<IDENTITY>) -> FiniteFieldElement<IDENTITY> {
        return FiniteFieldElement {
            val: (self.val + other.val) % IDENTITY
        };
    }
}


/// substract operator
impl<const IDENTITY: i64> Sub for FiniteFieldElement<IDENTITY> {
    type Output = FiniteFieldElement<IDENTITY>;

    fn sub(self, other: FiniteFieldElement<IDENTITY>) -> FiniteFieldElement<IDENTITY> {
        return FiniteFieldElement {
            val: (self.val - other.val + IDENTITY) % IDENTITY
        };
    }
}


/// multiply operator
impl<const IDENTITY: i64> Mul for FiniteFieldElement<IDENTITY> {
    type Output = FiniteFieldElement<IDENTITY>;

    fn mul(self, other: FiniteFieldElement<IDENTITY>) -> FiniteFieldElement<IDENTITY> {
        return FiniteFieldElement {
            val: (self.val * other.val) % IDENTITY
        };
    }
}


/// divide operator
impl<const IDENTITY: i64> Div for FiniteFieldElement<IDENTITY> {
    type Output = FiniteFieldElement<IDENTITY>;

    fn div(self, other: FiniteFieldElement<IDENTITY>) -> FiniteFieldElement<IDENTITY> {
        for _i in 0 .. IDENTITY {
            if (_i * other.val) % IDENTITY == self.val % IDENTITY {
                return FiniteFieldElement{val: _i};
            }
        }
        return FiniteFieldElement{val: 0};
    }
}


/// equal operator
impl<const IDENTITY: i64> PartialEq for FiniteFieldElement<IDENTITY> {
    fn eq(&self, other: &FiniteFieldElement<IDENTITY>) -> bool {
        return (self.val - other.val) % IDENTITY == 0;
    }
}


/// main entry; take 5-finite field as example
pub fn main() {
    let FIVE_0 = FiniteFieldElement::<5>{val: 0};
    let FIVE_1 = FiniteFieldElement::<5>{val: 1};
    let FIVE_2 = FiniteFieldElement::<5>{val: 2};
    let FIVE_3 = FiniteFieldElement::<5>{val: 3};
    let FIVE_4 = FiniteFieldElement::<5>{val: 4};

    println!("{}", (FIVE_3 / FIVE_4 == FIVE_2));
}
