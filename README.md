This project has been created as part of the 42 curriculum by mmustone

# Description

The Philosophers project is a classic concurrency problem that teaches the fundamentals of multi-threaded programming and synchronization. In this project, you will implement a solution to the "Dining Philosophers Problem," a famous illustration of deadlock and resource contention in concurrent systems.

## Problem Overview

You have a number of philosophers sitting around a circular table with a fork between each pair of philosophers. Each philosopher alternates between thinking, eating, and sleeping. To eat, a philosopher must acquire both the fork on their left and the fork on their right. If a philosopher doesn't eat within a specified time, they die.

## Key Concepts

- **Multithreading**: Each philosopher is represented by a separate thread
- **Mutexes**: Forks are protected by mutexes to ensure exclusive access
- **Deadlock Prevention**: Implement strategies to prevent philosophers from deadlocking while waiting for forks
- **Race Conditions**: Handle proper synchronization to avoid data races
- **State Monitoring**: A monitoring thread checks if any philosopher has died due to starvation

# Instructions
./philo <num_of_philo> <time_to_die> <time_to_eat> <time_to_sleep>

- `num_of_philo`: Number of philosophers and forks
- `time_to_die`: Time in milliseconds before a philosopher dies if they haven't eaten
- `time_to_eat`: Time in milliseconds it takes for a philosopher to eat
- `time_to_sleep`: Time in milliseconds a philosopher spends sleeping

## Example

```bash
./philo 5 800 200 200
```

This creates 5 philosophers with death time of 800ms, eating time of 200ms, and sleep time of 200ms.

# Resources

- **POSIX Threads (pthreads)**: Official POSIX thread documentation
- **Mutexes**: Thread synchronization primitive for protecting shared resources
- **The Dining Philosophers Problem**: A classic computer science problem illustrating deadlock and resource contention
- **Concurrency Issues**: Understanding race conditions, deadlocks, and starvation

## Recommended Reading

- Man pages: `man pthread`, `man pthread_mutex_lock`, `man pthread_create`
- "The Little Book of Semaphores" by Allen B. Downey
- Wikipedia: Dining Philosophers Problem

# 42_Philosophers
In this project, you will learn the basics of threading a process. You will learn how to create threads and explore the use of mutexes.
