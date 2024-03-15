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
#include "Sound.h"

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

    ///Note's sound name
    wxString mSoundName;

    ///which beat does this note appear
    int mMeasure;

    ///which beat does this note appear
    double mBeat;

    ///Duration of this note's sound
    double mDuration;

    /// Declaration's image dir
    std::wstring mImageFile;

    /// Declaration's image
    std::unique_ptr<wxImage> mItemImage;

    /// Declaration's bitmap
    std::unique_ptr<wxBitmap> mItemBitmap;

    double mX = 0;     ///< X location for the center of the item
    double mY = 0;     ///< Y location for the center of the item

    /// does the note appear
    bool mFirstUpdate = false;

    /// size of this note display
    double mPercentOfFullSize = 0;

    /// is this note pass the key
    bool mStopAtKey = false;

    /// is this note played
    bool mIsPlayed = false;

    /// beat per measure of this song
    double mSongBpMeasure;

    double mLongDurationX1; ///< X1 locations for the track contains this note

    double mLongDurationY1; ///< Y1 locations for the track contains this note

    double mLongDurationX2; ///< X2 locations for the track contains this note

    double mLongDurationY2; ///< Y2 locations for the track contains this note

    /// to draw line for long duration note
    bool mContinueDurationLine = false;

    ///note's tolerance
    double mNoteTolerance = 50;

    ///note stop time
    double mStoppedTime = 0;

    ///if the note ready for delete
    bool mReadyForDeletion = false;

    /// the sound of this note
    std::shared_ptr<Sound> mSound;

    ///When does the note played
    double mBeatAtPlay = 0;

    ///the key associated with this note
    char mAssociatedKey;
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
    Game *GetGame() { return mGame; }

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

    /**
     * to get the song bpm
    * @param bpMeasure
    */
    void SetBpMeasure(double bpMeasure) { mSongBpMeasure = bpMeasure; }

    /**
     * Set the note's size
    * @param percentSize
    */
    void SetPercentOfFullSize(double percentSize) { mPercentOfFullSize = percentSize; }

    virtual void XmlLoad(wxXmlNode *node);

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

    /**
    * Set X location of the note
    * @param x X location in pixels
    */
    void SetX(double x) { mX = x; };

    /**
    * Set long duration x1 to draw
    * @param x X location in pixels
    */
    void SetLongDurationX1(double x) { mLongDurationX1 = x; };

    /**
    * Set long duration y1 to draw
    * @param y Y location in pixels
    */
    void SetLongDurationY1(double y) { mLongDurationY1 = y; };

    /**
    * Set long duration x2 to draw
    * @param x X location in pixels
    */
    void SetLongDurationX2(double x) { mLongDurationX2 = x; };

    /**
    * Set long duration y2 to draw
    * @param y Y location in pixels
    */
    void SetLongDurationY2(double y) { mLongDurationY2 = y; };

    /**
     * Set Y location of the note
     * @param y Y location in pixels
     */
    void SetY(double y) { mY = y; };

    /**
    * @return does the note appear
    */
    bool GetFirstUpdate() { return mFirstUpdate; };

    /**
    * @param set the note first update status
    */
    void SetFirstUpdate(bool set) { mFirstUpdate = set; };

    /**
    * @return does the note stop
    */
    bool GetStopAtKey() { return mStopAtKey; };

    /**
    * @param stop the note first play status
    */
    void SetStopAtKey(bool stop) { mStopAtKey = stop; }

    /**
    * @return to continue drawing red line
    */
    bool GetContinueDurationLine() { return mContinueDurationLine; }

    /**
    * @return red line x location
    */
    double GetLongDurationX2() { return mLongDurationX2; };

    /**
    * @return red line y location
    */
    double GetLongDurationY2() { return mLongDurationY2; };

    /**
    * @param continueDraw set red line status
    */
    void SetContinueDurationLine(bool continueDraw) { mContinueDurationLine = continueDraw; }

    void IncrementStoppedTime(double elapsed);

    bool IsReadyForDeletion() const;

    void PlaySound(double beat);

    void PlayEnd();

    /**
    * @return if this note played
    */
    bool IsSoundPlayed() { return mIsPlayed; }

    /**
    * @return the beat when this note played
    */
    double GetBeatAtPlay() {return mBeatAtPlay;}

    /**
    * @return this note's sound name
    */
    wxString GetSoundName() {return mSoundName;};

    /**
    * @return this note's associated key
    */
    char GetAssociatedKey() {return mAssociatedKey;};

    /**
     * Set the note's associated key
    * @param key
    */
    void SetAssociatedKey(char key) {mAssociatedKey = key;};

    /**
    * @return if this note danger
    */
    bool IsDangerNote() {return GetSoundName() == L"fail";}
};

#endif //PROJECT1_PROJECT1LIB_MUSICNOTE_H