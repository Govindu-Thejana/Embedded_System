#include <xc.inc>

; Configuration Word
CONFIG  FOSC = XT        ; Oscillator Selection bits (XT oscillator)
CONFIG  WDTE = OFF       ; Watchdog Timer Enable bit (WDT disabled)
CONFIG  PWRTE = ON       ; Power-up Timer Enable bit (PWRT enabled)
CONFIG  CP = OFF         ; Code Protection bit (Code protection disabled)

; Variable declarations
PSECT udata_bank0
COUNTER:    DS      1    ; Counter variable
DELAY_VAR1: DS      1    ; Delay variable 1
DELAY_VAR2: DS      1    ; Delay variable 2

; Reset Vector
PSECT resetVec,class=CODE,delta=2
resetVec:
    GOTO    START

; Main program
PSECT code,class=CODE,delta=2
START:
    ; Initialize ports
    BANKSEL TRISB       ; Select bank containing TRISB
    CLRF    TRISB       ; Set all PORTB pins as outputs
    BANKSEL PORTB       ; Select bank containing PORTB
    
    CLRF    COUNTER     ; Initialize counter to 0

MAIN_LOOP:
    MOVF    COUNTER,W   ; Move counter value to W
    ANDLW   0x0F        ; Ensure only lower 4 bits are used
    MOVWF   PORTB       ; Output to PORTB (connected to 74LS42)
    
    ; Delay routine
    CALL    DELAY
    
    ; Increment counter
    INCF    COUNTER,F   ; Increment counter
    MOVLW   10          ; Load literal 10
    SUBWF   COUNTER,W   ; Check if counter = 10
    BTFSC   STATUS,2    ; Check Zero flag (bit 2 of STATUS register)
    CLRF    COUNTER     ; Reset counter to 0
    
    GOTO    MAIN_LOOP

DELAY:
    MOVLW   255
    MOVWF   DELAY_VAR1
DELAY_LOOP1:
    MOVLW   255
    MOVWF   DELAY_VAR2
DELAY_LOOP2:
    DECFSZ  DELAY_VAR2,F
    GOTO    DELAY_LOOP2
    DECFSZ  DELAY_VAR1,F
    GOTO    DELAY_LOOP1
    RETURN

    END     resetVec