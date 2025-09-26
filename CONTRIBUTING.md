# Contributing to ESP32 GPIO PCB

Thank you for your interest in contributing to the ESP32 GPIO PCB project! This document provides guidelines for contributing to this open hardware project.

## Code of Conduct

This project follows the [Contributor Covenant Code of Conduct](https://www.contributor-covenant.org/version/2/1/code_of_conduct/). By participating, you are expected to uphold this code.

## How to Contribute

### Reporting Issues

Before creating a new issue, please:

1. **Search existing issues** to avoid duplicates
2. **Use the issue templates** when available
3. **Provide detailed information** including:
   - Hardware version/revision
   - Software/firmware version
   - Steps to reproduce the problem
   - Expected vs actual behavior
   - Photos or screenshots if applicable

### Suggesting Enhancements

Enhancement suggestions are welcome! Please:

1. **Check if the enhancement has already been suggested**
2. **Describe the enhancement in detail**
3. **Explain why this enhancement would be useful**
4. **Consider backward compatibility**

### Contributing Code/Design Changes

#### Hardware Design Contributions

1. **KiCad Compatibility**: All hardware designs should use KiCad 6.0 or later
2. **Design Rules**: Follow the design rules specified in the KiCad project
3. **Documentation**: Update hardware documentation for any changes
4. **Testing**: Ensure designs have been tested (simulation and/or prototype)

#### Firmware Contributions

1. **Arduino IDE Compatibility**: Code should compile with Arduino IDE 2.0+
2. **ESP32 Platform**: Target ESP32-WROOM-32 module specifically
3. **Code Style**: Follow existing code style and conventions
4. **Comments**: Include meaningful comments and documentation
5. **Examples**: Provide usage examples for new features

### Pull Request Process

1. **Fork** the repository and create a feature branch
2. **Make your changes** following the guidelines above
3. **Test thoroughly** on actual hardware when possible
4. **Update documentation** as needed
5. **Commit** with clear, descriptive messages
6. **Create pull request** with detailed description

#### Pull Request Guidelines

- **Branch Naming**: Use descriptive names (e.g., `feature/wifi-improvements`, `fix/power-led-issue`)
- **Commit Messages**: Use imperative mood ("Add feature" not "Added feature")
- **Small Changes**: Keep PRs focused and reasonably sized
- **Testing**: Include test results or validation information
- **Documentation**: Update relevant documentation files

## Development Setup

### Hardware Development

#### Required Software
- **KiCad 6.0+**: For schematic and PCB design
- **Git**: For version control
- **Text Editor**: For documentation updates

#### Repository Structure
```
├── hardware/          # KiCad design files
├── firmware/          # Arduino sketches and examples
├── docs/              # Documentation
├── manufacturing/     # BOM, gerbers, assembly files
└── examples/          # Usage examples and tutorials
```

### Firmware Development

#### Required Software
- **Arduino IDE 2.0+** or VS Code with PlatformIO
- **ESP32 Board Package**
- **Required Libraries**: ArduinoJson

#### Development Board
- ESP32-WROOM-32 development board for testing
- USB-C cable for programming
- Breadboard and components for prototyping

## Design Guidelines

### Hardware Design

#### PCB Design Standards
- **Layer Count**: 4-layer minimum for signal integrity
- **Track Width**: Minimum 0.1mm for signals, 0.25mm for power
- **Via Size**: 0.2mm drill, 0.45mm pad
- **Clearance**: 0.1mm minimum between traces
- **Copper Pour**: Use ground planes and power planes

#### Component Selection
- **Availability**: Use readily available components
- **Reliability**: Select components with good track record
- **Cost**: Balance performance with cost-effectiveness
- **Package Size**: Consider hand-assembly requirements

### Firmware Design

#### Coding Standards
- **Indentation**: 2 spaces (no tabs)
- **Line Length**: Maximum 120 characters
- **Functions**: Keep functions focused and reasonably sized
- **Variables**: Use descriptive variable names
- **Constants**: Use `const` and `#define` appropriately

#### Performance Guidelines
- **Memory Usage**: Be mindful of RAM constraints
- **Power Consumption**: Consider deep sleep modes when applicable
- **Real-time**: Avoid blocking operations in time-critical code
- **Error Handling**: Include appropriate error checking

## Testing

### Hardware Testing

#### Design Verification
- **Schematic Review**: Peer review of schematic designs
- **Simulation**: SPICE simulation where applicable
- **DRC**: Design Rule Check must pass
- **ERC**: Electrical Rule Check must pass

#### Prototype Testing
- **Power Supply**: Verify all voltage rails
- **GPIO Functionality**: Test all GPIO pins
- **Communication**: Verify UART, SPI, I2C interfaces
- **Environmental**: Test temperature and humidity ranges

### Firmware Testing

#### Functional Testing
- **Unit Tests**: Test individual functions where possible
- **Integration Tests**: Test complete functionality
- **Edge Cases**: Test boundary conditions and error cases
- **Performance**: Measure timing and memory usage

#### Hardware-in-Loop Testing
- **GPIO Control**: Verify all GPIO pins function correctly
- **WiFi Connectivity**: Test AP mode and station mode
- **Web Interface**: Test all web interface functions
- **Serial Interface**: Verify command processing

## Documentation

### Required Documentation Updates

When making changes, update relevant documentation:

- **README.md**: For project overview changes
- **Hardware Design**: For schematic/PCB changes
- **Assembly Guide**: For component or assembly changes
- **User Manual**: For functionality changes
- **API Documentation**: For firmware interface changes

### Documentation Style

- **Markdown**: Use standard Markdown formatting
- **Images**: Include relevant diagrams and photos
- **Examples**: Provide code examples and usage scenarios
- **Links**: Keep internal links up to date
- **Version**: Update version numbers appropriately

## Release Process

### Version Numbers

Use semantic versioning (MAJOR.MINOR.PATCH):
- **MAJOR**: Incompatible hardware changes
- **MINOR**: Backward-compatible functionality additions
- **PATCH**: Backward-compatible bug fixes

### Release Checklist

1. **Testing**: Complete test suite passes
2. **Documentation**: All documentation updated
3. **BOM**: Bill of materials verified and updated
4. **Gerbers**: Manufacturing files generated and verified
5. **Examples**: All examples tested and working
6. **Changelog**: Release notes prepared

## Getting Help

### Resources

- **Project Repository**: Main source of information
- **Issue Tracker**: For bugs and feature requests
- **Discussions**: For general questions and ideas
- **Wiki**: Additional documentation and tutorials

### Communication

- **GitHub Issues**: Primary communication channel
- **Pull Request Comments**: For code review discussions
- **Email**: For sensitive security-related issues

## Recognition

Contributors will be acknowledged in:
- **README.md**: Contributors section
- **Release Notes**: Highlighting major contributions
- **About Page**: Web interface credits
- **Documentation**: Author attributions where appropriate

## License

By contributing to this project, you agree that your contributions will be licensed under the CERN-OHL-W v2 license. This ensures that the project remains open and accessible to everyone.

---

Thank you for contributing to the ESP32 GPIO PCB project! Your contributions help make this a better resource for the entire community.