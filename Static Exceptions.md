First, we need to declare an exception. On iris, it's as easy as follow:

```
exception Ex1;
```

Behind the scenes, the compiler would assign a unique identifier to that exception, starting from 1, and incrementing it by 1 once a new exception is declared.

Now, to throw that exception, we would do the following:

```
fn throw_ex() bool
{
  if(whatever)
    throw Ex1; //here, the unique identifier of Ex1, in this case 1, because it's the only exception declared, will be assigned to a register,
                     like 'rax', and it would return the default structure, in this case, by being the return type of bool, would return a false
  return true;
}

main
{
  bool b = throw_ex();
  catch(Ex1) //here, the compiler will just check the register assigned the thrown exception,
                      and compare(in this case rax) with the value of the unique identifier of the exception 'Ex1', which is 1
  {
    print("Exception thrown: " + Ex1.name);
  }
  //if it isn't the case that the register 'rax' is 1, it will check if it isn't 0,
          since 0 isn't assigned to any exception unique identifier and therefore it would mean that no exception was thrown, if it isn't 0,
          it means 'rax' was modified to another exception that wasn't specified at 'catch' and therefore, the program would abort
}
```
