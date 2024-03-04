/**
 * @file ItemSoundBoard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H
#define PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H
#include "Item.h"
#include "ItemTrack.h"
#include <memory>

/**
 * SoundBoard Class derived from Item
 *
 */
class ItemSoundBoard : public Item
{
private:
    /// holding the tracks
    std::vector<std::shared_ptr<ItemTrack>> mTracks;
public:
    /// Default constructor (disabled)
    ItemSoundBoard() = delete;

    /// Copy constructor (disabled)
    ItemSoundBoard(const ItemSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemSoundBoard &) = delete;

    ItemSoundBoard(Game* game);

    void Add(std::shared_ptr<ItemTrack> itemTrack);

    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration) override;
};

#endif //PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H
