/**
 * @file ItemTrack.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMTRACK_H
#define PROJECT1_PROJECT1LIB_ITEMTRACK_H
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
};

#endif //PROJECT1_PROJECT1LIB_ITEMTRACK_H
