//
// Author: Marwane Khsime 
// Date: 2017-06-04 06:10:56 
//
// Last Modified by:   Marwane Khsime 
// Last Modified time: 2017-06-04 06:10:56
//

#ifndef MAP_HPP
# define MAP_HPP

#include <vector>
#include <memory>
#include "Interfaces/IMap.hpp"
#include "Game/Tile.hpp"
#include "Game/ModelsId.hpp"
#include "Exception/exception.hpp"

namespace indie
{
    class Map : public indie::IMap
    {

        enum class GAME_MAP : int {

            LITTLE_MAP = 0

        };

        public:
            Map(std::size_t which_map);
            Map(Map &&) = default;
            Map(const Map &) = default;
            Map &operator=(Map &&) = default;
            Map &operator=(const Map &) = default;
            virtual ~Map();

            virtual std::size_t getLayerNb() const;
            virtual std::size_t getWidth() const;
            virtual std::size_t getHeight() const;
            virtual std::size_t getSceneId() const;
            virtual ITile const &at(std::size_t layer,
                                    std::size_t x,
                                    std::size_t y) const;

        private:
            // Fill a layer from the index 'layer'
            void    create_layer(std::size_t layer);

            // Push a Tile in the line y
            void    create_tile(std::size_t layer, std::size_t y,
                                bool tile_has_model = false,
                                MODELS_ID model_id = MODELS_ID::UNKNOWN,
                                const std::string &resource_path = "");

            // Map generators
            void    generate_little_map();

            std::size_t _width;
            std::size_t _height;
            std::size_t _nbLayers;
            std::size_t _sceneId;
            std::vector<std::vector<std::vector< std::unique_ptr< Tile > > > > _layers;
            std::vector<std::vector< int > >   _rawMap;
    };
   
}


#endif // MAP_HPP