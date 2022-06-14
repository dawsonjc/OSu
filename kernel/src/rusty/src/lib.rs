#![no_std]
#![allow(nonstandard_style)]
#![allow(unused_parens)]

use core::panic::PanicInfo;

#[no_mangle]
pub extern "C" fn testFunction(withValue: bool, hasValue: bool) -> i32 {
    return 32_i32;
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    return loop {};
}