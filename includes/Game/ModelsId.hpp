//
// Author: Marwane Khsime
// Date: 2017-06-08 01:06:38
//
// Last Modified by:   Marwane Khsime
// Last Modified time: 2017-06-08 01:06:38
//

#ifndef MODELS_ID_HPP
# define MODELS_ID_HPP

namespace indie
{

    enum class MODELS_ID : int {

        UNKNOWN = -1,
        SKELETON_MODEL = 0,
        BOX_MODEL = 1,
        SQUAREBOMB_MODEL = 2,
        PIKES_MODEL_1 = 3,
        PIKES_MODEL_2 = 4,
        PIKES_MODEL_3 = 5,
        PIKES_MODEL_4 = 6,
        PIKES_MODEL_CENTER = 7,
        TENTACLE_MODEL_1 = 8,
        TENTACLE_MODEL_2 = 9,
        TENTACLE_MODEL_3 = 10,
        TENTACLE_MODEL_4 = 11,
        TENTACLE_MODEL_5 = 12,
        TENTACLE_MODEL_6 = 13,
        TENTACLE_MODEL_PORTAL = 14,
        FALLING_PILLAR_MODEL = 15,
        BONUS_SQUAREB_MODEL = 16,
        BONUS_TENTACLEB_MODEL = 17
    };

    enum class OBJECTS_ID : int {

        UNKNOWN = -1,
        EMPTY = 0,
        PLAYER_ONE = 1,
        PLAYER_TWO = 2,
        PLAYER_THREE = 3,
        PLAYER_FOURTH = 4,
        BOX = 5,
        WALL = 6,
        SQUAREBOMB = 7,
        PIKESBOMB = 8,
        TENTACLEBOMB = 9,
        BONUS_TENTACLEB = 10,
        BONUS_SQUAREB = 11,
        FALLING_PILLAR = 12
    };

    struct      AnimationState {
      size_t id;
      bool over;
      AnimationState(size_t id_, bool over_ = true) : id(id_), over(over_){};
    };

}

#endif // MODELS_ID_HPP
