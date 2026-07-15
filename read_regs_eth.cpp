//MIT License

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
//include the corresponding header file
#include "read_regs_eth.h"
//including regdefs header file
#include "regdefs.h"

typedef short int counter_width_t;

// gatescope compressed scope
GateScope_struct Get_GateScope(DEVBUS* board_port) {
    GateScope_struct gate_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_GATESCOPE; reg_addr <= R_GATESCOPED; reg_addr+=4)
    {
        gate_placeholder.GateScope_regs[counter] = board_port->readio(reg_addr) ; 
        counter++;
    }
    return gate_placeholder;
} 

// i2cscope compressed scope
i2cScope_struct Get_i2cScope(DEVBUS* board_port){
    i2cScope_struct i2cSc_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_I2CSCOPE; reg_addr <= R_I2CSCOPED; reg_addr+=4)
    {
        i2cSc_placeholder.i2cScope_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    return i2cSc_placeholder;
}

// netscope compressed scope
NetScope_struct Get_NetScope(DEVBUS* board_port){
    NetScope_struct net_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_NETSCOPE; reg_addr <= R_NETSCOPED; reg_addr+=4)
    {
        net_placeholder.NetScope_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    return net_placeholder;
}

// routescope compressed scope
RouteScope_struct Get_RouteScope(DEVBUS* board_port){
    RouteScope_struct route_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_ROUTESCOPE; reg_addr <= R_ROUTESCOPED; reg_addr+=4)
    {
        route_placeholder.RouteScope_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    return route_placeholder;  
}

// I2C Controller registers
i2cController_struct Get_i2cController(DEVBUS* board_port){
    i2cController_struct i2cCtrl_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_I2CCPU; reg_addr <= R_I2CCPU_CKCOUNT; reg_addr+=4)
    {
        i2cCtrl_placeholder.i2cController_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    
    for (reg_addr = R_I2CDMA; reg_addr <= R_I2CDMA_LEN; reg_addr+=4)
    {
        i2cCtrl_placeholder.i2cController_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    return i2cCtrl_placeholder;
}

// CONSOLE registers
Console_struct Get_Console(DEVBUS* board_port){
    Console_struct console_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_CONSOLE_FIFO; reg_addr <= R_CONSOLE_UARTTX; reg_addr+=4)
    {
        console_placeholder.Console_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    return console_placeholder;
}

// Fan registers
Fan_struct Get_Fan(DEVBUS* board_port){
    Fan_struct fan_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_FAN_FPGAPWM; reg_addr <= R_VERSION; reg_addr+=4)
    {
        fan_placeholder.Fan_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    return fan_placeholder;
}

// FPGA CONFIG REGISTERS
fpgaConf_struct Get_FPGAConf(DEVBUS* board_port){
    fpgaConf_struct fpgaConf_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_CFG_CRC; reg_addr <= R_CFG_TIMER; reg_addr+=4)
    {
        fpgaConf_placeholder.fpgaConf_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    fpgaConf_placeholder.fpgaConf_regs[counter] = board_port->readio(R_CFG_BOOTSTS) ;
    counter++;
    fpgaConf_placeholder.fpgaConf_regs[counter] = board_port->readio(R_CFG_CTL1) ;
    counter++;
    fpgaConf_placeholder.fpgaConf_regs[counter] = board_port->readio(R_CFG_BSPI) ;
    counter++;
    return fpgaConf_placeholder;
}

// CPU Net Controller registers
cpuNetCtrl_struct Get_CPUNetCtrl(DEVBUS* board_port){
    cpuNetCtrl_struct CPU_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    for (reg_addr = R_CPUNET; reg_addr <= R_CPUNETTXPKTS; reg_addr+=4)
    {
        CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    for (reg_addr = R_CPUNETTX_BASE; reg_addr <= R_CPUNETTX_DBG; reg_addr+=4)
    {
        CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    for (reg_addr = R_ROUTER; reg_addr <= R_ROUTERDBG4; reg_addr+=4)
    {
        CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    for (reg_addr = R_ROUTERNEVER; reg_addr <= R_ROUTERALWAYS; reg_addr+=4)
    {
        CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(R_ROUTERDBGS) ;
    counter++;
    for (reg_addr = R_DDR3_PHY; reg_addr <= R_DDR3_PHYCTRLSTAT; reg_addr+=4)
    {
        CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(R_DDR3_PHYRESET) ;
    counter++;
    CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(R_DDR3_PHYDBGSEL) ;
    counter++;
    CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(R_NETSTAT) ;
    counter++;
    CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(R_BKRAM) ;
    counter++;
    CPU_placeholder.cpuNetCtrl_regs[counter] = board_port->readio(R_DDR3_CONTROLLER) ;
    counter++;
    return CPU_placeholder;
}

// ZipCPU control/debug registers
zipctrldbg_struct Get_ZIPCtrlDBG(DEVBUS* board_port){
    zipctrldbg_struct ZIPCD_placeholder;
    reg_width_t reg_addr;
    counter_width_t counter =0;
    ZIPCD_placeholder.zipctrldbg_regs[counter] = board_port->readio(R_ZIPCTRL) ;
    counter++;
    for (reg_addr = R_ZIPREGS; reg_addr <= R_ZIPDMAC; reg_addr+=4)
    {
        ZIPCD_placeholder.zipctrldbg_regs[counter] = board_port->readio(reg_addr) ;
        counter++;
    }
    return ZIPCD_placeholder;
}