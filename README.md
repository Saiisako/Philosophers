# Philosophers

An implementation of the classic **Dining Philosophers** problem in C, using threads and mutexes to explore concurrency, race conditions, and deadlock/starvation avoidance.

## The problem

N philosophers sit around a table with N forks. Each philosopher alternates between thinking, eating (needs both their left and right fork) and sleeping. A philosopher who doesn't eat within `time_to_die` ms starves and the simulation stops. The challenge is to let philosophers eat as much as possible without deadlocking or starving anyone, and without a philosopher ever incorrectly being declared dead.

## Implementation

- One thread per philosopher, one mutex per fork.
- A dedicated monitoring routine tracks each philosopher's last meal time to detect death with millisecond precision — a false positive/negative fails the project.
- Careful ordering of fork acquisition to avoid deadlock, and mutex-protected logging to keep output readable under concurrency.
- Handles the single-philosopher edge case (one fork, can never eat).

## Build & usage

```bash
make
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

## Skills demonstrated

POSIX threads (`pthread`), mutex synchronization, precise timing, and reasoning about concurrent systems under strict correctness constraints.

*42 School — Common Core project.*
