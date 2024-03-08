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

class SoundboardAddNote : public ItemVisitor
{
private:
    std::shared_ptr<MusicNote> mNote;
public:
    SoundboardAddNote(std::shared_ptr<MusicNote> note) : mNote(note) {}

    void VisitSoundboard(ItemSoundBoard* soundboard) override
    {
        soundboard->AddNote(mNote);
    }
};

#endif //PROJECT1_PROJECT1LIB_SOUNDBOARDADDNOTE_H
