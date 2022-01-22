# RTOS_proj
Projects using FreeRtos on ESP32 platform
## cdac
simple hello-cdac program on ESP32 board
## task_p
creating two tasks: Task_1 & Task_2 with functionality Increment and Decrement respectively and monitoring task prority
task_1: high priority , task_2 :low priority
## task_delay
A simple delay program having two tasks of same priority with delay functionality
Observations were made that both tasks follows RoundRobin algo to execute.
Also refer: task_delay _P2..
## task_delay_p2
Second example of simple delay program having two tasks with DIFFERENT priorities both following
delay functions. Task_1_LED => priority 20 && Task_2_ALARM => priority 10
Observations made: Task_1_LED(1000ms=delay) executes first having high priority and goes to wait state when delay given..meanwhile Task_2_ALARM(500ms=delay) if Ready executes and goes to wait state when delay arrives
NOTE: while Task_2_ALARM executes if Task_1_LED changed into READY state it starts executing 


