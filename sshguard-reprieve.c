#include <stdio.h>
#include <stdlib.h>
#include <libgen.h> // For basename

#include "sshguard_blacklist.h"
#include "seekers.h"

#include <regex.h>
#include "regexlib.h"

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: %s <blacklist file> <ip address>\n", basename(argv[0]));
    return 1;
  }

  char *filename = argv[1];
  attacker_t *el;
  list_t *blacklist;
  sshg_address_t me;
  regex_t ipreg4, ipreg6;

  if (regcomp(&ipreg4, "^" REGEXLIB_IPV4 "$", REG_EXTENDED) ||
      regcomp(&ipreg6, "^" REGEXLIB_IPV6 "$", REG_EXTENDED)) {
    printf("Failed detecting ip address type: regex compile failed\n");
    return 2;
  }

  if (!regexec(&ipreg4, argv[2], 0, NULL, 0)) {
    me.kind = ADDRKIND_IPv4;
  } else if (!regexec(&ipreg6, argv[2], 0, NULL, 0)) {
    me.kind = ADDRKIND_IPv6;
  } else {
    printf("%s is not a valid ip address\n", argv[2]);
    regfree(&ipreg4);
    regfree(&ipreg6);
    return 2;
  }

  for(int i = 0; *(me.value + i) = *(argv[2] + i); i++);
  regfree(&ipreg4);
  regfree(&ipreg6);

  if (!(blacklist = blacklist_load(filename))) {
      perror("Failed opening blacklist");
      return 3;
  }

  list_attributes_seeker(blacklist, seeker_addr);
  list_attributes_serializer(blacklist, attacker_serializer);

  if ((el = list_seek(blacklist, &me))) {
    list_delete(blacklist, el);

    printf("Removed %s from blacklist\n", me.value);

    if (list_dump_file(blacklist, filename, NULL) == 0) {
      printf("Saved modified blacklist\n");
    } else {
      perror("Failed saving blacklist");
      list_destroy(blacklist);
      free(blacklist);
      return 5;
    }
  } else {
    printf("%s is not in blacklist\n", me.value);
    list_destroy(blacklist);
    free(blacklist);
    return 4;
  }

  list_destroy(blacklist);
  free(blacklist);

  return 0;
}
