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
/**
 * Visitor for counting note passed
 */
class TotalNotesVisitor : public ItemVisitor {
private:
    /// the total note passed
    int mTotalNotesPassed = 0;

public:
    /**
     * Counting note passed
     * @param soundboard where to count the note
     */
    void VisitSoundboard(ItemSoundBoard* soundboard) override {
        mTotalNotesPassed += soundboard->GetTotalNotesPassed();
    }

    /**
     * @return how many total note passed
     */
    int GetTotalNotesPassed() const { return mTotalNotesPassed; }
};

#endif //PROJECT1_PROJECT1LIB_TOTALNOTESVISITOR_H
