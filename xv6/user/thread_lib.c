#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

int
thread_create(void (*funcptr)(void*), void *arg)
{
	void *ptr;
	int ret;
	ptr = malloc(4096);
	ret = clone(funcptr, arg, ptr);
	return ret;
}

int
thread_join(void)
{
        void *user_stack;
        int ret;
	ret = join(&user_stack);
	if (ret != -1)
		free(user_stack);
        return ret;
}
