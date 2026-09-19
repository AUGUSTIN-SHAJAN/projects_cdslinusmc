#include "header/stm32f1xx.h"

// void delay(void)
// {
//     for (volatile unsigned int i = 0; i < 1000000; i++)
//     {
//     }
// }

// int main(void)
// {
//     /* Enable GPIOC clock */
//     RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

//     GPIOC->CRH &= ~(7 << 20);//clear 4 bits 23-20
//     GPIOC->CRH |=  (0x3 << 20);// set 0011 for 23-20

//     while (1)
//     {
//         /* LED ON */
//         GPIOC->ODR &= ~(1 << 13);
//         delay();

//         /* LED OFF */
//         GPIOC->ODR |= (1 << 13);
//         delay();
//     }
// }

int main(void)
    {
        RCC->APB2ENR = 0;
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;//enable clock to port A.
        GPIOA->CRH = 0;
        GPIOA->CRH |= (0b1001 << 4);//pa09 alternate function 10mhz out
        GPIOA->CRH |= (0b0100 << 8);//pa10 input floating pin- uart idle is high so ok if flating

    }