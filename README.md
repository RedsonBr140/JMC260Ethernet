# JMC260Ethernet

An experimental native Ethernet driver for the **JMicron JMC260 PCI Express Fast Ethernet Controller** on **Mac OS X Snow Leopard 10.6**.

The goal of this project is to implement native support for the JMC260 (`PCI 197B:0260`) using Apple's Snow Leopard-era I/O Kit networking stack.

> **Status:** Early development. The kext currently builds and loads successfully under Mac OS X 10.6, but does not yet provide Ethernet functionality.

## Target Hardware

- **Controller:** JMicron JMC260
- **PCI Vendor ID:** `0x197B`
- **PCI Device ID:** `0x0260`
- **IOPCIPrimaryMatch:** `0x0260197b`
- **Interface:** PCI Express
- **Ethernet:** 10/100 Mbps Fast Ethernet

This project specifically targets the **JMC260**. Support for related JMicron controllers such as the JMC250 is not currently a goal.

## Target Operating System

The initial target is:

- Mac OS X Snow Leopard 10.6
- I/O Kit
- IOPCIFamily
- IONetworkingFamily
- i386 and x86_64 where possible

Development is currently performed using:

- Mac OS X Snow Leopard
- Xcode 3.2.4
- GCC 4.2
- MacOSX10.6 SDK

The final driver must remain usable with a 32-bit Snow Leopard kernel because some target systems require the i386 kernel for other hardware support.

## Project Structure

```text
JMC260Ethernet/
├── JMC260Ethernet.xcodeproj/
└── JMC260Ethernet/
    ├── JMC260Ethernet.cpp
    ├── JMC260Ethernet.h
    ├── Info.plist
    └── English.lproj/
        └── InfoPlist.strings
````

Additional source files will be introduced as hardware support is implemented.

## Current Status

The project currently implements the initial I/O Kit driver skeleton.

Completed:

* [x] Snow Leopard development environment
* [x] Native I/O Kit kext project
* [x] `IOService` subclass
* [x] `IOPCIDevice` provider matching
* [x] JMC260 PCI personality
* [x] PCI ID match for `197B:0260`
* [x] Kernel dependencies configured
* [x] Successful compilation
* [x] Successful kext validation
* [x] Successful loading under Snow Leopard
* [ ] PCI attachment tested on real JMC260 hardware
* [ ] PCI BAR discovery
* [ ] MMIO mapping
* [ ] JMC260 register access
* [ ] Hardware reset
* [ ] PHY/MDIO support
* [ ] MAC address retrieval
* [ ] DMA
* [ ] TX descriptor ring
* [ ] RX descriptor ring
* [ ] Interrupt handling
* [ ] `IOEthernetController` integration
* [ ] Link negotiation
* [ ] Packet transmission
* [ ] Packet reception
* [ ] Functional Ethernet interface

## Development Roadmap

Development is intentionally being performed in small hardware-validation milestones.

### Milestone 1 — Kext Infrastructure

Establish a minimal Snow Leopard kernel extension capable of being loaded by the kernel.

The driver must:

1. Build successfully.
2. Validate as a Snow Leopard kext.
3. Register an I/O Kit personality.
4. Match PCI device `197B:0260`.
5. Attach to an `IOPCIDevice`.
6. Load and unload cleanly.

The kext has already been successfully loaded under Snow Leopard.

Hardware attachment remains to be tested on a machine containing the actual JMC260 controller.

### Milestone 2 — PCI and MMIO

Establish communication with the controller without initializing Ethernet functionality.

Planned work:

1. Read PCI vendor/device IDs.
2. Inspect PCI BAR0-BAR5.
3. Determine the JMC260 MMIO BAR.
4. Enable PCI memory access.
5. Map the MMIO region.
6. Read known JMC260 registers.
7. Verify register values against expected hardware behavior.

No DMA or networking will be enabled during this stage.

### Milestone 3 — Hardware Initialization

Implement the minimum controller initialization sequence:

* Hardware reset
* Register initialization
* MAC configuration
* EEPROM access where required
* MAC address retrieval
* JMC260-specific configuration

### Milestone 4 — PHY

Implement communication with the Ethernet PHY:

* MDIO/MII access
* PHY register reads/writes
* PHY identification
* Link detection
* Auto-negotiation
* 10/100 Mbps configuration
* Duplex detection

At this stage the driver should be capable of determining whether an Ethernet cable is connected and reporting negotiated link state.

### Milestone 5 — DMA

Implement the controller's DMA infrastructure:

* DMA-safe memory allocation
* TX descriptor ring
* RX descriptor ring
* Descriptor ownership
* Buffer management
* DMA address handling
* Ring initialization

Special care must be taken with address widths and i386/x86_64 compatibility.

### Milestone 6 — Interrupts

Implement hardware interrupt handling:

* Interrupt source registration
* Interrupt acknowledgement
* RX completion
* TX completion
* Link-state changes
* Error conditions

### Milestone 7 — IONetworkingFamily

Convert/integrate the hardware driver with Apple's Ethernet stack using `IOEthernetController`.

This stage will implement the interface expected by `IONetworkingFamily`, eventually allowing Snow Leopard to expose the JMC260 as a normal Ethernet interface.

### Milestone 8 — Networking

Final bring-up:

* Interface enable/disable
* Packet transmission
* Packet reception
* Link reporting
* MAC address reporting
* DHCP
* IPv4 networking
* Stability testing

## Driver Architecture

The driver follows the conventional Ethernet NIC architecture:

```text
Mac OS X Networking Stack
          |
          v
  IONetworkingFamily
          |
          v
 IOEthernetController
          |
          v
   JMC260Ethernet
          |
    +-----+-----+
    |           |
    v           v
   MMIO        DMA
    |           |
    +-----+-----+
          |
          v
      JMC260 MAC
          |
          v
          PHY
          |
          v
      Ethernet
```

The **control path** primarily uses MMIO registers.

The **data path** uses DMA descriptor rings in system memory for packet transmission and reception.

The PHY is controlled through the JMC260's MII/MDIO interface.

## Reference Implementation

The Linux `jme` driver is being used as an important reference for understanding the JMC260 hardware.

Relevant areas include:

* Register definitions
* Hardware reset
* Initialization sequence
* DMA descriptors
* TX/RX operation
* PHY access
* MDIO/MII
* EEPROM access
* MAC address retrieval
* Interrupt handling
* Hardware quirks

The Linux driver is used as a **hardware behavior reference**, not as code to be directly ported.

Linux networking APIs, DMA APIs, synchronization primitives, and driver architecture differ significantly from I/O Kit and must be reimplemented appropriately for Mac OS X.

## JMC260 vs JMC250

The Linux `jme` driver supports multiple related JMicron Ethernet controllers.

This project initially targets only:

```text
JMC260 — PCI 197B:0260
```

JMC250/Gigabit-specific functionality should not be introduced unless it is also required by the JMC260.

Keeping the initial implementation JMC260-specific reduces the amount of hardware behavior that must be understood during bring-up.

## Building

Open:

```text
JMC260Ethernet.xcodeproj
```

using Xcode 3.2.4 under Snow Leopard.

Then build the `JMC260Ethernet` target.

The resulting development kext is normally located at:

```text
build/Debug/JMC260Ethernet.kext
```

Verify its architecture with:

```bash
file build/Debug/JMC260Ethernet.kext/Contents/MacOS/JMC260Ethernet
```

For a universal build:

```bash
lipo -info build/Debug/JMC260Ethernet.kext/Contents/MacOS/JMC260Ethernet
```

## Testing

For development testing, copy the kext outside the Xcode build directory before changing ownership:

```bash
sudo rm -rf /tmp/JMC260Ethernet.kext
sudo cp -R build/Debug/JMC260Ethernet.kext /tmp/
sudo chown -R root:wheel /tmp/JMC260Ethernet.kext
sudo chmod -R go-w /tmp/JMC260Ethernet.kext
```

Load it with:

```bash
sudo kextutil -v 2 /tmp/JMC260Ethernet.kext
```

Verify that it is loaded:

```bash
kextstat | grep -i JMC260
```

Unload it with:

```bash
sudo kextunload -b com.redsonbr140.driver.JMC260Ethernet
```

Kernel messages can be inspected using:

```bash
dmesg
```

or Console.app.

## Important Testing Note

Loading the kext and attaching the driver are two different events.

The kext can successfully load on a machine without a JMC260:

```text
JMC260Ethernet.kext loaded
        |
        v
IOKit personality registered
        |
        v
Search for PCI 197B:0260
        |
        +---- Device present ----> JMC260Ethernet::start()
        |
        +---- Device absent -----> No driver instance
```

Therefore, successful loading in a virtual machine does **not** demonstrate that PCI attachment or hardware access works.

Those stages require real JMC260 hardware.

## Warning

This is experimental kernel-mode software.

An incorrect register write, DMA address, descriptor, interrupt handler, memory mapping, or synchronization operation can cause:

* Kernel panics
* System freezes
* Memory corruption
* Network controller lockups
* Data loss

Do not test development builds on a machine containing important unsaved data.

Hardware initialization will be introduced incrementally so that each stage can be validated before enabling more complex functionality.

## Documentation

JMC260/JMC261 documentation:

* JMicron JMC260/JMC261 Ethernet Controller Datasheet

Linux hardware reference:

* Linux `jme` Ethernet driver

Apple development references:

* I/O Kit
* `IOPCIDevice`
* `IOEthernetController`
* `IONetworkingFamily`

## License

No license has been selected yet.

Until a license is explicitly added to this repository, do not assume permission to redistribute or reuse the source code.

## Project Goal

The end goal is simple:

> Make the JMicron JMC260 work as a native Ethernet controller under Mac OS X Snow Leopard.