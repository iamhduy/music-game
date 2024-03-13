/**
 * @file TotalNotesVisitor.h
 * @author Mitchell Bjorne
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_TOTALNOTESVISITOR_H
#define PROJECT1_PROJECT1LIB_TOTALNOTESVISITOR_H

#include "ItemVisitor.h"
#include "ItemSoundBoard.h"

class TotalNotesVisitor : public ItemVisitor {
private:
    int mTotalNotesPassed = 0;

public:
    void VisitSoundboard(ItemSoundBoard* soundboard) override {
        mTotalNotesPassed += soundboard->GetTotalNotesPassed();
    }

    int GetTotalNotesPassed() const { return mTotalNotesPassed; }
};

#endif //PROJECT1_PROJECT1LIB_TOTALNOTESVISITOR_H
