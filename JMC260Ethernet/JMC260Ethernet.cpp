#include "JMC260Ethernet.h"
#include "JMC260Registers.h"

#include <IOKit/IOLib.h>

#define super IOService

OSDefineMetaClassAndStructors(JMC260Ethernet, IOService)

UInt32 JMC260Ethernet::readReg32(UInt32 offset) {
	return *(volatile UInt32 *)(mmioBase + offset);
}

bool JMC260Ethernet::start(IOService *provider) {
	IOLog("JMC260Ethernet: start()\n");
	
	pciDevice = 0;
	mmioMap = 0;
	mmioBase = 0;
	
	if (!super::start(provider)) {
		IOLog("JMC260Ethernet: super::start() failed!\n");
		return false;
	}
	
	pciDevice = OSDynamicCast(IOPCIDevice, provider);
	
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

	pciDevice->setMemoryEnable(true);
	mmioMap = pciDevice->mapDeviceMemoryWithRegister(kIOPCIConfigBaseAddress0);
	
	if (!mmioMap) {
		IOLog("JMC260Ethernet: failed to map BAR0\n");
		return false;
	}
	
	mmioBase = (volatile UInt8 *)mmioMap->getVirtualAddress();
	
	if (!mmioBase) {
		IOLog("JMC260Ethernet: BAR0 virtual address is null\n");
		
		mmioMap->release();
		mmioMap = 0;
		
		return false;
	}
	
	IOLog("JMC260Ethernet: BAR0 mapped at %p\n", mmioBase);
	
	UInt32 rxumaLo = readReg32(JMC260::RXUMA_LO);
	UInt32 rxumaHi = readReg32(JMC260::RXUMA_HI);
	UInt32 ghc = readReg32(JMC260::GHC);
	UInt32 phyLink = readReg32(JMC260::PHY_LINK);
	
	IOLog("JMC260Ethernet: RXUMA_LO = 0x%08x\n",
		  (unsigned int)rxumaLo);
	
	IOLog("JMC260Ethernet: RXUMA_HI = 0x%08x\n",
		  (unsigned int)rxumaHi);

	IOLog("JMC260Ethernet: GHC      = 0x%08x\n",
		  (unsigned int)ghc);
	
	IOLog("JMC260Ethernet: PHY_LINK = 0x%08x\n",
		  (unsigned int)phyLink);
	return true;
}

void JMC260Ethernet::stop(IOService *provider) {
	IOLog("JMC260Ethernet: stop()\n");
	
	mmioBase = 0;
	
	if (mmioMap) {
		mmioMap->release();
		mmioMap = 0;
	}
	
	pciDevice = 0;
	
	super::stop(provider);
}