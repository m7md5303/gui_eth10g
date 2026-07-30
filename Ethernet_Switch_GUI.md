**Disclaimer: The Documentation is AI-generated and may make mistakes**

### Implementation

The motivation for creating a GUI for the Ethernet switch lies in the need to visualize and manage the switch's internal registers, which are crucial for network operations. The switch operates at the network layer, and the application layer requires a graphical interface to interact with these registers. This project aims to abstract the process of accessing these registers, making the system more modular and easier to debug.

The Ethernet switch, abbreviated as eth_switch, contains registers that need to be read and displayed in the GUI. The repository on GitHub, eth_switch, includes a software layer called devbus, which serves as an abstract interface for connections to the board. This layer ensures that any connection to the board adheres to a consistent set of functions, regardless of the type of connection.

To implement the GUI, a connection must be established with the devbus to access the switch's registers. The devbus interface enables reading the switch's registers, but direct access in the GUI main can lead to code unmodularity and make debugging more challenging. Therefore, an intermediate software layer (ISWL) was created to handle the details of accessing the registers using the devbus. This layer exposes a library of functions to the GUI main, allowing it to read the registers without exposing the underlying implementation details.

### Functions Definitions

The regdefs header file contains 202 registers grouped into 10 distinct groups. Each group corresponds to a specific function in the ISWL library, which retrieves the values of the registers within each group. The functions in the ISWL library are responsible for mapping to these groups and returning a struct containing the array of registers specific to each group. The functions in the ISWL library are designed to be simple, receiving only a pointer to an instance of the devbus class. Each function maps to a single group of registers and returns a struct containing the array of registers for that group.

Get_GateScope returns GateScope_struct
Get_GateScope returns GateScope_struct
Get_i2cScope returns i2cScope_struct
Get_NetScope returns NetScope_struct
Get_RouteScope returns RouteScope_struct
Get_i2cController returns i2cController_struct
Get_Console returns Console_struct
Get_Fan returns Fan_struct
Get_FPGAConf returns fpgaConf_struct
Get_CPUNetCtrl returns cpuNetCtrl_struct