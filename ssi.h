#define TARGET_IS_BLIZZARD_RB1
#define PART_TM4C123GH6PM

#include <stdbool.h>
#include <stdint.h>
#include "platform.h"
#include "rom.h"
#include "sysctl.h"
#include "pin_map.h"
#include "hw_memmap.h"

#define F_SPI 1000000
//*****************************************************************************
#define SSI_TXEOT               0x00000040  // Transmit FIFO is empty
#define SSI_DMATX               0x00000020  // DMA Transmit complete
#define SSI_DMARX               0x00000010  // DMA Receive complete
#define SSI_TXFF                0x00000008  // TX FIFO half full or less
#define SSI_RXFF                0x00000004  // RX FIFO half full or more
#define SSI_RXTO                0x00000002  // RX timeout
#define SSI_RXOR                0x00000001  // RX overrun

//*****************************************************************************
//
// Values that can be passed to SSIConfigSetExpClk.
//
//*****************************************************************************
#define SSI_FRF_MOTO_MODE_0     0x00000000  // Moto fmt, polarity 0, phase 0
#define SSI_FRF_MOTO_MODE_1     0x00000002  // Moto fmt, polarity 0, phase 1
#define SSI_FRF_MOTO_MODE_2     0x00000001  // Moto fmt, polarity 1, phase 0
#define SSI_FRF_MOTO_MODE_3     0x00000003  // Moto fmt, polarity 1, phase 1
#define SSI_FRF_TI              0x00000010  // TI frame format
#define SSI_FRF_NMW             0x00000020  // National MicroWire frame format

#define SSI_MODE_MASTER         0x00000000  // SSI master
#define SSI_MODE_SLAVE          0x00000001  // SSI slave
#define SSI_MODE_SLAVE_OD       0x00000002  // SSI slave with output disabled

//*****************************************************************************
//
// Values that can be passed to SSIDMAEnable() and SSIDMADisable().
//
//*****************************************************************************
#define SSI_DMA_TX              0x00000002  // Enable DMA for transmit
#define SSI_DMA_RX              0x00000001  // Enable DMA for receive

//*****************************************************************************
//
// Values that can be passed to SSIClockSourceSet() or returned from
// SSIClockSourceGet().
//
//*****************************************************************************
#define SSI_CLOCK_SYSTEM        0x00000000
#define SSI_CLOCK_PIOSC         0x00000005

//*****************************************************************************
//
// Values that can be passed to SSIAdvModeSet().
//
//*****************************************************************************
#define SSI_ADV_MODE_LEGACY     0x00000000
#define SSI_ADV_MODE_READ_WRITE 0x000001c0
#define SSI_ADV_MODE_WRITE      0x000000c0
#define SSI_ADV_MODE_BI_READ    0x00000140
#define SSI_ADV_MODE_BI_WRITE   0x00000040
#define SSI_ADV_MODE_QUAD_READ  0x00000180
#define SSI_ADV_MODE_QUAD_WRITE 0x00000080

#define SSI_TX_RX_BUFFER_SIZE	((uint16_t)1024)
#define SSI_RX_MASK             ((uint32_t)0x000000FF)
// #define debug

typedef void (* ssi_callcout_func_type)(boolean_t);

extern void SSI_init (void);

extern void SSI_Send_Receive_buffers (uint32_t ulDataRx[],uint32_t ulDataTx[],uint8_t size, ssi_callcout_func_type ssi_callout);

extern void set_ssiFlagStatusTrue (void);

extern boolean_t get_ssiFlagStatus (void);

extern void ssi_cyclic (void);

extern void ISR_SSI_handler (void);

extern void set_ssiFlagStatusTrue (void);

extern boolean_t get_ssiFlagStatus (void);
