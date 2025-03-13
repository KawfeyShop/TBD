# Overview
The goal of this document is to get comfortable with a rough set of coding standards I want everyone to follow. Whenever we develop, I want all sets of code to be similarly readable, so that if we ever need to go back it will be a lot less of a headache.

Need to have a code structure for log management, and ease of readability

## General Tree 
```
TBD_Checker
│   README.md
│
├───build
└───src
    │   main.c
    │   utils.c
    │   utils.h
    │
    └───checks
            common_checks.h
            NTLMv1.c
            rdp.c
            sticky_keys.c
	         ....
```

## General Files
main.c
* starts the program (obvi)
* will run each check function
	* sticky_keys();
	* rdp();
	* NTLMv1();
	* ...
utils.h
* centralized logging
* this could possibly be integrated with a testing framework
	* gtest? maybe?
* composed of general utility functions
* will make error detection easier in the long run
* basic logging functions for the entire tool
* creates/manages the log.txt file
_Examples_
``` c
// Logging functions for commandline view
void log_error(const char *message);
void log_info(const char *message);

// File utility functions
int write_to_log_file(const char *filename, const char *message);
```

## Style and Standards
- Source file extensions will be ".c" and header file extensions will be ".h"
- Line length will not exceed ~85 columns
- Function names and variable names are `foo_bar`
- Global constants are `SOME_FOO_BAR`
- Always use "in-line" braces:
``` C
void good() {

}

void bad() 
{

}
```
