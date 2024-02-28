/**
 * @file DeclarationImage.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_DECLARATIONIMAGE_H
#define PROJECT1_PROJECT1LIB_DECLARATIONIMAGE_H
#include "Declaration.h"

/**
 * Image Class derived from Declaration
 *
 */
class DeclarationImage : public Declaration
{
private:

public:
    /// Default constructor (disabled)
    DeclarationImage() = delete;

    /// Copy constructor (disabled)
    DeclarationImage(const DeclarationImage &) = delete;

    /// Assignment operator
    void operator=(const DeclarationImage &) = delete;

    DeclarationImage(Game* game);
};

#endif //PROJECT1_PROJECT1LIB_DECLARATIONIMAGE_H
