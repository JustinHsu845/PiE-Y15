# Power Distribution Board
## Pioneers in Engineering Year 2022-2023
---
We are basing our design on the Y9 PDB design. We will use a toggle switch instead of the circuit breaker to power on the device, and a fuse in series with the battery as a safety feature. This is an effort to cut costs.  
  
**To Do:**  
- Find toggle switch and make symbols and footprints
- Find fuse pads and make symbols and footprints
- Setup staff bot and measure current draw under load to decide on fuse
- Determine number of ports necessary
- Figure out LED circuit
    - Need 1 green power on LED
        - On whenever power is entering the board.
    - Need 1 green 5v power LED
        - On when 5v power is working
    - Need 1 low battery LED
        - On when battery is below 11V (ask around)
