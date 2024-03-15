/**
 * @file SoundboardAddNote.h
 * @author Milo Baran
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_SOUNDBOARDADDNOTE_H
#define PROJECT1_PROJECT1LIB_SOUNDBOARDADDNOTE_H

#include "ItemVisitor.h"
#include "ItemSoundBoard.h"
/**
 * Visitor for adding note to tracks
 */
class SoundboardAddNote : public ItemVisitor
{
private:
    ///music note to add
    std::shared_ptr<MusicNote> mNote;
public:
    /**
    * Constructor
    * @param note the note for this class
    */
    SoundboardAddNote(std::shared_ptr<MusicNote> note) : mNote(note) {}

    /**
    * add the note to soundboard
    * @param soundboard where to add
    */
    void VisitSoundboard(ItemSoundBoard* soundboard) override
    {
        soundboard->AddNote(mNote);
    }
};

#endif //PROJECT1_PROJECT1LIB_SOUNDBOARDADDNOTE_H
