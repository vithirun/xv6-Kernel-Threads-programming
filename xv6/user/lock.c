// Mutual exclusion spin locks.

#include "types.h"
#include "param.h"
#include "x86.h"
#include "user.h"

void
lock_init(lock_t *lk)
{
  *lk = 0;
}

void
lock_acquire(lock_t *lk)
{
  // The xchg is atomic.
  // It also serializes, so that reads after acquire are not
  // reordered before it. 
  while(xchg(lk, 1) != 0)
    ;
}

// Release the lock.
void
lock_release(lock_t *lk)
{

  // The xchg serializes, so that reads before release are 
  // not reordered after it.  The 1996 PentiumPro manual (Volume 3,
  // 7.2) says reads can be carried out speculatively and in
  // any order, which implies we need to serialize here.
  // But the 2007 Intel 64 Architecture Memory Ordering White
  // Paper says that Intel 64 and IA-32 will not move a load
  // after a store. So lock->locked = 0 would work here.
  // The xchg being asm volatile ensures gcc emits it after
  // the above assignments (and after the critical section).
  xchg(lk, 0);

}

void
cond_init(cond_t *cv)
{
	cinit(cv);
}

void
cond_wait(cond_t *cv, lock_t *lk)
{
	cwait(cv, lk);
}

void
cond_signal(cond_t *cv)
{
	csignal(cv);
}

