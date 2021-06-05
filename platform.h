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

typedef enum{FALSE,TRUE}boolean_t;

typedef enum{E_NOT_OK,E_OK} Std_ReturnType;

#endif
