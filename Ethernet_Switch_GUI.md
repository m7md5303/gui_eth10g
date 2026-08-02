**Disclaimer: The Documentation is AI-generated and may make mistakes**

# Ethernet Switch GUI

## Motivation

This project aims to create a user interface (GUI) for an Ethernet switch, specifically focusing on the application layer. The motivation stems from the need to provide a graphical interface for displaying the values of registers within the switch. The network system comprises five layers, with the network layer being handled by the switch. The requirement is to implement an application layer using ImGUI to display these register values.

The Ethernet switch is abbreviated as eth_switch. It contains registers that need to be read and displayed in the GUI.

## Implementation

The implementation details involve how to access and display the registers in the GUI. The eth_switch repository on GitHub includes a software layer called devbus, which serves as an abstract interface for any connection to the board. This layer provides essential functions that any connection to the board must have, regardless of its type or details.

The devbus interface is responsible for abstracting the connection to the board, making it a standardized way to interact with the switch.

To display the register values in the GUI, a connection must be established with the devbus. This connection enables the reading of the switch registers.

Directly accessing the registers in the GUI main would make the system less modular and harder to debug. Additionally, the GUI main would contain details unrelated to how the registers are accessed, making code maintenance and debugging more challenging.

To address these issues, Mohamed created an intermediate software layer (ISWL) between the devbus and the GUI main. This layer implements the details of how to access the switch registers using the devbus and exposes a library of functions to the GUI main for reading the registers.

The ISWL is called read_regs_eth and contains functions responsible for retrieving the values of the register groups. Each group in the regdefs header file has a corresponding function in the read_regs_eth library, which returns a struct containing the array of registers specific to that group.

The regdefs header file defines these groups, and each function in the ISWL maps to a specific group of registers. The functions only require a pointer to an instance of the devbus class.

The functions in the ISWL include:

- Get_GateScope, which returns a GateScope_struct.
- Get_i2cScope, which returns an i2cScope_struct.
- Get_NetScope, which returns a NetScope_struct.
- Get_RouteScope, which returns a RouteScope_struct.
- Get_i2cController, which returns an i2cController_struct.
- Get_Console, which returns a Console_struct.
- Get_Fan, which returns a Fan_struct.
- Get_FPGAConf, which returns a fpgaConf_struct.
- Get_CPUNetCtrl, which returns a cpuNetCtrl_struct.

Each function retrieves the values of the registers in its respective group and returns a struct containing the array of registers specific to that group.
