

bool - 1-byte boolean type

u8 - 1-byte unsigned integer type

s8 - 1-byte signed integer type

u16 - 2-bytes unsigned integer type

s16 - 2-bytes signed integer type

u32 - 4-bytes unsigned integer type

s32 - 4-bytes signed integer type

f32 - 4-bytes scalar single-precision floating-point type

u64 - 8-bytes unsigned integer type

s64 - 8-bytes signed integer type

f64 - 8-bytes scalar double-precision floating-point type

sentence - utf-8 static string

delegate - holds a function pointer, to serve as a callback later:

```
delegate del;
//any function can be assigned to del

delegate() del2;
//only a function without arguments and return type can be assigned to del2

delegate(in f32) del3;
//only functions with an input argument of type 'f32' and without return type can be assigned to del3

delegate() del4 -> f32;
//only functions without arguments and with return type 'f32' can be assigned to del4

fn foo() f32
{
}

f32 foo_result;

fn callback()
{
  del4 = foo;
  foo_result = del4(); //here we are calling foo indirectly through the delegate attached to it
}
```

and then, we would have pointers and heap pointers, which would be specified as, i.e.:

f32' f; //raw pointer

f32@ f; //heap pointer
