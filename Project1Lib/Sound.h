/**
 * @file Sound.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_SOUND_H
#define PROJECT1_PROJECT1LIB_SOUND_H

#include <string>
#include "C:\Users\Admin\project1\cmake-build-debug\_deps\miniaudio-src\miniaudio.h"
#include "Item.h"

class Sound : public Item
{
private:
    /// Name of the sound
    wxString mName;

    /// The audio file to load
    wxString mAudioFile;

    /// long sound or not
    bool mLong = false;

    /// volume of the sound
    double mVolume = 1.0;

    /// The miniaudio sound
    ma_sound mSound;

    /// Has the sound been loaded?
    bool mLoaded = false;

public:
    ~Sound();

    void PlaySound();

    void PlayEnd();

    void LoadSound(ma_engine* audioEngine);

    void XmlLoad(wxXmlNode *node);
};

#endif //PROJECT1_PROJECT1LIB_SOUND_H
