# OS_assignment
## Update
The code defines functions related to process scheduling in an operating system.

The `init_scheduler` function initializes the ready queue, run queue and queue lock.

The `queue_empty` function checks if both the ready queue and run queue are empty. If the `MLQ_SCHED` macro is defined, it also checks if all the priority queues in the `mlq_ready_queue` array are empty.

The `get_proc`, `put_proc` and `add_proc` functions are used to manipulate the ready queue and run queue. When the `MLQ_SCHED` macro is defined, these functions call the corresponding `get_mlq_proc`, `put_mlq_proc` and `add_mlq_proc` functions instead.

The `get_mlq_proc` function returns the highest priority process from the priority queues in the `mlq_ready_queue` array.

The `put_mlq_proc` and `add_mlq_proc` functions add a process to the appropriate priority queue in the `mlq_ready_queue` array.

All of these functions use a mutex lock to ensure that only one thread can access the queues at a time, avoiding race conditions.
