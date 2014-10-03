#pragma once

#include <stdint.h>

#ifndef UNUSED
#define UNUSED(a) ((void)a)
#endif

/* forward declarations (defined below only as needed) */
struct tdt_cond_t;

#ifdef WIN32
    /* TODO: I believe this is actually an OpenCV version issue */
    #define CV_CAP_PROP_WHITE_BALANCE CV_CAP_PROP_WHITE_BALANCE_BLUE_U

    /* in C on Windows we would like bool to work-ish */
    #ifndef __cplusplus
        typedef int bool;
        enum
        {
            false = 0,
            true = 1
        };
    #endif

    #include <windows.h>
    /* stolen from Qt since MS dropped M_PI */
    #ifndef M_PI
      #define M_PI (3.14159265358979323846)
    #endif

    /* fixing up some of the unix style low level io functionality */
    #include <io.h>
    #include <direct.h>
    #pragma warning( disable : 4996) /* POSIX name for 'close' is deprecated */
    #include <fcntl.h>
    #define pipe(a) _pipe(a, 65536, _O_BINARY) /* TODO: pipe objects might not be thread safe? */


    #define alignedAllocate(ptr, alignment, size) ((ptr = (char*)malloc(size)) != NULL)

	#define random rand
    #define makeDir(a) _mkdir(a)

    /* TODO: need usleep! */
    #define compatUSleep(a) Sleep((a) / 1000)

    #define PACKED /* TODO: need to fix this */
    #define THREAD HANDLE
    #define WAITSEM HANDLE
    #define THREAD_START_FUNC LPTHREAD_START_ROUTINE
    #define createThread(threadPtr, funcPtr, arg) ((*threadPtr = CreateThread(NULL, 0, funcPtr, arg, 0, NULL)) != NULL)
    #define joinThread(a) (WaitForSingleObject(a, INFINITE) == WAIT_OBJECT_0)
    #define tryJoinThread(a) (WaitForSingleObject(a, 0) == WAIT_OBJECT_0)

    #define initializeCriticalSection(a) (InitializeCriticalSection(a), 0)

    /* had to implement condition variables for Windows XP.... lovely */
    #define CONDITION_VARIABLE struct tdt_cond_t
    #define NEED_TDT_COND_T
    #ifdef __cplusplus
    extern "C" {
    #endif 
        int initializeCondition(CONDITION_VARIABLE *cond);
        int waitOnCondition(CONDITION_VARIABLE *cond, CRITICAL_SECTION *mutex, uint32_t timeout);
        int signalCondition(CONDITION_VARIABLE *cond);
        int signalAllCondition(CONDITION_VARIABLE *cond);
        int destroyCondition(CONDITION_VARIABLE *cond);
    #ifdef __cplusplus
    }
    #endif 

    #define GET_THREAD_ID() (long int)GetCurrentThreadId()

    #if 0
/* Need to build this for Vista/Win7 someday using their condition var api*/
VOID WINAPI InitializeConditionVariable(
  __out  PCONDITION_VARIABLE ConditionVariable
    );

BOOL WINAPI SleepConditionVariableCS(
    PCONDITION_VARIABLE ConditionVariable,
    PCRITICAL_SECTION CriticalSection,
  DWORD dwMilliseconds
    );

/*
VOID WINAPI WakeAllConditionVariable(
  __inout  PCONDITION_VARIABLE ConditionVariable
    );
*/

VOID WINAPI WakeConditionVariable(
  PCONDITION_VARIABLE ConditionVariable
    );
    #endif

#else
    #ifndef __cplusplus
        #include <stdbool.h>
    #endif

    #include <unistd.h>

    #define alignedAllocate(ptr, alignment, size) (posix_memalign((void**)&ptr, alignment, size) == 0)

    #define makeDir(a) mkdir(a, 0775)

    #ifndef INFINITE
      #define INFINITE 0xFFFFFFFF
    #endif
    #define compatUSleep(a) usleep(a)
    #define PACKED   __attribute__((packed))
    #define WAITSEM pthread_mutex_t
    #define INT_PTR  unsigned long
    #define MAX_PATH PATH_MAX
/*    #define INT_MAX  MAX_INT */

    /* pthread wrapping */
    #include <pthread.h>
    #define THREAD pthread_t
    typedef void* (*THREAD_START_FUNC )(void*);
    #define createThread(threadPtr, funcPtr, arg) (pthread_create(threadPtr, NULL, funcPtr, arg) == 0)
    #define joinThread(a) (pthread_join(a, NULL) == 0)
    #define tryJoinThread(a) (pthread_tryjoin_np((a), NULL) != 0)

    /* critical sections are simpler in Windows' form */
    #define CRITICAL_SECTION pthread_mutex_t
    #define initializeCriticalSection(a) pthread_mutex_init(a, NULL)
    #define EnterCriticalSection(a) pthread_mutex_lock(a)
    #define LeaveCriticalSection(a) pthread_mutex_unlock(a)
    #define DeleteCriticalSection(a) pthread_mutex_destroy(a)

    #define OutputDebugString(a) fprintf(stderr, "%s", a)

    /* since the code merge setting priorities seems to improve performance */
    #define SET_PRIORITIES

    /* when changing thread priorities we directly call gettid for the id */
    #include <sys/syscall.h>
    #define GET_THREAD_ID() (long int)syscall(SYS_gettid)

#ifdef AS_FUNCS
  #ifdef AS_COND_T
    #define CONDITION_VARIABLE pthread_cond_t
  #else
    #define CONDITION_VARIABLE struct tdt_cond_t
    #define NEED_TDT_COND_T
  #endif

  #ifdef __cplusplus
  extern "C" {
  #endif 
    int initializeCondition(CONDITION_VARIABLE *cond);
    int waitOnCondition(CONDITION_VARIABLE *cond, CRITICAL_SECTION *mutex,
                        uint32_t timeout);
    int signalCondition(CONDITION_VARIABLE *cond);
    int signalAllCondition(CONDITION_VARIABLE *cond);
    int destroyCondition(CONDITION_VARIABLE *cond);
  #ifdef __cplusplus
  }
  #endif 
#else
    #define CONDITION_VARIABLE pthread_cond_t
    #define initializeCondition(a) pthread_cond_init(a, NULL)
  #ifdef __cplusplus
  extern "C" {
  #endif 
    int waitOnCondition(CONDITION_VARIABLE *cond, CRITICAL_SECTION *mutex,
                        uint32_t timeout);
  #ifdef __cplusplus
  }
  #endif 
    #define signalCondition(a)     pthread_cond_signal(a)
    #define signalAllCondition(a)  pthread_cond_broadcast(a)
    #define destroyCondition(a)    pthread_cond_destroy(a)
#endif

    typedef int64_t __int64;
#endif

#ifdef NEED_TDT_COND_T
    typedef struct tdt_cond_t
    {
        int waiters, wakers;
        CRITICAL_SECTION modLock;
        WAITSEM waitSem;
    } tdt_cond_t;
#endif

/* moving all the priority setting code to one place */
#ifdef __cplusplus
extern "C" {
#endif 
  extern bool setThreadPriority(int diffFromMax);
#ifdef __cplusplus
}
#endif 
