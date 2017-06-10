//
// Author: Marwane Khsime 
// Date: 2017-06-04 05:33:17 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-04 05:33:17
//

#include "Game/Component.hpp"

indie::Component::Component(std::vector<indie::ISprite*> &sprites,
                            size_t backId,
                            double x,
                            double y,
                            double width,
                            double height,
                            indie::Color backColor,
                            indie::Color textColor,
                            std::string text)
        :
        _x(x),
        _y(y),
        _width(width),
        _height(height),
        _backgroundId(backId),
        _posState(0),
        _backgroundColor(backColor),
        _textColor(textColor),
        _text(text),
        _sprites(sprites) {

}

double  indie::Component::getX() const { return (_x); }
void    indie::Component::setX(double x) { this->_x = x; }


double  indie::Component::getY() const { return (_y); }
void    indie::Component::setY(double y) { this->_y = y; }

double  indie::Component::getWidth() const { return (_width); }
void    indie::Component::setWidth(double width) { this->_width = width; }

double  indie::Component::getHeight() const { return (_height); }
void    indie::Component::setHeight(double height) { this->_height = height; }

size_t  indie::Component::getBackgroundId() const { return (_backgroundId); }
void    indie::Component::setBackgroundId(std::size_t id) { this->_backgroundId = id; }

indie::Color    indie::Component::getBackgroundColor() const { return (_backgroundColor); }
void            indie::Component::setBackgorundColor(const Color &color) { this->_backgroundColor = color; }

indie::Color    indie::Component::getTextColor() const { return (_textColor); }
void            indie::Component::setTextColor(const Color &color) { this->_textColor = color; }

std::string const&  indie::Component::getText() const { return (_text); }
void                indie::Component::setText(const std::string &text) { this->_text = text; }

bool                indie::Component::hasSprite() const { return this->_sprites.size() > 0 ? true : false; }