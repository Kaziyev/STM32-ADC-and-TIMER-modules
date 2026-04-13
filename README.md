# Подключение библиотек 
``` C#
#include "stm32f401xc.h"
#include <stm32f4xx_ll_bus.h>
#include <stm32f4xx_ll_gpio.h>
#include <stm32f4xx_ll_adc.h>
```
 
 ### Инициализация функций таймер
 ``` C#
 void tim2_1hz_init(void);
 ```

 У нас существует Timers and Counters
 Timers
 1. Внутреннего Источника тактирование
Counters 
1. Внешнего источника тактирования 
    1. Такт подается на ЦПУ
   
### Timer Register
**Timer Count Register** (TIMx_CNT)
Отображает текущее значение счетчика

**Time Auto-Reload Register** (TIMx_ARR) если счетчик дошел до определенного до флага то оно сбрасывается

**Timer Prescaler Register**
(TIMx_PSC) делитель который замедляет скорость таймера деля его входное тактирование таймера

 ``` C#
 void tim2_1hz_init()
 {
 /* 1. enable clock acces to timer module*/
 LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
 /* 2. Set the prescaler*/
 LL_TIM_SetPrescaler(TIM2, 10000-1); /*это предделитель */
 /* 3. Set auto-reload value */
 LL_TIM_SetAutoReload(TIM2, 160-1);
 /* 4. enable timer module*/
 LL_TIM_EnableCounter(TIM2);
 }
 ```