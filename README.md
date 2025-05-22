# Example of how the implementation works:
compiling the main.c example.
Output:
```
╰─ ❯❯ gcc main.c -o a && ./a
this is x: 123
failed, type: Rectangle
false
a // this is the user input given
error message: scanf failed.
had nothing.

╰─ ❯❯ gcc main.c -o a && ./a
this is x: 123
failed, type: Rectangle
false
213123 // this is the user input given
_Ok: stored position.x as: 213123.
had nothing.

```

```c
#include "fumo_lib.h"

Result get_input();

int main() {

    int x = 123;
    PRINTF("this is x: ", x); // printf helpful utility

    Rectangle rect = {.width = 123, .height = 1231};
    Variant var = Variant(rect); // variant takes any registered type

    let inner_value = get_if(Shape, var) {
        // only enters this scope if we held a Shape type
        // the type is checked at compile time and store in inner_value
        inner_value->shape_id = 123123;
    }
    else {
        // default scope for failure
        // inner_value is set to NULL if Shape was not inside the variant.
        printf("failed, type: %s\n", type_name(var));
    }

    // type comparison between any primitive data type or user defined struct
    // and also adds support for variant/result types against any type
    is_same_t((Position) {}, var) ? printf("true\n") : printf("false\n");

    Shape s = {.shape_id = 123123};
    Variant var1 = Variant(s);

    // match case picks case based on the held type of the variant
    // you can only make a case label if the type is registered.
    // failing to do so is a compile time error.
    // all type checking is done at compile time
    match(var) ({
        case(Shape, var) var->shape_id = 213;

        case(Rectangle, rect) {
            // user specifies the name of the variable returned by the match
            // the variable is always a *pointer* to the variable stored in
            // the variant struct
            rect->height = 123; // code will go here since its a Rectangle type
        }
        case(Position, pos) {
            // all variables only exist on each label scope.
            // that means you can only use "pos" inside of this label
            // (to guarantee more type safety)
            pos->x = 123;
            printf("%d sucessfully updated pos.\n", pos->x);
            pos->y = 123;
            printf("%d sucessfully updated pos.\n", pos->y);
        }
        _ {
            printf("unknown type.\n");
            // this is the default case label.
            // triggered if none of the types the user added was valid
        }
    });

    // match also supports Result type
    // result types are deduced at runtime (not proper compile time sadly)
    // if the user doesnt specify the types they gave the Result they returned
    // then the match wont go into _Ok() or _Err(),  but no warning is emitted.
    // (warnings can be added if necessary by changing the implementation).
    match(get_input())({
        _Ok(Position, somepos) printf("_Ok: stored position.x as: %d.\n", somepos->x);
        _Err(char*, errval) {
            // if scanf() fails, we go in here and get our string
            printf("error message: %s", *errval);
        }
    });

    // matches must be scoped with ({}); for them to work
    match(var) ({
        case(int, someint) {(*someint)++;}
            // you can indent as many match statements as you want
            match(var1) ({
                case(char*, str) {
                // continue indenting....
                    printf("had a string %s", *str);
                }
                _ {} // you can do nothing on default
            });

        case(Position**, pos_ptr_ptr) {
            // double pointers are automatically declared for you
            // when you register a user type
            // (more than this needs implementation changes)
            // gets a Position***
            printf("position's x: %d", (*(*pos_ptr_ptr))->x);
        }
        _  printf("had nothing."); 
    });

    return 0;
}

Result get_input() {
    int n = 0;
    
    Position pos = {.x = 213, .y = 21312};

    let result = Ok(&pos); // valid code, stores Position*
    // can take any user type or standard type

    if (scanf("%d", &n)) {
        pos.x = n;
        // Ok type, stores an int
        return Ok(pos);
    }
    // Err type, stores a char*
    return Err("scanf failed.\n");
}
```
Output:
```
false
true
false
width before: 123 
there was a rectangle, width: 213123
type_name: Rectangle

couldn't get shape from variant.
type in variant: Position
```
