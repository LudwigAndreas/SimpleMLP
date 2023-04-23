# libs21

`libs21` is a static library that contains functions for various tasks from school 21.

## Contents
This library contains the following functions:

* `split`: Split string using some delimiter
* `to_lower`: Converts string to lowercase
* `to_upper`: Converts string to uppercase
* `load_bmp`: Read bmp file into unsigned char array
* `bmp_data_to_grayscale`: Converts bmp data into grayscale

## Requirements
To use this library, you'll need the following:

A clang++ that supports C++17 or later

## Building

To build the library, simply run `make` in the project directory. This will compile the library into a static archive file named `libs21.a`. 


## Using

To use the library in your own project, you can include the header files for the functions you need and link against the `libs21.a` file. For example, if you wanted to use the `foo` function from the library in your own program:

```c
#include <stdio.h>
#include "libs21.h"

int main() {
    printf("%s\n", s21::to_upper("hello world!"));
    return 0;
}
```
Then you can compile your program with:
```bash
gcc -o myprogram myprogram.c -I/path/to/libs21/include -L/path/to/libs21
```
Make sure to replace /path/to/libs21 with the actual path to your libs21 project directory.

## Contributing
If you would like to contribute to libs21, feel free to submit a pull request with your changes. Make sure to write tests for any new functionality you add and update the documentation as necessary.

## License

`libs21` is released under the MIT License. See LICENSE for details.
