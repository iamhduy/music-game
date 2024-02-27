/**
 * @file Image.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_IMAGE_H
#define PROJECT1_PROJECT1LIB_IMAGE_H
#include "Item.h"

class Image : public Item
{
private:

public:
    /// Default constructor (disabled)
    Image() = delete;

    /// Copy constructor (disabled)
    Image(const Image &) = delete;

    /// Assignment operator
    void operator=(const Image &) = delete;

    Image(Game* game);
};

#endif //PROJECT1_PROJECT1LIB_IMAGE_H
