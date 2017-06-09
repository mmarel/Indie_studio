//
// Author: Marwane Khsime 
// Date: 2017-06-04 05:36:00 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-04 05:36:00
//

#ifndef TILE_HPP
# define TILE_HPP

#include "Interfaces/ITile.hpp"

namespace indie
{
    class Tile : public indie::ITile {

        public:

            Tile(bool hasModel = false,
                 std::size_t modelId = 0,
                 const std::string &texture = ""
                 );

            virtual ~Tile() { }


            virtual Color                           getColor() const;
            virtual bool                            hasModel() const;
            virtual std::size_t                     getModelId() const;
            virtual std::size_t                     getObjectId() const;
            virtual ELookAt                         getObjectRotation() const;
            virtual std::string                     getObjectTexture() const;
            virtual bool                            doesAnimationChanged() const;
            virtual std::pair<size_t, size_t>       getObjectFrameLoop() const;
            virtual double                          getShiftX() const;
            virtual double                          getShiftY() const;

            void                    setColor(const Color &);
            void                    setHasModel(bool);
            void                    setModelId(std::size_t);
            void                    setObjectId(std::size_t);
            void                    setObjectRotation(ELookAt);
            void                    setObjectTexture(const std::string &);
            void                    setDoesAnimationChanged(bool);
            void                    setObjectFrameLoop(const std::pair<std::size_t, std::size_t> &);
            void                    setShiftX(double);
            void                    setShiftY(double);

        private:

            Color                                   _color;
            bool                                    _hasModel;
            std::size_t                             _modelId;
            std::size_t                             _objectId;
            ELookAt                                 _objectRotation;
            std::string                             _objectTexture;
            bool                                    _doesAnimationChanged;
            std::pair<std::size_t, std::size_t>     _objectFrameLoop;
            double                                  _shiftX;
            double                                  _shiftY;

    };
}

#endif // TILE_HPP
