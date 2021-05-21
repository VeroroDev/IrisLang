array - a fixed-size set of elements of a static type

Array example:

```
bool[4] b = {false, false, false, false};//bounded array

bool[] b = {false, false};//unbounded array, size assumed to be the number of elements on its initialization
```

struct - an aggregate type that only can pack data, but it can't implement local functions:
```
struct vec2
{
  f32 x, y;
}
```

class - an aggregate type that can define data(acting as an struct) but also implement local functions as well as operators:

```
class vec2impl
{
  operator +(in vec2 a, in vec2 b) vec2
  {
    return {a.x + b.x, a.y + b.y};
  }
}

class vec3
{
  f32 x, y, z;

  operator +(in vec2 a) vec3
  {
    return {x + a.x, y + a.y, z};
  }
}
```
