#ifndef _SMALL_HASH_H_
#define _SMALL_HASH_H_

#define LIB_SMALL_HASH

/** Predefined macros **/

#define INITIAL_TABLE_ENTRIES 16

/** Error Codes **/
#define SH_NOERROR            0
#define SH_ERR_MALLOC_FAILED  1

/** Type Defines **/
typedef int sh_general_status_t;

/**
 * User defined macro SH_FREE_RTOS for the environments that freeRTOS exists
 * so the small_hash library prefer to use freeRTOS dynamic memory allocation
 * APIs for the sake of thread safety and some other benefits.
 */
#ifdef SH_FREE_RTOS

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define MALLOC(S) pvPortMalloc(S)
#define FREE(v)   vPortFree(V)

#else

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(S) malloc(S)
#define FREE(V)   free(v)

#endif

/** structs **/

/**
 * A node in hash table that contains actual hashed key(not hashed) and
 * value of that key.
 *
 * key: string value of actual key(not hashed).
 * value: void pointer to any data user provide for actual key.
 * next: points to the next node in the linked list.
 */
typedef struct sh_node
{
  const char     *key;
  void           *value;
  struct sh_node *next;
} sh_node_t;

/**
 * A hash table struct that can contain meta-data and a linked list to
 * hash table nodes.
 *
 * nodes: A dynamic array that contains list of hashed keys that refers to
 * sh_node_t
 */
typedef struct
{
  sh_node_t **nodes;
} sh_table_t;

typedef struct
{
  int initial_table_entries;
} sh_table_options_t;

#define SH_DEFAULT_TABLE_OPTIONS { .initial_table_entries = -1 }

/** Public APIs **/

/**
 * Create a fresh hash table.
 *
 * @param initial_table_entries Refers to the initial table size; If -1, it
 * lookups for INITIAL_TABLE_ENTRIES macro's value and initializes 'nodes'
 * dynamic array with initial size of `initial_table_entries *
 * sizeof(sh_table_t)`.
 *
 * @return A pointer to a fresh hash table.
 */
sh_general_status_t sh_create_hash_table(sh_table_options_t *options,
                                         sh_table_t        **hash_table);

#ifdef LIB_SMALL_HASH
/** Implementations **/

/**
 * Function implementations placed here, so client should define LIB_SMALL_HASH
 * macro in exactly one place of their program.
 */

inline sh_general_status_t
sh_create_hash_table(sh_table_options_t *options, sh_table_t **hash_table)
{
  if(options == NULL)
    {
      /**
       * If user does not provide 'options' nor 'SH_DEFAULT_TABLE_OPTIONS', we
       * initialize 'options' with 'SH_DEFAULT_TABLE_OPTIONS'.
       */
      sh_table_options_t _options = SH_DEFAULT_TABLE_OPTIONS;
      options                     = &_options;
    }

  *hash_table = NULL;

  *hash_table = (sh_table_t *)MALLOC(sizeof(sh_table_t));

  if(hash_table == NULL)
    return SH_ERR_MALLOC_FAILED;

  hash_table = hash_table;

  if(options->initial_table_entries <= 0)
    (*hash_table)->nodes
        = (sh_node_t **)MALLOC(INITIAL_TABLE_ENTRIES * sizeof(sh_node_t *));
  else
    (*hash_table)->nodes = (sh_node_t **)MALLOC(options->initial_table_entries
                                                * sizeof(sh_node_t *));

  if((*hash_table)->nodes == NULL)
    {
      return SH_ERR_MALLOC_FAILED;
    }

  return SH_NOERROR;
}

#endif

#endif
