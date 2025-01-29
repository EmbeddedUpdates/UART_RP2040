# UART_RP2040

## OSI formatting
The RP2040 UART peripheral acts as both OSI-Layer-1 and OSI-Layer2. This UART is really a TTL, so the UART peripheral register handles the physical layer as well as the datalink layer.
So this driver would be both layers, so a naming scheme like UART_OSI00-OSI01_RP2040 doesnt make a lot of sense.

Is there a way we can break it up? Just for simplicity or design?
Physical layer interface - writing to registers
datalink layer interface - error checking with physical layer.
Benefit? UART_EU_OSI2 then can be reused with a different physical layer, including a world where the physical layer is bitbang gpio.

So then the Layer-2 implementation is a software layer that interacts with the physical layer driver to actually configure it if needed.
Or - we just call it like it is and say that the UART is both the L1 and L2.

## Let's talk through the split design:
### Advantages of This Separation:
1. Modularity & Reusability:
    1. A dedicated Layer 1 (Physical) driver could handle hardware-specific configurations, baud rate settings, voltage levels, and low-level signal integrity.
    2. A Layer 2 (Data Link) driver could handle UART framing, error detection (parity), and potentially even protocol-specific byte handling.
    3. If you ever switch to a different physical layer (e.g., RS-485 instead of TTL), the Layer 1 driver can be swapped without affecting Layer 2.
2. Abstraction & Maintainability:
    1. Higher layers (Layer 3+) will interact only with the Layer 2 module, keeping the system architecture cleaner and more maintainable.
    2. Layer 1 remains focused on hardware interfacing, avoiding unnecessary protocol logic.
3. Flexibility for Future Enhancements:
    1. If you later need software flow control (e.g., XON/XOFF at Layer 2) or implement multi-drop UART protocols, these can be added cleanly at Layer 2 without modifying low-level hardware handling.

### Possible Implementation Strategy:
1. Layer 1 Driver (Physical, TTL signaling)
    1. Configures UART registers (baud rate, TX/RX pins)
    2. Controls the hardware FIFO
    3. Manages low-level power or clocking requirements
    4. Provides raw byte streams to Layer 2
2. Layer 2 Driver (UART Framing & Data Link)
    1. Implements start/stop bit interpretation
    2. Handles parity checking and error flags
    3. Supports software flow control if needed
    4. Passes valid data frames to Layer 3+

## So what is this?

This is an implementation of the SFR access with helper functions to make those accesses easier. A UART_dl module should act as the 'generic' OSI-L2 for this.
The only user of this module should be UART_dl, unless a manual UART_Transmit() is acceptable for whatever testing is being performed.


# old ramblings
This module would act as an OSI-layer-1 module.

It may be worth renaming this module to something like UART_OSI01_RP2040, this naming scheme describes the following:
1. Its a UART driver
2. Its usecase is on an RP2040 microcontroller based project
3. It's assuming the upper layer is related to an OSI stack, so the data it provides out somewhere else should be related to OSI, or in a common format
If we wanted to do this, we see some quick questions:
1) can OSI model 1 talk to OSI model 2 only? Are there cases where we want to pass the data directly to OSI model 3?
2) How does data get transmitted between layers? How do we mark directions of messages/data
    send_local() vs pass_up() or send_local() vs pass_down().
3) How do we mark the end path of a message, i.e. in this node (from layer 1 to layer 2) or out of this node (from node a (this node) to another node on the physical layer)
    send_local(), vs send_remote()
    UART -> RS232 is transmission, but if the data came from external to this micro, then it's actually received data.
        Autosar indicates this with something like Can_RxMainFunction -> CanIf_RxIndication -> upTp_RxIndication
        In this case, Tx tends to be data going down the stack and out, and Rx tends to be data coming into the module and up the stack.
        Is this distinction relevant?
            What if we want to pass a RS232 frame from one module of code to another? Can it only go from L3 to L3? Can it go from L3 to L1? or From L3->L2->L3?
            What if spi module is reading from ext. flash and needs to read a lot of data. This would be L1 receiving data. We would need to verify and frame the data (L2), and pass this up to the application layer which could actually process the data.
                The application can do whatever it needs to do, but what if we want to send out this data on UART?
            
            
            (1)  ext. read request: UART->RS232->UDS->App code (RX)
            (2)  ext flash read processing: app_code -> memorydriver -> ext.flashdriver -> spi (TX)

            All data processing is taking a request (data) and transforming it into a request (new data) and then doing something with it.
            These two sequences above are inter-related (1) must happen for (2) to be triggered

            So at least, here, I am contradicting myself and saying that (1) is RX, despite the fact that UART is 'transmitting' the data to RS232.
            The conversation changes if we get rid of the app code?
            UART->RS232->UDS->memorydriver->ext.flashdriver->spi (is this still rx, even though we went from one physical layer to another?)
                          ~->UDS TX RCRRP -> RS232 -> UART  (clearly this route is Tx)

            Further, we haven't even considered the fact that there are so many different requirements that each layer here would impose. i.e. UDS requires that the request is given a response in P2 time. At least RCRRP must be transmitted at the UDS layer.
            And what if we want to change the stack later and want to do some gatewaying instead of module specific work?

            UART0 -> RS232 -> UDS -> RS232 -> UART1 -> data was received, and then it was transmitted, it's not just received here.
            So we need to explicitly separate where rx and transmission occur, these are considered in autosar 'paths', and this is more intuitive I think than the other concepts
                So, RX is 'up' or 'in' and Tx is 'down' or 'out' the stack/layers, where redirection occurs, the datapath should change from RX->TX or TX->RX.
                Sometimes data will reach it's end location (phy layers) or 

    To mark a message as having a route, we need to identify who it is, or where it is coming from. some of this is not possible at the physical layer, or just shouldn't be done at the physical layer.
        One possibility is to have a message-router that takes in a message or info of a message and reports the correct path. autosar does this with the PduR (PDU router).

