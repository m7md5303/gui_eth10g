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
#include "devbus.h"
//regdefs
#include "reggroup_numbers.h"

typedef uint32_t reg_width_t;


/******************************************************* */
//Defining placeholder structs
// gatescope compressed scope
struct GateScope_struct{             
  reg_width_t GateScope_regs [GateScope_Group];  
} ;  
// i2cscope compressed scope
struct i2cScope_struct{             
  reg_width_t i2cScope_regs [i2cScope_Group];
} ;  
// netscope compressed scope
struct NetScope_struct{             
  reg_width_t NetScope_regs [NetScope_Group]; 
} ; 
// routescope compressed scope
struct RouteScope_struct{             
  reg_width_t RouteScope_regs [RouteScope_Group]; 
} ; 
// I2C Controller registers
struct i2cController_struct{             
  reg_width_t i2cController_regs [i2cController_Group]; 
} ; 
// CONSOLE registers
struct Console_struct{             
  reg_width_t Console_regs [Console_Group]; 
} ; 
// Fan registers
struct Fan_struct{             
  reg_width_t Fan_regs [Fan_Group]; 
} ; 
// FPGA CONFIG REGISTERS
struct fpgaConf_struct{             
  reg_width_t fpgaConf_regs [FPGAConf_Group]; 
} ;  
// CPU Net Controller registers
struct cpuNetCtrl_struct{             
  reg_width_t cpuNetCtrl_regs [CPUNetCtrl_Group]; 
} ; 
// ZipCPU control/debug registers
struct zipctrldbg_struct{             
  reg_width_t zipctrldbg_regs [ZIPCtrlDBG_Group]; 
} ; 

/*************************************************************** */
//Function Headers for reading corresponding registers
// gatescope compressed scope
GateScope_struct Get_GateScope(DEVBUS* board_port) ; 
// i2cscope compressed scope
i2cScope_struct Get_i2cScope(DEVBUS* board_port);
// netscope compressed scope
NetScope_struct Get_NetScope(DEVBUS* board_port);
// routescope compressed scope
RouteScope_struct Get_RouteScope(DEVBUS* board_port);
// I2C Controller registers
i2cController_struct Get_i2cController(DEVBUS* board_port);
// CONSOLE registers
Console_struct Get_Console(DEVBUS* board_port);
// Fan registers
Fan_struct Get_Fan(DEVBUS* board_port);
// FPGA CONFIG REGISTERS
fpgaConf_struct Get_FPGAConf(DEVBUS* board_port);
// CPU Net Controller registers
cpuNetCtrl_struct Get_CPUNetCtrl(DEVBUS* board_port);
// ZipCPU control/debug registers
zipctrldbg_struct Get_ZIPCtrlDBG(DEVBUS* board_port);

#endif