# Ethernet Switch GUI
## Motivation

This section is to discuss the motivation of this project and why it matters to create a GUI for the switch.

Typically, network systems consists of 5 layers starting from the physical layer up to the application layer while passing through the network layer.

The ethernet switch is responsible for the network layer. The requirement was to create an application layer using ImGUI for displaying the values of registers inside the switch.

Ethernet switch has abbreviation eth_switch

Ethernet switch contains registers to be read

## Implementation

This section is to cover the implementation details of how to read the registers in the switch to display them in the GUI Main

The eth_switch repository on github has an interface software layer called devbus. It is responsible for providing the essential functions that any connection to the board has to provide regardless its type and the details of this connection making it an abstract way of interfacing with the switch.

eth_switch sw layer has resource/reference github.com/ZipCPU/eth10g/tree/master/sw/host

eth_switch sw layer contains abstract interface for connections to the board

Abstract interface for connections to the board is called devbus

The previous givens implies that the GUI that is to display the registers values has to initiate a connection with the devbus to be able to access the switch registers.

System details implies devbus connection initiating

devbus connection initiating enables reading switch registers

Direct registers reading in GUI main will make the system unmodular and will make code debugging harder. Additionally, the GUI main will contain details that the application engineer doesnot have to concern about related to how the registers are read

Direct registers access in GUI main implies code unmodularity

Direct registers access in GUI main implies harder debugging

Direct registers access in GUI main implies exposing application engineer to non relavant details

Mohamed created an intermediate software layer between the devbus and the GUI main. This layer is responsible for the implementation of the details of how to access the switch registers using the devbus. This layer exposes a library of functions to the GUI main that can read the registers from instead of adding these details to the GUI main

The intermediate software layer can be abbreviated as ISWL while being called read_regs_eth

intermediate software layer has abbreviation ISWL

intermediate software layer is created by Mohamed

intermediate software layer has subject role performing the details of registers access using the devbus

intermediate software layer has subject role exposing library of functions for the GUI main to read registers from

intermediate software layer is called read_regs_eth

The functions in this layer or library are responsible for retrieving the value of the registers groups. These groups are defined in regdefs header file. Each group in the regdefs has a separate function in the read_regs_eth that is responsible for reading the registers values of this group. Each function returns a struct where this struct contains the array of the registers of this group

functions in ISWL has subject role retrieving registers values in groups

regdefs header file contains the definition of these groups

Each function map to separate group

Each function gives the registers values of this group

Each function gives a single struct

Each struct contains array of registers specific to its group

## Functions Definitions

In this section, the functions are revealed

The registers in regdefs header are 249 registers grouped in 25 groups

regdefs header contains 249 registers

regdefs header consists of 25 groups

This leads to having 25 functions where each function maps to a single group of registers

Functions only receive a pointer to an instance of the devbus class

Functions has an attribute pointer to an instance of the devbus class

Get_EMMCScope function returns EMMCScope_struct

Get_i2cScope function returns i2cScope_struct

Get_NetScope function returns NetScope_struct

Get_RouteScope function returns RouteScope_struct

Get_SATA_DRPScope function returns SATA_DRPScope_struct

Get_SATA_LScope function returns SATA_LScope_struct

Get_SATA_PSScope function returns SATA_PSScope_struct

Get_SATA_RSScope function returns SATA_RSScope_struct

Get_SATA_TSScope function returns SATA_TSScope_struct

Get_zipScope function returns zipScope_struct

Get_Console function returns Console_struct

Get_Fan function returns Fan_struct

Get_SATA_ctrl function returns SATA_ctrl_struct

Get_EMMC_Card function returns EMMC_Card_struct

Get_SDIO function returns SDIO_struct

Get_fpgaCfg function returns fpgaCfg_struct

Get_CPUNet function returns CPUNet_struct

Get_i2cCtrl function returns i2cCtrl_struct

Get_NetMisc function returns NetMisc_struct

Get_Router function returns Router_struct

Get_DDR function returns DDR_struct

Get_NETSTAT function returns NETSTAT_struct

Get_SATA_DRPctrl function returns SATA_DRPctrl_struct

