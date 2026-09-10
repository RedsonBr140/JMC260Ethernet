#pragma once

namespace JMC260 {
	enum IOMapOffset {
		MAC  = 0x0000,
		PHY  = 0x0400,
		MISC = 0x0800,
		RSS  = 0x0C00
	};
	
	enum IOMapLength {
		MAC_LEN  = 0x80,
		PHY_LEN  = 0x58,
		MISC_LEN = 0x98,
		RSS_LEN  = 0xFF
	};
	
	enum Register {
		TXCS      = MAC | 0x00,
		TXDBA_LO  = MAC | 0x04,
		TXDBA_HI  = MAC | 0x08,
		TXQDC     = MAC | 0x0C,
		TXNDA     = MAC | 0x10,
		TXMCS     = MAC | 0x14,
		TXPFC     = MAC | 0x18,
		TXTRHD    = MAC | 0x1C,
		
		RXCS      = MAC | 0x20,
		RXDBA_LO  = MAC | 0x24,
		RXDBA_HI  = MAC | 0x28,
		RXQDC     = MAC | 0x2C,
		RXNDA     = MAC | 0x30,
		RXMCS     = MAC | 0x34,
		RXUMA_LO  = MAC | 0x38,
		RXUMA_HI  = MAC | 0x3C,
		RXMCHT_LO = MAC | 0x40,
		RXMCHT_HI = MAC | 0x44,
		WFODP     = MAC | 0x48,
		WFOI      = MAC | 0x4C,
		
		SMI       = MAC | 0x50,
		GHC       = MAC | 0x54,
		PMCS      = MAC | 0x60,
		
		PHY_PWR   = PHY | 0x24,
		PHY_CS    = PHY | 0x28,
		PHY_LINK  = PHY | 0x30,
		SMBCSR    = PHY | 0x40,
		SMBINTF   = PHY | 0x44,
		
		TMCSR     = MISC | 0x00,
		GPREG0    = MISC | 0x08,
		GPREG1    = MISC | 0x0C,
		
		IEVE      = MISC | 0x20,
		IREQ      = MISC | 0x24,
		IENS      = MISC | 0x28,
		IENC      = MISC | 0x2C,
		PCCRX0    = MISC | 0x30,
		PCCTX     = MISC | 0x40,
		CHIPMODE  = MISC | 0x44,
		SHBA_HI   = MISC | 0x48,
		SHBA_LO   = MISC | 0x4C,
		TIMER1    = MISC | 0x70,
		TIMER2    = MISC | 0x74,
		APMC      = MISC | 0x7C,
		PCCSRX0   = MISC | 0x80
	};
}