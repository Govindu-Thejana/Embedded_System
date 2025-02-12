LIST P=16F84A
    #include <P16F84A.INC>
    
    ; Configuration bits
    __CONFIG _FOSC_XT & _WDTE_OFF & _PWRTE_ON & _CP_OFF
    
    ; Variable definitions
    CBLOCK 0x0C
        delay_count1
        delay_count2
    ENDC
    
    ; Reset vector
    ORG 0x00
    goto Start
    
    ; Interrupt vector
    ORG 0x04
    retfie
    
    ; Main program
    Start
        BSF STATUS, RP0      ; Select Bank 1
        CLRF TRISA          ; Set all PORTA pins as outputs
        BCF STATUS, RP0      ; Select Bank 0
        
    Main_Loop
        ; Turn on both LEDs
        BSF PORTA, 0        ; Turn on LED1 (RA0)
        BSF PORTA, 1        ; Turn on LED2 (RA1)
        CALL Delay          ; Wait
        
        ; Turn off both LEDs
        BCF PORTA, 0        ; Turn off LED1 (RA0)
        BCF PORTA, 1        ; Turn off LED2 (RA1)
        CALL Delay          ; Wait
        
        GOTO Main_Loop      ; Repeat forever
        
    ; Delay subroutine
    Delay
        MOVLW   d'255'
        MOVWF   delay_count1
    Delay_Loop1
        MOVLW   d'255'
        MOVWF   delay_count2
    Delay_Loop2
        DECFSZ  delay_count2, F
        GOTO    Delay_Loop2
        DECFSZ  delay_count1, F
        GOTO    Delay_Loop1
        RETURN
        
        END