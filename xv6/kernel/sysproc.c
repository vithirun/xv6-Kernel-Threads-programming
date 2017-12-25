#include "types.h"
#include "x86.h"
#include "defs.h"
#include "param.h"
#include "mmu.h"
#include "proc.h"
#include "sysfunc.h"

typedef uint lock_t;

int
sys_fork(void)
{
  return fork();
}

int
sys_cinit(void)
{
  cond_t *cv;
  if(argptr(0, (char**)&cv, sizeof(cond_t)) < 0)
	return -1;
  cond_init(cv);
  return 0; 
}

int
sys_cwait(void)
{
  cond_t *cv;
  lock_t *lk;
  if(argptr(0, (char**)&cv, sizeof(cond_t)) < 0)
	return -1;
  if(argptr(1, (char**)&lk, sizeof(uint)) < 0)
	return -1;
  cond_wait(cv, lk);
  return 0; 
}

int
sys_csignal(void)
{
  cond_t *cv;
  if(argptr(0, (char**)&cv, sizeof(cond_t)) < 0)
	return -1;
  cond_signal(cv);
  return 0; 
}

int
sys_join(void)
{
  void **user_stack;
  if(argptr(0, (char **)&user_stack, sizeof(user_stack)) < 0)
     return -1;
  return join(user_stack);
}

int
sys_clone(void)
{
  void (*funcptr)(void*);
  void *stack_arg;
  void *stack;

  if(argptr(0, (char**)&funcptr, sizeof(*funcptr)) < 0)
     return -1;
  if(argptr(1, (char**)&stack_arg, sizeof(*stack_arg)) < 0)
     return -1;
  if(argptr(2, (char**)&stack, PGSIZE) < 0)
     return -1; 
  return clone(funcptr, stack_arg, stack);
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return proc->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = proc->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;
  
  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(proc->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since boot.
int
sys_uptime(void)
{
  uint xticks;
  
  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
