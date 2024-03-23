#pragma once
#include <unordered_map>
#include "TransformationRoutine.h"

class RoutineContainer {
protected:
	MovementRoutineEngine* m_movementRoutineEngine{};
	std::unordered_map<std::string*, TransformationRoutine*> m_routines{};

	// Constructors / Destructors
	RoutineContainer();
	RoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr);
	RoutineContainer(const RoutineContainer& obj);
	~RoutineContainer();

public:
	void setDelayBefore(const float delay, const bool reset = false);
	void setDelayBefore(std::string& name, const float delay, const bool reset = false);

	void setMotionDuration(const float time, const bool reset = false);
	void setMotionDuration(std::string& name, const float time, const bool reset = false);

	void setDelayAfter(const float delay, const bool reset = false);
	void setDelayAfter(std::string& name, const float delay, const bool reset = false);

	const size_t& getRoutineCount() const;
};

class MovementRoutineContainer : public RoutineContainer {
private:
	std::unordered_map<std::string, MovementRoutine*> m_movementRoutines{};

public:
	// Constructors / Destructors
	MovementRoutineContainer();
	MovementRoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr);
	~MovementRoutineContainer();

	// Public functions
	MovementRoutine* exists(const std::string& name);
	MovementRoutine* exists(const MovementRoutine* movementRoutine);

	MovementRoutine getRoutine(const std::string& name);
	MovementRoutine* getRoutinePtr(const std::string& name);

	MovementRoutine* createRoutine(const std::string& name);
	MovementRoutine* createRoutine(const std::string& name, MovementRoutine* movementRoutine);

	void clear();
	void deleteRoutine(const std::string& name);

	const long long int& size() const;
};

class ScalingRoutineContainer : public RoutineContainer {
private:
	std::unordered_map<std::string, ScalingRoutine*> m_scalingRoutines{};

public:
	// Constructors / Destructors
	ScalingRoutineContainer();
	ScalingRoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr);
	~ScalingRoutineContainer();

	// Public functions
	ScalingRoutine* exists(const std::string& name);
	ScalingRoutine* exists(const ScalingRoutine* scalingRoutine);

	ScalingRoutine getRoutine(const std::string& name);
	ScalingRoutine* getRoutinePtr(const std::string& name);

	ScalingRoutine* createRoutine(const std::string& name);
	ScalingRoutine* createRoutine(const std::string& name, ScalingRoutine* scalingRoutine);

	void clear();
	void deleteRoutine(const std::string& name);

	const long long int& size() const;
};

class RotationRoutineContainer : public RoutineContainer {
private:
	std::unordered_map<std::string, RotationRoutine*> m_rotationRoutines{};

public:
	// Constructors / Destructors
	RotationRoutineContainer();
	RotationRoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr);
	~RotationRoutineContainer();

	RotationRoutine* exists(const std::string& name);
	RotationRoutine* exists(const RotationRoutine* rotationRoutine);

	RotationRoutine getRoutine(const std::string& name);
	RotationRoutine* getRoutinePtr(const std::string& name);

	RotationRoutine* createRoutine(const std::string& name);
	RotationRoutine* createRoutine(const std::string& name, RotationRoutine* rotationRoutine);

	void clear();
	void deleteRoutine(const std::string& name);

	const long long int& size() const;
};