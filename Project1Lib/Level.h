/**
 * @file Level.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_LEVEL_H
#define PROJECT1_PROJECT1LIB_LEVEL_H

#include <memory>
#include "Item.h"

/**
 * The background drawing of the level
 */
class Level
{
private:
    std::unique_ptr<wxBitmap> mBackground; ///< Background image to use

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<Item>> mItems;
public:
    Level();

    /**
     * Get the width of the aquarium
     * @return Aquarium width in pixels
     */
    int GetWidth() const { return mBackground->GetWidth(); }

    /**
     * Get the height of the aquarium
     * @return Aquarium height in pixels
     */
    int GetHeight() const { return mBackground->GetHeight(); }
};

#endif //PROJECT1_PROJECT1LIB_LEVEL_H
