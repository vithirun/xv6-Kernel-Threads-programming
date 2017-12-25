#include "types.h"
#include "stat.h"
#include "user.h"

lock_t lock;

void
funcptr(void* dummy)
{
  printf(1, "hello from thread %d\n", *((int*)dummy));
  return;
}

int
main(void)
{
  int *a = (int*)malloc(4);
  *a = 5;
  lock_init(&lock);
  printf(1, "lock->locked: %u\n", lock);
  printf(1, "hello from threadtest main\n");
  thread_create(&funcptr, a);
  thread_join(); 
  printf(1, "bye from threadtest main\n");
  exit();
}
