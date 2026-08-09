// MIT License

// Copyright (c) 2026 MohamedKhaled5303

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//Project Author: Mohamed Khaled
/****************************************** */
#ifndef READ_REGS_ETH_H
#define READ_REGS_ETH_H

//importing general header
#include <cstdint>
//devbus
#include "./../test/eth10g/sw/host/devbus.h"
//regdefs
#include "reggroup_numbers.h"

typedef uint32_t reg_width_t;


/******************************************************* */
//Defining placeholder structs
// flash config compressed scope
struct FlashCfg_struct{             
  reg_width_t FlashCfg_regs [FLASHCFG_Group];  
} ;
// emmcscope compressed scope
struct EMMCScope_struct{             
  reg_width_t EMMCScope_regs [EMMCScope_Group];  
} ;  
// i2cscope compressed scope
struct i2cScope_struct{             
  reg_width_t i2cScope_regs [i2cScope_Group];
} ;  
// netscope compressed scope
struct NetScope_struct{             
  reg_width_t NetScope_regs [netScope_Group]; 
} ; 
// routescope compressed scope
struct RouteScope_struct{             
  reg_width_t RouteScope_regs [RouteScope_Group]; 
} ; 
// SATA_DRPScope registers
struct SATA_DRPScope_struct{             
  reg_width_t SATA_DRPScope_regs [SATA_DRPScope_Group]; 
} ; 
// SATA_LScope registers
struct SATA_LScope_struct{             
  reg_width_t SATA_LScope_regs [SATA_LScope_Group]; 
} ; 
// SATA_PSScope registers
struct SATA_PSScope_struct{             
  reg_width_t SATA_PSScope_regs [SATA_PSScope_Group]; 
} ; 
// SATA_RSScope REGISTERS
struct SATA_RSScope_struct{             
  reg_width_t SATA_RSScope_regs [SATA_RSScope_Group]; 
} ;  
// SATA_TSScope registers
struct SATA_TSScope_struct{             
  reg_width_t SATA_TSScope_regs [SATA_TSScope_Group]; 
} ; 
// ZipSCoperegisters
struct zipScope_struct{             
  reg_width_t zipScope_regs [zipScope_Group]; 
} ; 
// Console registers
struct Console_struct{             
  reg_width_t Console_regs [Console_Group]; 
} ; 
// Fan registers
struct Fan_struct{             
  reg_width_t Fan_regs [Fan_Group]; 
} ; 
// SATA_ctrl registers
struct SATA_ctrl_struct{             
  reg_width_t SATA_ctrl_regs [SATA_ctrl_Group]; 
} ; 
// EMMC_Card registers
struct EMMC_Card_struct{             
  reg_width_t EMMC_Card_regs [EMMC_Card_Group]; 
} ; 
// SDIO registers
struct SDIO_struct{             
  reg_width_t SDIO_regs [SDIO_Group]; 
} ; 
// fpgaCfg registers
struct fpgaCfg_struct{             
  reg_width_t fpgaCfg_regs [fpgaCfg_Group]; 
} ; 
// CPUNet registers
struct CPUNet_struct{             
  reg_width_t CPUNet_regs [CPUNet_Group]; 
} ; 
// i2cCtrl registers
struct i2cCtrl_struct{             
  reg_width_t i2cCtrl_regs [i2cCtrl_Group]; 
} ; 
// NetMisc registers
struct NetMisc_struct{             
  reg_width_t NetMisc_regs [NetMisc_Group]; 
} ; 
// Router registers
struct Router_struct{             
  reg_width_t Router_regs [Router_Group]; 
} ; 
// DDR registers
struct DDR_struct{             
  reg_width_t DDR_regs [DDR_Group]; 
} ; 
// NETSTAT registers
struct NETSTAT_struct{             
  reg_width_t NETSTAT_regs [NETSTAT_Group]; 
} ; 
// SATA_DRPctrl registers
struct SATA_DRPctrl_struct{             
  reg_width_t SATA_DRPctrl_regs [SATA_DRPctrl_Group]; 
} ; 
// ZIPCtrlDBG registers
struct ZIPCtrlDBG_struct{             
  reg_width_t ZIPCtrlDBG_regs [ZIPCtrlDBG_Group]; 
} ; 



/*************************************************************** */
//Function Headers for reading corresponding registers

// flash config compressed scope
FlashCfg_struct Get_FlashCfg(DEVBUS* board_port);
// emmcscope compressed scope
EMMCScope_struct Get_EMMCScope(DEVBUS* board_port);
// i2cscope compressed scope
i2cScope_struct Get_i2cScope(DEVBUS* board_port);
// netscope compressed scope
NetScope_struct Get_NetScope(DEVBUS* board_port);
// routescope compressed scope
RouteScope_struct Get_RouteScope(DEVBUS* board_port);
// SATA_DRPScope registers
SATA_DRPScope_struct Get_SATA_DRPScope(DEVBUS* board_port);
// SATA_LScope registers
SATA_LScope_struct Get_SATA_LScope(DEVBUS* board_port);
// SATA_PSScope registers
SATA_PSScope_struct Get_SATA_PSScope(DEVBUS* board_port);
// SATA_RSScope REGISTERS
SATA_RSScope_struct Get_SATA_RSScope(DEVBUS* board_port);
// SATA_TSScope registers
SATA_TSScope_struct Get_SATA_TSScope(DEVBUS* board_port);
// ZipSCoperegisters
zipScope_struct Get_zipScope(DEVBUS* board_port);
// Console registers
Console_struct Get_Console(DEVBUS* board_port);
// Fan registers
Fan_struct Get_Fan(DEVBUS* board_port);
// SATA_ctrl registers
SATA_ctrl_struct Get_SATA_ctrl(DEVBUS* board_port);
// EMMC_Card registers
EMMC_Card_struct Get_EMMC_Card(DEVBUS* board_port);
// SDIO registers
SDIO_struct Get_SDIO(DEVBUS* board_port);
// fpgaCfg registers
fpgaCfg_struct Get_fpgaCfg(DEVBUS* board_port);
// CPUNet registers
CPUNet_struct Get_CPUNet(DEVBUS* board_port);
// i2cCtrl registers
i2cCtrl_struct Get_i2cCtrl(DEVBUS* board_port);
// NetMisc registers
NetMisc_struct Get_NetMisc(DEVBUS* board_port);
// Router registers
Router_struct Get_Router(DEVBUS* board_port);
// DDR registers
DDR_struct Get_DDR(DEVBUS* board_port);
// NETSTAT registers
NETSTAT_struct Get_NETSTAT(DEVBUS* board_port);
// SATA_DRPctrl registers
SATA_DRPctrl_struct Get_SATA_DRPctrl(DEVBUS* board_port);
// ZIPCtrlDBG registers
ZIPCtrlDBG_struct Get_ZIPCtrlDBG(DEVBUS* board_port);
#endif
