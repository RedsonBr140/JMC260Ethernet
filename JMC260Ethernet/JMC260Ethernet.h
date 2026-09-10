#pragma once

#include <IOKit/IOService.h>

class JMC260Ethernet : public IOService {
	OSDeclareDefaultStructors(JMC260Ethernet)

	public:
	virtual bool start(IOService *provider);
	virtual void stop(IOService *provider);
};