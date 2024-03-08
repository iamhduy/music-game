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

    /// Beats per minute in song
    int mBpMinute;

    /// Beats per measure in song
    int mBpMeasure;

    /// Measures in song
    int mMeasures;

    ///Backing track for song
    wxString mBack;

public:
    Music();

//    /// Default constructor (disabled)
//    Music() = delete;

    /// Copy constructor (disabled)
    Music(const Music &) = delete;

    virtual ~Music();

    /**
     * Get the pointer to the Level object
     * @return Pointer to Level object
     */
    Game *GetGame() { return mGame;}


    virtual void XmlLoad(wxXmlNode *node);

    /**
     * @return beats per minute of music
     */
    int GetBpMinute() { return mBpMinute; }

    /**
     * @return beats per measure of music
     */
    int GetBpMeasure() { return mBpMeasure; }

    /**
     * @return number of measures
     */
    int GetMeasures() { return mBpMeasure; }

    /**
     * @return number of measures
     */
    wxString GetBacking() { return mBack; }
};
#endif //PROJECT1_PROJECT1LIB_MUSIC_H
