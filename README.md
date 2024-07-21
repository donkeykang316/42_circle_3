## Pipex
Pipex is a project focused on process and pipe management in Unix-like operating systems. The goal is to reproduce the behavior of shell piping by creating a program that takes file and command arguments and replicates the behavior of the shell's pipe (|) operator.

Students are required to:

Create child processes using fork().
Use pipe() to establish communication between these processes.
Redirect input and output with dup2() to achieve the desired piping effect.
This project helps students understand inter-process communication, file descriptors, and the mechanisms behind shell operations.

## Philosopher
Philosopher (often referred to as the Dining Philosophers Problem) is a classic synchronization problem in computer science. This project involves simulating a scenario where multiple philosophers sit at a table and alternate between eating, thinking, and sleeping. Each philosopher needs two forks to eat, but there are only as many forks as there are philosophers, leading to potential conflicts.

The primary goals are to:

Implement thread management using POSIX threads (pthread).
Synchronize access to shared resources using mutexes or semaphores to prevent deadlock and ensure that all philosophers can eventually eat.
This project is designed to teach students about concurrency, synchronization, and how to handle race conditions in a multi-threaded environment.

Both pipex and philosopher provide valuable lessons in process management and synchronization, which are crucial for developing robust and efficient software.
