#include <stdio.h>
#include <stdlib.h>
#include <libgen.h> // For basename
 
#include "sshguard_blacklist.h"
#include "seekers.h"

// Output Examples:
// 
// Compile: cmake ./; make
// sudo ./sshguard-dump ./sshguard.db |awk -F ',' '{print $2}' |sort 

 
int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Usage: %s <blacklist file>\n", basename(argv[0]));
    return 1;
  }
 
  char *filename = argv[1];
  list_t *blacklist;
  
  
  if (!(blacklist = blacklist_load(filename))) {
      perror("Failed opening blacklist");
      return 3;
  }
  
  /* printing out the result */
  printf("Current Blacklist:\n");
  printf("list_size: %d\n", list_size(blacklist));
  printf("Entry, ip, count, service, last seen\n");
  int i = 0;
  list_iterator_start(blacklist);
    while (list_iterator_hasnext(blacklist)) {
        const attacker_t *bl_attacker = list_iterator_next(blacklist);
        if (bl_attacker->attack.address.kind != 4)
            continue;
        printf("%d, %s, %d, %d, %s", i,
                bl_attacker->attack.address.value, bl_attacker->attack.address.kind, bl_attacker->attack.service,
                ctime(& bl_attacker->whenlast));
        ++i;
    }
  list_iterator_stop(blacklist);
  
  list_destroy(blacklist);
  free(blacklist);
 
  return 0;
}