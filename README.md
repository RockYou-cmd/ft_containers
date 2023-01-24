# ft_containers
In this project, I will implement a few container types of the C++ standard template library.</br>
we'll talk about some essential concepts before diving into the implementation of containers :

## 1 - Exception safety


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

### There are several techniques for implementing exception safety

##### - The RAII idiom: Resource Acquisition Is Initialization idiom is a technique that ensures that resources are properly acquired and released in a program. This is achieved by using constructors and destructors to acquire and release resources.

##### - Avoiding exception in critical section: critical section of a program should be designed in a way that they do not throw any exception. This can be achieved by validating the inputs before entering into critical section or by using exception handling mechanism to handle the exception.

It's important to note that no single technique will completely prevent all exceptions, and a combination of these techniques may be necessary to achieve exception safety in a program.

### Functors  (Function Objects)

In C++, a functor (short for "function object") is a type that can be used as if it were a function. A functor is an object of a class that overloads the function call operator (operator()), allowing the class's objects to be used as if they were functions. This allows for the creation of function-like objects that can store state and other information, and can be passed as arguments to algorithms and other functions that expect function pointers or function-like objects. Functors are often used as arguments to the STL algorithms, such as "sort" and "for_each".

#### Classification of functors

* generator: a functor with no arguments
* unary: a functor that takes one argument
* binary: a functor that takes two arguments
* predicate: Used as a functor that returns a boolean value, Unary predicate, Binary predicate, etc.
* operator: a functor that returns an operation value

## 2 - SFINAE (Substitution Failure Is Not An Error)

 let's first see how the compiler chooses the right function overload to call before we describe SFINAE.</br>
   
 in c++, the compiler goes through a process in order for it to find the right function overload.</br>
 these steps are :
#### name lookup
there are two different ways to resolve the meaning of an identifier (such as a variable or function name) in a program, Unqualified name lookup and qualified name lookup. </br>

Unqualified name lookup, also known as unqualified lookup or ordinary lookup, is the process of resolving the meaning of an identifier without considering any namespace or class scope qualifiers. In C++, unqualified name lookup starts by searching the current scope and any enclosing scopes, from the innermost to the outermost, to find the declaration associated with the identifier. If the identifier is not found in any of the scopes, the compiler will also search through the global namespace.

On the other hand, qualified name lookup, also known as qualified lookup or explicit lookup, is the process of resolving the meaning of an identifier by considering the namespace or class scope qualifiers. In C++, when an identifier is used in a program with a namespace or class scope qualifier, the compiler will only search for the declaration of the identifier within that specific namespace or class.

Unqualified name lookup is the default lookup mechanism in C++, but it can lead to naming conflicts, where multiple declarations of the same identifier exist in different scopes. Qualified name lookup can be used to avoid such conflicts or to access specific identifiers that have the same name but are in different namespaces or classes.

#### ADL (Argument Dependent Lookup)
ADL stands for Argument-Dependent Lookup. It is a C++ feature that allows the compiler to look for functions or operators in the namespaces of the types of the arguments, in addition to the namespaces in the current scope. This can be useful for resolving function or operator overloads, especially when working with templates.</br>

#### template argument deduction
Template argument deduction is a feature of C++ that allows the compiler to deduce the template arguments for a function or class template based on the types of the function arguments or the class constructor arguments.</br>

#### template argument substitution
it is the process that the C++ compiler uses to determine the actual types or values to use for the template arguments when instantiating a template. When a template is called, the compiler compares the template arguments with the template parameters to ensure they match the expected types or values, and then generates a new version of the template with the actual arguments substituted for the parameters.</br>

In other words, TAS is the process of replacing the template parameters by their corresponding arguments, while TAD is the process of determining the arguments for a template by looking at the types of the function or constructor arguments. TAD is used to deduce template arguments from the arguments of a function call, TAS is used to substitute the deduced or explicitly specified template arguments into the template code.</br>

So TAS is a process that happens during the instantiation of a template and TAD is a process that happens during the call of a template function or class.



