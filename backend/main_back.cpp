#include <stdio.h>
#include <cstdint>
#include <string>
#ifndef REGGROUP_NUMBERS_H
#include "reggroup_numbers.h"
#endif
#ifndef READ_REGS_ETH_H
#include "read_regs_eth.h"
#endif
#include "./../../test/eth10g/sw/host/ttybus.h"
#include "./../../test/eth10g/sw/host/port.h"
#include <iostream>
#include "./../IXWebSocket/ixwebsocket/IXWebSocketServer.h"
#include "./../IXWebSocket/ixwebsocket/IXWebSocket.h"
          
#define MAX_SIZE 60 //max size is router_group = 60


typedef	TTYBUS FPGA;

FPGA	*m_fpga;
int read_tot =0;
FlashCfg_struct flash_backend;
EMMCScope_struct emmcscope_backend;
i2cScope_struct i2cscope_backend;
NetScope_struct netscope_backend;
RouteScope_struct routescope_backend;
SATA_DRPScope_struct satadrpscope_backend;
SATA_LScope_struct satalscope_backend;
SATA_PSScope_struct satapsscope_backend;
SATA_RSScope_struct satarsscope_backend;
SATA_TSScope_struct satatsscope_backend;
zipScope_struct zipscope_backend;
Console_struct console_backend;
Fan_struct fan_backend;
SATA_ctrl_struct satactrl_backend;
EMMC_Card_struct emmccard_backend;
SDIO_struct sdio_backend;
fpgaCfg_struct fpgacfg_backend;
CPUNet_struct cpunet_backend;
i2cCtrl_struct i2cctrl_backend;
NetMisc_struct netmisc_backend;
Router_struct router_backend;
DDR_struct ddr_backend;
NETSTAT_struct netstat_backend;
SATA_DRPctrl_struct satadrpctrl_backend;
ZIPCtrlDBG_struct zipctrldbg_backend;

std::string payload;
uint8_t i=0;


int main(int argc, char **argv) {

   const char *host = FPGAHOST;
   int port = FPGAPORT;

    m_fpga = new FPGA(new NETCOMMS(host, port));

    ix::WebSocketServer server(9001);

    server.setOnConnectionCallback(
        [](std::weak_ptr<ix::WebSocket> webSocket,
        std::shared_ptr<ix::ConnectionState> connectionState)
        {
            auto ws = webSocket.lock();

            if (!ws)
            {
                std::cout << "Connection no longer exists" << std::endl;
                        
                return;
            }

            std::cout << "Browser connected!" << std::endl;

            ws->setOnMessageCallback(
                [ws, connectionState](
                    const ix::WebSocketMessagePtr& msg)
                {
                    if (msg->type ==
                        ix::WebSocketMessageType::Message)
                    {
                        if(msg->str == "FLASHCFG_Group"){
                            flash_backend = Get_FlashCfg(m_fpga);
                            for (i = 0; i < FLASHCFG_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(flash_backend.FlashCfg_regs[i]);
                                }
                                else {
                                    payload += std::to_string(flash_backend.FlashCfg_regs[i]);
                                }
                                if(i<FLASHCFG_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "EMMC Scope_Group"){
                            emmcscope_backend = Get_EMMCScope(m_fpga);
                            for (i = 0; i < EMMCScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(emmcscope_backend.EMMCScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(emmcscope_backend.EMMCScope_regs[i]);
                                }
                                if(i<EMMCScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "I2C Scope_Group"){
                            i2cscope_backend = Get_i2cScope(m_fpga);
                            for (i = 0; i < i2cScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(i2cscope_backend.i2cScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(i2cscope_backend.i2cScope_regs[i]);
                                }
                                if(i<i2cScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "Net Scope_Group"){
                            netscope_backend = Get_NetScope(m_fpga);
                            for (i = 0; i < netScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(netscope_backend.NetScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(netscope_backend.NetScope_regs[i]);
                                }
                                if(i<netScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "Route Scope_Group"){
                            routescope_backend = Get_RouteScope(m_fpga);
                            for (i = 0; i < RouteScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(routescope_backend.RouteScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(routescope_backend.RouteScope_regs[i]);
                                }
                                if(i<RouteScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "SATA_DRP Scope_Group"){
                            satadrpscope_backend = Get_SATA_DRPScope(m_fpga);
                            for (i = 0; i < SATA_DRPScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(satadrpscope_backend.SATA_DRPScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(satadrpscope_backend.SATA_DRPScope_regs[i]);
                                }
                                if(i<SATA_DRPScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "SATA_L Scope_Group"){
                            satalscope_backend = Get_SATA_LScope(m_fpga);
                            for (i = 0; i < SATA_LScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(satalscope_backend.SATA_LScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(satalscope_backend.SATA_LScope_regs[i]);
                                }
                                if(i<SATA_LScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "SATA_PS Scope_Group"){
                            satapsscope_backend = Get_SATA_PSScope(m_fpga);
                            for (i = 0; i < SATA_PSScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(satapsscope_backend.SATA_PSScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(satapsscope_backend.SATA_PSScope_regs[i]);
                                }
                                if(i<SATA_PSScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "SATA_RS Scope_Group"){
                            satarsscope_backend = Get_SATA_RSScope(m_fpga);
                            for (i = 0; i < SATA_RSScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(satarsscope_backend.SATA_RSScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(satarsscope_backend.SATA_RSScope_regs[i]);
                                }
                                if(i<SATA_RSScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "SATA_TS Scope_Group"){
                            satatsscope_backend = Get_SATA_TSScope(m_fpga);
                            for (i = 0; i < SATA_TSScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(satatsscope_backend.SATA_TSScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(satatsscope_backend.SATA_TSScope_regs[i]);
                                }
                                if(i<SATA_TSScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "ZIP Scope_Group"){
                            zipscope_backend = Get_zipScope(m_fpga);
                            for (i = 0; i < zipScope_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(zipscope_backend.zipScope_regs[i]);
                                }
                                else {
                                    payload += std::to_string(zipscope_backend.zipScope_regs[i]);
                                }
                                if(i<zipScope_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "Console_Group"){
                            console_backend = Get_Console(m_fpga);
                            for (i = 0; i < Console_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(console_backend.Console_regs[i]);
                                }
                                else {
                                    payload += std::to_string(console_backend.Console_regs[i]);
                                }
                                if(i<Console_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "Fan_Group"){
                            fan_backend = Get_Fan(m_fpga);
                            for (i = 0; i < Fan_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(fan_backend.Fan_regs[i]);
                                }
                                else {
                                    payload += std::to_string(fan_backend.Fan_regs[i]);
                                }
                                if(i<Fan_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "SATA_ctrl_Group"){
                            satactrl_backend = Get_SATA_ctrl(m_fpga);
                            for (i = 0; i < SATA_ctrl_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(satactrl_backend.SATA_ctrl_regs[i]);
                                }
                                else {
                                    payload += std::to_string(satactrl_backend.SATA_ctrl_regs[i]);
                                }
                                if(i<SATA_ctrl_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "EMMC_Card_Group"){
                            emmccard_backend = Get_EMMC_Card(m_fpga);
                            for (i = 0; i < EMMC_Card_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(emmccard_backend.EMMC_Card_regs[i]);
                                }
                                else {
                                    payload += std::to_string(emmccard_backend.EMMC_Card_regs[i]);
                                }
                                if(i<EMMC_Card_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "SDIO_Group"){
                            sdio_backend = Get_SDIO(m_fpga);
                            for (i = 0; i < SDIO_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(sdio_backend.SDIO_regs[i]);
                                }
                                else {
                                    payload += std::to_string(sdio_backend.SDIO_regs[i]);
                                }
                                if(i<SDIO_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "FPGA Cfg_Group"){
                            fpgacfg_backend = Get_fpgaCfg(m_fpga);
                            for (i = 0; i < fpgaCfg_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(fpgacfg_backend.fpgaCfg_regs[i]);
                                }
                                else {
                                    payload += std::to_string(fpgacfg_backend.fpgaCfg_regs[i]);
                                }
                                if(i<fpgaCfg_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "CPUNet_Group"){
                            cpunet_backend = Get_CPUNet(m_fpga);
                            for (i = 0; i < CPUNet_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(cpunet_backend.CPUNet_regs[i]);
                                }
                                else {
                                    payload += std::to_string(cpunet_backend.CPUNet_regs[i]);
                                }
                                if(i<CPUNet_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "I2C Ctrl_Group"){
                            i2cctrl_backend = Get_i2cCtrl(m_fpga);
                            for (i = 0; i < i2cCtrl_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(i2cctrl_backend.i2cCtrl_regs[i]);
                                }
                                else {
                                    payload += std::to_string(i2cctrl_backend.i2cCtrl_regs[i]);
                                }
                                if(i<i2cCtrl_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "NetMisc_Group"){
                            netmisc_backend = Get_NetMisc(m_fpga);
                            for (i = 0; i < NetMisc_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(netmisc_backend.NetMisc_regs[i]);
                                }
                                else {
                                    payload += std::to_string(netmisc_backend.NetMisc_regs[i]);
                                }
                                if(i<NetMisc_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "Router_Group"){
                            router_backend = Get_Router(m_fpga);
                            for (i = 0; i < Router_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(router_backend.Router_regs[i]);
                                }
                                else {
                                    payload += std::to_string(router_backend.Router_regs[i]);
                                }
                                if(i<Router_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "DDR_Group"){
                            ddr_backend = Get_DDR(m_fpga);
                            for (i = 0; i < DDR_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(ddr_backend.DDR_regs[i]);
                                }
                                else {
                                    payload += std::to_string(ddr_backend.DDR_regs[i]);
                                }
                                if(i<DDR_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "NETSTAT_Group"){
                            netstat_backend = Get_NETSTAT(m_fpga);
                            for (i = 0; i < NETSTAT_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(netstat_backend.NETSTAT_regs[i]);
                                }
                                else {
                                    payload += std::to_string(netstat_backend.NETSTAT_regs[i]);
                                }
                                if(i<NETSTAT_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "SATA_DRPctrl_Group"){
                            satadrpctrl_backend = Get_SATA_DRPctrl(m_fpga);
                            for (i = 0; i < SATA_DRPctrl_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(satadrpctrl_backend.SATA_DRPctrl_regs[i]);
                                }
                                else {
                                    payload += std::to_string(satadrpctrl_backend.SATA_DRPctrl_regs[i]);
                                }
                                if(i<SATA_DRPctrl_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        else if(msg->str == "ZIPCtrlDBG_Group"){
                            zipctrldbg_backend = Get_ZIPCtrlDBG(m_fpga);
                            for (i = 0; i < ZIPCtrlDBG_Group; i++)
                            {
                                if(i==0){
                                    payload = std::to_string(zipctrldbg_backend.ZIPCtrlDBG_regs[i]);
                                }
                                else {
                                    payload += std::to_string(zipctrldbg_backend.ZIPCtrlDBG_regs[i]);
                                }
                                if(i<ZIPCtrlDBG_Group-1){
                                    payload += ',';
                                }
                            }
                        }
                        ws->send(payload);
                    }
                });
        });

    auto res = server.listen();

    if (!res.first)
    {
        std::cerr << "Failed to start WebSocket server: " << res.second << std::endl;
                
        return 1;
    }

    server.start();

    std::cout << "WebSocket server started on port 9001" << std::endl;
    

    while(1);
    
    delete m_fpga;
    server.stop();
    return 0;
}
