; LED Blinking Program for PIC16F84A
#include <xc.inc>

; Configuration bits
CONFIG  FOSC = XT        ; Oscillator Selection bits (XT oscillator)
CONFIG  WDTE = OFF       ; Watchdog Timer (WDT disabled)
CONFIG  PWRTE = ON       ; Power-up Timer Enable bit (Power-up Timer is enabled)
CONFIG  CP = OFF         ; Code Protection bit (Code protection disabled)

; Variable definitions
PSECT udata_bank0
counter1:  DS 1    ; Reserve 1 byte for counter1
counter2:  DS 1    ; Reserve 1 byte for counter2

PSECT resetVec,class=CODE,delta=2
resetVec:
    GOTO    START

PSECT code
START:
    ; Configure PORTA
    BANKSEL TRISA       ; Select bank 1
    MOVLW   0xFC        ; Set RA0 and RA1 as outputs (0 = output)
    MOVWF   TRISA       ; Configure PORTA direction
    BANKSEL PORTA       ; Select bank 0

MAIN_LOOP:
    ; Turn on LED1 (RA0) and turn off LED2 (RA1)
    MOVLW   0x01
    MOVWF   PORTA
    CALL    DELAY       ; Call delay subroutine

    ; Turn off LED1 (RA0) and turn on LED2 (RA1)
    MOVLW   0x02
    MOVWF   PORTA
    CALL    DELAY       ; Call delay subroutine
    GOTO    MAIN_LOOP   ; Repeat forever

; Delay subroutine
DELAY:
    MOVLW   0xFF
    MOVWF   counter1
DELAY_LOOP1:
    MOVLW   0xFF
    MOVWF   counter2
DELAY_LOOP2:
    DECFSZ  counter2,1
    GOTO    DELAY_LOOP2
    DECFSZ  counter1,1
    GOTO    DELAY_LOOP1
    RETURN

    END resetVec        ; End of program


