#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "jig.pio.h"

// duration of a single pattern cycle
#define CYCLE_DURATION 0.01557f

// output to GPIO 13-15
#define PIN_BASE 13
#define PIN_COUNT 3

uint32_t jig_set_delay(PIO pio, uint sm, float base, uint32_t cycles) {
    // PIO code takes 4 more cycles for n+1, pull, out and jmp
    pio_sm_put_blocking(pio, sm, (base * cycles) - 4);
}

int main() {
    // load program
    PIO pio = pio0;
    uint sm = pio_claim_unused_sm(pio, true);
    uint offset = pio_add_program(pio, &jig_program);

    // init program, will wait for fifo
    jig_program_init(pio, sm, offset, PIN_BASE, PIN_COUNT, PICO_DEFAULT_LED_PIN);

    const float base = (float)clock_get_hz(clk_sys) * CYCLE_DURATION;

    while (1) {
        // do this pattern twice
        for (int i = 0; i < 2; i++) {
            jig_set_delay(pio, sm, base, 1);
            jig_set_delay(pio, sm, base, 1);
            jig_set_delay(pio, sm, base, 2);
            jig_set_delay(pio, sm, base, 3);
            jig_set_delay(pio, sm, base, 2);
            jig_set_delay(pio, sm, base, 1);
            jig_set_delay(pio, sm, base, 1);
            jig_set_delay(pio, sm, base, 6);
        }

        // wait a bit before repeating
        sleep_ms(1 * 1000);
    }
}
