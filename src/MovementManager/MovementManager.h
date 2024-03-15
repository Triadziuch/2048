#pragma once
#include "MovementContainer.h"
#include "RoutineContainer.h"
#include <set>

class MovementManager {
private:
	// Singleton instance
	static MovementManager* sInstance;

	bool debug = false;

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

	// Constructors / Destructors
	MovementManager();
	~MovementManager();

	inline void printDebug(const std::string& message) const;

public:
	MovementManager(const MovementManager&) = delete;
	MovementManager& operator=(const MovementManager&) = delete;

	static MovementManager* getInstance();

	// Movement container
	MovementRoutineEngine* movementRoutineEngine;

	// Update functions
	void update(const float dt);

	// Universal public functions
	void setFunction(sf::Transformable& transformable, easeFunctions::Tmovement_function usedFunctionType);
	void setAnimationTime(sf::Transformable& transformable, const float _time);
	void resetRoutines(sf::Transformable& transformable);

	// === Movement ===
	MovementRoutine* createMovementRoutine(const std::string& _name);

	MovementRoutine* getMovementRoutine(const std::string& _name);
	MovementRoutine* getMovementRoutine(sf::Transformable& transformable, const std::string& _name);

	MovementRoutine* linkMovementRoutine(sf::Transformable& transformable, const std::string& _name);
	void unlinkMovementRoutine(sf::Transformable* transformable, const std::string& _name);

	void startMovementRoutine(sf::Transformable& transformable, const std::string& _name);
	void pauseMovementRoutine(sf::Transformable& transformable, const std::string& _name);
	void resumeMovementRoutine(sf::Transformable& transformable, const std::string& _name);
	void resetMovementRoutine(sf::Transformable& transformable, const std::string& _name);
	void stopMovementRoutine(sf::Transformable* transformable, const std::string& _name);

	void deleteMovementRoutine();
	void deleteMovementRoutine(const std::string& _name);

	const long long int getSizeMovement() const;

	// === Scaling ===
	ScalingRoutine* createScalingRoutine(const std::string& _name);

	ScalingRoutine* getScalingRoutine(const std::string& _name);
	ScalingRoutine* getScalingRoutine(sf::Transformable& transformable, const std::string& _name);

	ScalingRoutine* linkScalingRoutine(sf::Transformable& transformable, const std::string& _name);
	void unlinkScalingRoutine(sf::Transformable* transformable, const std::string& _name);

	void startScalingRoutine(sf::Transformable& transformable, const std::string& _name);
	void pauseScalingRoutine(sf::Transformable& transformable, const std::string& _name);
	void resumeScalingRoutine(sf::Transformable& transformable, const std::string& _name);
	void resetScalingRoutine(sf::Transformable& transformable, const std::string& _name);
	void stopScalingRoutine(sf::Transformable* transformable, const std::string& _name);

	void deleteScalingRoutine();
	void deleteScalingRoutine(const std::string& _name);

	const long long int getSizeScaling() const;

	// === Rotation ===
	RotationRoutine* createRotationRoutine(const std::string& _name);

	RotationRoutine* getRotationRoutine(const std::string& _name);
	RotationRoutine* getRotationRoutine(sf::Transformable& transformable, const std::string& _name);

	RotationRoutine* linkRotationRoutine(sf::Transformable& transformable, const std::string& _name);
	void unlinkRotationRoutine(sf::Transformable* transformable, const std::string& _name);

	void startRotationRoutine(sf::Transformable& transformable, const std::string& _name);
	void pauseRotationRoutine(sf::Transformable& transformable, const std::string& _name);
	void resumeRotationRoutine(sf::Transformable& transformable, const std::string& _name);
	void resetRotationRoutine(sf::Transformable& transformable, const std::string& _name);
	void stopRotationRoutine(sf::Transformable* transformable, const std::string& _name);

	void deleteRotationRoutine();
	void deleteRotationRoutine(const std::string& _name);

	const long long int getSizeRotation() const;

	// Accessors / Mutators
	void setDebug(const bool debug);
};