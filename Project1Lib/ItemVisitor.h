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

/**
 * Visitor class for Item
 */
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

    /**
     * Visit a ItemImage object
     * @param image image we are visiting
     */
    virtual void VisitImage(ItemImage *image) {}

    /**
     * Visit a ItemMeter object
     * @param meter meter we are visiting
     */
    virtual void VisitMeter(ItemMeter* meter) {}

    /**
     * Visit a ItemScoreBoard object
     * @param scoreboard scoreboard we are visiting
     */
    virtual void VisitScoreboard(ItemScoreBoard* scoreboard) {}

    /**
     * Visit a ItemSoundBoard object
     * @param soundboard soundboard we are visiting
     */
    virtual void VisitSoundboard(ItemSoundBoard* soundboard) {}
};

#endif //PROJECT1_PROJECT1LIB_ITEMVISITOR_H
