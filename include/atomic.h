#ifndef _ATOMIC_H_
#define _ATOMIC_H_

#define CONFIG_SMP

#ifdef CONFIG_SMP
#define LOCK_PREFIX_HERE \
	".section .smp_locks,\"a\"\n"   \
".balign 4\n"           \
".long 671f - .\n" /* offset */ \
".previous\n"           \
"671:"

#define LOCK_PREFIX LOCK_PREFIX_HERE "\n\tlock; "

#else /* ! CONFIG_SMP */
#define LOCK_PREFIX_HERE ""
#define LOCK_PREFIX ""
#endif


typedef struct 
{  
	volatile int counter;  

} atomic_t;  

static inline int atomic_read(const atomic_t *v)  
{  
	return v->counter;  
}  

static inline void atomic_set(atomic_t *v, int i)  
{  
	v->counter = i;  
}  

static inline void atomic_add(int i, atomic_t *v)  
{  
	asm volatile(LOCK_PREFIX "addl %1,%0"  
			: "+m" (v->counter)  
			: "ir" (i));  
}  

static inline void atomic_sub(int i, atomic_t *v)  
{  
	asm volatile(LOCK_PREFIX "subl %1,%0"  
			: "+m" (v->counter)  
			: "ir" (i));  
}  

static inline void atomic_inc(atomic_t *v)  
{  
	asm volatile(LOCK_PREFIX "incl %0"  
			: "+m" (v->counter));  
}  

static inline void atomic_dec(atomic_t *v)  
{  
	asm volatile(LOCK_PREFIX "decl %0"  
			: "+m" (v->counter));  
}  


#endif

