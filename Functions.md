There are 2 types of functions:

Globals and locals:

· Global:

```
fn foo(){}
```

· Local:

```
class bar
{
  fn foo(){}
}
```

Function arguments:

First, we need to indicate the argument direction. That's, if the data will be treated as input, input & output, or output, then the argument type and name:

```
fn foo(in bool b1, inout bool b2, out bool b3, bool b4) //'in' for input, 'inout' for input and output, 'out' for output, without any of the three, it will be implicitly assumed as input,
{
  b1 = true;
  b2 = true;
  b3 = true;
  b4 = true;
}

main
{
  bool b1 = false, b2 = false, b3 = false, b4 = false;
  foo(b1, b2, b3 // instead of throwing a compile error, the previous value of 'b3' will be ignored and only the default value(always 0) will be passed, in this case, 'b3' in 'foo' will be initialized as 'false'
  , b4);
  //b1 and b4 are still false, and b2 and b3 are true
}
```

Function return type(optional):

That's, as it name indicates, the return type of the function:
```
bool b;

fn foo() bool // the returning type of 'foo' is a 'bool'
{
  return false;
}

main
{
  b = foo();
}
```

There's a little difference between local and global functions, and it's that, local functions requires an instantiation of the type they are defined at:
```
class bar
{
  fn foo(){}
}

main
{
  bar b;
  b.foo();
}
```
