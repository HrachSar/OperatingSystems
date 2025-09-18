Objective:

    Understand how the C compilation process works, especially the different compilation units (source files, object files, and executables).
    Learn how to use tools like nm, objdump, and readelf to examine the symbols, sections, and structure of compiled C programs.

Assignment Tasks:

    Write a simple multi-file C Program:
        Create three files:
            main.c: Contains the main function and a call to the square function from math_utls.
            math_utils.c: Implements a utility function that returns the square of an integer.
            math_utils.h: The header file with the function declaration for the utility function.

    Compile the program separately:
        Compile the program into object files first (without linking).
            gcc -c main.c
            gcc -c math_utils.c
        Link the object files into an executable.
            gcc main.o math_utils.o -o square_prog
    Use nm to examine the Object and Executable Files:
        Use nm on both object files (main.o and math_utils.o) to list the symbols defined and referenced in them.
            nm main.o
            nm math_utils.o
        Use nm on the executable (square_prog) to see the final list of symbols.
            nm square_prog
    Use objdump to view Assembly code:
        Use objdump to disassemble the object files and the executable.
            objdump -d main.o
            objdump -d math_utils.o
            objdump -d square_prog
        Analyze the assembly output and describe the differences between the object files and the final executable.
    Use readelf to examine the ELF structure:
        Use readelf to explore the ELF headers of the object files and the executable.
            readelf -h main.o
            readelf -h math_utils.o
            readelf -h square_prog
        Inspect the section headers using the -S option in readelf and describe the different sections present.
            readelf -S main.o
            readelf -S math_utils.o
            readelf -S square_prog
    Compare the outputs:
        Compare the outputs of nm, objdump, and readelf across the object files and the final executable.
        Write a report summarizing your findings, including:
            What symbols are defined in each file?
            How the sections of the object files differ from the final executable?
            The role of the linking process in combining the object files.

Submission Requirements:

    Do all the tasks on our server and keep source, object, and executable files there. This is a mandatory step! I'll also check the history of your commands on the server, so please do all the activities there.
    Push the source code files (main.c, math_utils.c, math_utils.h) to github.
    Collect the terminal outputs of nm, objdump, and readelf commands for the object files and the executable and include them in the report.
    Submit a report summarizing your analysis and github repo link.

