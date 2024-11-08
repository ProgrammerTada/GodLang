```
if(temp = get_some_value() > 6)
{
    // temp is usable here
}
else (temp < 2)
{
    // temp is usable here
}
else
{
    // temp is usable here
}
```
First temp will be initialized with teh return value of `get_some_value()`. Then temp will be used for the comparison and as a scoped variable inside all ifelse-branches.

```
if(val_1~[== compare_to_val_1 || > also_compare_to_val_1])

// is equivalent to:

if(val_1 == compare_to_val_1 || val_1 > also_compare_to_val_1)
```