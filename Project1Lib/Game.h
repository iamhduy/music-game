/**
 * @file Game.h
 * @author Milo Baran
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_GAME_H
#define PROJECT1_PROJECT1LIB_GAME_H

#include <memory>
#include "Item.h"

class Game
{
private:
// keep level objects for level 0,1,2,3?

    std::unique_ptr<wxBitmap> mBackground; ///< Background image to use

    /// holding the item
    std::vector<std::shared_ptr<Item>> mItems;

    void XmlItem(wxXmlNode *node);
public:
    Game();

    void Load(const wxString &filename);

    void Clear();
    void OnDraw(wxDC *dc);
    void Add(std::shared_ptr<Item> item);
};

#endif //PROJECT1_PROJECT1LIB_GAME_H
