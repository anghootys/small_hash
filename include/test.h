#ifndef _SH_TEST_H_
#define _SH_TEST_H_

#include "small_hash.h"
#include <stdio.h>

#define TESTING(S) printf("\033[36m[ TEST ]\033[0m %s\n", S)
#define TEST_PASS  printf("\033[32m[PASSED]\033[0m\n")
#define TEST_FAIL  printf("\033[31m[FAILED]\033[0m\n")

/**
 * Pretty prints hash set to the standard output.
 */
void print_hash_table(sh_table_t *hash_table, int only_non_null_nodes);

inline void
print_hash_table(sh_table_t *hash_table, int only_non_null_nodes)
{
  if(hash_table == NULL)
    printf("Hash Table is NULL\n");

  for(int i = 0; i < hash_table->options->initial_table_entries; i++)
    {
      if(only_non_null_nodes != 0 && hash_table->nodes[i] == NULL)
        continue;

      printf("[%d] ", i);

      sh_node_t *node = hash_table->nodes[i];
      while(node != NULL)
        {
          printf("-> %s(%s) ", node->key, (char *)node->value);
          if(node->next == NULL)
            break;
          node = node->next;
        }
      printf("-> NULL\n");
    }
}

#endif
