#include "chardefs.h"

void configure_peripherals();
void run_video_loop();

int main(void) {
    // Init video related peripherals, etc.
    configure_peripherals();

    // Run main video display loop
    run_video_loop();
}
