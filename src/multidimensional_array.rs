//! multi-dimensional array

/** typings  */
type Vector2f = [f64; 2];
type Matrix2x2f = [Vector2f; 2];


/// rotate a 2-dim vector
fn rotate(vec: &Vector2f, angle: f64) -> Vector2f {

    let rotate_mat: Matrix2x2f = [
        [angle.cos(), -angle.sin()],
        [angle.sin(), angle.cos()]
    ];

    return [
        rotate_mat[0][0] * vec[0] + rotate_mat[0][1] * vec[1],
        rotate_mat[1][0] * vec[0] + rotate_mat[1][1] * vec[1]
    ]
}


/// string representation
fn to_string(vec: &Vector2f) -> String {
    return format!("({:.2}, {:.2})", vec[0], vec[1])
}


/// main method
pub fn main() {
    
    let x_unit: Vector2f = [1.0, 0.0];
    let oblique_unit = rotate(&x_unit, std::f64::consts::PI / 6.0);

    println!("{}", to_string(&oblique_unit));
}
