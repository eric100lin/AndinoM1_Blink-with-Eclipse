/*  Declare a pointer to void function type.  */
typedef void (*func_ptr) (void);
/* Define __dso_handle which would be needed for C++ library.
 *    Since our elf-toolchain only builds programs with static link,
 *       we can directly define 'void *__dso_handle = 0'.  */
void *__dso_handle = 0;
func_ptr __CTOR_END__[1] __attribute__ ((section (".ctors")))
     = { (func_ptr) 0 };

extern func_ptr __CTOR_LIST__[1];
/* Run all global constructors for the program.
 *    Note that they are run in reverse order.  */
void
__do_global_ctors (void)
{
  func_ptr *p;
  for (p = __CTOR_END__ - 1; p != __CTOR_LIST__ ; p--)
    (*p) ();
}


