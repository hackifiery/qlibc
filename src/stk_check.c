#include "unistd.h"
/* dummy function so the c compiler is satisfied */
__attribute__((noreturn))
void __stack_chk_fail(void) {
    _exit(1);
    __builtin_unreachable();
}