#ifndef _DEBUG_H_
#define _DEBUG_H_

#define TRACE_LVL 2
#define ERROR_LVL 1

#define DBG TRACE_LVL

#if (DBG >= TRACE_LVL)
    #define TRACE(...)      do{\
                                printf("Trace: "); \
                                printf (__VA_ARGS__); \
                                printf("\r\n"); \
                                }while(0);
                                
    //#define COMMON_Print(...) printf (__VA_ARGS__)
#else
    #define TRACE(...)
#endif

#if (DBG >= ERROR_LVL)
    #define ERROR(...)      do{ \
                            printf("\r\nError: "); \
                            printf (__VA_ARGS__); \
                            printf("\r\n"); \
                            }while(0);
    //#define COMMON_Print(...) printf (__VA_ARGS__)
#else
    #define ERROR(...)
#endif





#endif /* #ifndef _DEBUG_H_ */