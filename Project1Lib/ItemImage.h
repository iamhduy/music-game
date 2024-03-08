/**
 * @file ItemImage.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMIMAGE_H
#define PROJECT1_PROJECT1LIB_ITEMIMAGE_H
#include "Item.h"

/**
 * Image Class derived from Item
 *
 */
class ItemImage : public Item
{
private:

public:
    /// Default constructor (disabled)
    ItemImage() = delete;

    /// Copy constructor (disabled)
    ItemImage(const ItemImage &) = delete;

    /// Assignment operator
    void operator=(const ItemImage &) = delete;

    ItemImage(Game* game);

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitImage(this); }
};

#endif //PROJECT1_PROJECT1LIB_ITEMIMAGE_H
