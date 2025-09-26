# ESP32 GPIO PCB

A comprehensive ESP32-based GPIO expansion and control PCB project featuring breakout capabilities, digital I/O control, and integrated power management.

## Overview

This project provides a custom PCB design for ESP32-based GPIO expansion and control applications. The board includes:

- ESP32-WROOM-32 module integration
- GPIO expansion with 3.3V and 5V level shifting
- Onboard power regulation and USB-C connectivity
- LED indicators for status and GPIO activity
- Screw terminals and header pins for easy connectivity
- Compact form factor suitable for industrial applications

## Project Structure

```
├── hardware/          # PCB design files (KiCad)
├── firmware/          # ESP32 firmware examples
├── docs/              # Documentation and datasheets
├── manufacturing/     # Fabrication files and BOM
└── examples/          # Usage examples and tutorials
```

## Features

- **ESP32-WROOM-32** Wi-Fi and Bluetooth connectivity
- **GPIO Expansion**: 16 controllable GPIO pins with level shifting
- **Power Supply**: 5V input with 3.3V regulation
- **USB-C Interface**: Programming and power
- **Status LEDs**: Power, connectivity, and GPIO activity indicators
- **Robust Connectors**: Screw terminals and pin headers
- **Compact Design**: 80mm x 60mm PCB footprint

## Getting Started

1. **Hardware Setup**: See `docs/assembly-guide.md` for PCB assembly instructions
2. **Firmware**: Upload example firmware from `firmware/` directory
3. **Testing**: Follow the examples in `examples/` for basic functionality tests

## Documentation

- [Hardware Design](docs/hardware-design.md) - Schematic and PCB layout details
- [Assembly Guide](docs/assembly-guide.md) - Step-by-step assembly instructions
- [Firmware Guide](docs/firmware-guide.md) - Programming and development setup
- [User Manual](docs/user-manual.md) - Operation and usage instructions

## License

This project is open-source hardware licensed under CERN-OHL-W v2.

## Contributing

Contributions are welcome! Please see CONTRIBUTING.md for guidelines.
