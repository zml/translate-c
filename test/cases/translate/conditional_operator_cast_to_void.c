int bar();
void foo() {
    int a;
    a ? a = 2 : bar();
}

// translate
//
// pub extern fn bar(...) c_int;
// pub export fn foo() void {
//     var a: c_int = undefined;
//     _ = &a;
//     _ = if (a != 0) blk: {
//         const tmp = @as(c_int, 2);
//         a = tmp;
//         break :blk tmp;
//     } else bar();
// }
