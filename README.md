# OS-mimic

A simple, mainly educational shell/OS simulator written in C. Implements a
command-line shell with in-memory variables, batch script execution, a toy multiprocessing 
model (PCBs + scheduling queue), and  CPU scheduling policies (FCFS, SJF, Round Robin, Aging).

## Features

- **Interactive shell** -- reads commands from stdin and dispatches them.
- **Batch mode** -- automatically detected when stdin is not a TTY (e.g.
  `./mysh < script.txt`).
- **Shell variables** -- `set`, `print`, `echo $VAR` backed by a simple
  key/value store (`shellmemory.c`).
- **File system helpers** -- `my_ls`, `my_mkdir`, `my_touch`, `my_cd`.
- **Script execution**
  - `source SCRIPT` -- run a single script to completion (FCFS).
  - `exec P1 [P2] [P3] [POLICY] [#]` --— load 1–3 programs as separate
    "processes" (PCBs), schedule them under a chosen policy, and run
    them. The trailing `#` puts the shell itself into "background mode,"
    so the rest of stdin becomes an additional process in the schedule.
- **Real process execution** -- `run PROGRAM [ARGS...]` forks and
  `execvp`s an actual external program, waiting for it to finish.
- **Command chaining** -- commands separated by `;` on one line are run
  in sequence.


## Building

```
make
```

This produces the `mysh` executable. To clean build artifacts:

```
make clean
```


## Running

Interactively:

```
./mysh
$ help
$ set X hello world
$ print X
$ quit
```

As a batch script:

```
./mysh < myscript.txt
```

## Command reference

| Command                     | Description                                                        |
|------------------------------|---------------------------------------------------------------------|
| `help`                       | Lists available commands.                                          |
| `quit`                       | Prints "Bye!" and exits.                                            |
| `set VAR VAL...`             | Assigns (possibly multi-word) value to a shell variable.           |
| `print VAR`                  | Prints the value of a variable, or "Variable does not exist".      |
| `echo TOKEN`                 | Prints a literal token, or the value of `$VAR` if prefixed with `$`.|
| `my_ls`                      | Lists files in the current directory (dotfiles hidden, sorted).    |
| `my_mkdir NAME`               | Creates a directory (name must be alphanumeric, or `$VAR` resolving to one). |
| `my_touch PATH`               | Creates an empty file at PATH.                                     |
| `my_cd PATH`                  | Changes the current working directory.                             |
| `source SCRIPT`               | Runs SCRIPT to completion under FCFS.                               |
| `exec P1 [P2] [P3] POLICY [#]`| Schedules 1–3 scripts under the given policy; `#` backgrounds the shell. |
| `run PROG [ARGS...]`          | Forks and execs a real external program.                            |


## Scheduling policies [POLICY]
Implemented in `schedule_policy.c` / `queue.c`, selected by name when
calling `exec`:

| Policy  | Behavior                                                          |
|---------|--------------------------------------------------------------------|
| `FCFS`  | Runs each process to completion, in arrival order.                 |
| `SJF`   | Shortest-Job-First; runs to completion; ties broken by FCFS.        |
| `RR`    | Round Robin; each process gets a 2-instruction time slice.          |
| `RR30`  | Round Robin with a 30-instruction time slice.                       |
| `AGING` | Priority scheduling with aging (1-instruction slices); durations of waiting processes decrease each dequeue, and ties at the head are handled specially so equal-length programs preserve arrival order on initial scheduling. |