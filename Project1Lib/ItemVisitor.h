/**
 * @file ItemVisitor.h
 * @author Milo Baran
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMVISITOR_H
#define PROJECT1_PROJECT1LIB_ITEMVISITOR_H

class ItemImage;
class ItemMeter;
class ItemScoreBoard;
class ItemSoundBoard;

class ItemVisitor
{
protected:
    /**
     * Constructor
     * Ensures this is an abstract class
     */
    ItemVisitor() {}

private:

public:
    virtual ~ItemVisitor() {}

    virtual void VisitImage(ItemImage *image) {}

    virtual void VisitMeter(ItemMeter* meter) {}

    virtual void VisitScoreboard(ItemScoreBoard* scoreboard) {}

    virtual void VisitSoundboard(ItemSoundBoard* soundboard) {}
};

#endif //PROJECT1_PROJECT1LIB_ITEMVISITOR_H
