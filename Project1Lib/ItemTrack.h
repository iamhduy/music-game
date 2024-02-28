/**
 * @file ItemTrack.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMTRACK_H
#define PROJECT1_PROJECT1LIB_ITEMTRACK_H
#include "ItemSoundBoard.h"
#include "Item.h"
class ItemSoundBoard;

/**
 * Track Class derived from Item
 *
 */
class ItemTrack : public Item
{
private:
    /// Track Number
    int mTrack;

    /// Key Image File
    wxString mKeyImageFile;

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

    ItemTrack(Game *game);

    void XmlLoad(wxXmlNode* node) override;

};

#endif //PROJECT1_PROJECT1LIB_ITEMTRACK_H
