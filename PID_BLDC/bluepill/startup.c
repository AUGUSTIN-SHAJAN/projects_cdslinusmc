#include <stdint.h>

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;

extern int main(void);
void Reset_Handler(void);

extern void Default_Handler(void);

extern void EXTI0_IRQHandler(void);
extern void EXTI1_IRQHandler(void);
extern void EXTI2_IRQHandler(void);
extern void EXTI3_IRQHandler(void);
extern void EXTI4_IRQHandler(void);
extern void EXTI9_5_IRQHandler(void);
extern void EXTI15_10_IRQHandler(void);

extern void USART1_IRQHandler(void);
extern void USART2_IRQHandler(void);
extern void USART3_IRQHandler(void);
extern void UART4_IRQHandler(void);
extern void UART5_IRQHandler(void);

extern void USB_HP_CAN1_TX_IRQHandler(void);
extern void USB_LP_CAN1_RX0_IRQHandler(void);
extern void USBWakeUp_IRQHandler(void);

__attribute__((section(".isr_vector")))
const uint32_t vector_table[] =
{
    (uint32_t)&_estack,
    (uint32_t)Reset_Handler,

    (uint32_t)Default_Handler,  // NMI
    (uint32_t)Default_Handler,  // HardFault
    (uint32_t)Default_Handler,  // MemManage
    (uint32_t)Default_Handler,  // BusFault
    (uint32_t)Default_Handler,  // UsageFault

    0,
    0,
    0,
    0,

    (uint32_t)Default_Handler,  // SVC
    (uint32_t)Default_Handler,  // DebugMon

    0,

    (uint32_t)Default_Handler,  // PendSV
    (uint32_t)Default_Handler,  // SysTick

    (uint32_t)Default_Handler,  // WWDG
    (uint32_t)Default_Handler,  // PVD
    (uint32_t)Default_Handler,  // TAMPER
    (uint32_t)Default_Handler,  // RTC
    (uint32_t)Default_Handler,  // FLASH
    (uint32_t)Default_Handler,  // RCC

    (uint32_t)EXTI0_IRQHandler,
    (uint32_t)EXTI1_IRQHandler,
    (uint32_t)EXTI2_IRQHandler,
    (uint32_t)EXTI3_IRQHandler,
    (uint32_t)EXTI4_IRQHandler,

    (uint32_t)Default_Handler,  // DMA1_Channel1
    (uint32_t)Default_Handler,  // DMA1_Channel2
    (uint32_t)Default_Handler,  // DMA1_Channel3
    (uint32_t)Default_Handler,  // DMA1_Channel4
    (uint32_t)Default_Handler,  // DMA1_Channel5
    (uint32_t)Default_Handler,  // DMA1_Channel6
    (uint32_t)Default_Handler,  // DMA1_Channel7
    (uint32_t)Default_Handler,  // ADC1_2

    (uint32_t)USB_HP_CAN1_TX_IRQHandler,
    (uint32_t)USB_LP_CAN1_RX0_IRQHandler,

    (uint32_t)Default_Handler,  // CAN1_RX1
    (uint32_t)Default_Handler,  // CAN1_SCE

    (uint32_t)EXTI9_5_IRQHandler,

    (uint32_t)Default_Handler,  // TIM1_BRK
    (uint32_t)Default_Handler,  // TIM1_UP
    (uint32_t)Default_Handler,  // TIM1_TRG_COM
    (uint32_t)Default_Handler,  // TIM1_CC
    (uint32_t)Default_Handler,  // TIM2
    (uint32_t)Default_Handler,  // TIM3
    (uint32_t)Default_Handler,  // TIM4
    (uint32_t)Default_Handler,  // I2C1_EV
    (uint32_t)Default_Handler,  // I2C1_ER
    (uint32_t)Default_Handler,  // I2C2_EV
    (uint32_t)Default_Handler,  // I2C2_ER
    (uint32_t)Default_Handler,  // SPI1
    (uint32_t)Default_Handler,  // SPI2

    (uint32_t)USART1_IRQHandler,
    (uint32_t)USART2_IRQHandler,
    (uint32_t)USART3_IRQHandler,

    (uint32_t)EXTI15_10_IRQHandler,

    (uint32_t)Default_Handler,  // RTCAlarm
    (uint32_t)USBWakeUp_IRQHandler,

    (uint32_t)Default_Handler,  // TIM8_BRK
    (uint32_t)Default_Handler,  // TIM8_UP
    (uint32_t)Default_Handler,  // TIM8_TRG_COM
    (uint32_t)Default_Handler,  // TIM8_CC
    (uint32_t)Default_Handler,  // ADC3
    (uint32_t)Default_Handler,  // FSMC
    (uint32_t)Default_Handler,  // SDIO
    (uint32_t)Default_Handler,  // TIM5
    (uint32_t)Default_Handler,  // SPI3

    (uint32_t)UART4_IRQHandler,
    (uint32_t)UART5_IRQHandler,

    (uint32_t)Default_Handler,  // TIM6
    (uint32_t)Default_Handler,  // TIM7
    (uint32_t)Default_Handler,  // DMA2_Channel1
    (uint32_t)Default_Handler,  // DMA2_Channel2
    (uint32_t)Default_Handler,  // DMA2_Channel3
    (uint32_t)Default_Handler   // DMA2_Channel4_5
};
void Reset_Handler(void)
{
    uint32_t *RAM_DATA_START = &_sdata;
    uint32_t *RAM__DATA_END = &_edata;
    uint32_t *RAM_BSS_START = &_sbss;
    uint32_t *RAM_BSS_END = &_ebss;
    uint32_t *FLASH_DATA_START = &_sidata;
    while (RAM_DATA_START < RAM__DATA_END)
    {
        *RAM_DATA_START++ = *FLASH_DATA_START++;
    }
    while (RAM_BSS_START < RAM_BSS_END) 
    {
        *RAM_BSS_START++ = 0;
    }
    while(1);
    //reset through hardware;
}