The syntax to create an event would be like ``event MyEvent Trigger
{
the code...
}``

where 'Trigger' could be a condition, i.e, lets say we wanna execute this event when a global variable 'x' is 5, then:

```event MyEvent x == 5
{
...
}
```

The magic would happen at an assembly level, where the compiler would insert a 'cmp' instruction after each time 'x' is modified, so it would indirectly check if x is 5 once it's modified, and execute the code inside that if it happens to be.

The usage cases would be pretty wide, but one could be a keyboard event system, like:

```
event EnterPressed key == enter_constant
{
  print("Enter key was pressed...");
}

u32 key;

fn update_key()
{
  key = GetSystemPressedKey();
  //here, the compiler would detect that key's been modified, so it would insert the 'cmp' instruction to check if 'key == enter_constant'
}
```
