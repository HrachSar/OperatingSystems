1. Basic Thread Creation

    Objective: Familiarize yourself with creating threads.
    Instructions:
        Write a C program that creates three threads.
        Each thread should print a message, including its thread ID, to indicate it is running (e.g., "Thread X is running").
        Ensure the main thread waits for each of the threads to complete using pthread_join.
    Expected Output: Each thread prints a message, and the program exits only after all threads are complete.

 
2. Array Processing with Threads

    Objective: Practice dividing an array processing task among multiple threads.
    Instructions:
        Create an array of integers with a few values.
        Write a function that calculates the sum of part of this array.
        Use two threads: assign each half of the array to a different thread.
        Each thread should calculate the sum of its half and print it.
    Expected Output: Two separate partial sums printed by each thread.

 
3. Printing Numbers with Threads

    Objective: Practice thread creation and task division without synchronization.
    Instructions:
        Write a program that creates three threads.
        Each thread should print numbers from 1 to 5, along with its thread ID.
        Observe that the order of printing may vary between runs, showing the concurrent execution.
    Expected Output: Each thread prints numbers from 1 to 5, but in potentially varying orders.

 
4. Calculating Square of Numbers in Parallel

    Objective: Demonstrate simple tasks that can run in parallel.
    Instructions:
        Create an array of integers (e.g., [1, 2, 3, 4, 5]).
        For each number in the array, create a thread that calculates its square and prints the result (e.g., "Square of 2 is 4").
        Wait for all threads to finish before the main program exits.
    Expected Output: Each thread prints the square of its assigned number.

