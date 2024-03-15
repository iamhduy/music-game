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
#include <map>
#include <vector>

/**
 * SoundBoard Class derived from Item
 *
 */
class ItemSoundBoard : public Item
{
private:
    /// holding the tracks
    std::vector<std::shared_ptr<ItemTrack>> mTracks;

    /// key positions
    std::map<int, std::pair<int, int>> keyPositions;

    ///key codes todo remove these hard codes?
    std::vector<wxChar> keyCodes = {'A', 'S', 'D', 'F', 'J', 'K', 'L', ';'};

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

    int GetKeyXPosition(wxChar keyCode);

    int GetKeyYPosition(wxChar keyCode);

    int GetTotalNotesPassed() const;
};

#endif //PROJECT1_PROJECT1LIB_ITEMSOUNDBOARD_H