#ifndef _TYPES_H_
#define _TYPES_H_

// Type definitions

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint lock_t;

typedef uint pde_t;
#ifndef NULL
#define NULL (0)
#endif

typedef struct cv {
 lock_t *lock;
 int tid[8];
 int head, tail;
} cond_t;

#endif //_TYPES_H_
