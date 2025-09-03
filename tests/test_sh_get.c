#include "../include/small_hash.h"
#include "../include/test.h"
#include <assert.h>
#include <sys/types.h>

void
test_sh_get_fetch_inserted()
{
  TESTING("sh_get should fetch inserted key-value pair into hash_table");

  sh_table_t *hash_table = NULL;
  sh_create_hash_table(NULL, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  const char *key   = "Complex Key! inserted Into Hash Table";
  char       *value = malloc(256 * sizeof(char));
  memset(value, '\0', 256);

  sh_set(hash_table, key, value);

  void *entity = sh_get(hash_table, key);
  if(entity == NULL)
    {
      TEST_FAIL;
      return;
    }

  if(strcmp((const char *)entity, (const char *)value) != 0)
    {
      TEST_FAIL;
      return;
    }

  sh_clear_hash_table(hash_table);
  TEST_PASS;
}

void
test_sh_get_multi_fetch()
{
  TESTING("sh_get should return inserted collisioned keys into tail of linked "
          "list.");

  /**
   * These keys have collision when mod is 1033
   */
  const char *key1   = "curtain";
  const char *key2   = "boiling";
  const char *key3   = "undesirable";

  char       *value1 = (char *)malloc(256 * sizeof(char));
  char       *value2 = (char *)malloc(256 * sizeof(char));
  char       *value3 = (char *)malloc(256 * sizeof(char));

  memset(value1, '\0', 256);
  memset(value2, '\0', 256);
  memset(value3, '\0', 256);

  memcpy(value1, "foo", strlen("foo"));
  memcpy(value2, "bar", strlen("bar"));
  memcpy(value3, "zoo", strlen("zoo"));

  sh_table_t        *hash_table = NULL;
  sh_table_options_t options    = { .initial_table_entries = 1033 };
  sh_create_hash_table(&options, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  sh_set(hash_table, key1, (void *)value1);
  sh_set(hash_table, key2, (void *)value2);
  sh_set(hash_table, key3, (void *)value3);

  if(strcmp((char *)sh_get(hash_table, key1), "foo") != 0
     || strcmp((char *)sh_get(hash_table, key2), "bar") != 0
     || strcmp((char *)sh_get(hash_table, key3), "zoo") != 0)
    {
      TEST_FAIL;
      return;
    }

  sh_clear_hash_table(hash_table);
  TEST_PASS;
}

int
main()
{
  test_sh_get_fetch_inserted();
  test_sh_get_multi_fetch();

  return 0;
}
