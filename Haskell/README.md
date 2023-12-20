## Pushswap Checker in Haskell

![Illustration](haskell.jpg)

### Project Description:

The main objective is to create a program, `pushswap_checker`, written in Haskell, which can validate if a given sequence of `push_swap` operations successfully sorts a list of integers.

### Invocation:

The `pushswap_checker` program can be invoked from the command line. It expects a list of signed integers as arguments and reads a sequence of operations from the standard input.

#### Expected Output:

- If the sorted list is obtained at the end of operations and list `l_b` is empty: `OK`
- If the list is not sorted or list `l_b` is not empty: `KO`
- Additional information can be displayed in case of a negative result.

### Compilation:

The program is compiled using a Makefile, which includes rules for compiling, recompiling, cleaning, and removing object files.

### Operations:

The following operations are supported:

- `sa`, `sb`, `sc`: Swap operations
- `pa`, `pb`: Push operations
- `ra`, `rb`, `rr`: Rotate operations
- `rra`, `rrb`, `rrr`: Reverse rotate operations

### Examples:

- Valid Input:
  ```
  echo "sa pb pb pb sa pa pa pa" | ./pushswap_checker 2 1 3 6 5 8
  OK
  ```

- Invalid Input:
  ```
  echo "sa pb pb pb" | ./pushswap_checker 2 1 3 6 5 8
  KO: ([6,5,8],[3,2,1])
  ```

### Return Codes:

- `0`: Successful execution
- `84`: Inadequate input
