#include <cmath>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_impl_sdlrenderer.h>

#include "gui.h"

GUI_Layer::GUI_Layer()
    : m_xangle(static_cast<f32>(M_PI / 2.0f)), m_yangle(0.0f),
      m_xspeed(5), m_yspeed(6)
{
    // ...
}

GUI_Layer::~GUI_Layer()
{
    ImGui_ImplSDLRenderer_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
}

void GUI_Layer::initialize_gui(SDL_Renderer *renderer, SDL_Window *window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    m_font = io.Fonts->AddFontFromFileTTF("Karmina_Bold.ttf", 26);
        
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer_Init(renderer);
}

void GUI_Layer::begin_frame()
{
    ImGui_ImplSDLRenderer_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
}

void GUI_Layer::end_frame()
{
    ImGui::Render();
    ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
}

void GUI_Layer::process_events(SDL_Event *e)
{
    ImGui_ImplSDL2_ProcessEvent(e);
}

void GUI_Layer::draw_control_panel()
{
    ImGui::PushFont(m_font);

    ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(400, 700), ImGuiCond_FirstUseEver);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    
    if (ImGui::Begin("Control Panel", 0, window_flags)) {
        ImGui::Text("Speed along the X-Axis");
        ImGui::PushItemWidth(385);
        ImGui::SliderInt("##X_Axis_Speed", &m_xspeed, 1, 20);        

        ImGui::Dummy(ImVec2(0, 20));
        ImGui::Text("Speed along the Y-Axis");
        ImGui::PushItemWidth(385);
        ImGui::SliderInt("##Y_Axis_Speed", &m_yspeed, 1, 20);

        ImGui::Dummy(ImVec2(0, 20));
        ImGui::Text("Angle for the X-Axis");
        ImGui::PushItemWidth(385);
        ImGui::SliderAngle("##X_Axis_Angle", &m_xangle, 0.0f);

        ImGui::Dummy(ImVec2(0, 20));
        ImGui::Text("Angle for the Y-Axis");
        ImGui::PushItemWidth(385);
        ImGui::SliderAngle("##Y_Axis_Angle", &m_yangle, 0.0f);
    } ImGui::End();

    ImGui::PopFont();
}
