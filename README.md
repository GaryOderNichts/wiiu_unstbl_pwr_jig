# Wii U UNSTBL_PWR Jig
Uses a Raspberry Pi Pico to trigger UNSTBL_PWR on a Wii U. The signal is output on GPIOs 13 - 15.  
This is a bit over-engineered using PIO to not do timings on the CPU, but the timings should hopefully be somewhat accurate.
