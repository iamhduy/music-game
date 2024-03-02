/**
 * @file DeclarationNote.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_DECLARATIONNOTE_H
#define PROJECT1_PROJECT1LIB_DECLARATIONNOTE_H
#include "Declaration.h"

/**
 * Note Class derived from Declaration
 *
 */
class DeclarationNote : public Declaration
{
private:
    /// Track Number
    int mTrack = 0;

    /// Tolerance
    double mTolerance = 0;
public:
    /// Default constructor (disabled)
    DeclarationNote() = delete;

    /// Copy constructor (disabled)
    DeclarationNote(const DeclarationNote &) = delete;

    /// Assignment operator
    void operator=(const DeclarationNote &) = delete;

    DeclarationNote(Game* game);

    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y) override;
};

#endif //PROJECT1_PROJECT1LIB_DECLARATIONNOTE_H
