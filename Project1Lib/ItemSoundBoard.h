/**
 * @file ItemSoundBoard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H
#define PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H
#include "Item.h"
#include "ItemTrack.h"
#include <memory>

/**
 * SoundBoard Class derived from Item
 *
 */
class ItemSoundBoard : public Item
{
private:
    /// holding the tracks
    std::vector<std::shared_ptr<ItemTrack>> mTracks;

    double mBeatSize;

    double mSoundboardTopWidth;

    double mSoundboardBottomWidth;

public:
    /// Default constructor (disabled)
    ItemSoundBoard() = delete;

    /// Copy constructor (disabled)
    ItemSoundBoard(const ItemSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const ItemSoundBoard &) = delete;

    ItemSoundBoard(Game* game);

    void Add(std::shared_ptr<ItemTrack> itemTrack);

    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration) override;
    void AddNote(std::shared_ptr<MusicNote> note);

    /**
    * Accept a visitor
    * @param visitor The visitor we accept
    */
    void Accept(ItemVisitor* visitor) override { visitor->VisitSoundboard(this); }

    void Update(double elapsed, double timeOnTrack) override;

    void SetBeatSize(double beatSize) {mBeatSize = beatSize;}

    void SetSoundboardTopWidth(double topWidth) {mSoundboardTopWidth = topWidth;}

    void SetSoundboardBottomWidth(double bottomWidth) {mSoundboardBottomWidth = bottomWidth;}
    void GetTrackValues(std::shared_ptr<Declaration> declaration,
                        double &y1Track,
                        double &y2Track,
                        double &x1Space,
                        double &x2Space,
                        double &x1InitLeftTrack,
                        double &x2InitLeftTrack,
                        double &x1InitRightTrack,
                        double &x2InitRightTrack);
    void DrawOnTop(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration) override;
};

#endif //PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H
