//
// Author: Marwane Khsime
// Date: 2017-05-22 17:50:23
//
// Last Modified by:   Marwane Khsime
// Last Modified time: 2017-05-22 17:50:23
//

#ifndef ITILE_HPP_
# define ITILE_HPP_

#include <cstddef>
#include <string>
#include <utility>
#include "Color.hpp"
#include "Game/ModelsId.hpp"

namespace indie
{

	///
	/// \enum class ELookAT : int
	///	\brief Indicate the direction where the model is looking at.
	///
	enum class ELookAt : int
	{
		NORTH = 0,
		EAST,
		SOUTH,
		WEST
	};

	///
	/// \class ITile
	/// \brief Interface representing a tile
	///
	/// A tile is a "block" of the map. It can be a wall, a empty block,
	/// a player, etc. It can be described with a type, a color and/or
	/// a Model.
	///
	class ITile
	{
	public:
		///
		/// \fn virtual ~ITile()
		/// \brief Virtual destructor of the interface
		///
		virtual ~ITile() {};

		///
		/// \fn virtual bool hasModel() const = 0
		/// \brief Returns true if the Tile has a Model affected
		///
		virtual bool hasModel() const = 0;
		///
		/// \fn virtual size_t getModelId() const = 0
		/// \brief Get the Mesh ID linked with the model
		///
		virtual size_t getModelId() const = 0;
		///
		/// \fn virtual size_t getObjectId() const = 0
		/// \brief Get the Model ID
		///
		virtual size_t getObjectId() const = 0;
		///
		/// \fn virtual ELookAt getObjectRotation() const = 0
		/// \brief Get the direction towards which the character is directed
		///
		virtual ELookAt getObjectRotation() const = 0;
		///
		/// \fn virtual std::string getObjectTexture() const = 0
		/// \brief Get the Model texture
		///
		virtual std::string getObjectTexture() const = 0;
		///
		/// \fn virtual bool doesAnimationChanged() const = 0
		/// \brief Returns true if the animation of the model has been changed
		///
		virtual bool doesAnimationChanged() const = 0;
		///
		/// \fn virtual std::pair<size_t, size_t> getObjectFrameLoop() const = 0
		/// \brief Get the new frame loop of the model.
		///
		virtual std::pair<size_t, size_t> getObjectFrameLoop() const = 0;
		///
		/// \fn virtual double getShiftX() const = 0
		/// \brief Get the tile position shift on x
		///
		virtual double getShiftX() const = 0;
			///
		/// \fn virtual size_t getShiftY() const = 0
		/// \brief Get the tile position shift on y
		///
		virtual double getShiftY() const = 0;
			///
		/// \fn virtual OBJECTS_ID getType() const = 0
		/// \brief Get the type of the object int the tile
		///
    virtual OBJECTS_ID getType() const = 0;
	};
}

#endif // !ITILE_HPP_
