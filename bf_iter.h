#ifndef STATE
#   define EXECUTE 0
#   define SKIP 1
#   define RSKIP 2
#   define STATE EXECUTE
#endif
#
#if STATE == EXECUTE
#   if C0 == '>'
#       include "shift_T.h"
#   elif C0 == '<'
#       include "rshift_T.h"
#   elif C0 == '+'
#       define T0_NEXT ((T0 + 1) & 0xff)
#       include "literals/T0.h"
#   elif C0 == '-'
#       define T0_NEXT ((T0 - 1) & 0xff)
#       include "literals/T0.h"
#   elif C0 == '.'
#       define PRINT T0
#       include "print.h"
#   elif C0 == ','
#       define T0_NEXT I0
#       include "literals/T0.h"
#       include "shift_I.h"
#   elif C0 == '['
#       if T0 == 0
#           undef STATE
#           define STATE SKIP
#           define NESTCOUNT 0
#       endif
#   elif C0 == ']'
#       if T0 != 0
#           undef STATE
#           define STATE RSKIP
#           define NESTCOUNT 0
#       endif
#   endif
#   include "shift_C.h"
#elif STATE == SKIP
#   if C0 == '['
#       define NEXT_NESTCOUNT (NESTCOUNT + 1)
#       include "literals/NESTCOUNT.h"
#   elif C0 == ']'
#       if NESTCOUNT == 0
#           undef STATE
#           define STATE EXECUTE
#           undef NESTCOUNT
#       else
#           define NEXT_NESTCOUNT (NESTCOUNT - 1)
#           include "literals/NESTCOUNT.h"
#       endif
#   endif
#   include "shift_C.h"
#elif STATE == RSKIP
#   if C0 == ']'
#       define NEXT_NESTCOUNT (NESTCOUNT + 1)
#       include "literals/NESTCOUNT.h"
#   elif C0 == '['
#       if NESTCOUNT == 0
#           undef STATE
#           define STATE EXECUTE
#           undef NESTCOUNT
#           include "shift_C.h"
#       else
#           define NEXT_NESTCOUNT (NESTCOUNT - 1)
#           include "literals/NESTCOUNT.h"
#       endif
#   endif
#   include "rshift_C.h"
#endif
#
#if Cc == 0
#   undef HALT
#   define HALT 1
#endif
