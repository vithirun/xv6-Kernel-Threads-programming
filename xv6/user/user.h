#ifndef _USER_H_
#define _USER_H_

struct stat;
struct cv;
typedef struct cv cond_t;

typedef uint lock_t;

// system calls
int fork(void);
int exit(void) __attribute__((noreturn));
int wait(void);
int pipe(int*);
int write(int, void*, int);
int read(int, void*, int);
int close(int);
int kill(int);
int exec(char*, char**);
int open(char*, int);
int mknod(char*, short, short);
int unlink(char*);
int fstat(int fd, struct stat*);
int link(char*, char*);
int mkdir(char*);
int chdir(char*);
int dup(int);
int getpid(void);
char* sbrk(int);
int sleep(int);
int uptime(void);
int clone(void (*funcptr)(void*), void*, void*);
int join(void**);
int cinit(cond_t *);
int cwait(cond_t *, lock_t *);
int csignal(cond_t *);

// user library functions (ulib.c)
int stat(char*, struct stat*);
char* strcpy(char*, char*);
void *memmove(void*, void*, int);
char* strchr(const char*, char c);
int strcmp(const char*, const char*);
void printf(int, char*, ...);
char* gets(char*, int max);
uint strlen(char*);
void* memset(void*, int, uint);
void* malloc(uint);
void free(void*);
int atoi(const char*);
int thread_create(void (*funcptr)(void*), void*);
int thread_join(void);


void lock_init(lock_t *);
void lock_acquire(lock_t *);
void lock_release(lock_t *);
void cond_init(cond_t *);
void cond_wait(cond_t *, lock_t *);
void cond_signal(cond_t *);

#endif // _USER_H_

