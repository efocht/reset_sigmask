# reset_sigmask
Tool for resetting the signal mask of a child process

This tool does, in a more compact form, what newer coreutils (8.31 and later) `env --reset-signal` does.
It resets the signal masks for a child process, which normally inherits this mask from its parent.
You might want this when running jobs in a queueing system that is blocking some signals for its children, but you
are used to control the jobs' behavior with signals (abort, checkpoint, prepare for end of job's elapsed time).

## Usage
```
reset_sigmask CMD [ARGS...]
```

## Build
```
gcc -o reset_sigmask reset_sigmask.c
```
