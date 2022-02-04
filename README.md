# RTOS_proj
Projects using FreeRtos on ESP32 platform
## 1.cdac
simple hello-cdac program on ESP32 board
## 2.task_p
creating two tasks: Task_1 & Task_2 with functionality Increment and Decrement respectively and monitoring task prority
task_1: high priority , task_2 :low priority
## 3.task_delay
A simple delay program having two tasks of same priority with delay functionality
Observations were made that both tasks follows "RoundRobin algo" to execute.
RTOS follows ==>> "RoundRobin Scheduling"
Also refer: task_delay _P2..
## 4.task_delay_p2
Second example of simple delay program having two tasks with DIFFERENT priorities both following
delay functions. Task_1_LED => priority 20 && Task_2_ALARM => priority 10
Observations made: Task_1_LED(1000ms=delay) executes first having high priority and goes to wait state when delay given..meanwhile Task_2_ALARM(500ms=delay) if Ready executes and goes to wait state when delay arrives
NOTE: while Task_2_ALARM executes if Task_1_LED changed into READY state it starts executing 
RTOS follows ==>> "Priority Preemption Scheduling"
## 5.stack_config
Finding the STACK utilization by each tasks and printing buffer STACK left sparred by each Tasks
Also deleting Tasks after execution.
## 6.task_gpio
gpio output pins enabled and set from task 1 LED and ALarm controll from another task

## 7. task_res_susp
TaskResume and TaskSuspend implementations between tasks

## 8. change_priority
Observations made while changing priority of task.

## 9. xQueue
the use of task to task communication using Queue management APIs. Also observed blocking on a queue
with same priority tasks.
## 10. xQueue_p2
repeating above prog of queue but with tasks having different priority.

## 11. count_sema
RTOS application to demonstrate counting semaphores to synchronize a task

## 12. Task_mutex
RTOS application to demonstrate mutual exclusion of shared resource between tasks

## 13. soft_timer
RTOS application to create a software timer that invokes a callback function every
5 seconds

## 14. event_group
Creating event group to set bits from two tasks and wait for all bit to set from third task 

## 15. Idle_task
prog to create idle hook callback funtion called each time by idle task on getting run time
## 16. binary_sema
RTOS application to demonstrate binary semaphores to synchronize a task
## 17. timestamp
RTOS that provides timestamp and  Observing the jitter in the timestamp vs the periodicity.
## 18. interrupts
enabling and disabling the interrupts
## 19. queue_intr
demonstrating the usage of queues within an interrupt service routine
## 20. defferd_intr
demonstrate deferred interrupt processing
## 21. priority inversion
demonstrating priority inversion problem and solving by priority ceiling/priority inversion protocols using MUTEX

  


