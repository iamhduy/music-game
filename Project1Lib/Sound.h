/**
 * @file Sound.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_SOUND_H
#define PROJECT1_PROJECT1LIB_SOUND_H

#include <string>
#include <miniaudio.h>
#include "Item.h"

class Sound
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

    void SetAudioFile(wxString audioFile) {mAudioFile = audioFile;};

    void SetVolume(double volume) {mVolume = volume;};
};

#endif //PROJECT1_PROJECT1LIB_SOUND_H
