#include <Engine.h>
#include <iostream>
#include <PythagorasTree.h>
#include <DragonsCurve.h>
#include <Core.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <nlohmann/json.hpp>    

namespace engine
{
    int initialize()
    {
        if(Core::initalize() == -1)
        {
            return -1;
        }

        return 0;
    }

    int update()
    {
        unsigned int shaderId = Core::getShader();
        //figure::PythagorasTree tree(1, 0, 2, 25, 3, 0.4, 0, &shaderId);
        figure::DragonsCurve curve(5, 0.1f, 0, &shaderId);
        int windowSize = Core::getWindowedHeight();

        ImGuiStyle& style = ImGui::GetStyle();
        style.FrameRounding = 3.f;

        while (!Core::WindowIsOpen())
        {
            Core::beginFrame();
            
            //tree.update(Core::getDeltaTime());
            curve.update(Core::getDeltaTime());
        
            // ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
            // ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
            // ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(.0f, .0f));
            // ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoDecoration 
            // | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMouseInputs;
            // ImGui::Begin("Window", nullptr, window_flags);
            // ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;
            // ImGui::DockSpace(ImGui::GetID("dockspace"), ImVec2(0.0f, 0.0f), dockspace_flags, nullptr);
            // ImGui::End();
            // ImGui::PopStyleVar();
            // ImGui::DockSpace(ImGui::GetID("dockspace"));

            
            ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x / 4, ImGui::GetIO().DisplaySize.y));
            ImGui::SetNextWindowPos(ImVec2(0, 0));
            style.WindowPadding = ImVec2(ImGui::GetIO().DisplaySize.x / 100, ImGui::GetIO().DisplaySize.y / 100);
            ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar; 
            ImGui::Begin(" ", nullptr, window_flags);
            ImGui::PushItemWidth(60);
            ImGui::Text("Window:");
            if(ImGui::DragInt("Size", &windowSize, 1.0f, 250, 1000, "%dpx", ImGuiSliderFlags_None))
            {
                Core::setWindowSize(windowSize, windowSize);
            }
            //tree.withdrawUI();
            //curve.update(Core::getDeltaTime());
            ImGui::End();

            Core::endFrame();
        }

        return 0;
    }

    int finish()
    {
        Core::cleanUp();

        return 0;
    }

    void run()
    {
        initialize();
        update();
        finish();
    }
}