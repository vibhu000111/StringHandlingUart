# StringHandlingUart
Task
In this exercise the task is to implement a program for the ATmega so that it
accepts a string from e.g. your PC via UART. The string is stored in a buffer. If
a end-of-string terminator is received such as a carriage return (CR, '\r' in C)
or line feed (LF, '\n' in C) the string is returned to the PC, but in reverse
. Also use only ISRs to implement this functionality, hence
polling of registers is not allowed.
