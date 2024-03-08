/**
 * @file ItemMeter.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMMETER_H
#define PROJECT1_PROJECT1LIB_ITEMMETER_H

#include "Item.h"

/**
 * Meter Class derived from Item
 *
 */
class ItemMeter : public Item
{
private:

public:
    /// Default constructor (disabled)
    ItemMeter() = delete;

    /// Copy constructor (disabled)
    ItemMeter(const ItemMeter &) = delete;

    /// Assignment operator
    void operator=(const ItemMeter &) = delete;

    ItemMeter(Game* game);

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitMeter(this); }
};

#endif //PROJECT1_PROJECT1LIB_ITEMMETER_H
