# OperatingSystems

## Pointers
# Assignment 1: Basics of Pointers

     Objective: Understand the basics of pointers, the address-of operator, and dereferencing.
    Task:
        Declare an integer variable and initialize it with a value.
        Declare a pointer variable that points to the integer.
        Print the address of the integer variable using both the variable and the pointer.
        Modify the value of the integer using the pointer and print the new value.

# Assignment 2: Pointer Arithmetic

    Objective: Learn how pointer arithmetic works.
    Task:
        Declare an array of integers and initialize it with 5 values.
        Use a pointer to traverse the array and print each element.
        Modify the values of the array using pointer arithmetic.
        Print the modified array using both the pointer and the array name.

# Assignment 3: Pointers and Functions

    Objective: Learn how to pass pointers to functions.
    Task:
        Write a function swap(int *a, int *b) that swaps two integer values using pointers.
        In the main() function, call swap() and pass the addresses of two integers.
        Print the values of the integers before and after the swap.

# Assignment 4: Pointers to Pointers

    Objective: Work with double pointers.
    Task:
        Declare an integer variable and a pointer to that variable.
        Declare a pointer to the pointer and initialize it.
        Print the value of the integer using both the pointer and the double-pointer.

# Assignment 5: Strings and Character Pointers

    Objective: Work with pointers to characters and string manipulation.
    Task:
        Declare a string as a character array: char str[] = "Hello";.
        Declare a pointer to the first character of the string.
        Print the string using the pointer and a loop (without using str[i]).
        Count the number of characters in the string using pointer arithmetic.

## Fork and Exec 

# Assignment 1: Simple Fork and Exec

Objective: Understand the creation of a child process using fork and how to replace it with a new program using execl.

    Write a program that:
        Uses fork to create a child process.
        In the child process, use execl to run the ls command to list the contents of the current directory.
        The parent process should print "Parent process done" after the child process is created.

Expected Output: The directory listing should be printed, followed by the parent's message.

# Assignment 2: Multiple Forks and Execs

Objective: Work with multiple child processes created using fork and run different commands using execl.

    Write a program that:
        Creates two child processes using fork.
        The first child process should use execl to run the ls command.
        The second child process should use execl to run the date command.
        The parent process should print "Parent process done" after creating both child processes.

Expected Output: The output of the ls command followed by the output of the date command, and finally the parent's message.
 
# Assignment 3: Fork and Exec with Arguments

Objective: Understand how to pass arguments to programs executed with execl.

    Write a program that:
        Uses fork to create a child process.
        The child process should use execl to run the echo command with an argument (e.g., "Hello from the child process").
        The parent process should print "Parent process done" after the child process is created.

    Expected Output: The message from the echo command followed by the parent's message.

# Assignment 4: Fork and Exec with Command-Line Arguments

Objective: Use fork and execl to run a command with multiple arguments.

    Prepare a test.txt file with some text.
    Write a program that:
        Uses fork to create a child process.
        The child process should use execl to run the grep command to search for a specific word (e.g., "main") in a text file (e.g., test.txt).
        The parent process should print "Parent process completed".

Expected Output: The lines in the file test.txt that contain the word "main" followed by "Parent process completed".
