#include "../include/small_hash.h"
#include "../include/test.h"
#include <assert.h>
#include <stdlib.h>

void
test_sh_create_hash_table_default_options()
{
  TESTING("sh_create_hash_table (with default options) initializes a "
          "hash_table and it should not be NULL.");

  sh_table_t *hash_table = NULL;
  sh_create_hash_table(NULL, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  free(hash_table);
  TEST_PASS;
}

void
test_sh_create_hash_table_custom_options()
{
  TESTING("sh_create_hash_table (with custom options) initializes a "
          "hash_table and it should not be NULL.");

  sh_table_t        *hash_table       = NULL;
  sh_table_options_t sh_table_options = { .initial_table_entries = 100000 };

  sh_create_hash_table(&sh_table_options, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  free(hash_table);
  TEST_PASS;
}

int
main()
{
  test_sh_create_hash_table_default_options();
  test_sh_create_hash_table_custom_options();

  return 0;
}
