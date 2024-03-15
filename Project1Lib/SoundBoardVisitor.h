/**
 * @file SoundBoardVisitor.h
 * @author Mitchell Bjorne
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_SOUNDBOARDVISITOR_H
#define PROJECT1_PROJECT1LIB_SOUNDBOARDVISITOR_H

#include "ItemVisitor.h"
#include "ItemSoundBoard.h"
#include <memory>

/**
 * Visitor for finding keys
 */
class SoundBoardVisitor : public ItemVisitor
{
private:
    ///Key to find
    wxChar mKey;

    ///Key x pos
    int mKeyXPos = 0;

    ///Key y pos
    int mKeyYPos = 0;

    ///Is the key found
    bool mKeyFound = false;

public:
    /**
    * Constructor
    * @param key the key for this class
    */
    SoundBoardVisitor(wxChar key) : mKey(key){}

    /**
    * find the key inside the soundboard and get its pos
    * @param soundboard where to find
    */
    virtual void VisitSoundboard(ItemSoundBoard* soundboard){
        mKeyXPos = soundboard->GetKeyXPosition(mKey);
        mKeyYPos = soundboard->GetKeyYPosition(mKey);
        mKeyFound = true;
    }
    /**
     * @return key x pos
    */
    int GetKeyXPosition() const {return mKeyXPos;}

    /**
     * @return key y pos
    */
    int GetKeyYPosition() const {return mKeyYPos;}

    /**
     * @return is the key found
    */
    bool KeyFound() const { return mKeyFound;}
};

#endif //PROJECT1_PROJECT1LIB_SOUNDBOARDVISITOR_H
