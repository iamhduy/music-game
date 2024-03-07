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
class Game;
/**
 * Sound Class derived from Audio
 *
 */
class Sound
{
private:
/// The game this sound is contained in
    Game* mGame;

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
    Sound(Game *game);

    /// Default constructor (disabled)
    Sound() = delete;

    /// Copy constructor (disabled)
    Sound(const Sound &) = delete;

    /// Assignment operator
    void operator=(const Sound &) = delete;

    ~Sound();

    void PlaySound();

    void PlayEnd();

    void LoadSound(ma_engine* audioEngine);

    void XmlLoad(wxXmlNode *node);

    /**
     * Set audio file directory
     * @param audioFile
     */
    void SetAudioFile(wxString audioFile) {mAudioFile = audioFile;};

    /**
     * Set audio volume directory
     * @param volume
     */
    void SetVolume(double volume) {mVolume = volume;};
};

#endif //PROJECT1_PROJECT1LIB_SOUND_H
