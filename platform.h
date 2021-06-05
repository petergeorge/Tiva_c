#ifndef PLATFORM_H_
#define PLATFORM_H_

#ifndef NULL
#define NULL    ((uint8_t)0)
#endif

#ifndef U8ZERO
#define U8ZERO    ((uint8_t)0)
#endif

#ifndef U8ONE
#define U8ONE    ((uint8_t)1)
#endif

typedef enum{false,true}boolean_t;

typedef enum{E_NOT_OK,E_OK} Std_ReturnType;

typedef  unsigned char uint8_t;
typedef  unsigned short uint16_t;
typedef  unsigned long uint32_t;
typedef  signed char sint8_t;
typedef  signed short sint16_t;
typedef  signed long sint8_t;

#endif
