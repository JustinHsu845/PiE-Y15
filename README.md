# Power Distribution Board
## Pioneers in Engineering Year 2022-2023
---
We are basing our design on the Y9 PDB design. We will use a toggle switch instead of the circuit breaker to power on the device, and a fuse in series with the battery as a safety feature. This is an effort to cut costs.  
  
**To Do:**  
- ~~Find toggle switch and make symbols and footprints~~
    - Use a rocker switch
- ~~Find fuse holders and make symbols and footprints~~
    - ~~Keystone Electronics through hole fuse holders~~ We found smd fuse holders
- ~~Setup staff bot and measure current draw under load to decide on fuse~~
    - 10A should be more than sufficient
    - Power switch more important
- ~~Determine number of ports necessary~~
    - 6 Anderson
    - 4 USB-A connectors (replacing molex)
- Figure out LED circuit (will handle with arduino (Pro Micro))
    - Need 1 green power on LED
        - On whenever power is entering the board.
    - Need 1 green 5v power LED
        - On when 5v power is working
    - ~~Need 1 low battery LED~~ Use Buzzer instead
        - On or flashing when any 1 cell is below 3.5 V (or something)
- Symbols and Footprints
    - Fuse Holder
    - Rocker Switch
    - ~~USB-A connector~~
    - ~~Pro Micro~~
    - Header Pins
    - ~~JST-XH~~
- Test ASAP
    - Main Power Distributor Circuit
    - Arduino LED circuit
    - Arduino Code
    - Make sure to add header pins to measure voltage from JST-XH plug
    - Use jumpers to connect between JST-XH and analog in

    