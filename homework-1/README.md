# p1_fall2023

## Write a C program to calculate and print the ranges of data types

* Name the program ranges.c
* Prompt user (first character of 4 integral and 2 floating-point data types)
* After the user enters valid input
  * print min & max values (in decimal) for signed & unsigned integral types
  * print min, max, +0, -0, -INF, +INF, & NaN values for floating-point types
    * print min and max in decimal
    * print +0, -0, -INF, +INF, and NaN in hexadecimal
* Can only include stdio.h; cannot hard code any value or output
* Use a modular approach to your design; your main function should essentially be a loop with calls to a getLine function and then calls to an appropriate function based on the user input (e.g., if user enters "s", call printShortRange function)
* Create prototypes for all your functions except main and place the prototypes above your main function; place the definitions of these functions below your main code
* Properly cite in C comments any online sources you used; explain how you adapted the code to "make it your own"
* Work independently; you may discuss high-level topics such as how to approach accomplishing some particular task, but do not look at anyone's code or share your code with anyone!
* Sample output

  ```
  Enter c|s|i|l|f|d <cntl+D to exit>: f
  The minimum value of float = ________________
  The maximum value of float = 3.4028234664e+38  /* use “%.10e” format specifier */
  The hex representation of -0 in float = 0x________________  /* the underscores are just placeholders */
  The hex representation of +0 in float = 0x________________
  The hex representation of -INF in float = 0x________________
  The hex representation of NaN in float = 0x________________
  Enter c|s|i|l|f|d <cntl+D to exit>: c
  The minimum value of signed char = -128
  …
  The maximum value of unsigned char = _____
  ```