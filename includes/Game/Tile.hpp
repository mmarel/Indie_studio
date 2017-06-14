//
// Author: Marwane Khsime
// Date: 2017-06-04 05:36:00
//
// Last Modified by:   Marwane Khsime
// Last Modified time: 2017-06-04 05:36:00
//

#ifndef TILE_HPP
# define TILE_HPP

# include "Interfaces/ITile.hpp"
# include <vector>
# include <map>
# include <algorithm>
# include <functional>

namespace indie
{
    typedef std::function<std::pair<size_t, size_t>()> FrameSeeker;

    class Tile : public indie::ITile {

        public:

            Tile(bool hasModel = false,
                 std::size_t modelId = 0,
                 const std::string &texture = ""
                 );

            virtual ~Tile() { }

            virtual bool                            hasModel() const;
            virtual std::size_t                     getModelId() const;
            virtual std::size_t                     getObjectId() const;
            virtual ELookAt                         getObjectRotation() const;
            virtual std::string                     getObjectTexture() const;
            virtual bool                            doesAnimationChanged() const;
            virtual std::pair<size_t, size_t>       getObjectFrameLoop() const;
            virtual double                          getShiftX() const;
            virtual double                          getShiftY() const;
            virtual OBJECTS_ID                      getType() const;

            void                    setHasModel(bool);
            void                    setModelId(std::size_t);
            void                    setObjectId(std::size_t);
            void                    setObjectRotation(ELookAt);
            void                    setObjectTexture(const std::string &);
            void                    setDoesAnimationChanged(bool);
            void                    setObjectFrameLoop(const std::pair<std::size_t, std::size_t> &);
            void                    setShiftX(double);
            void                    setShiftY(double);
            void                    setType(OBJECTS_ID);

            void        setCD(std::size_t);
            std::size_t getCurrentCD() const;
            Tile        &operator=(const Tile &);
            void        reset();

        public:
          static std::pair<size_t, size_t> getSkeletonFrame(std::string);
          static std::pair<size_t, size_t> getLethalFrame(OBJECTS_ID);
          static bool                      isFrameLethal(OBJECTS_ID,
                                                          std::pair<size_t, size_t>);
          static std::pair<size_t, size_t> getNextFrameSquareBomb(std::pair<size_t, size_t>);
          static std::pair<size_t, size_t> getNextFramePikesBomb(std::pair<size_t, size_t>);
          static std::pair<size_t, size_t> getNextFrameTentacleBomb(std::pair<size_t, size_t>);
          static std::pair<size_t, size_t> getNextFrame(OBJECTS_ID,
                                                        std::pair<size_t, size_t>);
        private:

            bool                                    _hasModel;
            std::size_t                             _modelId;
            std::size_t                             _objectId;
            ELookAt                                 _objectRotation;
            std::string                             _objectTexture;
            bool                                    _doesAnimationChanged;
            std::pair<std::size_t, std::size_t>     _objectFrameLoop;
            double                                  _shiftX;
            double                                  _shiftY;
            OBJECTS_ID                              _type;
            std::size_t                             _cd;
    };
}

#endif // TILE_HPP
