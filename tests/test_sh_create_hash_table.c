#include "../include/small_hash.h"
#include "../include/test.h"
#include <assert.h>
#include <stdio.h>

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

  sh_clear_hash_table(hash_table);
  TEST_PASS;
}

void
test_sh_create_hash_table_custom_options()
{
  TESTING("sh_create_hash_table (with custom options) initializes a "
          "hash_table and it should not be NULL.");

  sh_table_t        *hash_table = NULL;
  sh_table_options_t options    = { .initial_table_entries = 100000 };

  sh_create_hash_table(&options, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  sh_clear_hash_table(hash_table);
  TEST_PASS;
}

void
test_sh_create_hash_table_custom_options_2()
{
  TESTING("sh_crate_hash_table should initialize "
          "options->initial_table_entries to INITIAL_TABLE_ENTRIES if "
          "provided enties length is less than or equal to 0.");

  sh_table_t        *hash_table = NULL;
  sh_table_options_t options    = { .initial_table_entries = -100 };

  sh_create_hash_table(&options, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  if(hash_table->options->initial_table_entries != INITIAL_TABLE_ENTRIES)
    {
      TEST_FAIL;
      return;
    }

  sh_clear_hash_table(hash_table);
  TEST_PASS;
}

void
test_sh_create_hash_table_allocated_memory_size()
{
  TESTING("sh_create_hash_table should allocate (INITIAL_TABLE_ENTRIES * "
          "sizeof(sh_node_t *)) bytes by default.");

  sh_table_t        *hash_table = NULL;
  sh_table_options_t options    = { .initial_table_entries = 256 };

  sh_create_hash_table(&options, &hash_table);

  if(hash_table == NULL)
    {
      TEST_FAIL;
      return;
    }

  for(int i = 0; i < hash_table->options->initial_table_entries; i++)
    {
      sh_node_t **tail = &hash_table->nodes[i];

      for(size_t j = 0; j < 10; j++)
        {
          sh_node_t *node = (sh_node_t *)malloc(sizeof(sh_node_t));
          node->key       = "test key";

          int *value      = (int *)malloc(sizeof(int));
          *value          = (int)j;
          node->value     = (void *)value;

          node->next      = NULL;

          if(*tail == NULL)
            {
              hash_table->nodes[i] = node;
            }
          else
            {
              (*tail)->next = node;
              (*tail)       = node;
            }
        }
    }

  sh_clear_hash_table(hash_table);
  TEST_PASS;
}

int
main()
{
  test_sh_create_hash_table_default_options();
  test_sh_create_hash_table_custom_options();
  test_sh_create_hash_table_custom_options_2();
  test_sh_create_hash_table_allocated_memory_size();

  return 0;
}
