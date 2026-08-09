**Disclaimer: The Documentation is AI-generated and may make mistakes**

### Title: Ethernet Switch GUI Implementation

#### Motivation
This project aims to create a GUI application for the network layer of an Ethernet switch. The motivation stems from the need to visualize and manage the values of registers within the switch, which are typically handled by the application layer. The switch, abbreviated as eth_switch, contains registers that need to be accessed and displayed in the GUI. The primary goal is to provide a user interface that allows engineers to interact with the switch's internal state without delving into the low-level details of register access.

#### Implementation
The implementation of the GUI application involves connecting to the switch's hardware layer through the devbus interface. The devbus interface is an abstract layer that provides essential functions for interfacing with the switch, regardless of the specific hardware type. The devbus interface is crucial for accessing the switch's registers, which are stored in the switch's hardware layer.

To facilitate the GUI's interaction with the switch, an intermediate software layer (ISWL)-called read_regs_eth-was created. This layer abstracts the details of how to access the switch's registers using the devbus interface. The ISWL exposes a library of functions to the GUI main that can read the registers from the devbus interface. This approach ensures that the GUI main remains modular and easier to debug, as it does not need to handle the low-level details of register access.

The ISWL functions retrieve the values of the registers groups. Each group is defined in the regdefs header file, and each group has a corresponding function in the ISWL that reads the registers' values. Each function returns a struct containing an array of registers specific to its group.

#### Functions Definitions
The regdefs header file contains 249 registers grouped into 25 distinct groups. Each group corresponds to a specific function in the ISWL, which retrieves the values of the registers in that group. The functions in the ISWL are responsible for accessing the registers through the devbus interface and returning the register values in a structured format. Each function maps to a specific group of registers and returns a struct containing the array of registers specific to that group.

The functions in the ISWL are as follows:

- **Get_EMMCScope**: Returns an EMMCScope_struct.
- **Get_i2cScope**: Returns an i2cScope_struct.
- **Get_NetScope**: Returns a NetScope_struct.
- **Get_RouteScope**: Returns a RouteScope_struct.
- **Get_SATA_DRPScope**: Returns a SATA_DRPScope_struct.
- **Get_SATA_LScope**: Returns a SATA_LScope_struct.
- **Get_SATA_PSScope**: Returns a SATA_PSScope_struct.
- **Get_SATA_RSScope**: Returns a SATA_RSScope_struct.
- **Get_SATA_TSScope**: Returns a SATA_TSScope_struct.
- **Get_zipScope**: Returns a zipScope_struct.
- **Get_Console**: Returns a Console_struct.
- **Get_Fan**: Returns a Fan_struct.
- **Get_SATA_ctrl**: Returns a SATA_ctrl_struct.
- **Get_EMMC_Card**: Returns an EMMC_Card_struct.
- **Get_SDIO**: Returns an SDIO_struct.
- **Get_fpgaCfg**: Returns a fpgaCfg_struct.
- **Get_CPUNet**: Returns a CPUNet_struct.
- **Get_i2cCtrl**: Returns an i2cCtrl_struct.
- **Get_NetMisc**: Returns a NetMisc_struct.
- **Get_Router**: Returns a Router_struct.
- **Get_DDR**: Returns a DDR_struct.
- **Get_NETSTAT**: Returns a NETSTAT_struct.
- **Get_SATA_DRPctrl**: Returns a SATA_DRPctrl_struct.

Each function is meticulously designed to ensure the accurate and efficient retrieval of the respective structures, facilitating further analysis and integration within the project.
