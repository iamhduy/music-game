/**
 * @file ItemTrack.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMTRACK_H
#define PROJECT1_PROJECT1LIB_ITEMTRACK_H
#include "SoundBoard.h"
#include "Item.h"
class SoundBoard;

class ItemTrack : public Item
{
private:
    int mTrack;

    wxString mKeyImageFile;

    int mSizeX;

    int mSizeY;

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
