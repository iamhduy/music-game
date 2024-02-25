/**
 * @file GameApp.h
 * @author phamhoan
 *
 */

#ifndef PROJECT1__GAMEAPP_H
#define PROJECT1__GAMEAPP_H

#include "miniaudio.h"

class GameApp : public wxApp
{
private:
    /// The audio engine for miniaudio
    ma_engine mAudioEngine;
public:
    bool OnInit() override;

    int OnExit() override;
};

#endif //PROJECT1__GAMEAPP_H
