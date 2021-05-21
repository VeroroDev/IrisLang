These are totally separate from raw pointers.

A raw pointer cannot be assigned with a heap pointer.

A heap pointer cannot be assigned with a raw pointer.

A heap pointer only can be null, assigned with 'new' (which simultaneously allocate the requested value on the heap), or assigned by another heap pointer(first it will delete the allocated memory, if non-null, and then get assigned by the other heap pointer value, the other heap pointer value then is modified to null).

A heap pointer will only be assigned by other heap pointer, if the later isn't nullptr, evading the propagation of nullptrs

A heap pointer will be deleted once it's out of scope

An example:
```
f32@ h;// null heap pointer by default
f32@ hh;

fn alloc()
{
  h = new f32(4.1);//if 'h' isn't nullptr, it will delete its own content, and then(and if it's nullptr) gets assigned the heap pointer pointing to the memory address of where that '4.1' were allocated on the heap
}

fn alloc2()
{
  h = hh;//if 'hh' isn't nullptr, 'h' will delete its content(if it isn't nullptr either), and gets assigned by the value of 'hh', and 'hh' is assigned to nullptr
}

fn alloc3()
{
  {
    f32@ hhh = new f32(4.2);
  }// here 'hhh' is out of scope, so its memory will be implicitly deleted
}

fn alloc4()
{
  f32@ hhh = new f32(4.2);
  delete hhh; //you can also explicitly delete the heap pointers, it will simply check if it's nullptr, if it isn't it gets deleted
}
```
