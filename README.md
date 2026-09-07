# gui_eth10g
GUI for 10GB Ethernet switch on Kluster Board

## Documentation
Project Documentation is available in this repository in three files using the N4L2Doc Methodology proposed in <a href="https://github.com/regymm/PCIe-DMA-DDR3-Accelerator/blob/main/10-documentation/N4L%20for%20Documentation/n4l2doc.md">this repo</a> :
- Ethernet_Switch_GUI.md
- Ethernet_Switch_GUI_direct_interpretation.md
- eth10_gui.n4l

## Building Steps
For running the GUI, you should go through some steps:

- clone the project
- Open a remote terminal on the rasp pi in the root directory of the cloned project
- run:
```shell
cd backend
./backend
```
- In another terminal in the root directory of the cloned project run:
```shell
python3 -m http.server 3000 -d frontend
```
- On your PC, open a local terminal then run:
```shell
ssh -p <ssh port> -L 3000:127.0.0.1:3000 -L 9001:127.0.0.1:9001 <user_name>@<user_IP_address>
```
This creates two ssh tunnels: one for backend and the other for the frontend
You shall need to contact an admin to know your IP
- Last step is to open your browser and visit :
```web
http://localhost:3000
```
