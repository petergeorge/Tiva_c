/*
 * I2C.h
 *
 *  Created on: Feb 3, 2021
 *      Author: Peter
 */

#ifndef I2C_H_
#define I2C_H_

#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#define TARGET_IS_BLIZZARD_RB1
#define PART_TM4C123GH6PM

#include <stdbool.h>
#include <stdint.h>
#include "rom.h"
#include "sysctl.h"
#include "pin_map.h"
#include "hw_memmap.h"
#include "TM4C123GH6PM.h"
//*****************************************************************************
#define I2C_INT_MASTER          0x00000001
#define I2C_INT_SLAVE           0x00000002

//*****************************************************************************
//
// I2C Master commands.
//
//*****************************************************************************
#define I2C_MASTER_CMD_SINGLE_SEND                                            \
                                0x00000007
#define I2C_MASTER_CMD_SINGLE_RECEIVE                                         \
                                0x00000007
#define I2C_MASTER_CMD_BURST_SEND_START                                       \
                                0x00000003
#define I2C_MASTER_CMD_BURST_SEND_CONT                                        \
                                0x00000001
#define I2C_MASTER_CMD_BURST_SEND_FINISH                                      \
                                0x00000005
#define I2C_MASTER_CMD_BURST_SEND_STOP                                        \
                                0x00000004
#define I2C_MASTER_CMD_BURST_SEND_ERROR_STOP                                  \
                                0x00000004
#define I2C_MASTER_CMD_BURST_RECEIVE_START                                    \
                                0x0000000b
#define I2C_MASTER_CMD_BURST_RECEIVE_CONT                                     \
                                0x00000009
#define I2C_MASTER_CMD_BURST_RECEIVE_FINISH                                   \
                                0x00000005
#define I2C_MASTER_CMD_BURST_RECEIVE_ERROR_STOP                               \
                                0x00000004
#define I2C_MASTER_CMD_QUICK_COMMAND                                          \
                                0x00000027
#define I2C_MASTER_CMD_HS_MASTER_CODE_SEND                                    \
                                0x00000013
#define I2C_MASTER_CMD_FIFO_SINGLE_SEND                                       \
                                0x00000046
#define I2C_MASTER_CMD_FIFO_SINGLE_RECEIVE                                    \
                                0x00000046
#define I2C_MASTER_CMD_FIFO_BURST_SEND_START                                  \
                                0x00000042
#define I2C_MASTER_CMD_FIFO_BURST_SEND_CONT                                   \
                                0x00000040
#define I2C_MASTER_CMD_FIFO_BURST_SEND_FINISH                                 \
                                0x00000044
#define I2C_MASTER_CMD_FIFO_BURST_SEND_ERROR_STOP                             \
                                0x00000004
#define I2C_MASTER_CMD_FIFO_BURST_RECEIVE_START                               \
                                0x0000004a
#define I2C_MASTER_CMD_FIFO_BURST_RECEIVE_CONT                                \
                                0x00000048
#define I2C_MASTER_CMD_FIFO_BURST_RECEIVE_FINISH                              \
                                0x00000044
#define I2C_MASTER_CMD_FIFO_BURST_RECEIVE_ERROR_STOP                          \
                                0x00000004

//*****************************************************************************
//
// I2C Master glitch filter configuration.
//
//*****************************************************************************
#define I2C_MASTER_GLITCH_FILTER_DISABLED                                     \
                                0
#define I2C_MASTER_GLITCH_FILTER_1                                            \
                                0x00010000
#define I2C_MASTER_GLITCH_FILTER_2                                            \
                                0x00020000
#define I2C_MASTER_GLITCH_FILTER_3                                            \
                                0x00030000
#define I2C_MASTER_GLITCH_FILTER_4                                            \
                                0x00040000
#define I2C_MASTER_GLITCH_FILTER_8                                            \
                                0x00050000
#define I2C_MASTER_GLITCH_FILTER_16                                           \
                                0x00060000
#define I2C_MASTER_GLITCH_FILTER_32                                           \
                                0x00070000

//*****************************************************************************
//
// I2C Master error status.
//
//*****************************************************************************
#define I2C_MASTER_ERR_NONE     0
#define I2C_MASTER_ERR_ADDR_ACK 0x00000004
#define I2C_MASTER_ERR_DATA_ACK 0x00000008
#define I2C_MASTER_ERR_ARB_LOST 0x00000010
#define I2C_MASTER_ERR_CLK_TOUT 0x00000080

//*****************************************************************************
                                  //*****************************************************************************
//
// I2C Slave action requests
//
//*****************************************************************************
#define I2C_SLAVE_ACT_NONE      0
#define I2C_SLAVE_ACT_RREQ      0x00000001  // Master has sent data
#define I2C_SLAVE_ACT_TREQ      0x00000002  // Master has requested data
#define I2C_SLAVE_ACT_RREQ_FBR  0x00000005  // Master has sent first byte
#define I2C_SLAVE_ACT_OWN2SEL   0x00000008  // Master requested secondary slave
#define I2C_SLAVE_ACT_QCMD      0x00000010  // Master has sent a Quick Command
#define I2C_SLAVE_ACT_QCMD_DATA 0x00000020  // Master Quick Command value

//*****************************************************************************
//
// Miscellaneous I2C driver definitions.
//
//*****************************************************************************
#define I2C_MASTER_MAX_RETRIES  1000        // Number of retries

//*****************************************************************************
//
// I2C Master interrupts.
//
//*****************************************************************************
#define I2C_MASTER_INT_RX_FIFO_FULL                                           \
                                0x00000800  // RX FIFO Full Interrupt
#define I2C_MASTER_INT_TX_FIFO_EMPTY                                          \
                                0x00000400  // TX FIFO Empty Interrupt
#define I2C_MASTER_INT_RX_FIFO_REQ                                            \
                                0x00000200  // RX FIFO Request Interrupt
#define I2C_MASTER_INT_TX_FIFO_REQ                                            \
                                0x00000100  // TX FIFO Request Interrupt
#define I2C_MASTER_INT_ARB_LOST                                               \
                                0x00000080  // Arb Lost Interrupt
#define I2C_MASTER_INT_STOP     0x00000040  // Stop Condition Interrupt
#define I2C_MASTER_INT_START    0x00000020  // Start Condition Interrupt
#define I2C_MASTER_INT_NACK     0x00000010  // Addr/Data NACK Interrupt
#define I2C_MASTER_INT_TX_DMA_DONE                                            \
                                0x00000008  // TX DMA Complete Interrupt
#define I2C_MASTER_INT_RX_DMA_DONE                                            \
                                0x00000004  // RX DMA Complete Interrupt
#define I2C_MASTER_INT_TIMEOUT  0x00000002  // Clock Timeout Interrupt
#define I2C_MASTER_INT_DATA     0x00000001  // Data Interrupt

//*****************************************************************************
//
// I2C Slave interrupts.
//
//*****************************************************************************
#define I2C_SLAVE_INT_RX_FIFO_FULL                                            \
                                0x00000100  // RX FIFO Full Interrupt
#define I2C_SLAVE_INT_TX_FIFO_EMPTY                                           \
                                0x00000080  // TX FIFO Empty Interrupt
#define I2C_SLAVE_INT_RX_FIFO_REQ                                             \
                                0x00000040  // RX FIFO Request Interrupt
#define I2C_SLAVE_INT_TX_FIFO_REQ                                             \
                                0x00000020  // TX FIFO Request Interrupt
#define I2C_SLAVE_INT_TX_DMA_DONE                                             \
                                0x00000010  // TX DMA Complete Interrupt
#define I2C_SLAVE_INT_RX_DMA_DONE                                             \
                                0x00000008  // RX DMA Complete Interrupt
#define I2C_SLAVE_INT_STOP      0x00000004  // Stop Condition Interrupt
#define I2C_SLAVE_INT_START     0x00000002  // Start Condition Interrupt
#define I2C_SLAVE_INT_DATA      0x00000001  // Data Interrupt

//*****************************************************************************
//
// I2C Slave FIFO configuration macros.
//
//*****************************************************************************
#define I2C_SLAVE_TX_FIFO_ENABLE                                              \
                                0x00000002
#define I2C_SLAVE_RX_FIFO_ENABLE                                              \
                                0x00000004

//*****************************************************************************
//
// I2C FIFO configuration macros.
//
//*****************************************************************************
#define I2C_FIFO_CFG_TX_MASTER  0x00000000
#define I2C_FIFO_CFG_TX_SLAVE   0x00008000
#define I2C_FIFO_CFG_RX_MASTER  0x00000000
#define I2C_FIFO_CFG_RX_SLAVE   0x80000000
#define I2C_FIFO_CFG_TX_MASTER_DMA                                            \
                                0x00002000
#define I2C_FIFO_CFG_TX_SLAVE_DMA                                             \
                                0x0000a000
#define I2C_FIFO_CFG_RX_MASTER_DMA                                            \
                                0x20000000
#define I2C_FIFO_CFG_RX_SLAVE_DMA                                             \
                                0xa0000000
#define I2C_FIFO_CFG_TX_NO_TRIG 0x00000000
#define I2C_FIFO_CFG_TX_TRIG_1  0x00000001
#define I2C_FIFO_CFG_TX_TRIG_2  0x00000002
#define I2C_FIFO_CFG_TX_TRIG_3  0x00000003
#define I2C_FIFO_CFG_TX_TRIG_4  0x00000004
#define I2C_FIFO_CFG_TX_TRIG_5  0x00000005
#define I2C_FIFO_CFG_TX_TRIG_6  0x00000006
#define I2C_FIFO_CFG_TX_TRIG_7  0x00000007
#define I2C_FIFO_CFG_TX_TRIG_8  0x00000008
#define I2C_FIFO_CFG_RX_NO_TRIG 0x00000000
#define I2C_FIFO_CFG_RX_TRIG_1  0x00010000
#define I2C_FIFO_CFG_RX_TRIG_2  0x00020000
#define I2C_FIFO_CFG_RX_TRIG_3  0x00030000
#define I2C_FIFO_CFG_RX_TRIG_4  0x00040000
#define I2C_FIFO_CFG_RX_TRIG_5  0x00050000
#define I2C_FIFO_CFG_RX_TRIG_6  0x00060000
#define I2C_FIFO_CFG_RX_TRIG_7  0x00070000
#define I2C_FIFO_CFG_RX_TRIG_8  0x00080000

//*****************************************************************************
//
// I2C FIFO status.
//
//*****************************************************************************
#define I2C_FIFO_RX_BELOW_TRIG_LEVEL                                          \
                                0x00040000
#define I2C_FIFO_RX_FULL        0x00020000
#define I2C_FIFO_RX_EMPTY       0x00010000
#define I2C_FIFO_TX_BELOW_TRIG_LEVEL                                          \
                                0x00000004
#define I2C_FIFO_TX_FULL        0x00000002
#define I2C_FIFO_TX_EMPTY       0x00000001

#define GPIO_PIN_0              0x00000001  // GPIO pin 0
#define GPIO_PIN_1              0x00000002  // GPIO pin 1
#define GPIO_PIN_2              0x00000004  // GPIO pin 2
#define GPIO_PIN_3              0x00000008  // GPIO pin 3
#define GPIO_PIN_4              0x00000010  // GPIO pin 4
#define GPIO_PIN_5              0x00000020  // GPIO pin 5
#define GPIO_PIN_6              0x00000040  // GPIO pin 6
#define GPIO_PIN_7              0x00000080  // GPIO pin 7
#define I2C_O_MSA               0x00000000  // I2C Master Slave Address
#define I2C_O_MCS               0x00000004  // I2C Master Control/Status
#define I2C_O_MDR               0x00000008  // I2C Master Data
#define I2C_O_MTPR              0x0000000C  // I2C Master Timer Period
#define I2C_O_MIMR              0x00000010  // I2C Master Interrupt Mask
#define I2C_O_MRIS              0x00000014  // I2C Master Raw Interrupt Status
#define I2C_O_MMIS              0x00000018  // I2C Master Masked Interrupt
                                            // Status
#define I2C_O_MICR              0x0000001C  // I2C Master Interrupt Clear
#define I2C_O_MCR               0x00000020  // I2C Master Configuration
#define I2C_O_MCLKOCNT          0x00000024  // I2C Master Clock Low Timeout
                                            // Count
#define I2C_O_MBMON             0x0000002C  // I2C Master Bus Monitor
#define I2C_O_MBLEN             0x00000030  // I2C Master Burst Length
#define I2C_O_MBCNT             0x00000034  // I2C Master Burst Count
#define I2C_O_MCR2              0x00000038  // I2C Master Configuration 2
#define I2C_O_SOAR              0x00000800  // I2C Slave Own Address
#define I2C_O_SCSR              0x00000804  // I2C Slave Control/Status
#define I2C_O_SDR               0x00000808  // I2C Slave Data
#define I2C_O_SIMR              0x0000080C  // I2C Slave Interrupt Mask
#define I2C_O_SRIS              0x00000810  // I2C Slave Raw Interrupt Status
#define I2C_O_SMIS              0x00000814  // I2C Slave Masked Interrupt
                                            // Status
#define I2C_O_SICR              0x00000818  // I2C Slave Interrupt Clear
#define I2C_O_SOAR2             0x0000081C  // I2C Slave Own Address 2
#define I2C_O_SACKCTL           0x00000820  // I2C Slave ACK Control
#define I2C_O_FIFODATA          0x00000F00  // I2C FIFO Data
#define I2C_O_FIFOCTL           0x00000F04  // I2C FIFO Control
#define I2C_O_FIFOSTATUS        0x00000F08  // I2C FIFO Status
#define I2C_O_PP                0x00000FC0  // I2C Peripheral Properties
#define I2C_O_PC                0x00000FC4  // I2C Peripheral Configuration

//*****************************************************************************
//
// The following are defines for the bit fields in the I2C_O_MSA register.
//
//*****************************************************************************
#define I2C_MSA_SA_M            0x000000FE  // I2C Slave Address
#define I2C_MSA_RS              0x00000001  // Receive not send
#define I2C_MSA_SA_S            1

#define HWREG(x)                                                              \
        (*((volatile uint32_t *)(x)))        

//#define debug
#define loop_back_enable

void InitI2C0(void);
void I2CSend(uint8_t slave_addr, uint8_t num_of_args, ...);
void I2CSendString(uint32_t slave_addr, char array[]);
uint32_t I2CReceive(uint32_t slave_addr);

#endif /* I2C_H_ */
