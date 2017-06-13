//
// Author: Sebastien Jacobin 
// Date: 2017-06-14 01:29:26 
//
// Last Modified by:   Sebastien Jacobin 
// Last Modified time: 2017-06-14 01:29:26
//

#include "Common/Sprite.hpp"

indie::Sprite& indie::Sprite::operator=(const indie::Sprite &other) {
    _spritesPath = other._spritesPath;
    return (*this);
}

size_t indie::Sprite::SpritesCount() const {
    return (_spritesPath.size());
}

std::string indie::Sprite::getGraphicPath(size_t pos) const {
    return (_spritesPath.at(pos));
}

void indie::Sprite::addPath(std::string path) {
    _spritesPath.push_back(path);
}