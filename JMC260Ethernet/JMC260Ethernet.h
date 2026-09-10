#pragma once

#include <IOKit/IOService.h>
#include <IOKit/pci/IOPCIDevice.h>

class JMC260Ethernet : public IOService {
	OSDeclareDefaultStructors(JMC260Ethernet)
	
	private:
	IOPCIDevice *pciDevice;
	IOMemoryMap *mmioMap;
	volatile UInt8 *mmioBase;
	
	UInt32 readReg32(UInt32 offset);

	public:
	virtual bool start(IOService *provider);
	virtual void stop(IOService *provider);
};