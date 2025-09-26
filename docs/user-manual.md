# User Manual

## ESP32 GPIO PCB - User Manual v1.0

### Quick Start Guide

#### What's in the Box
- 1x ESP32 GPIO PCB (assembled)
- 1x USB-C Cable
- 1x Quick Reference Card
- 1x Safety Information Sheet

#### First Power-On
1. **Connect Power**: Use USB-C cable or 5-12V DC adapter
2. **Check Status**: Green power LED should illuminate
3. **Connect to WiFi**: Look for "ESP32_GPIO_PCB" network
   - Password: `gpio123456`
   - Web interface: `http://192.168.4.1`

### Hardware Overview

#### Physical Dimensions
- **Size**: 80mm × 60mm × 1.6mm
- **Weight**: ~45g (including connectors)
- **Mounting**: 4x M3 mounting holes

#### Connectors and Interfaces

##### Power Input
- **USB-C (J1)**: 5V, 2A maximum
- **DC Jack (J2)**: 5-12V DC, 1A maximum
- **Polarity**: Center positive for DC jack

##### GPIO Expansion
- **Headers (J3-J4)**: 2x 10-pin, 2.54mm pitch
- **Screw Terminals (J5-J12)**: 8x 2-pin, 5mm pitch
- **Logic Levels**: 3.3V (5V tolerant with level shifters)

##### Programming Interface
- **USB-C**: Automatic programming mode detection
- **UART**: TX/RX available on header pins
- **Reset**: Hardware reset button (SW1)

#### Status Indicators

| LED Color | Label    | Indication |
|-----------|----------|------------|
| Green     | PWR      | 3.3V power present |
| Blue      | WiFi     | WiFi activity/connection |
| Yellow    | ACT      | GPIO activity |
| Red       | D0-D15   | Individual GPIO states |

### Pin Assignment Reference

#### GPIO Pin Mapping
```
PCB Label | ESP32 Pin | Function          | Notes
----------|-----------|-------------------|------------------
D0        | GPIO2     | Digital I/O       | Built-in LED
D1        | GPIO4     | Digital I/O       | 
D2        | GPIO5     | Digital I/O       | SPI SS (optional)
D3        | GPIO12    | Digital I/O       | SPI MISO (optional)
D4        | GPIO13    | Digital I/O       | SPI MOSI (optional)
D5        | GPIO14    | Digital I/O       | SPI SCK (optional)
D6        | GPIO15    | Digital I/O       | 
D7        | GPIO16    | Digital I/O       | 
D8        | GPIO17    | Digital I/O       | 
D9        | GPIO18    | Digital I/O       | SPI SCK (alt)
D10       | GPIO19    | Digital I/O       | SPI MISO (alt)
D11       | GPIO21    | Digital I/O       | I2C SDA (optional)
D12       | GPIO22    | Digital I/O       | I2C SCL (optional)
D13       | GPIO23    | Digital I/O       | SPI MOSI (alt)
D14       | GPIO25    | Digital I/O / DAC | DAC output 1
D15       | GPIO26    | Digital I/O / DAC | DAC output 2
```

#### Special Pins (Not on expansion headers)
```
Pin       | Function        | Notes
----------|-----------------|---------------------------
GPIO0     | Boot/Program    | Pull LOW for programming
GPIO1     | UART TX         | Serial debug output
GPIO3     | UART RX         | Serial debug input
GPIO27    | Status LED      | Power indicator
GPIO32    | Status LED      | WiFi indicator  
GPIO33    | Status LED      | Activity indicator
EN        | Reset           | Hardware reset (active LOW)
```

### Software Setup

#### Arduino IDE Setup
1. **Install ESP32 Board Package**:
   - File → Preferences
   - Add to Additional Board Manager URLs:
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_dev_index.json
     ```
   - Tools → Board → Boards Manager
   - Search "ESP32" and install "esp32 by Espressif Systems"

2. **Board Configuration**:
   - Board: "ESP32 Dev Module"
   - Upload Speed: 921600
   - CPU Frequency: 240MHz
   - Flash Frequency: 80MHz
   - Flash Mode: QIO
   - Flash Size: 4MB
   - Partition Scheme: Default 4MB
   - Port: Select appropriate COM/USB port

3. **Required Libraries**:
   ```
   ArduinoJson (by Benoit Blanchon)
   ```

#### Programming the Board
1. **Connect USB-C cable** to computer
2. **Select correct board and port** in Arduino IDE
3. **Upload sketch** - board automatically enters programming mode
4. **Monitor Serial output** at 115200 baud

### Web Interface

#### Accessing the Interface
1. **Power on** the ESP32 GPIO PCB
2. **Connect** to "ESP32_GPIO_PCB" WiFi network
3. **Open browser** and navigate to `http://192.168.4.1`

#### Web Interface Features
- **Real-time GPIO control**: Toggle individual pins ON/OFF
- **Status monitoring**: View current state of all pins
- **Bulk operations**: Reset all pins, refresh status
- **Visual feedback**: Color-coded pin status display

### Serial Command Interface

Connect via USB-C at 115200 baud for command-line control:

#### Available Commands
```
SET <pin> <state>    Set GPIO pin state
                     pin: 0-15, state: 0 (LOW) or 1 (HIGH)
                     Example: SET 5 1

GET <pin>           Get GPIO pin state
                     Example: GET 5

STATUS              Show all GPIO states

RESET               Reset all GPIOs to LOW
```

#### Example Session
```
ESP32 GPIO PCB - Initializing...
System ready!

> SET 0 1
GPIO 0 set to HIGH

> GET 0  
GPIO 0 state: HIGH

> STATUS
GPIO Status:
  GPIO  0 (Pin  2): HIGH
  GPIO  1 (Pin  4): LOW
  ...

> RESET
All GPIOs reset to LOW
```

### Application Examples

#### Example 1: LED Control
```arduino
// Turn on LED connected to D0
digitalWrite(2, HIGH);  // GPIO2 = D0

// Blink pattern on multiple pins
int pins[] = {2, 4, 5, 12};
for(int i = 0; i < 4; i++) {
  digitalWrite(pins[i], HIGH);
  delay(250);
  digitalWrite(pins[i], LOW);
}
```

#### Example 2: Relay Control
```arduino
// Control 8 relays connected to D0-D7
for(int relay = 0; relay < 8; relay++) {
  digitalWrite(GPIO_PINS[relay], HIGH);
  delay(1000);
  digitalWrite(GPIO_PINS[relay], LOW);
}
```

#### Example 3: Sensor Reading (Analog)
```arduino
// Read analog sensor on GPIO25 (D14)
int sensorValue = analogRead(25);
float voltage = sensorValue * (3.3 / 4095.0);
Serial.printf("Sensor: %d, Voltage: %.2fV\n", sensorValue, voltage);
```

### Power Management

#### Power Consumption
- **Idle (WiFi connected)**: ~80mA @ 3.3V
- **All GPIOs active**: ~400mA @ 3.3V
- **Deep sleep mode**: <1mA @ 3.3V

#### Power Sources
1. **USB-C**: Recommended for development and low-power applications
2. **DC Jack**: Use for higher current requirements or permanent installation
3. **Both connected**: Automatic switching, USB takes priority

#### Power Budget per GPIO
- **Maximum current per pin**: 20mA (ESP32 limitation)
- **Total GPIO current**: 200mA maximum recommended
- **For high-current loads**: Use external drivers/relays

### Troubleshooting

#### Power Issues
| Problem | Symptoms | Solution |
|---------|----------|----------|
| No power LED | Board appears dead | Check power source, try different cable |
| Brown-out reset | Frequent reboots | Reduce load, check power supply capacity |
| Overheating | Hot regulator | Reduce current draw, improve cooling |

#### Programming Issues
| Problem | Symptoms | Solution |
|---------|----------|----------|
| Upload failed | "Failed to connect" error | Press reset during upload, check USB cable |
| Wrong board | Compilation errors | Select "ESP32 Dev Module" in Arduino IDE |
| Port not found | No COM port visible | Install USB-to-serial drivers |

#### GPIO Issues
| Problem | Symptoms | Solution |
|---------|----------|----------|
| Pin not responding | No output change | Check connections, verify pin assignment |
| Weak output | Insufficient drive current | Add buffer/driver circuit |
| Input not reading | Always reads same value | Check pull-up/down resistors |

#### WiFi Issues
| Problem | Symptoms | Solution |
|---------|----------|----------|
| AP not visible | Cannot find network | Check antenna, reset board |
| Cannot connect | Connection timeout | Verify password, check signal strength |
| Web page not loading | Browser error | Check IP address (192.168.4.1) |

### Specifications

#### Electrical Characteristics
| Parameter | Min | Typ | Max | Unit | Conditions |
|-----------|-----|-----|-----|------|------------|
| Supply Voltage (USB) | 4.5 | 5.0 | 5.5 | V | USB-C input |
| Supply Voltage (DC) | 5.0 | 9.0 | 12.0 | V | DC jack input |
| Supply Current | 50 | 80 | 500 | mA | Typical operation |
| GPIO Output High | 2.4 | 3.0 | 3.3 | V | IOH = -8mA |
| GPIO Output Low | 0 | 0.1 | 0.4 | V | IOL = 8mA |
| GPIO Input High | 2.0 | - | 3.6 | V | |
| GPIO Input Low | -0.3 | - | 0.8 | V | |

#### Environmental Specifications
| Parameter | Min | Max | Unit |
|-----------|-----|-----|------|
| Operating Temperature | -20 | +70 | °C |
| Storage Temperature | -40 | +85 | °C |
| Humidity (non-condensing) | 10 | 90 | %RH |
| Altitude | 0 | 2000 | m |

### Compliance and Certifications

- **FCC Part 15**: Radio frequency emissions compliance
- **CE**: European conformity marking
- **RoHS**: Restriction of hazardous substances compliant
- **IC**: Industry Canada certification (ESP32 module)

### Warranty and Support

#### Warranty Coverage
- **Duration**: 1 year from purchase date
- **Coverage**: Manufacturing defects and component failures
- **Exclusions**: Physical damage, misuse, modifications

#### Technical Support
- **Documentation**: Available at project repository
- **Community Forum**: GitHub Issues page
- **Email Support**: Available for warranty issues

### Safety Information

⚠️ **Important Safety Notes**:
- Maximum input voltage: 12V DC
- Do not exceed 20mA per GPIO pin
- Use in dry, indoor environments only
- Disconnect power when making connections
- Follow local electrical codes for permanent installations

### Revision History

| Version | Date | Changes |
|---------|------|---------|
| 1.0 | 2024-01-01 | Initial release |

---
*ESP32 GPIO PCB User Manual v1.0 - For technical support, visit the project repository or contact support.*