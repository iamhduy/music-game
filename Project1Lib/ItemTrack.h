/**
 * @file ItemTrack.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMTRACK_H
#define PROJECT1_PROJECT1LIB_ITEMTRACK_H
#include "DeclarationNote.h"
#include "MusicNote.h"
class ItemSoundBoard;

/**
 * Track Class derived from Item
 *
 */
class ItemTrack
{
protected:

private:
    /// Track Number
    int mTrack;

    /// Key Image File
    std::wstring mKeyImageFile;

    int mSizeX = 0; ///< X size for the center of the item
    int mSizeY = 0; ///< Y size for the center of the item

    /// Key value for this Track
    wxString mKeyValue;

    /// x1 pos of this track
    double mX1;
    /// x2 pos of this track
    double mX2;
    /// y1 pos of this track
    double mY1;
    /// y2 pos of this track
    double mY2;

    ///the notes play on this track
    std::vector<std::shared_ptr<MusicNote>> mNotes;

    ///beat size
    double mBeatSize;

    ///size of the note at the start
    double mInitPercentOfSize;

    ///number of note passed
    int mNotesPassed = 0;
public:
    /// Default constructor (disabled)
    ItemTrack() = delete;

    /// Copy constructor (disabled)
    ItemTrack(const ItemTrack &) = delete;

    /// Assignment operator
    void operator=(const ItemTrack &) = delete;

    void XmlLoad(wxXmlNode* node);

    ItemTrack(ItemSoundBoard *soundBoard);

    std::wstring GetKeyImageFile();

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y);

    /**
     * Set Y location of the note
     * @param y1 Y location in pixels
     */
    void SetY1(double y1) { mY1 = y1; };

    /**
     * Set Y location of the note
     * @param y2 Y location in pixels
     */
    void SetY2(double y2) { mY2 = y2; };

    /**
     * Set X location of the note
     * @param x1 X location in pixels
     */
    void SetX1(double x1) { mX1 = x1; };

    /**
     * Set X location of the note
     * @param x2 X location in pixels
     */
    void SetX2(double x2) { mX2 = x2; };

    /**
     * Add note to list of notes
     * @param note note to be added
     */
    void AddNote(std::shared_ptr<MusicNote> note)
    {
        mNotes.push_back(note);
    }

    void UpdateNotes(double elapsed, double beatsPerSecond);

    /**
     * @return size x of the key
     */
    double GetSizeX() {return mSizeX;}

    /**
     * @return size y of the key
     */
    double GetSizeY() {return mSizeY;}

    /**
     * @return track number
     */
    int GetTrackNum() {return mTrack;}

    /**
     * @return key's image file
     */
    wxString GetImageFile() {return mKeyImageFile;}

    /**
     * Set beat size
     * @param beatSize
     */
    void SetBeatSize(double beatSize) {mBeatSize = beatSize;}

    /**
     * Set size of the note
     * @param percent percent of full size
     */
    void SetInitPercentOfSize(double percent) { mInitPercentOfSize = percent;};

    /**
     * @return number of the notes passed
     */
    int GetNotesPassed(){return mNotesPassed;}

    /**
     * @return the key of this track
     */
    char GetKey() {return mKeyValue[0];};

};

#endif //PROJECT1_PROJECT1LIB_ITEMTRACK_H