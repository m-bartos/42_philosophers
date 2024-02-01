# 42_philosophers
The goal of this project is to explore the basics of threading a process and try to solve the [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

## Project description
The key points to understand the assignment:
* The scenario involves multiple philosophers seated at a round table.
* A large bowl of spaghetti is placed at the centre of the table.
* Philosophers engage in three activities: eating, thinking, and sleeping.
  - While eating, they do not think or sleep.
  - While thinking, they do not eat or sleep.
  - While sleeping, they do not eat or think.
* Forks are available on the table, with the same number as philosophers.
* Due to inconvenience, a philosopher takes both their right and left forks to eat.
* After finishing eating, philosophers place their forks back on the table and start sleeping.
* Upon waking up, they resume thinking.
* The simulation stops when a philosopher dies of starvation.

## Requirements
* Every philosopher must eat and should never starve.
* Philosophers do not communicate with each other.
* Philosophers are unaware if another philosopher is on the verge of dying.
* There is one fork between each pair of philosophers. Therefore, if there are several
philosophers, each philosopher has a fork on their left side and a fork on their right
side. If there is only one philosopher, there should be only one fork on the table.
* Each philosopher should be a thread.
* To prevent philosophers from duplicating forks, you should protect the fork's state
with a mutex for each of them.

## Implementation
* Each philosopher is a thread
* There is another thread for watching if any philosopher died or all philosophers have eaten at least the number of times they should
* Different struct composition is implemented for each type of thread (for more info see [philo.h](src/philo.h))

## How to use
* First, you need to make: `Make`
* Run the program with the command (the last parameter is optional):
```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]`

example:
./philo 5 800 200 200 7
```
* Any state change of a philosopher is shown on the terminal in a way:
```
timestamp  | philo  |         action         |
  in_ms    | number |                        |
----------------------------------------------
0              0     has taken a left fork
0              0     has taken a right fork
0              0     is eating
0              2     has taken a left fork
0              2     has taken a right fork
0              2     is eating
200            2     is sleeping
200            3     has taken a right fork
200            3     has taken a left fork
200            3     is eating
200            4     has taken a left fork
200            1     has taken a right fork
200            1     has taken a left fork
200            1     is eating
200            0     is sleeping
...
```

## Examples
You can try different inputs:
* `./philo 1 800 200 200` The philosopher should not eat and should die.
* `./philo 5 800 200 200` No philosopher should die.
* `./philo 5 800 200 200 7` No philosopher should die and the simulation should stop when every philosopher has eaten at least 7 times.
* `./philo 4 410 200 200` No philosopher should die.
* `./philo 4 310 200 100` One philosopher should die.

## Checking threads data races, deadlocks, etc.
Different checkers can be used. Such as:
* Compile with `-fsanitize=thread` flag - see different CFLAGS in [Makefile](Makefile)
* Or try helgrind tool (compile without `-fsanitize=thread` flag!):
```
valgrind --tool=helgrind --fairsched=yes
```
* Or drd tool (compile without `-fsanitize=thread` flag!):
```
valgrind --tool=drd --fairsched=yes
```

## What I learned during this project
* Understanding the mechanics of threads in C (running parallel, shared memory, data races, deadlocks, mutexes, etc.)
* Using new thread functions such as: `pthread_create`, `pthread_join`, `pthread_mutex_init`, `pthread_mutex_lock`, `pthread_mutex_unlock`, and `pthread_mutex_destroy`.
* Enhancing proficiency with structs, struct pointers and pointers to structs inside other structs

## Thanks and kudos
* Acknowledgements to CodeVault's YouTube playlist on [Unix Threads in C](https://www.youtube.com/playlist?list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2) for the valuable insights.
* Appreciate the project discussions with my fellow 42Prague students.
