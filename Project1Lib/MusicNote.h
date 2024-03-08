/**
 * @file MusicNote.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_MUSICNOTE_H
#define PROJECT1_PROJECT1LIB_MUSICNOTE_H
#include "Music.h"
#include "Item.h"

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

    /// Declaration's image dir
    std::wstring mImageFile;

    /// Declaration's image
    std::unique_ptr<wxImage> mItemImage;

    /// Declaration's bitmap
    std::unique_ptr<wxBitmap> mItemBitmap;

    // Item location in the game
    double mX = 0;     ///< X location for the center of the item
    double mY = 0;     ///< Y location for the center of the item

    bool mFirstUpdate = false;

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

    /**
     * @return
     */
    double GetBeat() { return mBeat; }

    /**
     * @return
     */
    double GetMeasure() { return mMeasure; }

    virtual void XmlLoad(wxXmlNode *node);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration);

    /**
    * The X location of the item
    * @returns X location in pixels
    */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @returns Y location in pixels
     */
    double GetY() const { return mY; }


    wxString GetSoundName() const {return mSoundName;}

    /**
    * Set X location of the note
    * @param x X location in pixels
    */
    void SetX(double x) { mX = x; };

    /**
     * Set Y location of the note
     * @param y Y location in pixels
     */
    void SetY(double y) { mY = y; };

    bool GetFirstUpdate() {return mFirstUpdate;};

    void SetFirstUpdate(bool set) {mFirstUpdate = set;};
};

#endif //PROJECT1_PROJECT1LIB_MUSICNOTE_H
