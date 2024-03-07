/**
 * @file Music.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_MUSIC_H
#define PROJECT1_PROJECT1LIB_MUSIC_H
class Game;

/**
 * Music Base Class
 *
 */
class Music
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
    Music(Game *game);

    /// Default constructor (disabled)
    Music() = delete;

    /// Copy constructor (disabled)
    Music(const Music &) = delete;

    virtual ~Music();

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
#endif //PROJECT1_PROJECT1LIB_MUSIC_H
