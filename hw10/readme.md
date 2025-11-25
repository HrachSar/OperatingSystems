Problem 1 – Broken Counter (Race, Mutex, Spinlock)

Write a C program using pthreads that:

    Has a global variable: long long counter = 0;

    Creates N threads (e.g. 4). Each thread increments counter exactly M times (e.g. 1,000,000).

    Implement three versions (can be three executables or one program with a mode argument):

        (A) No synchronization: threads do counter++; directly.

        (B) With mutex: protect counter++ using pthread_mutex_t.

        (C) With spinlock: protect counter++ using pthread_spinlock_t.

    After joining all threads, print:

        Expected value N * M.

        Actual value of counter.

Short answer (2–3 sentences):
Explain why version (A) may give a wrong result and why (B) and (C) fix the problem.

Problem 2 – Bank Account (Mutex vs Spinlock, Short vs Long CS)

Write a C program using pthreads that simulates a bank account:

    Global variable: long long balance = 0;

    Create several deposit threads and several withdraw threads:

        Deposit threads repeatedly do balance++;.

        Withdraw threads repeatedly do balance--;.

    Protect balance using:

        either a mutex (pthread_mutex_t),

        or a spinlock (pthread_spinlock_t).

    Choose the mode via a macro or command-line argument (e.g. ./bank mutex / ./bank spin).

    Run in two variants (you can control this also via argument or macro):

        Short critical section: only balance++ / balance-- inside the lock.

        Long critical section: call usleep(100); inside the locked region.

    For each of the 4 cases (mutex+short, spin+short, mutex+long, spin+long):

        Print the final balance (it should be 0).

        Measure runtime approximately using time.

Short answer (3–4 sentences):
Compare mutex vs spinlock in short and long critical sections. When is spinning worse and why?

Problem 3 – Bounded Buffer (Producer–Consumer with Semaphores + Mutex)

Write a C program using pthreads and POSIX semaphores that implements producer–consumer:

    Use a fixed-size integer buffer: 

#define BUFFER_SIZE 8
int buffer[BUFFER_SIZE];
int in_pos = 0;
int out_pos = 0;

    Create P producer threads and C consumer threads.

    Use:

        sem_t empty_slots; – initialized to BUFFER_SIZE.

        sem_t full_slots; – initialized to 0.

        pthread_mutex_t buffer_mutex; – protects buffer, in_pos, and out_pos.

    Producers:

        Wait on empty_slots (sem_wait).

        Lock buffer_mutex.

        Write an integer into buffer[in_pos], advance in_pos circularly.

        Unlock buffer_mutex.

        Post full_slots (sem_post).

    Consumers:

        Wait on full_slots.

        Lock buffer_mutex.

        Read an integer from buffer[out_pos], advance out_pos circularly.

        Unlock buffer_mutex.

        Post empty_slots.

    Stop the program when a fixed total number of items (e.g. P * K) has been produced and consumed.

Short answer (2–3 sentences):
Explain why the mutex is still needed even though you use semaphores.

Problem 4 – Ordered Printing A → B → C (Semaphores)

Write a C program using pthreads and semaphores that:

    Creates 3 threads: thread_A, thread_B, thread_C.

    Each thread runs a loop from i = 0 to N - 1 and prints, for example:

        Thread A: A i

        Thread B: B i

        Thread C: C i

    The output must always follow this order: A 0 B 0 C 0 A 1 B 1 C 1 ...

    Use only semaphores to enforce ordering (no busy-wait and no sleep() for ordering):

        Example: sem_t semA, semB, semC;

        Initialize so that only A can run first.

        Each thread waits on its own semaphore and posts the next thread’s semaphore.

You may use a mutex only to protect printf if you want cleaner output, but not for ordering.

Short answer (1–2 sentences):
Why is using only sleep() not a reliable way to enforce this strict order between threads?

Problem 5 – Limited Resources: Printer Pool (Counting Semaphore)

Write a C program using pthreads and semaphores that simulates a pool of printers:

    There are K identical printers (e.g. K = 3).

    Create N threads (print jobs).

    Use a counting semaphore:  sem_t printers; // init to K

    Each print job thread:

        sem_wait(&printers); before “using” a printer.

        Prints a message like “Thread X is printing…”, then usleep(...) to simulate work.

        sem_post(&printers); when done.

    Show in the log that at most K threads are in the “printing” section at the same time (you can maintain a shared counter protected by a mutex to check this).

Short answer (1–2 sentences):
What happens if you initialize the semaphore to 1? What if you initialize it to a too large value?
