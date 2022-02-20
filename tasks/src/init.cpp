// needed by scheduler
long int ts_systime() {
    return (long int)HAL_GetTick();
}

// this is the entry point of the program after STM32 autogenerated initializations are complete
// NOTE: init should not return
void init() {
    while(1) {};
}
