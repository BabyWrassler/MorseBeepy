#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>

#define LED_PIN (13)

volatile int f_wdt=1;



/***************************************************
 *  Name:        ISR(WDT_vect)
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Watchdog Interrupt Service. This
 *               is executed when watchdog timed out.
 *
 ***************************************************/
ISR(WDT_vect)
{
  if(f_wdt == 0)
  {
    f_wdt=1;
  }
  else
  {
//    Serial.println("WDT Overrun!!!");
  }
}


/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Enters the arduino into sleep mode.
 *
 ***************************************************/
void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();
  
  /* Now enter sleep mode. */
  sleep_mode();
  
  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */
  
  /* Re-enable the peripherals. */
  power_all_enable();
  /* Disable Analog to Digital Converter to preserve power */
  (ADCSRA &= ~(1<<ADEN));
}

int morseUnit;

void TinyTone(unsigned char divisor, unsigned char octave, unsigned long duration)
{
 // TCCR1 = 0x90 | (8-octave); // for 1MHz clock
  TCCR1 = 0x90 | (11-octave); // for 8MHz clock
  OCR1C = divisor-1;         // set the OCR
  delay(duration);
  TCCR1 = 0x90;              // stop the counter
}

void morseLetterSpace() {
  delay((3 * morseUnit));
}

void morseDot() {
  digitalWrite(0, HIGH);
  TinyTone(239,4,morseUnit);
  digitalWrite(0, LOW);
  delay(morseUnit);
}

void morseDash() {
  digitalWrite(0, HIGH);
  TinyTone(239,4,(3 * morseUnit));
  digitalWrite(0, LOW);
  delay(morseUnit);
}


void morseWordSpace() {
  delay((7 * morseUnit));
}

void morseA() {
  morseDot();
  morseDash();
  morseLetterSpace();
}

void morseB() {
  morseDash();
  morseDot();
  morseDot();
  morseDot();
  morseLetterSpace();
}

void morseC() {
  morseDash();
  morseDot();
  morseDash();
  morseDot();
  morseLetterSpace();
}

void morseD() {
  morseDash();
  morseDot();
  morseDot();
  morseLetterSpace();
}

void morseE() {
  morseDot();
  morseLetterSpace();
}

void morseF() {
  morseDot();
  morseDot();
  morseDash();
  morseDot();
  morseLetterSpace();
}

void morseG() {
  morseDash();
  morseDash();
  morseDot();
  morseLetterSpace();
}

void morseH() {
  morseDot();
  morseDot();
  morseDot();
  morseDot();
  morseLetterSpace();
}

void morseI() {
  morseDot();
  morseDot();
  morseLetterSpace();
}

void morseJ() {
  morseDot();
  morseDash();
  morseDash();
  morseDash();
  morseLetterSpace();
}

void morseK() {
  morseDash();
  morseDot();
  morseDash();
  morseLetterSpace();
}

void morseL() {
  morseDot();
  morseDash();
  morseDot();
  morseDot();
  morseLetterSpace();
}

void morseM() {
  morseDash();
  morseDash();
  morseLetterSpace();
}

void morseN() {
  morseDash();
  morseDot();
  morseLetterSpace();
}

void morseO() {
  morseDash();
  morseDash();
  morseDash();
  morseLetterSpace();
}

void morseP() {
  morseDot();
  morseDash();
  morseDash();
  morseDot();
  morseLetterSpace();
}

void morseQ() {
  morseDash();
  morseDash();
  morseDot();
  morseDash();
  morseLetterSpace();
}

void morseR() {
  morseDot();
  morseDash();
  morseDot();
  morseLetterSpace();
}

void morseS() {
  morseDot();
  morseDot();
  morseDot();
  morseLetterSpace();
}

void morseT() {
  morseDash();
  morseLetterSpace();
}

void morseU() {
  morseDot();
  morseDot();
  morseDash();
  morseLetterSpace();
}

void morseV() {
  morseDot();
  morseDot();
  morseDot();
  morseDash();
  morseLetterSpace();
}

void morseW() {
  morseDot();
  morseDash();
  morseDash();
  morseLetterSpace();
}

void morseX() {
  morseDash();
  morseDot();
  morseDot();
  morseDash();
  morseLetterSpace();
}

void morseY() {
  morseDash();
  morseDot();
  morseDash();
  morseDash();
  morseLetterSpace();
}

void morseZ() {
  morseDash();
  morseDash();
  morseDot();
  morseDot();
}

void setup()
{
  /* Enable output on pins for LED and Piezo Buzzer */
  pinMode(0, OUTPUT);
  pinMode(1, OUTPUT);

  /* Disable Analog to Digital Converter to preserve power */
  (ADCSRA &= ~(1<<ADEN));

  /*** Setup the WDT ***/
  
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  WDTCR = 1<<WDP0 | 1<<WDP3; /* 8.0 seconds */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCR |= _BV(WDIE);

  morseUnit = 200;
}


void loop()
{
  
  if(f_wdt == 1)
  {
    morseC();
    morseO();
    morseD();
    morseY();
//    morseWordSpace();
    
    /* Don't forget to clear the flag. */
    f_wdt = 0;
    
    /* Re-enter sleep mode. */
    enterSleep();
  }
  else
  {
    /* Do nothing. */
  }

}
