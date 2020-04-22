/* 
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* Erich Focht, NEC HPC Europe */

#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main (int argc, char **argv)
{
  sigset_t set;

  if (argc == 1 ||
      strncmp(argv[1], "-h", 2) == 0 ||
      strncmp(argv[1], "--help", 6) == 0) {
    printf("Run a command with signal processig masks reset to default.\n");
    printf("Usage:\n\t%s cmd [cmdargs...]\n", argv[0]);
    exit(0);
  }

  sigemptyset (&set);
  for (int i = 1; i <= _NSIG; i++) {
    struct sigaction act;
    int sig_err = sigaction (i, NULL, &act);
    if (! sig_err) {
      act.sa_handler = SIG_DFL;
      sig_err = sigaction (i, &act, NULL);
    }
  }
  if (sigprocmask (SIG_SETMASK, &set, NULL)) {
    perror("failed to set signal process mask");
    exit(1);
  }
  execvp (argv[1], &argv[1]);
  perror("exec failed");
  return errno;
}

