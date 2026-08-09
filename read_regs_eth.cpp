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


// flash config compressed scope
FlashCfg_struct Get_FlashCfg(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    FlashCfg_struct placeholder;

    placeholder.FlashCfg_regs[counter] = board_port->readio(R_FLASHCFG);

    return placeholder;
}


// emmcscope compressed scope
EMMCScope_struct Get_EMMCScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    EMMCScope_struct placeholder;

    board_port->readi(R_EMMCSCOPE, EMMCScope_Group, placeholder.EMMCScope_regs);

    return placeholder;
}


// i2cscope compressed scope
i2cScope_struct Get_i2cScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    i2cScope_struct placeholder;

    board_port->readi(R_I2CSCOPE, i2cScope_Group, placeholder.i2cScope_regs);

    return placeholder;
}


// netscope compressed scope
NetScope_struct Get_NetScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    NetScope_struct placeholder;

    board_port->readi(R_NETSCOPE, netScope_Group, placeholder.NetScope_regs);

    return placeholder;
}


// routescope compressed scope
RouteScope_struct Get_RouteScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    RouteScope_struct placeholder;

    board_port->readi(R_ROUTESCOPE, RouteScope_Group, placeholder.RouteScope_regs);

    return placeholder;
}


// SATA_DRPScope registers
SATA_DRPScope_struct Get_SATA_DRPScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    SATA_DRPScope_struct placeholder;

    board_port->readi(R_SATADRPSCOPE, SATA_DRPScope_Group, placeholder.SATA_DRPScope_regs);

    return placeholder;
}


// SATA_LScope registers
SATA_LScope_struct Get_SATA_LScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    SATA_LScope_struct placeholder;

    board_port->readi(R_SATALSCOPE, SATA_LScope_Group, placeholder.SATA_LScope_regs);

    return placeholder;
}


// SATA_PSScope registers
SATA_PSScope_struct Get_SATA_PSScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    SATA_PSScope_struct placeholder;

    board_port->readi(R_SATAPSCOPE, SATA_PSScope_Group, placeholder.SATA_PSScope_regs);

    return placeholder;
}


// SATA_RSScope REGISTERS
SATA_RSScope_struct Get_SATA_RSScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    SATA_RSScope_struct placeholder;

    board_port->readi(R_SATARSCOPE, SATA_RSScope_Group, placeholder.SATA_RSScope_regs);

    return placeholder;
}


// SATA_TSScope registers
SATA_TSScope_struct Get_SATA_TSScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    SATA_TSScope_struct placeholder;

    board_port->readi(R_SATATSCOPE, SATA_TSScope_Group, placeholder.SATA_TSScope_regs);

    return placeholder;
}


// ZipSCoperegisters
zipScope_struct Get_zipScope(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    zipScope_struct placeholder;

    board_port->readi(R_ZIPSCOPE, zipScope_Group, placeholder.zipScope_regs);

    return placeholder;
}


// Console registers
Console_struct Get_Console(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    Console_struct placeholder;

    board_port->readi(R_CONSOLE_FIFO, Console_Group, placeholder.Console_regs);

    return placeholder;
}


// Fan registers
Fan_struct Get_Fan(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    Fan_struct placeholder;

    board_port->readi(R_FAN_FPGAPWM, Fan_Group, placeholder.Fan_regs);

    return placeholder;
}


// SATA_ctrl registers
SATA_ctrl_struct Get_SATA_ctrl(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    SATA_ctrl_struct placeholder;

    board_port->readi(R_SATA, SATA_ctrl_Group-2, placeholder.SATA_ctrl_regs);
    board_port->readi(R_SATAPHY, 2, &placeholder.SATA_ctrl_regs[SATA_ctrl_Group-2]);

    return placeholder;
}


// EMMC_Card registers
EMMC_Card_struct Get_EMMC_Card(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    EMMC_Card_struct placeholder;

    board_port->readi(R_EMMC_CTRL, EMMC_Card_Group-4, placeholder.EMMC_Card_regs);
    board_port->readi(R_EMMC_DMAA, 4, &placeholder.EMMC_Card_regs[EMMC_Card_Group-4]);

    return placeholder;
}


// SDIO registers
SDIO_struct Get_SDIO(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    SDIO_struct placeholder;

    board_port->readi(R_SDIO_CTRL, SDIO_Group-4, placeholder.SDIO_regs);
    board_port->readi(R_SDIO_DMAA, 4, &placeholder.SDIO_regs[SDIO_Group-4]);

    return placeholder;
}


// fpgaCfg registers
fpgaCfg_struct Get_fpgaCfg(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    fpgaCfg_struct placeholder;

    board_port->readi(R_CFG_CRC, fpgaCfg_Group-3, placeholder.fpgaCfg_regs);
    counter = fpgaCfg_Group-3;
    reg_addr = R_CFG_BOOTSTS;
    placeholder.fpgaCfg_regs[counter] = board_port->readio(reg_addr);
    counter++;
    reg_addr = R_CFG_CTL1;
    placeholder.fpgaCfg_regs[counter] = board_port->readio(reg_addr);
    counter++;
    reg_addr = R_CFG_BSPI;
    placeholder.fpgaCfg_regs[counter] = board_port->readio(reg_addr);

    return placeholder;
}


// CPUNet registers
CPUNet_struct Get_CPUNet(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    CPUNet_struct placeholder;

    board_port->readi(R_CPUNET, CPUNet_Group-10, placeholder.CPUNet_regs);
    board_port->readi(R_CPUNETTX_BASE, 10, &placeholder.CPUNet_regs[CPUNet_Group-10]);

    return placeholder;
}


// i2cCtrl registers
i2cCtrl_struct Get_i2cCtrl(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    i2cCtrl_struct placeholder;

    board_port->readi(R_I2CCPU, i2cCtrl_Group, placeholder.i2cCtrl_regs);

    return placeholder;
}


// NetMisc registers
NetMisc_struct Get_NetMisc(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    NetMisc_struct placeholder;

    board_port->readi(R_RXNETCK0, NetMisc_Group-16, placeholder.NetMisc_regs);
    board_port->readi(R_BUILDTIME, 16, &placeholder.NetMisc_regs[NetMisc_Group-16]);

    return placeholder;
}


// Router registers
Router_struct Get_Router(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    Router_struct placeholder;

    board_port->readi(R_ROUTER0, Router_Group-3, placeholder.Router_regs);
    board_port->readi(R_ROUTERNEVER, 2, &placeholder.Router_regs[Router_Group-3]);
    counter = Router_Group-1;
    reg_addr = R_ROUTERDBGS;
    placeholder.Router_regs[counter] = board_port->readio(reg_addr);

    return placeholder;
}


// DDR registers
DDR_struct Get_DDR(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    DDR_struct placeholder;

    board_port->readi(R_DDR3_PHY, DDR_Group-2, placeholder.DDR_regs);
    counter = DDR_Group-2;
    reg_addr = R_DDR3_PHYRESET;
    placeholder.DDR_regs[counter] = board_port->readio(reg_addr);
    counter++;
    reg_addr = R_DDR3_PHYDBGSEL;
    placeholder.DDR_regs[counter] = board_port->readio(reg_addr);

    return placeholder;
}


// NETSTAT registers
NETSTAT_struct Get_NETSTAT(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    NETSTAT_struct placeholder;

    placeholder.NETSTAT_regs[counter] = board_port->readio(R_NETSTAT);

    return placeholder;
}


// SATA_DRPctrl registers
SATA_DRPctrl_struct Get_SATA_DRPctrl(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    SATA_DRPctrl_struct placeholder;

    reg_addr = R_PLLDRP;
    placeholder.SATA_DRPctrl_regs[counter] = board_port->readio(reg_addr);
    reg_addr = R_GTXDRP;
    counter++;
    placeholder.SATA_DRPctrl_regs[counter] = board_port->readio(reg_addr);
    reg_addr = R_BKRAM;
    counter++;
    placeholder.SATA_DRPctrl_regs[counter] = board_port->readio(reg_addr);
    reg_addr = R_FLASH;
    counter++;
    placeholder.SATA_DRPctrl_regs[counter] = board_port->readio(reg_addr);
    reg_addr = R_DDR3_CONTROLLER;
    counter++;
    placeholder.SATA_DRPctrl_regs[counter] = board_port->readio(reg_addr);

    return placeholder;
}


// ZIPCtrlDBG registers
ZIPCtrlDBG_struct Get_ZIPCtrlDBG(DEVBUS* board_port){
    reg_width_t reg_addr;
    counter_width_t counter =0;
    ZIPCtrlDBG_struct placeholder;

    placeholder.ZIPCtrlDBG_regs[counter] = board_port->readio(0x80000000);
    counter++;
    board_port->readi(R_ZIPS0, ZIPCtrlDBG_Group-1, &placeholder.ZIPCtrlDBG_regs[counter]);

    return placeholder;
}


