
Assignment 1. Understanding Data Alignment in C

    Objective: To understand how different data types are aligned in memory and the concept of data alignment.
    Task:
        Write a C program where you declare variables of the following types: int, char, double, and short.
        Use sizeof() to print the size of each data type.
        Print the addresses of each variable using the & operator.
        Observe and compare the addresses of these variables.
    Expected Output: Your program should show that variables are aligned to specific boundaries based on their types.
    Submission:
        Include your C code.
        Write a short explanation of what you observed regarding how variables of different types are aligned in memory.

Assignment 2. Struct Padding

    Objective: To observe how padding is used in struct alignment and how it affects memory layout.
    Task:
        Create a struct in C with the following fields in the given order:
            char a;
            int b;
            double c;
        Use sizeof() to print the size of the struct and print the addresses of each field using the & operator.
        Change the order of the fields (for example, place double first, then int, then char) and observe the size of the struct again.
        Answer the following questions:
            Does changing the order of fields reduce or increase the size of the struct? Why?
            How is memory padding affecting the size of your struct?
    Submission:
        Include your C code.
        Provide screenshots or the output of the program showing the size of the struct and the addresses of each field.
        Write a short explanation of how rearranging fields affects the struct size.

 
Assignment 3. Data Alignment with #pragma pack

    Objective: To learn how #pragma pack changes the alignment of a struct and affects memory usage.
    Task:
        Create a struct with the following fields:
            char a;
            int b;
            double c;
        Without using #pragma pack, print the size of the struct and the addresses of each field.
        Add #pragma pack(1) before the struct definition and print the size and addresses again.
        Compare the two results and explain how #pragma pack affects memory usage.
    Bonus Task:
        Experiment with different packing values (e.g., #pragma pack(2), #pragma pack(4)), and note how the alignment changes.
    Submission:
        Include your C code with and without #pragma pack.
        Provide the output before and after applying #pragma pack.
        Write a short explanation of how packing affects the alignment and size of the struct.
        Example code

        #pragma pack(1)
        struct PackedStruct {
            char a;
            int b;
            double c;
        };
