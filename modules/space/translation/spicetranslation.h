/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2025                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#ifndef __OPENSPACE_MODULE_SPACE___SPICETRANSLATION___H__
#define __OPENSPACE_MODULE_SPACE___SPICETRANSLATION___H__

#include <openspace/scene/translation.h>

#include <openspace/properties/misc/stringproperty.h>
#include <openspace/properties/scalar/floatproperty.h>
#include <optional>

namespace openspace {

class SpiceTranslation : public Translation {
public:
    explicit SpiceTranslation(const ghoul::Dictionary& dictionary);

    glm::dvec3 position(const UpdateData& data) const override;

    static documentation::Documentation Documentation();

private:
    properties::StringProperty _target;
    properties::StringProperty _observer;
    properties::StringProperty _frame;
    properties::StringProperty _fixedDate;
    properties::FloatProperty _timeOffset;

    // We are accessing these values every frame and when retrieving a string from the
    // StringProperty, it allocates some new memory, which we want to prevent. Until the
    // property can return a const ref of the string, we keep a local copy as the target,
    // observer, and frame are not likely to change very often
    std::string _cachedTarget;
    std::string _cachedObserver;
    std::string _cachedFrame;
    std::optional<double> _fixedEphemerisTime;

    glm::dvec3 _position = glm::dvec3(0.0);
};

} // namespace openspace

#endif // __OPENSPACE_MODULE_SPACE___SPICETRANSLATION___H__
