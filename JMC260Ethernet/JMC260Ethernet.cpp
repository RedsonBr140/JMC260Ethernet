#include "JMC260Ethernet.h"

#include <IOKit/IOLib.h>
#include <IOKit/pci/IOPCIDevice.h>

#define super IOService

OSDefineMetaClassAndStructors(JMC260Ethernet, IOService)

bool JMC260Ethernet::start(IOService *provider) {
	IOLog("JMC260Ethernet: start()\n");
	
	if (!super::start(provider)) {
		IOLog("JMC260Ethernet: super::start() failed!\n");
		return false;
	}
	
	IOPCIDevice	*pciDevice = OSDynamicCast(IOPCIDevice, provider);
	
	if (!pciDevice) {
		IOLog("JMC260Ethernet: provider is not an IOPCIDevice\n");
		return false;
	}
	
	UInt16 vendorID = pciDevice->configRead16(kIOPCIConfigVendorID);
	UInt16 deviceID = pciDevice->configRead16(kIOPCIConfigDeviceID);
	
	IOLog("JMC260Ethernet: attached to PCI device %04x:%04x\n",
		  vendorID,
		  deviceID);
	
	UInt32 bar0 = pciDevice->configRead32(kIOPCIConfigBaseAddress0);
	UInt32 bar1 = pciDevice->configRead32(kIOPCIConfigBaseAddress1);
	UInt32 bar2 = pciDevice->configRead32(kIOPCIConfigBaseAddress2);
	UInt32 bar3 = pciDevice->configRead32(kIOPCIConfigBaseAddress3);
	UInt32 bar4 = pciDevice->configRead32(kIOPCIConfigBaseAddress4);
	UInt32 bar5 = pciDevice->configRead32(kIOPCIConfigBaseAddress5);
	
	IOLog("JMC260Ethernet: BAR0 = 0x%08x\n", bar0);
	IOLog("JMC260Ethernet: BAR1 = 0x%08x\n", bar1);
	IOLog("JMC260Ethernet: BAR2 = 0x%08x\n", bar2);
	IOLog("JMC260Ethernet: BAR3 = 0x%08x\n", bar3);
	IOLog("JMC260Ethernet: BAR4 = 0x%08x\n", bar4);
	IOLog("JMC260Ethernet: BAR5 = 0x%08x\n", bar5);

	return true;
}

void JMC260Ethernet::stop(IOService *provider) {
	IOLog("JMC260Ethernet: stop()\n");
	
	super::stop(provider);
}