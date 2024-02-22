/**
 * @file GameApp.cpp
 * @author phamhoan
 */
#include "pch.h"
#include "GameApp.h"
#include <MainFrame.h>

#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

/// The audio engine for miniaudio
ma_engine mAudioEngine;

bool GameApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;
    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    // Initialize the audio engine
    auto result = ma_engine_init(NULL, &mAudioEngine);
    if (result != MA_SUCCESS)
    {
        wxString msg;
        msg.Printf(L"Unable to initialize miniaudio engine - %d", result);
        wxMessageBox( msg, wxT("miniaudio failure"), wxICON_ERROR);
        return false;
    }

    return true;
}

int GameApp::OnExit()
{
    ma_engine_uninit(&mAudioEngine);
    return wxAppBase::OnExit();
}