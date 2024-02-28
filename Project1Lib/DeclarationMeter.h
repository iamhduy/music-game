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
    wxString mCoverFile;

    /// Needle image dir
    wxString mNeedleFile;
public:
    /// Default constructor (disabled)
    DeclarationMeter() = delete;

    /// Copy constructor (disabled)
    DeclarationMeter(const DeclarationMeter &) = delete;

    /// Assignment operator
    void operator=(const DeclarationMeter &) = delete;

    DeclarationMeter(Game* game);

    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_PROJECT1LIB_DECLARATIONMETER_H
