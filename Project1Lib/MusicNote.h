/**
 * @file MusicNote.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_MUSICNOTE_H
#define PROJECT1_PROJECT1LIB_MUSICNOTE_H
#include "Music.h"

class Game;

/**
 * Note Class derived from Music
 *
 */
class MusicNote
{
protected:
private:
    /// The game this item is contained in
    Game *mGame;

    /// Note's id
    wxString mId;

    wxString mSoundName;

    int mMeasure;

    double mBeat;

    double mDuration;
public:
    MusicNote(Game *game);

    /// Default constructor (disabled)
    MusicNote() = delete;

    /// Copy constructor (disabled)
    MusicNote(const Music &) = delete;

    virtual ~MusicNote();

    /**
     * Get the pointer to the Level object
     * @return Pointer to Level object
     */
    Game *GetGame() { return mGame;}

    /**
     * @return the id of this object
     */
    wxString GetId() { return mId; }

    virtual void XmlLoad(wxXmlNode *node);
};

#endif //PROJECT1_PROJECT1LIB_MUSICNOTE_H
