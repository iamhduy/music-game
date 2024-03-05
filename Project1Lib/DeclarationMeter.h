/**
 * @file DeclarationMeter.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_DECLARATIONMETER_H
#define PROJECT1_PROJECT1LIB_DECLARATIONMETER_H
#include "Declaration.h"
/**
 * Meter Class derived from Declaration
 *
 */
class DeclarationMeter : public Declaration
{
private:
    /// Cover image dir
    std::wstring mCoverFile;

    std::unique_ptr<wxImage> mCoverImage;

    std::unique_ptr<wxBitmap> mCoverBitmap;

    /// Needle image dir
    std::wstring mNeedleFile;

    std::unique_ptr<wxImage> mNeedleImage;

    std::unique_ptr<wxBitmap> mNeedleBitmap;

    double mScorePct;
public:
    /// Default constructor (disabled)
    DeclarationMeter() = delete;

    /// Copy constructor (disabled)
    DeclarationMeter(const DeclarationMeter &) = delete;

    /// Assignment operator
    void operator=(const DeclarationMeter &) = delete;

    DeclarationMeter(Game* game);

    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y) override;
};

#endif //PROJECT1_PROJECT1LIB_DECLARATIONMETER_H
