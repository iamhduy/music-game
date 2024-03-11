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

class SoundBoardVisitor : public ItemVisitor
{
private:
    wxChar mKey;
    int mKeyXPos = 0;
    int mKeyYPos = 0;
    bool mKeyFound = false;

public:
    SoundBoardVisitor(wxChar key) : mKey(key){}

    virtual void VisitSoundboard(ItemSoundBoard* soundboard){
        mKeyXPos = soundboard->GetKeyXPosition(mKey);
        mKeyYPos = soundboard->GetKeyYPosition(mKey);
        mKeyFound = true;
    }

    int GetKeyXPosition() const {return mKeyXPos;}
    int GetKeyYPosition() const {return mKeyYPos;}
    bool KeyFound() const { return mKeyFound;}
};

#endif //PROJECT1_PROJECT1LIB_SOUNDBOARDVISITOR_H
