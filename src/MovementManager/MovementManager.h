#pragma once
#include "MovementContainer.h"
#include "RoutineContainer.h"
#include <set>

class MovementManager {
private:
	// Movement container
	MovementRoutineEngine* movementRoutineEngine;
	
	bool m_showDebug = false;

	std::map<sf::Transformable*, MovementRoutine*> m_routineMovementActive;
	std::unordered_map<std::string, std::vector<std::map<sf::Transformable*, MovementRoutine*>::iterator> > m_routineMovementActiveMapped;

	std::map<sf::Transformable*, MovementRoutineContainer*>  m_routineMovement;
	std::unordered_map<std::string, std::vector<std::map<sf::Transformable*, MovementRoutineContainer*>::iterator> > m_routineMovementMapped;
	MovementRoutineContainer* m_movementRoutineContainer;

	std::map<sf::Transformable*, ScalingRoutine*> m_routineScalingActive;
	std::unordered_map<std::string, std::vector<std::map<sf::Transformable*, ScalingRoutine*>::iterator> > m_routineScalingActiveMapped;

	std::map<sf::Transformable*, ScalingRoutineContainer*>  m_routineScaling;
	std::unordered_map<std::string, std::vector<std::map<sf::Transformable*, ScalingRoutineContainer*>::iterator> > m_routineScalingMapped;
	ScalingRoutineContainer* m_scalingRoutineContainer;

	std::map<sf::Transformable*, RotationRoutine*> m_routineRotationActive;
	std::unordered_map<std::string, std::vector<std::map<sf::Transformable*, RotationRoutine*>::iterator> > m_routineRotationActiveMapped;

	std::map<sf::Transformable*, RotationRoutineContainer*>  m_routineRotation;
	std::unordered_map<std::string, std::vector<std::map<sf::Transformable*, RotationRoutineContainer*>::iterator> > m_routineRotationMapped;
	RotationRoutineContainer* m_rotationRoutineContainer;

	inline void printDebug(const std::string& message) const;

public:
	MovementManager();
	MovementManager(const MovementManager& obj);
	~MovementManager();

	// Update functions
	void update(const float dt);

	// Universal public functions
	void setFunction(easeFunctions::Tmovement_function usedFunctionType);
	void setFunction(std::string& name, easeFunctions::Tmovement_function usedFunctionType);
	void setFunction(sf::Transformable& transformable, easeFunctions::Tmovement_function usedFunctionType);

	void setDelayBefore(const float delay, const bool reset = false);
	void setDelayBefore(std::string& name, const float delay, const bool reset = false);
	void setDelayBefore(sf::Transformable& transformable, const float delay, const bool reset = false);

	void setMotionDuration(const float time, const bool reset = false);
	void setMotionDuration(std::string& name, const float time, const bool reset = false);
	void setMotionDuration(sf::Transformable& transformable, const float time, const bool reset = false);

	void setDelayAfter(const float delay, const bool reset = false);
	void setDelayAfter(std::string& name, const float delay, const bool reset = false);
	void setDelayAfter(sf::Transformable& transformable, const float delay, const bool reset = false);

	void resetRoutines();
	void resetRoutines(sf::Transformable& transformable);

	// === Movement ===
	MovementRoutine* createMovementRoutine(const std::string& name);

	MovementRoutine* getMovementRoutine(const std::string& name);
	MovementRoutine* getMovementRoutine(sf::Transformable& transformable, const std::string& name);

	MovementRoutine* linkMovementRoutine(sf::Transformable& transformable, const std::string& name);
	void unlinkMovementRoutine(sf::Transformable* transformable, const std::string& name);

	void startMovementRoutine(sf::Transformable& transformable, const std::string& name);
	void pauseMovementRoutine(sf::Transformable& transformable, const std::string& name);
	void resumeMovementRoutine(sf::Transformable& transformable, const std::string& name);
	void resetMovementRoutine(sf::Transformable& transformable, const std::string& name);
	void stopMovementRoutine(sf::Transformable* transformable, const std::string& name);

	void deleteMovementRoutine();
	void deleteMovementRoutine(const std::string& name);

	const long long int getSizeMovement() const;

	// === Scaling ===
	ScalingRoutine* createScalingRoutine(const std::string& name);

	ScalingRoutine* getScalingRoutine(const std::string& name);
	ScalingRoutine* getScalingRoutine(sf::Transformable& transformable, const std::string& name);

	ScalingRoutine* linkScalingRoutine(sf::Transformable& transformable, const std::string& name);
	void unlinkScalingRoutine(sf::Transformable* transformable, const std::string& name);

	void startScalingRoutine(sf::Transformable& transformable, const std::string& name);
	void pauseScalingRoutine(sf::Transformable& transformable, const std::string& name);
	void resumeScalingRoutine(sf::Transformable& transformable, const std::string& name);
	void resetScalingRoutine(sf::Transformable& transformable, const std::string& name);
	void stopScalingRoutine(sf::Transformable* transformable, const std::string& name);

	void deleteScalingRoutine();
	void deleteScalingRoutine(const std::string& name);

	const long long int getSizeScaling() const;

	// === Rotation ===
	RotationRoutine* createRotationRoutine(const std::string& name);

	RotationRoutine* getRotationRoutine(const std::string& name);
	RotationRoutine* getRotationRoutine(sf::Transformable& transformable, const std::string& name);

	RotationRoutine* linkRotationRoutine(sf::Transformable& transformable, const std::string& name);
	void unlinkRotationRoutine(sf::Transformable* transformable, const std::string& name);

	void startRotationRoutine(sf::Transformable& transformable, const std::string& name);
	void pauseRotationRoutine(sf::Transformable& transformable, const std::string& name);
	void resumeRotationRoutine(sf::Transformable& transformable, const std::string& name);
	void resetRotationRoutine(sf::Transformable& transformable, const std::string& name);
	void stopRotationRoutine(sf::Transformable* transformable, const std::string& name);

	void deleteRotationRoutine();
	void deleteRotationRoutine(const std::string& name);

	const long long int getSizeRotation() const;

	// Accessors / Mutators
	void setDebug(const bool debug);
};