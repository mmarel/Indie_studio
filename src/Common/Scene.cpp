//
// Author: Marwane Khsime 
// Date: 2017-06-05 06:55:37 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-05 06:55:37
//

#include "Common/Scene.hpp"

indie::Scene::Scene(const std::vector<std::pair<std::string, std::string> > &parts,
                    float x,
                    float y,
                    float z)
        : _sceneParts(parts),
          _x(x),
          _y(y),
          _z(z) {

}

indie::Scene::~Scene() {

}

std::size_t indie::Scene::getNumberParts() const { return this->_sceneParts.size(); }

std::pair<std::string, std::string> indie::Scene::getPartAtPos(std::size_t pos) const {
 
    if (pos < this->_sceneParts.size()) {
        return this->_sceneParts.at(pos);
    }

    return std::pair<std::string, std::string>( { "", "" } );
}

float indie::Scene::getStartX() const { return this->_x; }

float indie::Scene::getStartY() const { return this->_y; }

float indie::Scene::getStartZ() const { return this->_z; }