#include "../include/small_hash.h"
#include "../include/test.h"
#include <assert.h>
#include <string.h>
#include <sys/types.h>

void
test_sh_set_insert()
{
  TESTING("sh_set should insert key-value pair into hash_table");

  sh_table_t *hash_table = NULL;
  sh_create_hash_table(NULL, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  const char *key   = "foo";
  char       *value = malloc(256 * sizeof(char));
  memset(value, '\0', 256);

  sh_set(hash_table, key, value);

  const u_int32_t hash = pv_sh_polynominal_rolling_hash(
      key, hash_table->options->initial_table_entries);

  if(hash_table->nodes[hash] == NULL)
    {
      TEST_FAIL;
      return;
    }

  if(strcmp((const char *)hash_table->nodes[hash]->value, (const char *)value)
     != 0)
    {
      TEST_FAIL;
      return;
    }

  sh_clear_hash_table(hash_table);
  TEST_PASS;
}

void
test_sh_set_update()
{
  TESTING("sh_set should update inserted key-value pair into hash_table");

  sh_table_t *hash_table = NULL;
  sh_create_hash_table(NULL, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  const char *key   = "foo";
  char       *value = malloc(256 * sizeof(char));
  memset(value, '\0', 256);
  strcpy(value, "Hello World");

  sh_set(hash_table, key, value);

  const u_int32_t hash = pv_sh_polynominal_rolling_hash(
      key, hash_table->options->initial_table_entries);

  if(hash_table->nodes[hash] == NULL)
    {
      TEST_FAIL;
      return;
    }

  if(strcmp((const char *)hash_table->nodes[hash]->value, "Hello World") != 0)
    {
      TEST_FAIL;
      return;
    }

  char *new_value = (char *)malloc(256 * sizeof(char));
  memset(new_value, '\0', 256);
  strcpy(new_value, "Small Hash is Fun :))");

  sh_set(hash_table, key, new_value);

  if(hash_table->nodes[hash] == NULL)
    {
      TEST_FAIL;
      return;
    }

  if(strcmp((const char *)hash_table->nodes[hash]->value,
            "Small Hash is Fun :))")
     != 0)
    {
      TEST_FAIL;
      return;
    }

  sh_clear_hash_table(hash_table);
  TEST_PASS;
}

void
test_sh_set_multi_insert()
{
  TESTING("sh_set should insert collisioned keys into tail of linked list.");

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
  memcpy(value2, "foo", strlen("foo"));
  memcpy(value3, "foo", strlen("foo"));

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

  const u_int32_t hash1 = pv_sh_polynominal_rolling_hash(
      key1, hash_table->options->initial_table_entries);
  const u_int32_t hash2 = pv_sh_polynominal_rolling_hash(
      key2, hash_table->options->initial_table_entries);
  const u_int32_t hash3 = pv_sh_polynominal_rolling_hash(
      key3, hash_table->options->initial_table_entries);

  if(strcmp(hash_table->nodes[hash1]->key, "curtain") != 0
     || strcmp(hash_table->nodes[hash2]->next->key, "boiling") != 0
     || strcmp(hash_table->nodes[hash3]->next->next->key, "undesirable") != 0)
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
  test_sh_set_insert();
  test_sh_set_update();
  test_sh_set_multi_insert();

  return 0;
}
