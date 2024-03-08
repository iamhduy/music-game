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
    /// The SoundBoard this item is contained in
    ItemSoundBoard *mSoundBoard;

    /// Track Number
    int mTrack;

    /// Key Image File
    std::wstring mKeyImageFile;

    int mSizeX = 0; ///< X size for the center of the item
    int mSizeY = 0; ///< Y size for the center of the item

    /// Key value for this Track
    wxString mKeyValue;

    double mX1;
    double mX2;
    double mY1;
    double mY2;

    std::vector<std::shared_ptr<MusicNote>> mNotes;

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

    //void Update(double elapsed);

    /**
     * Set Y location of the note
     * @param y Y location in pixels
     */
    void SetY1(double y1) { mY1 = y1; };

    /**
     * Set Y location of the note
     * @param y Y location in pixels
     */
    void SetY2(double y2) { mY2 = y2; };

    /**
     * Set Y location of the note
     * @param y Y location in pixels
     */
    void SetX1(double x1) { mX1 = x1; };

    /**
     * Set Y location of the note
     * @param y Y location in pixels
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

    wxString GetId()
    {
        return wxString::Format(wxT("t%d"), mTrack);
    }

    void UpdateNotes(double elapsed, double timeOnTrack);
};

#endif //PROJECT1_PROJECT1LIB_ITEMTRACK_H
