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

#### overload resolution
Overload resolution is a process that the C++ compiler uses to determine which version of a function or operator to call when there are multiple versions with the same name but different parameters. The compiler compares the types of the arguments with the parameter types of each version and selects the one that is the best match. If there are multiple versions that are equally good matches, the compiler will generate an error. This feature allows you to create multiple versions of a function or operator with different behavior based on the types of the arguments.

###### now the SFINAE is a technique used in C++ template programming to avoid compilation errors when the compiler tries to substitute a template parameter and the substitution results in an invalid or ill-formed expression. Instead of generating an error, SFINAE causes the compiler to simply ignore the invalid substitution and continue with the next one. This allows for more flexibility in template programming and can be used to implement concepts like concept checking and tag dispatching.

Here's a basic example of SFINAE in C++:


     template <typename T>
     void foo(T x) {
         static_assert(std::is_integral<T>::value, "T must be an integral type");
         // ...
     }

     int main() {
         foo(5); // OK
         foo(3.14); // Compilation error: T must be an integral type
         return 0;
     }
In this example, we have a function template foo that takes a single argument of any type T. Inside the function, we use the static_assert function to check if T is an integral type (i.e. an integer type). If the check fails, the static_assert will generate a compile-time error and the program will not be able to be compiled.

In the main function, we call foo with an argument of type int, which is an integral type, so the function is instantiated successfully and the program compiles and runs without errors. But if we call the function with a non-integral type like double, the static_assert check will fail and the program will not be able to be compiled.

This is a basic example of how SFINAE can be used to check the types of template arguments at compile-time and prevent compilation errors.

## 3 - Type Traits / Tag dispatching

### -Type Traits
Type traits are a feature of the C++ programming language that provide a way to determine properties of a type at compile-time. They are typically implemented as template classes or structs that can be specialized for specific types, and provide a way to query information about a type, such as whether it is a pointer, a reference, or a fundamental type, or whether it is const-qualified or has a specific member function. Examples of type traits include `std::is_pointer`, `std::is_const`, and `std::is_class`. Type traits are typically used in template metaprogramming to write generic code that can work with a wide range of types.</br>
For example, given a generic type T — it could be int, bool, std::vector, or whatever you want — with type traits you can ask the compiler some questions: is it an integer? Is it a function? Is it a pointer? Or maybe a class? Does it have a destructor? Can you copy it? Will it throw exceptions? ... and so on. This is extremely useful in conditional compilation, where you instruct the compiler to pick the right path according to the type in input. We will see an example shortly.

Here is an example of how you might use std::is_pointer to write a generic function that prints the value of an object only if it's a pointer:
```template <typename T>
void print_if_pointer(T &obj)
{
    if constexpr (std::is_pointer<T>::value)
    {
        std::cout << "The value of the pointer is: " << *obj << std::endl;
    }
    else
    {
        std::cout << "This is not a pointer." << std::endl;
    }
}
```
In this example, the if `constexpr statement` is used to conditionally enable or disable the code inside the if block based on whether `T` is a pointer or not. The `std::is_pointer<T>::value` expression returns true if `T` is a pointer, and false otherwise.

This is a simple example, but type traits can be used to do much more complex things like creating complex type manipulations, template metaprogramming, and generic programming.
 
 ### - Tag Dispatching :
 Tag Dispatching is a technique in C++ for selecting the correct function overload or implementation of a function template based on the type of its arguments. It is typically used as a more efficient alternative to virtual function calls and type-based dispatching, and can be used to implement various design patterns such as the Visitor and Double Dispatch patterns. The technique involves creating small, empty structs called "tags" that are used to distinguish between different types, and then using template specialization to select the correct function implementation based on the presence or absence of a particular tag.
`you may wonder what is the deference between tag dispatching and overload resolution ?`</br>
In short, name overload resolution uses the types of the arguments to select the correct function, while tag dispatching uses the types of the arguments to select the correct implementation of a function template.</br>
###### Name Overload Resolution:</br>
Consider the example of a simple function named "print" that takes an integer or a floating-point number as an argument and prints it to the screen.
```void print(int x) {
    std::cout << x << std::endl;
}
void print(float x) {
    std::cout << x << std::endl;
}
```
When we call the function with different types of arguments, the compiler will automatically select the correct version of the function to call based on the type of the argument. For example, if we call "print(5)" the compiler will call the first function void print(int x) and if we call "print(5.0f)" the compiler will call the second function void print(float x)
###### Tag Dispatching:
```struct float_tag {};
struct int_tag {};

template <typename T>
void print(T x, float_tag) {
    std::cout << x << std::endl;
}
template <typename T>
void print(T x, int_tag) {
    std::cout << x << std::endl;
}
template <typename T>
void print(T x) {
    print(x, typename std::conditional<std::is_floating_point<T>::value, float_tag, int_tag>::type{});
}
```
In this example, the print function is a function template that takes a single argument of any type. The function template has two specializations. One for float_tag and the other for int_tag.
When we call the function with different types of arguments, the compiler will automatically select the correct version of the function to call based on the type of the argument. For example, if we call "print(5)" the compiler will call the void print(T x, int_tag) and if we call "print(5.0f)" the compiler will call the void print(T x, float_tag)

`std::conditional` is a template class in the C++ Standard Template Library (STL) that allows for conditional compilation of types. It is used to select one type or another based on a Boolean value. The `std::conditional` template takes two template arguments, `T` and `F`, and a Boolean value `B`. If `B` is true, `std::conditional` will evaluate to `T`, otherwise it will evaluate to `F`.

It is typically used in template metaprogramming, a technique in which templates are used to generate code at compile-time rather than runtime.

Here is an example of how you would use std::conditional to understand the code above:
```template<bool B, typename T, typename F>
using conditional_t = std::conditional<B, T, F>::type;

int main() {
  conditional_t<true, int, char> a = 5;
  conditional_t<false, int, char> b = 'c';
  std::cout << a << " " << b << std::endl;
}
```
As you can see, the main difference is that in Name overload resolution we use different functions with the same name, while in Tag Dispatching we use different specializations of the same function template.


