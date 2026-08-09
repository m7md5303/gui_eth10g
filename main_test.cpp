#include <stdio.h>
#include <cstdint>
#include "read_regs_eth.h"
#include "./../test/eth10g/sw/host/ttybus.h"
#include "./../test/eth10g/sw/host/port.h"

typedef	TTYBUS FPGA;

FPGA	*m_fpga;
int read_tot =0;

int main(int argc, char **argv) {

   const char *host = FPGAHOST;
   int port = FPGAPORT;

    m_fpga = new FPGA(new NETCOMMS(host, port));

    printf("flash regs\n");
    FlashCfg_struct flash_test;
    flash_test = Get_FlashCfg(m_fpga);
    for(int i =0;i<FLASHCFG_Group;i++) {
        printf("%0x\n", flash_test.FlashCfg_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("emmcscope regs\n");
    EMMCScope_struct emmcscope_test;
    emmcscope_test = Get_EMMCScope(m_fpga);
    for(int i =0;i<EMMCScope_Group;i++) {
        printf("%0x\n", emmcscope_test.EMMCScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("i2cscope regs\n");
    i2cScope_struct i2cscope_test;
    i2cscope_test = Get_i2cScope(m_fpga);
    for(int i =0;i<i2cScope_Group;i++) {
        printf("%0x\n", i2cscope_test.i2cScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("netscope regs\n");
    NetScope_struct netscope_test;
    netscope_test = Get_NetScope(m_fpga);
    for(int i =0;i<netScope_Group;i++) {
        printf("%0x\n", netscope_test.NetScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("routescope regs\n");
    RouteScope_struct routescope_test;
    routescope_test = Get_RouteScope(m_fpga);
    for(int i =0;i<RouteScope_Group;i++) {
        printf("%0x\n", routescope_test.RouteScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("satadrpscope regs\n");
    SATA_DRPScope_struct satadrpscope_test;
    satadrpscope_test = Get_SATA_DRPScope(m_fpga);
    for(int i =0;i<SATA_DRPScope_Group;i++) {
        printf("%0x\n", satadrpscope_test.SATA_DRPScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("satalscope regs\n");
    SATA_LScope_struct satalscope_test;
    satalscope_test = Get_SATA_LScope(m_fpga);
    for(int i =0;i<SATA_LScope_Group;i++) {
        printf("%0x\n", satalscope_test.SATA_LScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("satapsscope regs\n");
    SATA_PSScope_struct satapsscope_test;
    satapsscope_test = Get_SATA_PSScope(m_fpga);
    for(int i =0;i<SATA_PSScope_Group;i++) {
        printf("%0x\n", satapsscope_test.SATA_PSScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("satarsscope regs\n");
    SATA_RSScope_struct satarsscope_test;
    satarsscope_test = Get_SATA_RSScope(m_fpga);
    for(int i =0;i<SATA_RSScope_Group;i++) {
        printf("%0x\n", satarsscope_test.SATA_RSScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("satatsscope regs\n");
    SATA_TSScope_struct satatsscope_test;
    satatsscope_test = Get_SATA_TSScope(m_fpga);
    for(int i =0;i<SATA_TSScope_Group;i++) {
        printf("%0x\n", satatsscope_test.SATA_TSScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("zipscope regs\n");
    zipScope_struct zipscope_test;
    zipscope_test = Get_zipScope(m_fpga);
    for(int i =0;i<zipScope_Group;i++) {
        printf("%0x\n", zipscope_test.zipScope_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("consolescope regs\n");
    Console_struct console_test;
    console_test = Get_Console(m_fpga);
    for(int i =0;i<Console_Group;i++) {
        printf("%0x\n", console_test.Console_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("fan regs\n");
    Fan_struct fan_test;
    fan_test = Get_Fan(m_fpga);
    for(int i =0;i<Fan_Group;i++) {
        printf("%0x\n", fan_test.Fan_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("fsatactrl regs\n");
    SATA_ctrl_struct satactrl_test;
    satactrl_test = Get_SATA_ctrl(m_fpga);
    for(int i =0;i<SATA_ctrl_Group;i++) {
        printf("%0x\n", satactrl_test.SATA_ctrl_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("emmccard regs\n");
    EMMC_Card_struct emmccard_test;
    emmccard_test = Get_EMMC_Card(m_fpga);
    for(int i =0;i<EMMC_Card_Group;i++) {
        printf("%0x\n", emmccard_test.EMMC_Card_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("sdio regs\n");
    SDIO_struct sdio_test;
    sdio_test = Get_SDIO(m_fpga);
    for(int i =0;i<SDIO_Group;i++) {
        printf("%0x\n", sdio_test.SDIO_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("fpgacfg regs\n");
    fpgaCfg_struct fpgacfg_test;
    fpgacfg_test = Get_fpgaCfg(m_fpga);
    for(int i =0;i<fpgaCfg_Group;i++) {
        printf("%0x\n", fpgacfg_test.fpgaCfg_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("cpunet regs\n");
    CPUNet_struct cpunet_test;
    cpunet_test = Get_CPUNet(m_fpga);
    for(int i =0;i<CPUNet_Group;i++) {
        printf("%0x\n", cpunet_test.CPUNet_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("i2cctrl regs\n");
    i2cCtrl_struct i2cctrl_test;
    i2cctrl_test = Get_i2cCtrl(m_fpga);
    for(int i =0;i<i2cCtrl_Group;i++) {
        printf("%0x\n", i2cctrl_test.i2cCtrl_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("netmiscellaneous regs\n");
    NetMisc_struct netmisc_test;
    netmisc_test = Get_NetMisc(m_fpga);
    for(int i =0;i<NetMisc_Group;i++) {
        printf("%0x\n", netmisc_test.NetMisc_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("router regs\n");
    Router_struct router_test;
    router_test = Get_Router(m_fpga);
    for(int i =0;i<Router_Group;i++) {
        printf("%0x\n", router_test.Router_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("ddr regs\n");
    DDR_struct ddr_test;
    ddr_test = Get_DDR(m_fpga);
    for(int i =0;i<DDR_Group;i++) {
        printf("%0x\n", ddr_test.DDR_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("netstat regs\n");
    NETSTAT_struct netstat_test;
    netstat_test = Get_NETSTAT(m_fpga);
    for(int i =0;i<NETSTAT_Group;i++) {
        printf("%0x\n", netstat_test.NETSTAT_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("satadrpctrl regs\n");
    SATA_DRPctrl_struct satadrpctrl_test;
    satadrpctrl_test = Get_SATA_DRPctrl(m_fpga);
    for(int i =0;i<SATA_DRPctrl_Group;i++) {
        printf("%0x\n", satadrpctrl_test.SATA_DRPctrl_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);

    printf("zipctrldbg regs\n");
    ZIPCtrlDBG_struct zipctrldbg_test;
    zipctrldbg_test = Get_ZIPCtrlDBG(m_fpga);
    for(int i =0;i<ZIPCtrlDBG_Group;i++) {
        printf("%0x\n", zipctrldbg_test.ZIPCtrlDBG_regs[i]);
        read_tot++;
    }
    printf("\nTotal Read Registers up to this step are %0d\n\n", read_tot);


    printf("////////////////////////////////////////\n//     TEST COMPLETED SUCCESSFULLY   //\n//     READ REGISTERS ARE %0d       //\n/////////////////////////////////////\n", read_tot);

    delete m_fpga;
    return 0;
}
