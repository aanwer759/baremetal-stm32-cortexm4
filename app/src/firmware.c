
// this is specific to STM32Fxx Cortex m4 MCUs, but concepts should be ok
//this header is provided by libopencm3 for STM32 cortex 

#include <libopencm3/stm32/rcc.h> // configuring system clock
#include <libopencm3/stm32/gpio.h> // to configure GPIO , provided by liopencm3
#include <libopencm3/cm3/systick.h> // to configure systick perapheril
#include <libopencm3/cm3/vector.h> // vector table 



//fucntion to setup rcc clock local(static) to this code file.

static void rcc_setup (void){
    rcc_clock_setup_pll(&rcc_hsi_configs[RCC_CLOCK_3V3_84MHZ]); // this clock setting is provided by libopencm3 
}

static void gpio_setup(void){
    rcc_periph_clock_enable(RCC_GPIOA);
    gpio_mode_setup(GPIOA,GPIO_MODE_OUTPUT,GPIO_PUPD_NONE,GPIO5);
}

volatile unit64_t tick_coont=0; 
// reason we are using 64 bits although architecture is 32 bits is because we want to keep track of time and total number of days we can keep track with 32 bits is 50 days approx.
//for this reason , we are using 64 bit so that we can have a bigger time value available. 
//however this posses a problem that 64 bit additon will take 2 assembly languages, this will cause problem because it is not an atomic operation anymore.
// to overcome this, we can disable interrupt for this particular operation and enable interrupt again

void sys_tick_handler(void){
    ticks++;
}

static void systick_setup(void){
    systick_set_frequency(1000,8400000);
    systick_counter_enable(); 
    // systick notifies main program about "time expiration" as interrupts.
    systick_interrupt_enable();
}

uint64_t get_ticks(void){
    return ticks;
}


int main(){
    rcc_Setup();
    gpio_setup();
    systick_setup();
    uint64_t start_time =get_ticks();
    while (1){
        if (get_ticks() - start_time >= 1000){
            gpio_toggle(GPIOA,GPIO5);
            start_time = get_time();
            }
    }

    //never returned because micro controller is running at Super Loop execution method
    return 0;
}