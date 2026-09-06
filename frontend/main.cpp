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
const char* FLASHCFG_Regname[FLASHCFG_Group] = {"R_FLASHCFG"};
const char* const EMMCScope_Regname[EMMCScope_Group] = {"R_EMMCSCOPE", "R_EMMCSCOPED"};
const char* const i2cScope_Regname[i2cScope_Group] = {"R_I2CSCOPE", "R_I2CSCOPED"};
const char* const netScope_Regname[netScope_Group] = {"R_NETSCOPE", "R_NETSCOPED"};
const char* const RouteScope_Regname[RouteScope_Group] = {"R_ROUTESCOPE", "R_ROUTESCOPED"};
const char* const SATA_DRPScope_Regname[SATA_DRPScope_Group] = {"R_SATADRPSCOPE", "R_SATADRPSCOPED"};
const char* const SATA_LScope_Regname[SATA_LScope_Group] = {"R_SATALSCOPE", "R_SATALSCOPED"};
const char* const SATA_PSScope_Regname[SATA_PSScope_Group] = {"R_SATAPSCOPE", "R_SATAPSCOPED"};
const char* const SATA_RSScope_Regname[SATA_RSScope_Group] = {"R_SATARSCOPE", "R_SATARSCOPED"};
const char* const SATA_TSScope_Regname[SATA_TSScope_Group] = {"R_SATATSCOPE", "R_SATATSCOPED"};
const char* const zipScope_Regname[zipScope_Group] = {"R_ZIPSCOPE", "R_ZIPSCOPED"};
const char* const Console_Regname[Console_Group] = {"R_CONSOLE_FIFO", "R_CONSOLE_UARTRX", "R_CONSOLE_UARTTX"};
const char* const Fan_Regname[Fan_Group] = {"R_FAN_FPGAPWM", "R_FAN_SYSPWM", "R_FAN_TACH", "R_FAN_TEMP", "R_FAN", "R_FAN_OVW", "R_FAN_ADDR", "R_FAN_CKCOUNT"};
const char* const SATA_ctrl_Regname[SATA_ctrl_Group] = {"R_SATA", "R_LBALO", "R_LBAHI", "R_SATACOUNT", "R_SATAPHY", "R_SATAADDR"};
const char* const EMMC_Card_Regname[EMMC_Card_Group] = {"R_EMMC_CTRL", "R_EMMC_DATA", "R_EMMC_FIFOA", "R_EMMC_FIFOB", "R_EMMC_PHY", "R_EMMC_DMAA", "R_EMMC_DMALN", "R_EMMC_TRIM", "R_EMMC_RXTRIM"};
const char* const SDIO_Regname[SDIO_Group] = {"R_SDIO_CTRL", "R_SDIO_DATA", "R_SDIO_FIFOA", "R_SDIO_FIFOB", "R_SDIO_PHY", "R_SDIO_DMAA", "R_SDIO_DMALN", "R_SDIO_TRIM", "R_SDIO_RXTRIM"};
const char* const fpgaCfg_Regname[fpgaCfg_Group] = {"R_CFG_CRC", "R_CFG_FAR", "R_CFG_FDRI", "R_CFG_FDRO", "R_CFG_CMD", "R_CFG_CTL0", "R_CFG_MASK", "R_CFG_STAT", "R_CFG_LOUT", "R_CFG_COR0", "R_CFG_MFWR", "R_CFG_CBC", "R_CFG_IDCODE", "R_CFG_AXSS", "R_CFG_COR1", "R_CFG_WBSTAR", "R_CFG_TIMER", "R_CFG_BOOTSTS", "R_CFG_CTL1", "R_CFG_BSPI"};
const char* const CPUNet_Regname[CPUNet_Group] = {"R_CPUNET", "R_CPUNETMAC1", "R_CPUNETMAC2", "R_CPUNETIPV4", "R_CPUNETIPV6P1", "R_CPUNETIPV6P2", "R_CPUNETIPV6P3", "R_CPUNETIPV6P4", "R_CPUNETRXDROPS", "R_CPUNETRXPKTS", "R_CPUNETTXPKTS", "R_CPUNETTX_BASE", "R_CPUNETTX_LEN", "R_CPUNETTX_RPTR", "R_CPUNETTX_WPTR", "R_CPUNETRX_BASE", "R_CPUNETRX_LEN", "R_CPUNETRX_RPTR", "R_CPUNETRX_WPTR", "R_CPUNETRX_DBG", "R_CPUNETTX_DBG"};
const char* const i2cCtrl_Regname[i2cCtrl_Group] = {"R_I2CCPU", "R_I2CCPU_OVW", "R_I2CCPU_ADDR", "R_I2CCPU_CKCOUNT", "R_I2CDMA", "R_I2CDMA_ADDR", "R_I2CDMA_BASE", "R_I2CDMA_LEN"};
const char* const NetMisc_Regname[NetMisc_Group] = {"R_RXNETCK0", "R_RXNETCK1", "R_RXNETCK2", "R_RXNETCK3", "R_TXNETCLK", "R_BUILDTIME", "R_GPIO", "R_NETDBG", "R_NETLOCK", "R_NETRESET", "R_PWRCOUNT", "R_RTCCOUNT", "R_SATAREF", "R_SATARX", "R_SATATX", "R_SCOPEPIC", "R_SICLKFREQ", "R_SIREFCLK", "R_SIREFFREQ", "R_SPIO", "R_VERSION"};
const char* const Router_Regname[Router_Group] = {"R_ROUTER0", "R_ROUTERSZ0", "R_ROUTERWR0", "R_ROUTERRD0", "R_ROUTER1", "R_ROUTERSZ1", "R_ROUTERWR1", "R_ROUTERRD1", "R_ROUTER2", "R_ROUTERSZ2", "R_ROUTERWR2", "R_ROUTERRD2", "R_ROUTER3", "R_ROUTERSZ3", "R_ROUTERWR3", "R_ROUTERRD3", "R_ROUTERPK0", "R_ROUTERBY0", "R_ROUTERFP0", "R_ROUTERFB0", "R_ROUTERPK1", "R_ROUTERBY1", "R_ROUTERFP1", "R_ROUTERFB1", "R_ROUTERPK2", "R_ROUTERBY2", "R_ROUTERFP2", "R_ROUTERFB2", "R_ROUTERPK3", "R_ROUTERBY3", "R_ROUTERFP3", "R_ROUTERFB3", "R_ROUTERNWH0", "R_ROUTERNWL0", "R_ROUTERLKH0", "R_ROUTERLKL0", "R_ROUTERNWH1", "R_ROUTERNWL1", "R_ROUTERLKH1", "R_ROUTERLKL1", "R_ROUTERNWH2", "R_ROUTERNWL2", "R_ROUTERLKH2", "R_ROUTERLKL2", "R_ROUTERNWH3", "R_ROUTERNWL3", "R_ROUTERLKH3", "R_ROUTERLKL3", "R_ROUTERNWH4", "R_ROUTERNWL4", "R_ROUTERLKH4", "R_ROUTERLKL4", "R_ROUTERDBG0", "R_ROUTERDBG1", "R_ROUTERDBG2", "R_ROUTERDBG3", "R_ROUTERDBG4", "R_ROUTERNEVER", "R_ROUTERALWAYS", "R_ROUTERDBGS"};
const char* const DDR_Regname[DDR_Group] = {"R_DDR3_PHY", "R_DDR3_PHYSTAT1", "R_DDR3_PHYSTAT2", "R_DDR3_PHYSTAT3", "R_DDR3_PHYCTRLSTAT", "R_DDR3_PHYRESET", "R_DDR3_PHYDBGSEL"};
const char* const NETSTAT_Regname[NETSTAT_Group] = {"R_NETSTAT"};
const char* const SATA_DRPctrl_Regname[SATA_DRPctrl_Group] = {"R_PLLDRP", "R_GTXDRP", "R_BKRAM", "R_FLASH", "R_DDR3_CONTROLLER"};
const char* const ZIPCtrlDBG_Regname[ZIPCtrlDBG_Group] = {"R_ZIPCTRL", "R_ZIPS0", "R_ZIPS1", "R_ZIPS2", "R_ZIPS3", "R_ZIPS4", "R_ZIPS5", "R_ZIPS6", "R_ZIPS7", "R_ZIPS8", "R_ZIPS9", "R_ZIPS10", "R_ZIPS11", "R_ZIPS12", "R_ZIPSSP", "R_ZIPCC", "R_ZIPPC", "R_ZIPU0", "R_ZIPU1", "R_ZIPU2", "R_ZIPU3", "R_ZIPU4", "R_ZIPU5", "R_ZIPU6", "R_ZIPU7", "R_ZIPU8", "R_ZIPU9", "R_ZIPU10", "R_ZIPU11", "R_ZIPU12", "R_ZIPUSP", "R_ZIPUCC", "R_ZIPUPC", "R_ZIPPIC", "R_ZIPWDOG", "R_ZIPBDOG", "R_ZIPAPIC", "R_ZIPTIMA", "R_ZIPTIMB", "R_ZIPTIMC", "R_ZIPJIFF", "R_ZIPMTASK", "R_ZIPMMSTL", "R_ZIPMPSTL", "R_ZIPMINSN", "R_ZIPUTASK", "R_ZIPUMSTL", "R_ZIPUPSTL", "R_ZIPUINSN", "R_ZIPDMAC"};
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
    float cell_width = ImGui::GetColumnWidth();
    float text_width = ImGui::CalcTextSize("R_XXXXXXXXXXXXXXXX: 0xFFFFFFFF").x;
    
    // Calculate centered cursor position within the current cell
    float start_x = ImGui::GetCursorPosX() + (cell_width - text_width) * 0.5f;
    
    // Prevent negative offset if text is wider than the column
    if (start_x > ImGui::GetCursorPosX()) {
        ImGui::SetCursorPosX(start_x);
    }

    ImGui::SetWindowFontScale(1.5f);
    
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
    if (ImGui::BeginTable("MyTable", NumberOfColumns, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg | ImGuiTableFlags_SizingStretchSame))
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
            ImGuiWindowFlags_NoTitleBar
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


        ImGui::SetWindowFontScale(1.5f);

        ImGui::PushStyleColor(ImGuiCol_Button,        ImVec4(202.0f/255.0f, 200.0f/255.0f,  207.0f/255.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(255.0f/255.0f, 255.0f/255.0f, 255.0f/255.0f, 1.0f));
        ImGui::PushStyleColor(ImGuiCol_Text,          ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

        ImGui::SetCursorPosX(100.0f);

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

        ImGui::SetCursorPosX(100.0f);

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

        ImGui::SetCursorPosX(100.0f);

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
