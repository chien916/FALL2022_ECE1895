#define MASTER true //master flag
#define THRE_LIGH true //three-light flag
#define ITER_COND size_t i = 0; i<sizeof(pinNumbersToIterate) / sizeof(*pinNumbersToIterate);++i
#if THRE_LIGH
    #define PINS_SEQU {8,7,6}
#else
    #define PINS_SEQU {8}
#endif
const uint8_t pinNumbersToIterate[] = PINS_SEQU;
void setup() { for(ITER_COND) pinMode(*(pinNumbersToIterate+i), OUTPUT);}
void loop() {
  for(ITER_COND){
    digitalWrite(*(pinNumbersToIterate+i), MASTER?HIGH:LOW);
    delay(500); 
    digitalWrite(*(pinNumbersToIterate+i), LOW);
    delay(500); 
  }
}