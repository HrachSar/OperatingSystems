

Task 1: Copy file contents

Objective: Copy the full contents of one file to another using read/write loops.

Requirements:

    At the start, prompt the user (via standard input) to type the source file path, then the destination file path
    Open the source for reading (O_RDONLY). Open/create the destination with O_WRONLY|O_CREAT|O_TRUNC and mode 0644.
    Repeatedly read from source and write to destination until EOF (read returns 0).
    Count and print the total number of bytes copied.

    Print an error if any system call fails.

Task 2: File truncation

Objective: Demonstrate writing, truncating, and verifying file size/content.

Requirements:

    Use the fixed filename “data.txt”.
    Open/create it with O_WRONLY|O_CREAT|O_TRUNC (0644) and write the ASCII text: ABCDEFGHIJKLMNOPQRSTUVWXYZ (26 bytes). Close.
    Reopen with O_RDWR. Print the current size (by lseek(fd, 0, SEEK_END)).
    Truncate the file to the first 10 bytes using ftruncate.
    Print the new size (again via lseek).
    Rewind (lseek to 0) and read the remaining content, then print it to stdout.

Task 3: Reverse file reader

Objective: Print a file’s bytes in reverse order using lseek to move backward.

Requirements:

    Prompt the user to enter a path to an existing text file.
    Open it read-only. Determine file size with lseek(fd, 0, SEEK_END).
    Starting from the last byte, repeatedly: lseek to the target position, read 1 byte, write that byte to standard output.
    After finishing, write a newline.

    Handle empty files (print just a newline).

Task 4: Append log entries with PID and final offset

Objective: Append a user-typed line to a log file in O_APPEND mode and show the final file offset.

Requirements:

    Fixed filename: “log.txt”.
    Open with O_WRONLY|O_CREAT|O_APPEND (0644).
    Read up to one line from standard input using read(0, …). Do not use fgets/gets.
    Prepend “PID=<pid>: ” to the line (getpid()) and write the result followed by a newline if not present.

    After writing, obtain and print the new file position by calling lseek(fd, 0, SEEK_CUR). Explain in a comment why SEEK_CUR still returns a growing offset even with O_APPEND.

Task 5: Sparse file creator

Objective: Create a sparse file by seeking beyond the end and writing at a far offset.

    Requirements:
    Fixed filename: “sparse.bin”.
    Open/create with O_WRONLY|O_CREAT|O_TRUNC (0644).
    Write the bytes “START”.
    Use lseek to skip forward by 1 MiB from the current position (1024*1024). Do not write zeros manually.
    Write the bytes “END”. Close the file.
    Reopen read-only, seek to end, and print the apparent file size (should be >= 1,048,581 bytes).

    Add a code comment explaining why disk usage (du) is much smaller than the apparent size.

Task 6: In-place overwrite using lseek

Objective: Write numbers 1..10 as decimal text (one per line), then overwrite the 4th number with 100 using lseek.

Requirements:

    Fixed filename: “numbers.txt”.
    Create/truncate and write the lines: “1\n” through “10\n”. Close.
    Reopen with O_RDWR. You must compute the byte offset of the start of line 4 by scanning the file (read and count newlines), then use lseek to position there.
    Overwrite the 4th line’s number with “100” and ensure the line still ends with ‘\n’. If the new text length differs (e.g., “4\n” → “100\n”), you must shift the subsequent content correctly. Implement either:
    a) Read the remainder into memory, lseek back, write “100\n”, then write the remainder; or
    b) Create a temporary file and reconstruct.

    Print the final file content to stdout at the end for verification.

Task 7: Byte-wise file comparator

Objective: Compare two files and report the first differing byte index.

Requirements:

    Prompt the user for the first file path, then the second file path.
    Open both read-only.
    Read both in fixed-size chunks and compare byte-by-byte.
    If a difference is found, print: “Files differ at byte N” (0-based index) and exit with non-zero code.
    If one file ends earlier but all preceding bytes matched, report the first differing byte as the end position of the shorter file.

    If no difference is found and sizes are equal, print: “Files are identical”.


