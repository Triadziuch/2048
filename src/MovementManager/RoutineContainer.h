#pragma once
#include <unordered_map>
#include "TransformationRoutine.h"

class RoutineContainer {
protected:
	MovementRoutineEngine* m_movementRoutineEngine{};

	// Constructors / Destructors
	RoutineContainer();
	RoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr);
	~RoutineContainer();
};

class MovementRoutineContainer : protected RoutineContainer {
private:
	std::unordered_map<std::string, MovementRoutine*> m_movementRoutines{};

public:
	// Constructors / Destructors
	MovementRoutineContainer();
	MovementRoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr);
	~MovementRoutineContainer();

	// Public functions
	MovementRoutine* exists(const std::string& _name);
	MovementRoutine* exists(const MovementRoutine* _movement_routine);

	MovementRoutine getRoutine(const std::string& _name);
	MovementRoutine* getRoutinePtr(const std::string& _name);

	MovementRoutine* createRoutine(const std::string& _name);
	MovementRoutine* createRoutine(const std::string& _name, MovementRoutine* _movement_routine);

	void clear();
	void deleteRoutine(const std::string& _name);

	const size_t& getRoutineCount() const;

	const long long int& size() const;
};

class ScalingRoutineContainer : protected RoutineContainer {
private:
	std::unordered_map<std::string, ScalingRoutine*> scalingRoutines{};

public:
	// Constructors / Destructors
	ScalingRoutineContainer();
	ScalingRoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr);
	~ScalingRoutineContainer();

	// Public functions
	ScalingRoutine* exists(const std::string& _name);
	ScalingRoutine* exists(const ScalingRoutine* _scaling_routine);

	ScalingRoutine getRoutine(const std::string& _name);
	ScalingRoutine* getRoutinePtr(const std::string& _name);

	ScalingRoutine* createRoutine(const std::string& _name);
	ScalingRoutine* createRoutine(const std::string& _name, ScalingRoutine* _scaling_routine);

	void clear();
	void deleteRoutine(const std::string& _name);

	const size_t& getRoutineCount() const;

	const long long int& size() const;
};

class RotationRoutineContainer : protected RoutineContainer {
private:
	std::unordered_map<std::string, RotationRoutine*> rotationRoutines{};

public:
	// Constructors / Destructors
	RotationRoutineContainer();
	RotationRoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr);
	~RotationRoutineContainer();

	RotationRoutine* exists(const std::string& _name);
	RotationRoutine* exists(const RotationRoutine* _rotation_routine);

	RotationRoutine getRoutine(const std::string& _name);
	RotationRoutine* getRoutinePtr(const std::string& _name);

	RotationRoutine* createRoutine(const std::string& _name);
	RotationRoutine* createRoutine(const std::string& _name, RotationRoutine* _rotation_routine);

	void clear();
	void deleteRoutine(const std::string& _name);

	const size_t& getRoutineCount() const;

	const long long int& size() const;
};