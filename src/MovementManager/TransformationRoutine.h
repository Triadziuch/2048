#pragma once
#include "transformationInfo.h"
class MovementContainerBase;
class MovementRoutineEngine;

// - - - - - - - - - - - - - - - - - - - - TransformationRoutine - - - - - - - - - - - - - - - - - - - - \\

class TransformationRoutine {
protected:
	MovementRoutineEngine* m_movementRoutineEngine{};
	std::vector <transformationInfo*> m_transformations;
	bool				   m_adjustStartToCurrentTransform{};
	bool				   m_adjustAllToCurrentTransform{};
	bool				   m_isLooping{};

public:
	std::string			   m_routineName{};
	size_t				   m_current{};
	size_t				   m_count{};
	bool				   m_isActive{};
	bool				   m_isPaused{};
	bool				   m_pauseAtStart{};
	bool				   m_pauseAfterChangingMovements{};

	// Constructors / Destructors
	TransformationRoutine() = delete;
	TransformationRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr);
	TransformationRoutine(const TransformationRoutine& obj);
	~TransformationRoutine();

	// Mutators
	void setLooping(bool looping);
	void setPauseAtStart(bool pauseAtStart);
	void setPauseAfterChangingMovements(bool pauseAfterChangingMovements);
	void adjustStartToCurrentTransform(bool adjust);
	void adjustAllToCurrentTransform(bool adjust);

	void setDelayBefore(const float delay, const bool reset = false);
	void setMotionDuration(const float animationTime, const bool reset = false);
	void setDelayAfter(const float delay, const bool reset = false);

	void setFunction(easeFunctions::Tmovement_function usedFunctionType);
	void setFunction(easeFunctions::Tmovement_function usedFunctionType, const size_t transformation_id);
	void setFunction(double(*usedFunctionPtr)(double));
	void setFunction(double(*usedFunctionPtr)(double), const size_t transformation_id);

	void pause();
	void reset();
	void resume();

	// Accessors
	std::string& getName();
	const std::string& getName() const;
};



// - - - - - - - - - - - - - - - - - - - - MovementRoutine - - - - - - - - - - - - - - - - - - - - \\

class MovementRoutine : public TransformationRoutine {
private:
	std::vector <movementInfo*> m_routineMovements;

	// Private functions
	void adjustStartToCurrent(const sf::Vector2f& currentPosition);
	void adjustAllToCurrent(const sf::Vector2f& currentPosition);

public:
	// Constructors / Destructors
	MovementRoutine() = delete;
	MovementRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr);
	MovementRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr, movementInfo* movement);
	MovementRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr, std::vector<movementInfo*> movements);
	MovementRoutine(const MovementRoutine& obj);
	~MovementRoutine();

	// Update functions
	const bool update(sf::Transformable& transformable, const float dt);
	
	// Public functions
	void addMovement(movementInfo* movement);
	void removeMovement(movementInfo* movement);

	void clear();

	const bool start(sf::Transformable& transformable);
	void reset(sf::Transformable& transformable);
	void stop(sf::Transformable* transformable);

	void move(const sf::Vector2f& offset);

	movementInfo* getCurrentMovement() const;

	const bool goToNextMovement(const sf::Transformable& transformable);

	movementInfo* operator[](const size_t& index) const;

	const long long int& size() const;
};

// - - - - - - - - - - - - - - - - - - - - ScalingRoutine - - - - - - - - - - - - - - - - - - - - \\

class ScalingRoutine : public TransformationRoutine {
private:
	std::vector <scalingInfo*> m_routineScalings;

	// Private functions
	void adjustStartToCurrent(const sf::Vector2f& currentScale);
	void adjustAllToCurrent(const sf::Vector2f& currentScale);

public:
	// Constructors / Destructors
	ScalingRoutine() = delete;
	ScalingRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr);
	ScalingRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr, scalingInfo* scaling);
	ScalingRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr, std::vector<scalingInfo*> scalings);
	ScalingRoutine(const ScalingRoutine& obj);
	~ScalingRoutine();

	// Update functions
	const bool update(sf::Transformable& transformable, const float dt);

	// Public functions
	void addScaling(scalingInfo* scaling);
	void removeScaling(scalingInfo* scaling);

	void clear();

	const bool start(sf::Transformable& transformable);
	void reset(sf::Transformable& transformable);
	void stop(sf::Transformable* transformable);

	scalingInfo* getCurrentScaling() const;

	const bool goToNextScaling(const sf::Transformable& transformable);
	ScalingRoutine* goToScaling(const sf::Transformable& transformable, const size_t scaling_id);

	const long long int& size() const;
};



// - - - - - - - - - - - - - - - - - - - - RotationRoutine - - - - - - - - - - - - - - - - - - - - \\

class RotationRoutine : public TransformationRoutine {
private:
	std::vector <rotationInfo*> m_routineRotations;
	bool m_wasLastClockwise{};

	void adjustStartToCurrent(float currentRotation);
	void adjustAllToCurrent(const float currentRotation);

public:
	// Constructors / Destructors
	RotationRoutine() = delete;
	RotationRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr);
	RotationRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr, rotationInfo* rotation);
	RotationRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr, std::vector<rotationInfo*> rotations);
	RotationRoutine(const RotationRoutine& obj);
	~RotationRoutine();

	// Update functions
	const bool update(sf::Transformable& transformable, const float dt);

	// Public functions
	void addRotation(rotationInfo* rotation);
	void removeRotation(rotationInfo* rotation);

	void clear();

	const bool start(sf::Transformable& transformable);
	void reset(sf::Transformable& transformable);
	void stop(sf::Transformable* transformable);

	rotationInfo* getCurrentRotation() const;

	const bool goToNextRotation(const sf::Transformable& transformable);

	const long long int& size() const;
};