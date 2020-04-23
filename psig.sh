#!/bin/bash
##########################################################################
# Slightly modified script from https://unix.stackexchange.com/a/85365
#
# Usage:
#   psig.sh [PID]
#
# With no argument the signal masks for the shell executing the psig script
# are shown.
###########################################################################

sigparse () {
    i=0
    # bits="$(printf "16i 2o %X p" "0x$1" | dc)" # variant for busybox
    bits="$(printf "ibase=16; obase=2; %X\n" "0x$1" | bc)"
    while [ -n "$bits" ] ; do
        i="$(expr "$i" + 1)"
        case "$bits" in
            *1) printf " %s(%s)" "$(kill -l "$i")" "$i" ;;
        esac
        bits="${bits%?}"
    done
}

PID=$$
if [ $# -eq 1 ]; then
    PID=$1
fi

grep "^Sig...:" "/proc/$PID/status" | while read a b ; do
        printf "%s%s\n" "$a" "$(sigparse "$b")"
    done # | fmt -t  # uncomment for pretty-printing

