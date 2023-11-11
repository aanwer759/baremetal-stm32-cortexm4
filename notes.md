This is a tutorial series made by Low Byte Production Channel on Youtube.
Link is https://www.youtube.com/watch?v=06ICtJjPKlA&list=PLP29wDx6QmW7HaCrRydOnxcy8QmW0SNdQ&index=1
Github Repo : https://github.com/lowbyteproductions/bare-metal-series.git

Notes for tutorial number 2: Hello World Blinky
Libopencm3  : opensource firmware library that for various Cortex M processors.
link : https://github.com/libopencm3/libopencm3.git

some important files such as linkerscript and Makefile is taken directly from libopencm3 project. other than that, VS code is setup to perform actions such as building firmware, starting debugging on terminal and some other stuff. 

in simple LED Blinking program , we can configure GPIO directly by configuring register attached to it. Before that, its important to configure system clock as well , for that libopencm3 provides libraries and abstraction layers that can be used to perform such operations.

first , we setup clock for system. libopencm3 provides options to setup clock required for MCU. required clock and info can be found on manual for chips.
after configuring clock , we can configure other peripherals to fucntion. by default, all peripherals are in off state in ARM based chips, and to turn them on , we need to provide clock signal so that these peripherals are changed in on state. 



