#pragma once
#include "easeFunctions.h"
#include "transformationInfo.h"
#include <map>
#include <assert.h>

class MovementManager;
class TransformationRoutine;
class MovementRoutine;
class ScalingRoutine;
class RotationRoutine;

class MovementContainerBase {
protected:
	constexpr static double M_RAD = 3.14159265358979323846 / 180.0;
};

class MovementContainer : public MovementContainerBase{
private:
	std::map<sf::Transformable*, std::tuple<movementInfo*, scalingInfo*, rotationInfo*>*>	m_Transforms;

	// Singleton instance
	static MovementContainer* sInstance;
	
	// Constructors / Destructors
	MovementContainer() {};
public:
	MovementContainer(const MovementContainer&) = delete;
	MovementContainer& operator=(const MovementContainer&) = delete;

	static MovementContainer* getInstance();

	// Update functions
	void update(float dt);

	// Public functions

	// Movement functions
	const movementInfo* addMovement(sf::Transformable* transformable, movementInfo* movement);

	void undoMovement();
	void undoMovement(sf::Transformable* transformable);

	void resetMovement();
	void resetMovement(sf::Transformable* transformable);

	void stopMovement();
	void stopMovement(sf::Transformable* transformable);

	// Scaling functions
	const scalingInfo* addScaling(sf::Transformable* transformable, scalingInfo* scaling);

	void undoScaling();
	void undoScaling(sf::Transformable* transformable);

	void resetScaling();
	void resetScaling(sf::Transformable* transformable);

	void stopScaling();
	void stopScaling(sf::Transformable* transformable);

	// Rotation functions
	const rotationInfo* addRotation(sf::Transformable* transformable, rotationInfo* rotation);

	void undoRotation();
	void undoRotation(sf::Transformable* transformable);

	void resetRotation();
	void resetRotation(sf::Transformable* transformable);

	void stopRotation();
	void stopRotation(sf::Transformable* transformable);

	// Accessors / Mutators
	const bool isMoving(sf::Transformable* transformable);
	const bool isScaling(sf::Transformable* transformable);
	const bool isRotating(sf::Transformable* transformable);
};

class MovementRoutineEngine : protected MovementContainerBase {
private:
	std::map<sf::Transformable*, std::tuple<MovementRoutine*, ScalingRoutine*, RotationRoutine*>*>	m_Routines;
	bool m_showDebug = false;

	MovementManager* movementManager{};

	void printDebug(const std::string& message) const;
	
public:
	// Constructors / Destructors
	MovementRoutineEngine(const MovementRoutineEngine& obj);
	MovementRoutineEngine(MovementManager* movementManager);

	void setMovementManager(MovementManager* movementManager);

	// Update functions
	void update(float dt);

	// Public functions

	// Movement functions
	const MovementRoutine* addMovement(sf::Transformable* transformable, MovementRoutine* routine);

	void undoMovement();
	void undoMovement(sf::Transformable* transformable);

	void resetMovement();

	void stopMovement();
	void stopMovement(sf::Transformable* transformable);

	// Scaling functions
	const ScalingRoutine* addScaling(sf::Transformable* transformable, ScalingRoutine* routine);

	void undoScaling();
	void undoScaling(sf::Transformable* transformable);

	void resetScaling();

	void stopScaling();
	void stopScaling(sf::Transformable* transformable);

	// Rotation functions
	const RotationRoutine* addRotation(sf::Transformable* transformable, RotationRoutine* routine);

	void undoRotation();
	void undoRotation(sf::Transformable* transformable);

	void resetRotation();

	void stopRotation();
	void stopRotation(sf::Transformable* transformable);

	// Accessors / Mutators
	const bool isMoving(sf::Transformable* transformable);
	const bool isScaling(sf::Transformable* transformable);
	const bool isRotating(sf::Transformable* transformable);
};