# Small Hash
A simple, lightweight, single-header C hash table library optimized for low-resource embedded systems.

**FreeRTOS compatibility: In progress (partial support).**

## Features
- Single-header, easy to include in any project
- Minimal memory footprint, suitable for embedded systems
- Simple API for hash table operations (create, insert, delete, lookup)
- Partial FreeRTOS compatibility (work in progress)
- No external dependencies

## Getting started

### Installation
Just include the `include/small_hash.h` header in your project. No additional build steps required.

```c
#include "small_hash.h"
```

Usage Example

```c
#include "small_hash.h"
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
```

* _All examples stored in `examples` directory_

## Public API
* `sh_general_status_t` is an `int` type mask used for return type of `sh_create_hash_table` function.
* `sh_general_status_t sh_create_hash_table(sh_table_options_t *options, sh_table_t **hash_table)`:
  creates new hash_table based on `options`. `options` could be NULL then `initial_table_entries`
  which refers to initial hash set's nodes length. More nodes length = less collision.
  This function returns `sh_general_status_t`. It would be `SH_NOERROR` in the case of creating
  hash table successfully and any other error types otherwise.*Error types are defined in small_hash.h*
  If this function creates hash set successfully, then hash set would be set in `sh_table_t **hash_table`
  reference.
* `void sh_clear_hash_table(sh_table_t *hash_table);` Free allocated memory by hash_table. Should be called
  in the end of program only once.
* `void sh_set(sh_table_t *hash_table, const char *key, void *value)` insert or updates appropriate node based on key.
* `void *sh_get(sh_table_t *hash_table, const char *key)` returns NULL if key does not found in the set or `value` of
  that key if it is exists in hash set.

## Supported Platforms

Designed for embedded systems and tested on:

* ESP8266 & ESP32 modules
* Linux x86_64 (for testing)
* Partial FreeRTOS support (work ongoing)


## Contributing
Contributions are welcome! Please open issues or pull requests, especially for FreeRTOS compatibility improvements.

## License
This project is licensed under the MIT License - see the LICENSE file for details.
