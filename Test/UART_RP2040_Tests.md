# tests for the uart_rp2040 module

## Should this be object oriented?
I may need multiple UART ports on the same device.
In the case of using a different DL layer, i.e. y

## Test setup
Abstraction for register access, type definition, sfr helper generation
debug printout for the UART registers (can be reused from Timer_RP2040:printTimerLive())

## Public interfaces
### INIT()
### TRANSMIT()
### RECEIVE()
### DEINIT()


## Private Interfaces
