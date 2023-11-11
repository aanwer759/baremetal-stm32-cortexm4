
// this is specific to STM32Fxx Cortex m4 MCUs, but concepts should be ok
//this header is provided by libopencm3 for STM32 cortex 

#include <libopencm3/stm32/rcc.h> // configuring system clock
#include <libopencm3/stm32/gpio.h> // to configure GPIO , provided by liopencm3



//fucntion to setup rcc clock local(static) to this code file.

static void rcc_setup (void){
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]); // this clock setting is provided by libopencm3 
}

static void gpio_setup(void){
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO5);
}

void time_delay(uint32_t ncycle){
    for (inr i=0;i <ncycle;i++){
        __asm__ ("nop");  // since we are waiting for time delay , therefore, compiler will remove this because essentially no operation is happening, to stop compiler from doing that,
                            // we can add inline assembly.
    }
}

int main(){
    rcc_Setup();
    gpio_setup();
    while (1){
        gpio_toggle(GPIOA,GPIO5);
        time_delay(25146);
        gpio_toggle(GPIOA,GPIO5);
        time_delay(12548);
    }

    //never returned because micro controller is running at Super Loop execution method
    return 0;
}