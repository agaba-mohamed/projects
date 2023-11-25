# MinilibC


## Project Overview

In the fascinating realm of x86-64 Assembly, we delve into the creation of MinilibC. The mission: craft a dynamic ELF library that serves as a selective replacement for the standard C library found in everyday systems.

## Project Objective

The goal is to implement essential C library functions, providing an alternative through a dynamic library using weak binding concepts. LD_PRELOAD will be employed to enable this functionality.


## Implemented Functions

Your MinilibC journey involves the implementation of core C library functions. Refer to the official man pages for precise behavior specifications:

- `strlen`
- `strchr`
- `memset`
- `memcpy`
- `strcmp`
- `memmove`
- `strncmp`
- `strcasecmp`
- `rindex`
- `strstr`
- `strpbrk`
- `strcspn`
