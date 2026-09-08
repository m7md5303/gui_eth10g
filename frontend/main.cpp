/*MIT License

Copyright (c) 2026 MohamedKhaled5303

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.*/

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <string>
#include <sstream>
#include <iostream>
#include <emscripten/websocket.h>

#ifndef REGGROUP_NUMBERS_H
#include "./../read_layer/reggroup_numbers.h"
#endif
#ifndef READ_REGS_ETH_H
#include "./../read_layer/read_regs_eth.h"
#endif
#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#define GROUP_NO 25
#define UPDATE_RATE 200


#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

// This example can also compile and run with Emscripten! See 'Makefile.emscripten' for details.
#ifdef __EMSCRIPTEN__
#include "../src/emscripten_mainloop_stub.h"
#endif
 
static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}


uint8_t update_guard=UPDATE_RATE;//control update rate
//received data
std::string payload_rec = "00000";
//Register Names
const char* FLASHCFG_Regname[FLASHCFG_Group] = {"FLASHCFG"};
const char* const EMMCScope_Regname[EMMCScope_Group] = {"EMMCSCOPE", "EMMCSCOPED"};
const char* const i2cScope_Regname[i2cScope_Group] = {"I2CSCOPE", "I2CSCOPED"};
const char* const netScope_Regname[netScope_Group] = {"NETSCOPE", "NETSCOPED"};
const char* const RouteScope_Regname[RouteScope_Group] = {"ROUTESCOPE", "ROUTESCOPED"};
const char* const SATA_DRPScope_Regname[SATA_DRPScope_Group] = {"SATADRPSCOPE", "SATADRPSCOPED"};
const char* const SATA_LScope_Regname[SATA_LScope_Group] = {"SATALSCOPE", "SATALSCOPED"};
const char* const SATA_PSScope_Regname[SATA_PSScope_Group] = {"SATAPSCOPE", "SATAPSCOPED"};
const char* const SATA_RSScope_Regname[SATA_RSScope_Group] = {"SATARSCOPE", "SATARSCOPED"};
const char* const SATA_TSScope_Regname[SATA_TSScope_Group] = {"SATATSCOPE", "SATATSCOPED"};
const char* const zipScope_Regname[zipScope_Group] = {"ZIPSCOPE", "ZIPSCOPED"};
const char* const Console_Regname[Console_Group] = {"CONSOLE_FIFO", "CONSOLE_UARTRX", "CONSOLE_UARTTX"};
const char* const Fan_Regname[Fan_Group] = {"FAN_FPGAPWM", "FAN_SYSPWM", "FAN_TACH", "FAN_TEMP", "FAN", "FAN_OVW", "FAN_ADDR", "FAN_CKCOUNT"};
const char* const SATA_ctrl_Regname[SATA_ctrl_Group] = {"SATA", "LBALO", "LBAHI", "SATACOUNT", "SATAPHY", "SATAADDR"};
const char* const EMMC_Card_Regname[EMMC_Card_Group] = {"EMMC_CTRL", "EMMC_DATA", "EMMC_FIFOA", "EMMC_FIFOB", "EMMC_PHY", "EMMC_DMAA", "EMMC_DMALN", "EMMC_TRIM", "EMMC_RXTRIM"};
const char* const SDIO_Regname[SDIO_Group] = {"SDIO_CTRL", "SDIO_DATA", "SDIO_FIFOA", "SDIO_FIFOB", "SDIO_PHY", "SDIO_DMAA", "SDIO_DMALN", "SDIO_TRIM", "SDIO_RXTRIM"};
const char* const fpgaCfg_Regname[fpgaCfg_Group] = {"CFG_CRC", "CFG_FAR", "CFG_FDRI", "CFG_FDRO", "CFG_CMD", "CFG_CTL0", "CFG_MASK", "CFG_STAT", "CFG_LOUT", "CFG_COR0", "CFG_MFWR", "CFG_CBC", "CFG_IDCODE", "CFG_AXSS", "CFG_COR1", "CFG_WBSTAR", "CFG_TIMER", "CFG_BOOTSTS", "CFG_CTL1", "CFG_BSPI"};
const char* const CPUNet_Regname[CPUNet_Group] = {"CPUNET", "CPUNETMAC1", "CPUNETMAC2", "CPUNETIPV4", "CPUNETIPV6P1", "CPUNETIPV6P2", "CPUNETIPV6P3", "CPUNETIPV6P4", "CPUNETRXDROPS", "CPUNETRXPKTS", "CPUNETTXPKTS", "CPUNETTX_BASE", "CPUNETTX_LEN", "CPUNETTX_RPTR", "CPUNETTX_WPTR", "CPUNETRX_BASE", "CPUNETRX_LEN", "CPUNETRX_RPTR", "CPUNETRX_WPTR", "CPUNETRX_DBG", "CPUNETTX_DBG"};
const char* const i2cCtrl_Regname[i2cCtrl_Group] = {"I2CCPU", "I2CCPU_OVW", "I2CCPU_ADDR", "I2CCPU_CKCOUNT", "I2CDMA", "I2CDMA_ADDR", "I2CDMA_BASE", "I2CDMA_LEN"};
const char* const NetMisc_Regname[NetMisc_Group] = {"RXNETCK0", "RXNETCK1", "RXNETCK2", "RXNETCK3", "TXNETCLK", "BUILDTIME", "GPIO", "NETDBG", "NETLOCK", "NETRESET", "PWRCOUNT", "RTCCOUNT", "SATAREF", "SATARX", "SATATX", "SCOPEPIC", "SICLKFREQ", "SIREFCLK", "SIREFFREQ", "SPIO", "VERSION"};
const char* const Router_Regname[Router_Group] = {"ROUTER0", "ROUTERSZ0", "ROUTERWR0", "ROUTERRD0", "ROUTER1", "ROUTERSZ1", "ROUTERWR1", "ROUTERRD1", "ROUTER2", "ROUTERSZ2", "ROUTERWR2", "ROUTERRD2", "ROUTER3", "ROUTERSZ3", "ROUTERWR3", "ROUTERRD3", "ROUTERPK0", "ROUTERBY0", "ROUTERFP0", "ROUTERFB0", "ROUTERPK1", "ROUTERBY1", "ROUTERFP1", "ROUTERFB1", "ROUTERPK2", "ROUTERBY2", "ROUTERFP2", "ROUTERFB2", "ROUTERPK3", "ROUTERBY3", "ROUTERFP3", "ROUTERFB3", "ROUTERNWH0", "ROUTERNWL0", "ROUTERLKH0", "ROUTERLKL0", "ROUTERNWH1", "ROUTERNWL1", "ROUTERLKH1", "ROUTERLKL1", "ROUTERNWH2", "ROUTERNWL2", "ROUTERLKH2", "ROUTERLKL2", "ROUTERNWH3", "ROUTERNWL3", "ROUTERLKH3", "ROUTERLKL3", "ROUTERNWH4", "ROUTERNWL4", "ROUTERLKH4", "ROUTERLKL4", "ROUTERDBG0", "ROUTERDBG1", "ROUTERDBG2", "ROUTERDBG3", "ROUTERDBG4", "ROUTERNEVER", "ROUTERALWAYS", "ROUTERDBGS"};
const char* const DDR_Regname[DDR_Group] = {"DDR3_PHY", "DDR3_PHYSTAT1", "DDR3_PHYSTAT2", "DDR3_PHYSTAT3", "DDR3_PHYCTRLSTAT", "DDR3_PHYRESET", "DDR3_PHYDBGSEL"};
const char* const NETSTAT_Regname[NETSTAT_Group] = {"NETSTAT"};
const char* const SATA_DRPctrl_Regname[SATA_DRPctrl_Group] = {"PLLDRP", "GTXDRP", "BKRAM", "FLASH", "DDR3_CONTROLLER"};
const char* const ZIPCtrlDBG_Regname[ZIPCtrlDBG_Group] = {"ZIPCTRL", "ZIPS0", "ZIPS1", "ZIPS2", "ZIPS3", "ZIPS4", "ZIPS5", "ZIPS6", "ZIPS7", "ZIPS8", "ZIPS9", "ZIPS10", "ZIPS11", "ZIPS12", "ZIPSSP", "ZIPCC", "ZIPPC", "ZIPU0", "ZIPU1", "ZIPU2", "ZIPU3", "ZIPU4", "ZIPU5", "ZIPU6", "ZIPU7", "ZIPU8", "ZIPU9", "ZIPU10", "ZIPU11", "ZIPU12", "ZIPUSP", "ZIPUCC", "ZIPUPC", "ZIPPIC", "ZIPWDOG", "ZIPBDOG", "ZIPAPIC", "ZIPTIMA", "ZIPTIMB", "ZIPTIMC", "ZIPJIFF", "ZIPMTASK", "ZIPMMSTL", "ZIPMPSTL", "ZIPMINSN", "ZIPUTASK", "ZIPUMSTL", "ZIPUPSTL", "ZIPUINSN", "ZIPDMAC"};
//Register Names ptrs
const char* const* reg_ptr_array[GROUP_NO] = {
    FLASHCFG_Regname,
    EMMCScope_Regname,
    i2cScope_Regname,
    netScope_Regname,
    RouteScope_Regname,
    SATA_DRPScope_Regname,
    SATA_LScope_Regname,
    SATA_PSScope_Regname,
    SATA_RSScope_Regname,
    SATA_TSScope_Regname,
    zipScope_Regname,
    Console_Regname,
    Fan_Regname,
    SATA_ctrl_Regname,
    EMMC_Card_Regname,
    SDIO_Regname,
    fpgaCfg_Regname,
    CPUNet_Regname,
    i2cCtrl_Regname,
    NetMisc_Regname,
    Router_Regname,
    DDR_Regname,
    NETSTAT_Regname,
    SATA_DRPctrl_Regname,
    ZIPCtrlDBG_Regname
};

//create websocket 
EMSCRIPTEN_WEBSOCKET_T ws_handle;
bool is_ws_connected = false;


EM_BOOL on_open(int eventType, const EmscriptenWebSocketOpenEvent *websocketEvent, void *userData) {
    std::cout << "Connected to IXWebSocket server!" << std::endl;
    is_ws_connected=true;
    return EM_TRUE;
}

EM_BOOL on_message(int eventType, const EmscriptenWebSocketMessageEvent *websocketEvent, void *userData) {
    if (websocketEvent->isText) {
        payload_rec = std::string((char*)websocketEvent->data, websocketEvent->numBytes);
    }
    return EM_TRUE;
}

EM_BOOL on_error(int eventType, const EmscriptenWebSocketErrorEvent *websocketEvent, void *userData) {
    std::cout << "WebSocket error" << std::endl;
    is_ws_connected=false;
    return EM_TRUE;
}

EM_BOOL on_close(int eventType, const EmscriptenWebSocketCloseEvent *websocketEvent, void *userData) {
    std::cout << "Connection closed" << std::endl;
    is_ws_connected=false;
    return EM_TRUE;
}


//enable the selected group only
void SelectTab(bool& selected, bool** tabs)
{
    for (int i = 0; i < GROUP_NO; i++)
        *tabs[i] = false;

    selected = true;
}

void TextCenteredInCell(uint32_t value, uint8_t group_id, uint8_t reg_idx)
{

    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetWindowFontScale(1.5f * (io.DisplaySize.x/1620.0));

    float cell_width = ImGui::GetColumnWidth();
    float text_width = ImGui::CalcTextSize("R_XXXXXXXXXX: 0xFFFFFFFF").x;
    
    // Calculate centered cursor position within the current cell
    float start_x = ImGui::GetCursorPosX() + (cell_width - text_width) * 0.5f;
    
    // Prevent negative offset if text is wider than the column
    if (start_x > ImGui::GetCursorPosX()) {
        ImGui::SetCursorPosX(start_x);
    }
    
    ImGui::TextColored(
    ImVec4(0.0f, 0.0f, 0.0f, 1.0f),
    "%s: 0x%08X",reg_ptr_array[group_id][reg_idx] ,value
    );

    ImGui::SetWindowFontScale(1.0f);
}

//create the layout for the desired group
void DrawRegisterTabs(uint8_t group , uint8_t group_id_f)
{
    std::stringstream ss(payload_rec);
    std::string value;

    int NumberOfColumns = (group + 9) / 10;
    uint8_t covered_regs= 0;

    ImGui::PushStyleColor(ImGuiCol_TableRowBg, ImVec4(1, 1, 1, 1));
    ImGui::PushStyleColor(ImGuiCol_TableRowBgAlt, ImVec4(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f));
    ImGui::Dummy(ImVec2(0.0f, 50.0f));
    if (ImGui::BeginTable("MyTable", NumberOfColumns, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingStretchSame ))
    {
        for (uint8_t i = 0; i < 10; i++)
        {
            ImGui::TableNextRow();
            for (uint8_t i = 0; i < NumberOfColumns; i++)
            {
                std::getline(ss, value, ',');
                ImGui::TableNextColumn();
                ImGui::SetWindowFontScale(1.3f);
                TextCenteredInCell(std::stoul(value , nullptr, 10) , group_id_f, covered_regs);
                ImGui::SetWindowFontScale(1.0f);
                covered_regs++;
                if(covered_regs>=group){
                    break;
                }
            }
                if(covered_regs>=group){
                    break;
                }
        }

        ImGui::EndTable();
        ImGui::PopStyleColor(2);
    }  
}



// Main code
int main(int, char**)
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100 (WebGL 1.0)
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(IMGUI_IMPL_OPENGL_ES3)
    // GL ES 3.0 + GLSL 300 es (WebGL 2.0)
    const char* glsl_version = "#version 300 es";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    // Create window with graphics context
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor()); // Valid on GLFW 3.3+ only
    GLFWwindow* window = glfwCreateWindow((int)(1280 * main_scale), (int)(800 * main_scale), "KlusterLab User Interface", nullptr, nullptr);
    if (window == nullptr)
        return 1;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync
 
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup scaling
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
    style.FontScaleDpi = main_scale;        // Set initial font scale. (in docking branch: using io.ConfigDpiScaleFonts=true automatically overrides this for every window depending on the current monitor)

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
    ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
    ImGui_ImplOpenGL3_Init(glsl_version);


    // tab states
    bool FLASHCFG_tab = true;
    bool EMMCScope_tab = false;
    bool i2cScope_tab = false;
    bool netScope_tab = false;
    bool RouteScope_tab = false;
    bool SATA_DRPScope_tab = false;
    bool SATA_LScope_tab = false;
    bool SATA_PSScope_tab = false;
    bool SATA_RSScope_tab = false;
    bool SATA_TSScope_tab = false;
    bool zipScope_tab = false;
    bool Console_tab = false;
    bool Fan_tab = false;
    bool SATA_ctrl_tab = false;
    bool EMMC_Card_tab = false;
    bool SDIO_tab = false;
    bool fpgaCfg_tab = false;
    bool CPUNet_tab = false;
    bool i2cCtrl_tab = false;
    bool NetMisc_tab = false;
    bool Router_tab = false;
    bool DDR_tab = false;
    bool NETSTAT_tab = false;
    bool SATA_DRPctrl_tab = false;
    bool ZIPCtrlDBG_tab = false;

    uint8_t previous_choice=25;

    bool* tabs[25] = {
    &FLASHCFG_tab,
    &EMMCScope_tab,
    &i2cScope_tab,
    &netScope_tab,
    &RouteScope_tab,
    &SATA_DRPScope_tab,
    &SATA_LScope_tab,
    &SATA_PSScope_tab,
    &SATA_RSScope_tab,
    &SATA_TSScope_tab,
    &zipScope_tab,
    &Console_tab,
    &Fan_tab,
    &SATA_ctrl_tab,
    &EMMC_Card_tab,
    &SDIO_tab,
    &fpgaCfg_tab,
    &CPUNet_tab,
    &i2cCtrl_tab,
    &NetMisc_tab,
    &Router_tab,
    &DDR_tab,
    &NETSTAT_tab,
    &SATA_DRPctrl_tab,
    &ZIPCtrlDBG_tab
    };

    ImVec4 back_color = ImVec4(0.0902f, 0.0627f, 0.3804f, 1.0f);//background color

    uint8_t group_no[25] = {
    FLASHCFG_Group,
    EMMCScope_Group,
    i2cScope_Group,
    netScope_Group,
    RouteScope_Group,
    SATA_DRPScope_Group,
    SATA_LScope_Group,
    SATA_PSScope_Group,
    SATA_RSScope_Group,
    SATA_TSScope_Group,
    zipScope_Group,
    Console_Group,
    Fan_Group,
    SATA_ctrl_Group,
    EMMC_Card_Group,
    SDIO_Group,
    fpgaCfg_Group,
    CPUNet_Group,
    i2cCtrl_Group,
    NetMisc_Group,
    Router_Group,
    DDR_Group,
    NETSTAT_Group,
    SATA_DRPctrl_Group,
    ZIPCtrlDBG_Group
    };

const char* group_names[25] = {
    "FLASHCFG_Group",
    "EMMC Scope_Group",
    "I2C Scope_Group",
    "Net Scope_Group",
    "Route Scope_Group",
    "SATA_DRP Scope_Group",
    "SATA_L Scope_Group",
    "SATA_PS Scope_Group",
    "SATA_RS Scope_Group",
    "SATA_TS Scope_Group",
    "ZIP Scope_Group",
    "Console_Group",
    "Fan_Group",
    "SATA_ctrl_Group",
    "EMMC_Card_Group",
    "SDIO_Group",
    "FPGA Cfg_Group",
    "CPUNet_Group",
    "I2C Ctrl_Group",
    "NetMisc_Group",
    "Router_Group",
    "DDR_Group",
    "NETSTAT_Group",
    "SATA_DRPctrl_Group",
    "ZIPCtrlDBG_Group"
};

float active_group_width;//table drawing

//init socket
EmscriptenWebSocketCreateAttributes ws_attrs = {
        "ws://127.0.0.1:9001",
        NULL,
        EM_TRUE
    };
    ws_handle = emscripten_websocket_new(&ws_attrs);

    emscripten_websocket_set_onopen_callback(ws_handle, NULL, on_open);
    emscripten_websocket_set_onmessage_callback(ws_handle, NULL, on_message);
    emscripten_websocket_set_onerror_callback(ws_handle, NULL, on_error);
    emscripten_websocket_set_onclose_callback(ws_handle, NULL, on_close);
//


    // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings from your own storage.
    io.IniFilename = nullptr;
    EMSCRIPTEN_MAINLOOP_BEGIN
#else
    while (!glfwWindowShouldClose(window))
#endif
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiStyle& style = ImGui::GetStyle();
        style.Colors[ImGuiCol_WindowBg] = back_color;//background color

        //creating window
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
        

        ImGui::Begin(
            "KlusterLab User Interface",
            nullptr,
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_HorizontalScrollbar
        );

        ImGui::SetWindowFontScale(3.0f);//bigger size for title

        float text_width = ImGui::CalcTextSize("KlusterLab User Interface").x;
        float window_width = ImGui::GetWindowWidth();

        ImGui::SetCursorPosX((window_width - text_width) * 0.5f);

        ImGui::TextColored(
            ImVec4(0.8588f, 0.7451f, 0.1020f, 1.0f),
            "KlusterLab User Interface"
        );
        ImGui::Dummy(ImVec2(0.0f, 30.0f));


        ImGui::SetWindowFontScale(1.5f * (io.DisplaySize.x/1620.0));

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(202.0f/255.0f, 200.0f/255.0f,  207.0f/255.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text,          ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        ImGui::SetCursorPosX(100.0f * (io.DisplaySize.x/1620.0));

        if(ImGui::Button("FLASHCFG_tab")){
            SelectTab(FLASHCFG_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("EMMC Scope_tab")){
            SelectTab(EMMCScope_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("I2C Scope_tab")){
            SelectTab(i2cScope_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("Net Scope_tab")){
            SelectTab(netScope_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("Route Scope_tab")){
            SelectTab(RouteScope_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("SATA_DRP Scope_tab")){
            SelectTab(SATA_DRPScope_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("SATA_L Scope_tab")){
            SelectTab(SATA_LScope_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("SATA_PS Scope_tab")){
            SelectTab(SATA_PSScope_tab , tabs);
        }

        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        ImGui::SetCursorPosX(100.0f * (io.DisplaySize.x/1620.0));

        if(ImGui::Button("SATA_RS Scope_tab")){
            SelectTab(SATA_RSScope_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("SATA_TS Scope_tab")){
            SelectTab(SATA_TSScope_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("ZIP Scope_tab")){
            SelectTab(zipScope_tab , tabs);
        }

        ImGui::SameLine(0.0f, 15.0f);
        
        if(ImGui::Button("Console_tab")){
            SelectTab(Console_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("Fan_tab")){
            SelectTab(Fan_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("SATA_ctrl_tab")){
            SelectTab(SATA_ctrl_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("EMMC_Card_tab")){
            SelectTab(EMMC_Card_tab , tabs);
        }

        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("SDIO_tab")){
            SelectTab(SDIO_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("FPGACfg_tab")){
            SelectTab(fpgaCfg_tab , tabs);
        }
        
        ImGui::Dummy(ImVec2(0.0f, 20.0f));

        ImGui::SetCursorPosX(100.0f * (io.DisplaySize.x/1620.0));

        if(ImGui::Button("CPUNet_tab")){
            SelectTab( CPUNet_tab, tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("I2CCtrl_tab")){
            SelectTab(i2cCtrl_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("NetMisc_tab")){
            SelectTab(NetMisc_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("Router_tab")){
            SelectTab(Router_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("DDR_tab")){
            SelectTab(DDR_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("NETSTAT_tab")){
            SelectTab(NETSTAT_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("SATA_DRPctrl_tab")){
            SelectTab(SATA_DRPctrl_tab , tabs);
        }
        ImGui::SameLine(0.0f, 15.0f);
        if(ImGui::Button("ZIPCtrlDBG_tab")){
            SelectTab(ZIPCtrlDBG_tab , tabs);
        }

        ImGui::PopStyleColor(3);

        for (uint16_t i = 0; i < GROUP_NO; i++)
        {
            if(*tabs[i]){

                
                //check if update is enabled
                if((update_guard==UPDATE_RATE || previous_choice != i) && is_ws_connected){
                    emscripten_websocket_send_utf8_text(ws_handle, group_names[i]);
                }
                //activating the read for the requested group
                DrawRegisterTabs(group_no[i] , i);
                //showing the current active group
                ImGui::SetWindowFontScale(2.0f);

                active_group_width = ImGui::CalcTextSize(group_names[i]).x;

                ImGui::Dummy(ImVec2(0.0f, 20.0f));

                ImGui::SetCursorPosX((window_width - active_group_width) * 0.5f);

                ImGui::TextColored(
                    ImVec4(1.0f, 1.0f, 1.0f, 1.0f),
                    "%s",
                    group_names[i]
                );
                ImGui::SetWindowFontScale(1.0f);
                //
                previous_choice = i;
            }
        }
        

        ImGui::SetWindowFontScale(1.0f);


        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(back_color.x * back_color.w, back_color.y * back_color.w, back_color.z * back_color.w, back_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);

        if(update_guard==200 && is_ws_connected){
            update_guard=0;
        }
        else {
            update_guard++;
        }
    }
#ifdef __EMSCRIPTEN__
    EMSCRIPTEN_MAINLOOP_END;
#endif

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
