#ifndef MAIN_H
#define MAIN_H

static void setup(void);
static void loop(void);

static __IO uint32_t TimingDelay;

void Delay(uint32_t nTime) {
  TimingDelay = nTime;
  while(TimingDelay != 0);
}

void SysTick_Handler(void) {
  if (TimingDelay != 0x00)
    TimingDelay--;
}

/*
 * Debug help -- if asserts are enabled, assertion failure
 * from standard peripheral library ends up here
 */
#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1) {}
}
#endif

int main(void)
{
  if (SysTick_Config(SystemCoreClock / 1000)) {
    /* Capture error */
    while (1);
  }

  setup();
  loop();

  return 0;
}

#endif /* MAIN_H */
