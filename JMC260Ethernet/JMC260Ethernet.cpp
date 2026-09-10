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
	return true;
}

void JMC260Ethernet::stop(IOService *provider) {
	IOLog("JMC260Ethernet: stop()\n");
	
	super::stop(provider);
}