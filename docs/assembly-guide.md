# Assembly Guide

## ESP32 GPIO PCB - Assembly Instructions v1.0

### Overview

This guide provides step-by-step instructions for assembling the ESP32 GPIO PCB. The board is designed for both manual assembly and automated pick-and-place manufacturing.

### Required Tools

#### Basic Tools
- Soldering iron (temperature controlled, 350°C)
- Solder (SAC305 lead-free, 0.6-0.8mm diameter)
- Flux (no-clean type recommended)
- ESD-safe work surface and wrist strap
- Tweezers (fine-tip, ESD-safe)
- Magnifying glass or microscope
- Multimeter with continuity tester

#### Optional Tools
- Hot air rework station
- Solder paste and stencil
- Pick-and-place machine (for volume production)
- Reflow oven (for SMD assembly)

### Bill of Materials (BOM)

#### Main Components
| Reference | Part Number      | Description                    | Package  | Qty |
|-----------|------------------|--------------------------------|----------|-----|
| U1        | ESP32-WROOM-32   | WiFi/BT Module                | Module   | 1   |
| U2        | AMS1117-3.3      | 3.3V Linear Regulator         | SOT-223  | 1   |
| U3        | 74LVC245APW      | Octal Bus Transceiver         | TSSOP-20 | 2   |
| U4        | CH340C           | USB-to-Serial Converter       | SOP-16   | 1   |

#### Passive Components
| Reference | Value    | Description           | Package | Qty |
|-----------|----------|-----------------------|---------|-----|
| C1-C4     | 10µF     | Ceramic Capacitor     | 0805    | 4   |
| C5-C12    | 0.1µF    | Ceramic Capacitor     | 0603    | 8   |
| C13-C14   | 22pF     | Ceramic Capacitor     | 0603    | 2   |
| R1-R4     | 10kΩ     | Resistor              | 0603    | 4   |
| R5-R8     | 330Ω     | Resistor              | 0603    | 4   |
| R9        | 1kΩ      | Resistor              | 0603    | 1   |
| L1        | 10µH     | Ferrite Bead          | 0603    | 1   |

#### Connectors and Mechanical
| Reference | Part Number      | Description               | Qty |
|-----------|------------------|---------------------------|-----|
| J1        | USB4085-GF-A     | USB-C Connector           | 1   |
| J2        | PJ-102AH         | 2.1mm DC Jack             | 1   |
| J3-J4     | PH254-10         | 10-pin Header (2.54mm)    | 2   |
| J5-J12    | TB002-2          | 2-pin Screw Terminal      | 8   |
| SW1       | SPST-SMD         | Reset Switch              | 1   |

#### Status LEDs
| Reference | Color  | Description    | Package | Qty |
|-----------|--------|----------------|---------|-----|
| LED1      | Green  | Power LED      | 0805    | 1   |
| LED2      | Blue   | WiFi LED       | 0805    | 1   |
| LED3      | Yellow | Activity LED   | 0805    | 1   |
| LED4-LED19| Red    | GPIO LEDs      | 0805    | 16  |

### Assembly Steps

#### Step 1: PCB Preparation
1. **Inspect PCB**: Check for any manufacturing defects, cracks, or contamination
2. **Clean PCB**: Use isopropyl alcohol (99%) to remove any flux residue
3. **ESD Protection**: Ensure proper ESD protection throughout assembly
4. **Temperature**: Allow PCB to reach room temperature if stored in cold environment

#### Step 2: Solder Paste Application (SMD Method)
1. **Stencil Alignment**: Align solder paste stencil with PCB fiducials
2. **Paste Application**: Apply SAC305 solder paste using squeegee
3. **Stencil Removal**: Carefully lift stencil to avoid paste smearing
4. **Inspection**: Check paste deposits for completeness and uniformity

#### Step 3: SMD Component Placement

##### 3.1: Small Passives (0603/0805)
1. **Resistors (R1-R9)**:
   - Place all resistors using tweezers
   - Check orientation (non-polarized)
   - Verify values with multimeter if uncertain

2. **Capacitors (C1-C14)**:
   - Place ceramic capacitors
   - Note: Polarized components not used in this design
   - Ensure proper value placement per BOM

3. **Ferrite Bead (L1)**:
   - Place on power supply line
   - Orientation not critical

##### 3.2: LEDs (LED1-LED19)
1. **Orientation**: Note polarity marking on PCB silkscreen
2. **Placement**: Cathode towards ground symbol
3. **Colors**: Follow BOM color assignment

##### 3.3: Integrated Circuits
1. **AMS1117 Regulator (U2)**:
   - Align pin 1 with PCB marking
   - Check for proper pad alignment
   - Handle with ESD precautions

2. **74LVC245 Level Shifters (U3-U4)**:
   - TSSOP package requires precise placement
   - Use magnification for pin alignment
   - Verify pin 1 orientation

3. **CH340C USB Controller (U4)**:
   - SOP-16 package placement
   - Check pin 1 alignment
   - Ensure no bent pins

#### Step 4: Reflow Soldering (SMD Method)
1. **Preheat**: 150°C for 90 seconds
2. **Ramp**: 3°C/second to 245°C
3. **Peak**: 245-250°C for 10-15 seconds
4. **Cool Down**: Natural cooling to room temperature

#### Step 5: ESP32 Module Installation
1. **Manual Soldering Required**: The ESP32-WROOM-32 module requires careful hand soldering
2. **Flux Application**: Apply flux to all pads
3. **Tack Welding**: Solder opposite corner pins first
4. **Pin Soldering**: Solder remaining pins systematically
5. **Inspection**: Check for shorts using magnification

#### Step 6: Through-Hole Components

##### 6.1: Connectors
1. **USB-C Connector (J1)**:
   - Insert from top side
   - Check mechanical alignment
   - Solder shield pins first, then signal pins

2. **DC Jack (J2)**:
   - Insert from top side
   - Ensure full insertion
   - Solder all pins

3. **Headers (J3-J4)**:
   - Use soldering jig for straight alignment
   - Solder one pin, check alignment, continue

4. **Screw Terminals (J5-J12)**:
   - Insert with proper polarity
   - Ensure tight fit before soldering

##### 6.2: Reset Switch (SW1)
1. **Positioning**: Ensure proper height for enclosure clearance
2. **Soldering**: Use minimal solder to avoid switch damage

#### Step 7: Final Assembly Checks

##### 7.1: Visual Inspection
- [ ] All components properly seated
- [ ] No visible solder bridges
- [ ] No cold solder joints
- [ ] Proper component orientation
- [ ] No missing components

##### 7.2: Electrical Testing
1. **Power Supply Test**:
   - Apply 5V to USB-C or DC jack
   - Measure 3.3V at test points
   - Check current consumption (<100mA idle)

2. **Continuity Tests**:
   - Test all GPIO connections
   - Verify ground continuity
   - Check power rail integrity

3. **Functional Tests**:
   - Program test firmware
   - Verify LED functionality
   - Test GPIO outputs
   - Confirm WiFi operation

#### Step 8: Programming and Calibration
1. **Bootloader**: ESP32 comes pre-programmed with bootloader
2. **Test Firmware**: Upload basic GPIO test program
3. **Calibration**: No calibration required for digital GPIO functions
4. **Configuration**: Set default WiFi AP name if desired

### Quality Control

#### Acceptance Criteria
- [ ] All electrical tests pass
- [ ] Current consumption within specifications
- [ ] All LEDs functional
- [ ] GPIO pins respond correctly
- [ ] WiFi connectivity operational
- [ ] Mechanical fit within specified tolerances

#### Common Issues and Solutions

| Problem | Cause | Solution |
|---------|-------|----------|
| No power LED | Regulator failure | Check input voltage, replace U2 |
| ESP32 not responding | Programming mode issue | Check GPIO0/EN connections |
| GPIO not working | Level shifter issue | Verify U3 power and connections |
| WiFi not connecting | Antenna issue | Check module orientation/shielding |
| USB not detected | CH340C driver | Install USB-to-serial driver |

### Packaging and Storage

#### Individual Unit Packaging
1. **ESD Bag**: Store assembled boards in anti-static bags
2. **Foam Padding**: Protect connectors during shipping
3. **Documentation**: Include quick start guide

#### Bulk Storage
- **Temperature**: 15-35°C
- **Humidity**: 40-60% RH
- **Protection**: Moisture barrier bags with desiccant

### Revision History

| Version | Date       | Changes                              |
|---------|------------|--------------------------------------|
| 1.0     | 2024-01-01 | Initial assembly guide               |

### Safety Notes

⚠️ **Important Safety Information**:
- Always use ESD protection when handling components
- Verify power connections before applying power
- Use proper ventilation when soldering
- Follow local regulations for lead-free soldering
- Keep workspace clean and organized

### References

- [Hardware Design Documentation](hardware-design.md)
- [Bill of Materials](../manufacturing/BOM.csv)
- [Fabrication Files](../manufacturing/gerbers/)
- [Test Procedures](test-procedures.md)