This is a tutorial series made by Low Byte Production Channel on Youtube.
Link is https://www.youtube.com/watch?v=06ICtJjPKlA&list=PLP29wDx6QmW7HaCrRydOnxcy8QmW0SNdQ&index=1

Notes for tutorial number 2: Hello World Blinky
Libopencm3  : opensource firmware library that for various Cortex M processors.
link : https://github.com/libopencm3/libopencm3.git

some important files such as linkerscript and Makefile is taken directly from libopencm3 project. other than that, VS code is setup to perform actions such as building firmware, starting debugging on terminal and some other stuff. 

in simple LED Blinking program , we can configure GPIO directly by configuring register attached to it. Before that, its important to configure system clock as well , for that libopencm3 provides libraries and abstraction layers that can be used to perform such operations.

first , we setup clock for system. libopencm3 provides options to setup clock required for MCU. required clock and info can be found on manual for chips.
after configuring clock , we can configure other peripherals to fucntion. by default, all peripherals are in off state in ARM based chips, and to turn them on , we need to provide clock signal so that these peripherals are changed in on state. 


interrupts and memory mapped IOs

in previous blinking example, we used inline assembly to wait for 1 sec by using "nop". This is not an ideal way to deal with these type situations as it will cause system to essentially hault completely. To make it more better, we can use peripherals. peripherals are technically hardware that can perform work independently. so one way to make system aware of passing certain amount of time would be by using systick peripheral.

memory mapped IO means that we are talking or communication with different peripherals on system which are connected to CPU through communication buses. This communication is done by using addresses of hardware. These addresses are similar to memory addresses and these addresses kind of talk to registers of IO

all system interrupt ticks are defined in vector file in libopencm3. These interrupts are very specific in terms of implementation as these are part of ARM Cortex implementation.

to keep track of interrupt, we can make a uint64_t type tick variable that can keep track of number of ticks. 
// reason we are using 64 bits although architecture is 32 bits is because we want to keep track of time and total number of days we can keep track with 32 bits is 50 days approx.
//for this reason , we are using 64 bit so that we can have a bigger time value available.  1000+ years
//however this posses a problem that 64 bit additon will take 2 assembly languages, this will cause problem because it is not an atomic operation anymore.
// to overcome this, we can disable interrupt for this particular operation and enable interrupt again
