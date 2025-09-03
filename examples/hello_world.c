#include "../include/small_hash.h"
#include <string.h>

int
main()
{
  sh_table_t        *hash_table = NULL;
  /**
   * `options` param is optional and initial_table_entries
   * would be set to INITIAL_TABLE_ENTRIES if first argument of
   * sh_create_hash_table is NULL.
   *
   * Here initialize our hash_table size with 1033 * sizeof(sh_node_t) bytes.
   * 1033 is a prime number near 1024(aka 1K).
   */
  sh_table_options_t options    = { .initial_table_entries = 1033 };

  int                err        = sh_create_hash_table(&options, &hash_table);

  if(err != SH_NOERROR)
    {
      fprintf(stderr, "hash_table cration failed. error code: %d\n", err);
    }

  const char *key   = "foo";

  char       *value = (char *)malloc((strlen("bar") + 1) * sizeof(char));
  memset(value, '\0', strlen("bar") + 1);
  strcpy(value, "bar");

  sh_set(hash_table, key, value);

  char *val = (char *)sh_get(hash_table, key);
  printf("%s: %s\n", key, val);

  /**
   * Never forget to call sh_clear_hash_table function in the end of
   * program to avoid memory leaks and other memory issues(specially in
   * embedded systems).
   */
  sh_clear_hash_table(hash_table);

  return 0;
}
