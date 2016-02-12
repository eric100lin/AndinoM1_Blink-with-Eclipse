/*  Declare a pointer to void function type.  */
typedef void (*func_ptr) (void);
func_ptr __CTOR_LIST__[1] __attribute__ ((section (".ctors")))
     = { (func_ptr) (-1) };

