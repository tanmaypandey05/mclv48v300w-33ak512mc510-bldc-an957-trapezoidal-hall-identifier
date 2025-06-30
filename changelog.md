# mclv48v300w-33ak512mc510-bldc-an957-trapezoidal-hall-identifier v1.0.0
### Release Highlights
This is the first version of code for Hall sensor-based trapezoidal control of BLDC motor with Hall sequence identifier on MCLV-48V-300W board [(EV18H47A)](https://www.microchip.com/en-us/development-tool/ev18h47a) with dsPIC33AK512MC510 MC DIM [EV67N21A](https://www.microchip.com/en-us/development-tool/ev67n21a). 

The code is set up for running the following motors,
- Hurst300 Motor(DMA0204024B101 - [AC300022](https://www.microchip.com/en-us/development-tool/AC300022)) (by default)
- Hurst075 Motor(DMB0224C10002 - [AC300020](https://www.microchip.com/en-us/development-tool/AC300020))
- ACT 57BLF02 [(57BLF02)](https://www.act-motor.com/brushless-dc-motor-57blf-product/) 
- Leadshine Servo Motor [(ELVM6020V24FH-B25-HD)](https://www.leadshine.com/product-detail/ELVM6020V24FH-B25-HD.html)

All the motors are tested under no load conditions. To achieve optimal performance under loaded conditions, the control parameters in the firmware may need additional tuning.

### Features Added\Updated



