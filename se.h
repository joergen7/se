#include <stdbool.h>

typedef enum {
  SE_TYPE_STR,
  SE_TYPE_BOOL,
  SE_TYPE_INT,
  SE_TYPE_NIL,
  SE_TYPE_CONS
} se_type_t;

typedef union {
  char *str_value;
  bool bool_value;
  long int_value;
  struct se_s *cons_value[2];
} se_data_t;

typedef struct se_s {
  se_type_t type;
  se_data_t data;
} se_t;

se_t *se_bool( bool value );
se_t *se_int( long value );
se_t *se_str( char *value );
se_t *se_nil( void );
se_t *se_cons( se_t *car, se_t *cdr );

void se_free( se_t *e );

void se_print( se_t *e );
void se_println( se_t *e );
