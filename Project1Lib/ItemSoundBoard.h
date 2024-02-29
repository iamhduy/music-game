/**
 * @file ItemSoundBoard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H
#define PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H
#include "Item.h"

/**
 * SoundBoard Class derived from Item
 *
 */
class ItemSoundBoard : public Item
{
private:

public:
    /// Default constructor (disabled)
    ItemSoundBoard() = delete;

    /// Copy constructor (disabled)
    ItemSoundBoard(const ItemSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemSoundBoard &) = delete;

    ItemSoundBoard(Game* game);

    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H