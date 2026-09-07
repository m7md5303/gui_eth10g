**Disclaimer: The Documentation is AI-generated and may make mistakes**

### Motivation

This section outlines the rationale behind creating a GUI for the Ethernet switch. The network system comprises five layers, starting from the physical layer to the application layer, with the network layer being handled by the switch. The requirement is to implement an application layer using ImGUI to display the values of registers within the switch. The switch is abbreviated as eth_switch, and it contains registers that need to be accessed and displayed.

### Implementation

The implementation details focus on how to access and display the switch's registers through the GUI. The eth_switch repository on GitHub includes a software layer called devbus, which serves as an abstract interface for any connection to the board, ensuring compatibility regardless of the type of connection. The devbus interface is defined in the sw/host directory of the eth_switch repository. The devbus interface enables the GUI to connect to the switch and access its registers.

To achieve this, the GUI needs to establish a connection with the devbus. This connection allows the GUI to read the switch's registers. Directly accessing the registers in the GUI main would make the system less modular and harder to debug. Additionally, the GUI would contain details unrelated to the register reading process, which the application engineer should not be concerned with.

Mohamed created an intermediate software layer (ISWL) between the devbus and the GUI main. This layer implements the details of accessing the switch's registers using the devbus and exposes a library of functions to the GUI main for reading the registers. The ISWL is called read_regs_eth. The functions in this layer retrieve the values of register groups, each group having a separate function responsible for reading the registers' values. Each function returns a struct containing an array of registers specific to its group.

### Functions Definitions

The functions in the ISWL are defined to retrieve the values of the 249 registers grouped into 25 groups. Each function corresponds to a specific group of registers. The functions receive a pointer to an instance of the devbus class. The functions return structs containing arrays of registers specific to their group. The functions are named according to the group they handle, such as Get_EMMCScope, Get_i2cScope, Get_NetScope, etc.

### Front End Implementation

The front-end implementation uses ImGUI, an open-source library available on GitHub. ImGUI is chosen for its flexibility in rendering graphics and transitions. The front-end GUI is compiled to WebAssembly (WASM) and deployed as a web application, allowing users to view it in their browser. The front-end receives the register values from the backend and displays them in a user-friendly manner, ensuring readability and understanding.

### Front End Implementation

The front-end GUI is implemented using ImGUI, which is an open-source library available on GitHub. ImGUI is chosen for its flexibility in rendering graphics and transitions. The front-end GUI is compiled to WebAssembly (WASM) and deployed as a web application, allowing users to view it in their browser. The front-end receives the register values from the backend and displays them in a user-friendly manner, ensuring readability and understanding.

The GUI design is adjusted to be user-friendly. There are 25 buttons corresponding to the 25 groups of registers. Each button displays the register values for its corresponding group. The register values are displayed in a table-like view, with each value accompanied by its corresponding register name. Additionally, the group name is displayed beneath the table to inform the user which group is currently being displayed. The register values are updated every 200 frames to avoid overwhelming the backend.

### Connecting the Backend and the Frontend

The frontend is compiled to WebAssembly, which means direct calls to the backend functions are not possible. A web socket is created between the backend and the frontend to facilitate communication. The backend uses the IXWebSocket library to create the web socket, while the frontend uses EMSDK web sockets, which are more appropriate given the compilation process. The web socket connects the frontend to the backend, allowing them to communicate properly.

### Testing

The testing section covers how the system was tested, including verifying the displayed register values and the communication between the frontend and the backend. After compiling the backend part, the backend binary runs, creating a backend server waiting for client requests. Similarly, the frontend web app initiates a web socket connected to the same backend server. The values are compared against previously printed ones to verify both the GUI implementation and the communication between the two parts of the system.
