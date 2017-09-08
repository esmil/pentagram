// SPDX-License-Identifier: Apache-2.0
#ifndef _SIFIVE_CONST_H
#define _SIFIVE_CONST_H

#ifdef __ASSEMBLER__
#define _AC(X,Y)        X
#define _AT(T,X)        X
#else
#define _AC(X,Y)        (X##Y)
#define _AT(T,X)        ((T)(X))
#endif

#define _BITU(x)        (_AC(1,U) << (x))
#define _BITUL(x)       (_AC(1,UL) << (x))
#define _BITULL(x)      (_AC(1,ULL) << (x))

#endif
