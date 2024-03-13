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

    double mPercentOfFullSize = 0;

    double mHitTime;

    bool mStopAtKey = false;

    double mSongBpMeasure;

    double mLongDurationX1;

    double mLongDurationY1;

    double mLongDurationX2;

    double mLongDurationY2;

    bool mContinueDurationLine = false;

    double mNoteTolerance = 50;

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

    int GetTrackNum();

    /**
     * @return the id of this object
     */
    wxString GetId() { return mId; }

    /**
     * @return beat
     */
    double GetBeat() { return mBeat; }

    /**
     * @return measure
     */
    double GetMeasure() { return mMeasure; }

    /**
     * @return duration
     */
    double GetDuration() { return mDuration; }

    /**
     * @return Song beat size
     */
    double GetBpMeasure() { return mSongBpMeasure; }

    void SetBpMeasure(double bpMeasure) {mSongBpMeasure = bpMeasure;}

    void SetPercentOfFullSize(double percentSize) {mPercentOfFullSize = percentSize;}

    virtual void XmlLoad(wxXmlNode *node);

    void SetHitTime(double hitTime){mHitTime = hitTime;}

    double GetHitTime() const {return mHitTime;}

    bool CheckIfHit(double currentBeat, int keyX, int keyY);

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
    * Set long duration x2 to draw
    * @param x X location in pixels
    */
    void SetLongDurationX1(double x) { mLongDurationX1 = x; };

    /**
    * Set long duration y2 to draw
    * @param y Y location in pixels
    */
    void SetLongDurationY1(double y) { mLongDurationY1 = y; };

    void SetLongDurationX2(double x) { mLongDurationX2 = x; };

    void SetLongDurationY2(double y) { mLongDurationY2 = y; };

    /**
     * Set Y location of the note
     * @param y Y location in pixels
     */
    void SetY(double y) { mY = y; };

    bool GetFirstUpdate() {return mFirstUpdate;};

    void SetFirstUpdate(bool set) {mFirstUpdate = set;};

    bool GetStopAtKey() {return mStopAtKey;};

    void SetStopAtKey(bool stop) {mStopAtKey = stop;}

    bool GetContinueDurationLine() {return mContinueDurationLine;};

    double GetLongDurationX1() {return mLongDurationX1;};

    double GetLongDurationY1() {return mLongDurationY1;};

    double GetLongDurationX2() {return mLongDurationX2;};

    double GetLongDurationY2() {return mLongDurationY2;};

    void SetContinueDurationLine(bool continueDraw) {mContinueDurationLine = continueDraw;}
};

#endif //PROJECT1_PROJECT1LIB_MUSICNOTE_H
