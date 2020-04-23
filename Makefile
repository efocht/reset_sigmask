#
# trivial makefile
#

reset_sigmask: reset_sigmask.c
	gcc -o $@ $<

