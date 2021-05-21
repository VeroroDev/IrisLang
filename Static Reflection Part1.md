The elements on the Iris Programming Language will have a set of predefined properties, owned by the compiler, with the purpose of providing info, that couldn't be explicitly acquired with any other way:

```
module std
{
  class foo{}

  fn bar() foo
  {
    return {};
  }
}

main
{
  print(std.foo.name); //the property name is inhereted and provided by the compiler, it will print the raw name of the class without decorations(such as modules or usings)
  print(std.foo.fullname); //the property fullname will print the full name of the class, with decorations, therefore, it would print something like 'std.foo'
  std.foo f; 
  print(f.type.name); //of course, you could just get the type of an instance and then print its name without decorations
  print(f.name); //... or print the instantiation name without decorations
  f.type ff; //the property type will reflect the type of the instance 'f', therefore, the local variable declaration would look like as 'foo ff;'
  bar.type another_foo; //the property type, on functions, will reflect the returning type
}
```
