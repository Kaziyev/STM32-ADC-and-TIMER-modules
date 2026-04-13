// #include <stm32f4xx_ll_bus.h>
// #include <stm32f4xx_ll_gpio.h>
// #include <stm32f4xx_ll_tim.h>

// void tim2_1hz_init(void);
// void led_init(void);

// int main(){
// tim2_1hz_init();
// led_init();
// while(1) {
//     while(!LL_TIM_IsActiveFlag_UPDATE(TIM2)){

//     }
//     LL_TIM_ClearFlag_UPDATE(TIM2);
//     LL_GPIO_TogglePin(GPIOC, LL_GPIO_PIN_13);
// }
// }
// void tim2_1hz_init()
// {
// /* 1. enable clock acces to timer module*/
// LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
// /* 2. Set the prescaler*/
// LL_TIM_SetPrescaler(TIM2, 10000-1);
// /* 3. Set auto-reload value */
// LL_TIM_SetAutoReload(TIM2, 160-1);
// /* 4. enable timer module*/
// LL_TIM_EnableCounter(TIM2);
// }

// void led_init()
// {
// /* 1. enable clock access to GPIO module*/
// LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
// /* 2. set PA5 as an output pin */
// LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_OUTPUT);

// }



// #include "stm32f401xc.h"
// #include <stm32f4xx_ll_bus.h>
// #include <stm32f4xx_ll_gpio.h>
// #include <stm32f4xx_ll_adc.h>
// #include <sys/types.h>

// void adc1_init(void);
// uint32_t volatile sensor_value=0;
// int main () {
// adc1_init();
// while(1){
//     /*start adc conversion*/
//     LL_ADC_REG_StartConversionSWStart(ADC1);
//     /*wait for conversion to be complete*/
//     while(!LL_ADC_IsActiveFlag_EOCS(ADC1)){}
//     /*read converted value*/
//     sensor_value = LL_ADC_REG_ReadConversionData32(ADC1);

// }
// }

// void adc1_init(void)
// {
//     /*Enable clock access to ADC module*/
//     LL_APB2_GRP1_EnableClock( LL_APB2_GRP1_PERIPH_ADC1);
//     /*Enable clock acces to ADC channel port */
//     LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
//     /*Enable adc channel pin mode to analog*/
//     LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG);
//     /*Set adc trigger */
//     LL_ADC_REG_SetTriggerSource(ADC1, LL_ADC_REG_TRIG_SOFTWARE);
//     /*Set sampling sequence */
//     LL_ADC_REG_SetSequencerRanks(ADC1, LL_ADC_REG_RANK_1, LL_ADC_CHANNEL_1);
//     /*Set sequence length*/
//     LL_ADC_REG_SetSequencerLength(ADC1, LL_ADC_REG_SEQ_SCAN_DISABLE);
//     /*Enable ADC*/
//     LL_ADC_Enable(ADC1);
// }

// #include "stm32f401xc.h"
// #include <stm32f4xx_ll_bus.h>
// #include <stm32f4xx_ll_gpio.h>

// int main () {

    
// while(1) {
//     if(LL_GPIO_IsInputPinSet(GPIOC, LL_GPIO_PIN_13)) {
//         LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_5);
//     }
//     else {
//         LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_5);
//     }
// }
// }
// void gpio_interrupt_init(void)
// {
//  LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOC);
//  LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_INPUT);
//  /*Enable clock access to EXTI module*/
//  LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_SYSCFG);
//  /*Set EXTI source*/
//  LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTC, LL_SYSCFG_EXTI_LINE13);
//  /*Enable EXTI line*/
//  LL_EXTI_EnableIT_0_31(LL_EXTI_LINE_13);
//  /*Set the trigger*/
//  LL_EXTI_EnableFallingTrig_0_31(LL_EXTI_LINE_13);
//  /*Enable NVIC interrupt*/
//  NVIC_EnableIRQ()
//  /*Set the interrupt priority*/
//  NVIC_SetPriority()
// }
// void led_init(void)
// {
//     LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
   
//     LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_INPUT);
// }
#include "stm32f401xc.h"
#include <stdint.h>

#include "stm32f4xx_ll_bus.h"
#include "stm32f4xx_ll_gpio.h"
#include "stm32f4xx_ll_tim.h"

static void System_Init(void);
static void Motor_GPIO_Init(void);
static void TIM1_PWM_Init(void);

static void Motor_Forward(void);
static void Motor_Backward(void);
static void Motor_Stop(void);
static void Motor_SetSpeed(uint16_t duty);

int main(void)
{
    System_Init();
    Motor_GPIO_Init();
    TIM1_PWM_Init();


    while (1)
    {
            if (!LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_2))
    {
        Motor_Forward();
        Motor_SetSpeed(1000); 
    }
    else if (!LL_GPIO_IsInputPinSet(GPIOA, LL_GPIO_PIN_3))
    {
        Motor_Backward();
        Motor_SetSpeed(1000); 
    }
    else
    {
        Motor_Stop();
    }
    }
}

static void System_Init(void)
{

    LL_AHB1_GRP1_EnableClock(LL_AHB1_GRP1_PERIPH_GPIOA);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
}

static void Motor_GPIO_Init(void)
{
    
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_0, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_1, LL_GPIO_MODE_OUTPUT);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_INPUT);
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_3, LL_GPIO_MODE_INPUT);


    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_0, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_1, LL_GPIO_OUTPUT_PUSHPULL);
    

    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_0, LL_GPIO_SPEED_FREQ_LOW);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_1, LL_GPIO_SPEED_FREQ_LOW);

    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_0, LL_GPIO_PULL_NO);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_1, LL_GPIO_PULL_NO);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_2, LL_GPIO_PULL_UP);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_3, LL_GPIO_PULL_UP);

  
    LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_9, LL_GPIO_MODE_ALTERNATE);
    LL_GPIO_SetAFPin_8_15(GPIOA, LL_GPIO_PIN_9, LL_GPIO_AF_1);
    LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_9, LL_GPIO_OUTPUT_PUSHPULL);
    LL_GPIO_SetPinSpeed(GPIOA, LL_GPIO_PIN_9, LL_GPIO_SPEED_FREQ_HIGH);
    LL_GPIO_SetPinPull(GPIOA, LL_GPIO_PIN_9, LL_GPIO_PULL_NO);
}

static void TIM1_PWM_Init(void)
{

    LL_TIM_SetPrescaler(TIM1, 83);
    LL_TIM_SetAutoReload(TIM1, 999);

    
    LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);
    LL_TIM_OC_SetPolarity(TIM1, LL_TIM_CHANNEL_CH2, LL_TIM_OCPOLARITY_HIGH);
    LL_TIM_OC_SetCompareCH2(TIM1, 0);

    LL_TIM_CC_EnableChannel(TIM1, LL_TIM_CHANNEL_CH2);
    LL_TIM_EnableARRPreload(TIM1);

    
    LL_TIM_EnableAllOutputs(TIM1);
    LL_TIM_EnableCounter(TIM1);
    LL_TIM_GenerateEvent_UPDATE(TIM1);
}

static void Motor_SetSpeed(uint16_t duty)
{
    if (duty > 999)
    {
        duty = 999;
    }

    LL_TIM_OC_SetCompareCH2(TIM1, duty);
}

static void Motor_Forward(void)
{
    LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_0);
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_1);
}

static void Motor_Backward(void)
{
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
    LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_1);
}

static void Motor_Stop(void)
{
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_0);
    LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_1);
    Motor_SetSpeed(0);
}


