#include "stm32f10x.h"
#include "system_stm32f10x.h"
#include "core_cm3.h"

static void dummySleep(uint32_t cnt)
{
    uint32_t i;
    for(i = 0; i < cnt; i++)
        __NOP();
}

static void setupUSART()
{
    RCC->APB2ENR  |=  RCC_APB2ENR_IOPAEN;   //Enable port A clock
    RCC->APB2RSTR |=  RCC_APB2RSTR_IOPARST; //Reset port A
    RCC->APB2RSTR &= ~RCC_APB2RSTR_IOPARST;

    RCC->APB2ENR  |=  RCC_APB2ENR_USART1EN;   //Enable USART1 clock
    RCC->APB2RSTR |=  RCC_APB2RSTR_USART1RST; //Reset USART1
    RCC->APB2RSTR &= ~RCC_APB2RSTR_USART1RST;

    //Configure USART
    USART1->CR1 &= ~USART_CR1_UE;
    USART1->CR1  = USART_CR1_TE | USART_CR1_RE;
    USART1->CR2  = 0;
    USART1->CR3  = 0;
    USART1->BRR  = 0x271; //115200 bauds for 72 MHz
    USART1->GTPR = 1;

    //Configure pins & enable USART
    GPIOA->CRH = (GPIOA->CRH & ~(GPIO_CRH_CNF9 | GPIO_CRH_MODE9)) | GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0;
    USART1->CR1 |= USART_CR1_UE;
}

static void writeUSART(const char *str)
{
    while(*str != 0) {
        while((USART1->SR & USART_SR_TXE) == 0);
        USART1->DR = (uint8_t) *str;
        str++;
    }
}

static void setupLED()
{
    RCC->APB2ENR  |= RCC_APB2ENR_IOPCEN;   //Enable port C clock
    RCC->APB2RSTR |= RCC_APB2RSTR_IOPCRST; //Reset port C
    RCC->APB2RSTR &= ~RCC_APB2RSTR_IOPCRST;

    GPIOC->CRH = (GPIOC->CRH & ~GPIO_CRH_CNF13) | GPIO_CRH_MODE13_1; //Output 2 MHz
}

static int keepGoing()
{
    //This is just to prevent CLion from crying about infinite loops
    return 1;
}

void main()
{
    //Called by startup.s

    SystemInit(); //Initialize clock to 72 MHz
    setupUSART(); //Initialize USART to 115200 bauds
    setupLED();

    while(keepGoing()) {
        //Blink
        GPIOC->ODR ^= GPIO_ODR_ODR13;
        writeUSART("It works!\r\n");
        dummySleep(500000U);
    }
}

