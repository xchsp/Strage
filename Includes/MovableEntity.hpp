#ifndef HPP_MOVABLE_ENTITY_HPP
#define HPP_MOVABLE_ENTITY_HPP

#include <Entity.hpp>
#include <LevelManager.hpp>
#include <Renderer.hpp>
#include <SDL2/SDL.h>
#include <TextureManager.hpp>

/** @class MovableEntity
 * An entity that can move up, down, left and right onto the map. A movable entity can't go across a scene wall.
 * @author Adrien RICCIARDI
 */
class MovableEntity: public Entity
{
	public:
		/** All entity possible facing directions. */
		typedef enum
		{
			FACING_DIRECTION_UP,
			FACING_DIRECTION_DOWN,
			FACING_DIRECTION_LEFT,
			FACING_DIRECTION_RIGHT
		} FacingDirection; // Must be declared before usage in protected section
		
	protected:
		/** Rotate the texture when rendering (degrees unit). */
		double _rotationAngle;
		/** Tell in which direction the entity is facing. */
		FacingDirection _facingDirection;
		
		/** How many pixels to move the entity. */
		int _movingPixelsAmount;
	
	public:
		/** Gather some initialization common to all movable entities.
		 * @param textureId The texture to use on rendering.
		 * @param x The X coordinate where to spawn the entity.
		 * @param y The Y coordinate where to spawn the entity.
		 * @param movingPixelsAmount Entity moving speed.
		 */
		MovableEntity(TextureManager::TextureId textureId, int x, int y, int movingPixelsAmount): Entity(textureId)
		{
			// Cache some parameters to fasten rendering
			_positionRectangle.x = x;
			_positionRectangle.y = y;
			
			_movingPixelsAmount = movingPixelsAmount;
			
			// Entity is facing up on spawn
			_rotationAngle = 0;
			_facingDirection = FACING_DIRECTION_UP;
		}
		
		/** Move the entity to the up.
		 * @return How many pixels the entity moved.
		 */
		virtual int moveToUp()
		{
			int leftSideDistanceToWall, rightSizeDistanceToWall, distanceToWall;
			
			// Check upper border distance against level walls
			leftSideDistanceToWall = LevelManager::getDistanceFromUpperWall(_positionRectangle.x, _positionRectangle.y);
			rightSizeDistanceToWall = LevelManager::getDistanceFromUpperWall(_positionRectangle.x + _positionRectangle.w - 1, _positionRectangle.y);
			
			// Keep the smaller distance
			if (leftSideDistanceToWall < rightSizeDistanceToWall) distanceToWall = leftSideDistanceToWall;
			else distanceToWall = rightSizeDistanceToWall;
			
			// Move if possible
			if (distanceToWall >= _movingPixelsAmount) _positionRectangle.y -= _movingPixelsAmount;
			else _positionRectangle.y -= distanceToWall;
			
			// Entity is facing up
			_rotationAngle = 0;
			_facingDirection = FACING_DIRECTION_UP;
			
			return distanceToWall;
		}
		
		/** Move the entity to the down.
		 * @return How many pixels the entity moved.
		 */
		virtual int moveToDown()
		{
			int leftSideDistanceToWall, rightSizeDistanceToWall, distanceToWall;
			
			// Check downer border distance against level walls
			leftSideDistanceToWall = LevelManager::getDistanceFromDownerWall(_positionRectangle.x, _positionRectangle.y + _positionRectangle.h);
			rightSizeDistanceToWall = LevelManager::getDistanceFromDownerWall(_positionRectangle.x + _positionRectangle.w - 1, _positionRectangle.y + _positionRectangle.h);
			
			// Keep the smaller distance
			if (leftSideDistanceToWall < rightSizeDistanceToWall) distanceToWall = leftSideDistanceToWall;
			else distanceToWall = rightSizeDistanceToWall;
			
			// Move if possible
			if (distanceToWall >= _movingPixelsAmount) _positionRectangle.y += _movingPixelsAmount;
			else _positionRectangle.y += distanceToWall;
			
			// Entity is facing down
			_rotationAngle = 180;
			_facingDirection = FACING_DIRECTION_DOWN;
			
			return distanceToWall;
		}
		
		/** Move the entity to the left.
		 * @return How many pixels the entity moved.
		 */
		virtual int moveToLeft()
		{
			int upperSideDistanceToWall, downerSizeDistanceToWall, distanceToWall;
			
			// Check leftmost border distance against level walls
			upperSideDistanceToWall = LevelManager::getDistanceFromLeftmostWall(_positionRectangle.x, _positionRectangle.y);
			downerSizeDistanceToWall = LevelManager::getDistanceFromLeftmostWall(_positionRectangle.x, _positionRectangle.y + _positionRectangle.h - 1);
			
			// Keep the smaller distance
			if (upperSideDistanceToWall < downerSizeDistanceToWall) distanceToWall = upperSideDistanceToWall;
			else distanceToWall = downerSizeDistanceToWall;
			
			// Move if possible
			if (distanceToWall >= _movingPixelsAmount) _positionRectangle.x -= _movingPixelsAmount;
			else _positionRectangle.x -= distanceToWall;
			
			// Entity is facing left
			_rotationAngle = 270;
			_facingDirection = FACING_DIRECTION_LEFT;
			
			return distanceToWall;
		}
		
		/** Move the entity to the right.
		 * @return How many pixels the entity moved.
		 */
		virtual int moveToRight()
		{
			int upperSideDistanceToWall, downerSizeDistanceToWall, distanceToWall;
			
			// Check rightmost border distance against level walls
			upperSideDistanceToWall = LevelManager::getDistanceFromRightmostWall(_positionRectangle.x + _positionRectangle.w, _positionRectangle.y);
			downerSizeDistanceToWall = LevelManager::getDistanceFromRightmostWall(_positionRectangle.x + _positionRectangle.w, _positionRectangle.y + _positionRectangle.h - 1);
			
			// Keep the smaller distance
			if (upperSideDistanceToWall < downerSizeDistanceToWall) distanceToWall = upperSideDistanceToWall;
			else distanceToWall = downerSizeDistanceToWall;
			
			// Move if possible
			if (distanceToWall >= _movingPixelsAmount) _positionRectangle.x += _movingPixelsAmount;
			else _positionRectangle.x += distanceToWall;
			
			// Entity is facing right
			_rotationAngle = 90;
			_facingDirection = FACING_DIRECTION_RIGHT;
			
			return distanceToWall;
		}
		
		/** Display the texture and rotate it in the same time. */
		virtual void render()
		{
			// Display the texture only if the entity is visible on screen
			if (Renderer::isDisplayable(&_positionRectangle)) _pointerTexture->render(_positionRectangle.x - Renderer::displayX, _positionRectangle.y - Renderer::displayY, _rotationAngle);
		}
		
		/** Tell in which direction the entity is facing.
		 * @return The entity facing direction.
		 */
		inline FacingDirection getFacingDirection()
		{
			return _facingDirection;
		}
};

#endif