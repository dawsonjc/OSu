#![no_std]
#![allow(nonstandard_style)]
#![allow(unused_parens)]

use core::panic::PanicInfo;

/**
 * This is a Test function to see if Rust goes with C.
 * # Arguments
 * * `withValue: bool` - to call this function this needs to be there
 * * `hasValue: bool` - this function has this variable
 *
 * returns: `32`
 *
 * # Examples
 * ```
 * int e = testFunction(true, true); // e holds 32
 * let e: i32 = testFunction(true, true); // e holds 32
 * ```
*/
#[no_mangle]
pub extern "C" fn testFunction(withValue: bool, hasValue: bool) -> i32 {
    return 32;
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    return loop {};
}