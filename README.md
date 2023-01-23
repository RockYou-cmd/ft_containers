# ft_containers
In this project, I will implement a few container types of the C++ standard template library.</br>
we'll talk about some essential concepts before diving into the implementation of containers :

### Exception safety


I should first introduce to you an important concept which is stack unwinding </br>

#### stack unwinding
Stack unwinding is the process of undoing the actions of a function call, including restoring the previous stack frame and returning control to the calling function. This is typically done when an exception is thrown, as part of the process of propagating the exception through the call stack to a point where it can be handled. The process of stack unwinding is also used during the normal return from a function call, in order to deallocate the memory used by the function's stack frame and restore the previous stack frame.

Exception safety is a programming concept that refers to the ability of a program to handle and recover from exceptions (unexpected errors or conditions) without causing memory leaks, data corruption, or other side effects. Exception safety is important because when an exception occurs, it can disrupt the normal flow of control in a program, and if the program is not prepared to handle the exception, it can lead to unpredictable and undesirable consequences.

There are three main levels of exception safety:

1 . Basic exception safety: This level ensures that the program will not crash or leak memory if an exception is thrown. However, the program's state may be left in an indeterminate state after the exception is handled.

2 . Strong exception safety: This level guarantees that the program's state will be left in a consistent state, even if an exception is thrown. This means that all memory and resources used by the program will be properly cleaned up, and the program will not crash or leak memory.

3 . No-throw exception safety: This level ensures that the program will not throw any exceptions, even in the event of an error. This is often achieved by using error codes or status flags instead of exceptions.

Achieving exception safety can require a lot of effort and attention to detail, but it is an important aspect of designing robust and reliable software.

#### relation between exception safety and stack unwinding 

Exception safety refers to the ability of a program to maintain a consistent state in the event of an exception being thrown. Stack unwinding is the process of unwinding the call stack when an exception is thrown in order to find the appropriate exception handler to handle the exception. The two concepts are related in that stack unwinding is a necessary step in implementing exception safety, as it allows the program to transfer control to the appropriate exception handler when an exception is thrown.

