# Hardware Design Documentation

## ESP32 GPIO PCB - Hardware Design v1.0

### Overview

The ESP32 GPIO PCB is designed as a compact, reliable GPIO expansion board based on the ESP32-WROOM-32 module. This document describes the hardware architecture, design decisions, and technical specifications.

### Design Goals

- **Expandability**: Provide 16 easily accessible GPIO pins with proper buffering
- **Reliability**: Robust power management and ESD protection
- **Usability**: Clear labeling, status indicators, and user-friendly connectors
- **Compactness**: Fit within 80mm x 60mm PCB footprint
- **Cost-effectiveness**: Use readily available components

### System Architecture

```
USB-C ──→ Power Management ──→ ESP32-WROOM-32 ──→ GPIO Buffers ──→ Expansion Connectors
   │              │                    │                │
   │              └── Status LEDs      └── Programming   └── Level Shifters
   │                                        Interface
   └── Programming Interface
```

### Main Components

#### 1. ESP32-WROOM-32 Module
- **Part Number**: ESP32-WROOM-32
- **Features**: Wi-Fi, Bluetooth, 32-bit dual-core processor
- **Flash Memory**: 4MB
- **RAM**: 520KB SRAM
- **Operating Voltage**: 3.0V - 3.6V
- **Power Consumption**: 
  - Active: ~160-260mA
  - Deep Sleep: 10-150µA

#### 2. Power Management System
- **Input**: USB-C connector, 5V DC jack
- **Primary Regulator**: AMS1117-3.3 (1A, 3.3V output)
- **Backup Power**: Optional battery connector
- **Protection**: Reverse polarity protection, overcurrent protection
- **Power LED**: Green LED indicator

#### 3. GPIO Expansion System
- **Available Pins**: 16 GPIO pins (3.3V logic level)
- **Level Shifters**: 74LVC245 octal transceivers for 5V compatibility
- **Output Current**: 20mA per pin (ESP32 limit)
- **Connectors**: 
  - 2x 10-pin headers (2.54mm pitch)
  - 8x 2-pin screw terminals for high-current applications

#### 4. Status Indicators
- **Power LED** (Green): Indicates 3.3V rail active
- **WiFi LED** (Blue): WiFi activity/connectivity status
- **Activity LED** (Yellow): GPIO activity indicator
- **GPIO LEDs**: Individual LEDs for each GPIO pin (optional)

### Pin Assignments

#### ESP32 GPIO Pin Mapping
```
GPIO Pin | PCB Label | Function        | Notes
---------|-----------|-----------------|----------------------
GPIO2    | D0        | Digital I/O     | Built-in LED
GPIO4    | D1        | Digital I/O     | 
GPIO5    | D2        | Digital I/O     | SPI SS
GPIO12   | D3        | Digital I/O     | SPI MISO
GPIO13   | D4        | Digital I/O     | SPI MOSI
GPIO14   | D5        | Digital I/O     | SPI SCK
GPIO15   | D6        | Digital I/O     | 
GPIO16   | D7        | Digital I/O     | 
GPIO17   | D8        | Digital I/O     | 
GPIO18   | D9        | Digital I/O     | SPI SCK
GPIO19   | D10       | Digital I/O     | SPI MISO
GPIO21   | D11       | Digital I/O     | I2C SDA
GPIO22   | D12       | Digital I/O     | I2C SCL
GPIO23   | D13       | Digital I/O     | SPI MOSI
GPIO25   | D14       | Digital I/O     | DAC1
GPIO26   | D15       | Digital I/O     | DAC2
```

#### Special Function Pins
```
GPIO Pin | Function           | Notes
---------|--------------------|------------------------
GPIO27   | Status LED (Power) | Always HIGH when powered
GPIO32   | Status LED (WiFi)  | WiFi activity indicator
GPIO33   | Status LED (Act.)  | GPIO activity indicator
GPIO0    | Boot/Program       | Programming mode
GPIO1    | UART TX           | Serial debug output
GPIO3    | UART RX           | Serial debug input
EN       | Reset             | Hardware reset
```

### Power Specifications

#### Input Power
- **USB-C**: 5V ± 0.25V, 2A maximum
- **DC Jack**: 5V - 12V DC, 1A maximum
- **Battery**: 3.7V Li-Po (optional, JST-PH connector)

#### Power Consumption
- **Idle (WiFi connected)**: ~80mA @ 3.3V
- **Active (all GPIOs HIGH)**: ~400mA @ 3.3V
- **Deep Sleep**: < 1mA @ 3.3V
- **Maximum Rating**: 1A @ 3.3V (limited by regulator)

### Environmental Specifications

- **Operating Temperature**: -20°C to +70°C
- **Storage Temperature**: -40°C to +85°C
- **Humidity**: 10% to 90% RH (non-condensing)
- **Altitude**: 0 to 2000m

### PCB Specifications

#### Physical Dimensions
- **Length**: 80mm
- **Width**: 60mm
- **Thickness**: 1.6mm (standard PCB)
- **Layers**: 4-layer PCB
- **Finish**: HASL (Hot Air Solder Leveling)

#### Electrical Specifications
- **Impedance**: 50Ω single-ended, 100Ω differential
- **Via Size**: 0.2mm drill, 0.45mm pad
- **Minimum Track Width**: 0.1mm
- **Minimum Via-to-Via**: 0.1mm

### Design Features

#### EMC/EMI Considerations
- **Ground Plane**: Continuous ground plane on layer 2
- **Power Plane**: Dedicated 3.3V plane on layer 3
- **Filtering**: Ferrite beads on power lines
- **Decoupling**: 0.1µF ceramic capacitors near all ICs

#### ESD Protection
- **USB Interface**: TVS diodes on D+/D- lines
- **GPIO Pins**: 330Ω series resistors
- **Power Rails**: Transient voltage suppressors

#### Thermal Management
- **Copper Pour**: Maximum copper coverage for heat dissipation
- **Via Stitching**: Thermal vias under power components
- **Component Spacing**: Adequate spacing for airflow

### Testing and Validation

#### Functional Tests
1. Power-on self-test (POST)
2. GPIO pin functionality test
3. WiFi connectivity test
4. Serial communication test
5. Web interface test

#### Compliance Tests
- **FCC Part 15**: Radio frequency emissions
- **CE Marking**: European conformity
- **RoHS**: Restriction of hazardous substances

### Known Limitations

1. **GPIO Current**: Limited to 20mA per pin (ESP32 specification)
2. **5V Tolerance**: Requires level shifters for 5V devices
3. **Analog Inputs**: Limited ADC resolution (12-bit)
4. **Real-time Performance**: WiFi activity can affect timing-critical applications

### Revision History

| Version | Date       | Changes                              |
|---------|------------|--------------------------------------|
| 1.0     | 2024-01-01 | Initial release                      |

### References

- [ESP32-WROOM-32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)
- [ESP32 Technical Reference Manual](https://www.espressif.com/sites/default/files/documentation/esp32_technical_reference_manual_en.pdf)
- [KiCad Design Files](../hardware/)
- [Firmware Examples](../firmware/)