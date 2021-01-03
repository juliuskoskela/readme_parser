# Parse readme

Parse a readme file from a function file. The function file must have the
42 header and the first function prototype starts at line 15. Static functions
are ignored. At the end of the file it feals the fucntion name and
description from the dot block. Dot block is as follows:


```c
/*
**  ----------------------------------------------------------------------------
**
**	Function name
**
**	Function description...
**
**  ----------------------------------------------------------------------------
*/
```
