/**
 * @file GameApp.cpp
 * @author phamhoan
 */
#include "pch.h"
#include "GameApp.h"
#include <MainFrame.h>

bool GameApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;
    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);
    return true;
}

