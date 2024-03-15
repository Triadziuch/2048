#include "RoutineContainer.h"

// - - - - - - - - - - - - - - - - - - - - RoutineContainer - - - - - - - - - - - - - - - - - - - - \\

// Constructors / Destructors
RoutineContainer::RoutineContainer() :
	m_movementRoutineEngine(nullptr)
	{}

RoutineContainer::RoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr) :
	m_movementRoutineEngine(movementRoutineEnginePtr)
	{}

RoutineContainer::~RoutineContainer()
{
	m_movementRoutineEngine = nullptr;
}

// - - - - - - - - - - - - - - - - - - - - MovementRoutineContainer - - - - - - - - - - - - - - - - - - - - \\

// Constructors / Destructors
MovementRoutineContainer::MovementRoutineContainer() :
	RoutineContainer{}
	{}

MovementRoutineContainer::MovementRoutineContainer(MovementRoutineEngine * movementRoutineEnginePtr) :
	RoutineContainer{ movementRoutineEnginePtr }
	{}

MovementRoutineContainer::~MovementRoutineContainer()
{
	for (auto& routine : m_movementRoutines) 
		delete routine.second;
	m_movementRoutines.clear();
}

// Public functions
MovementRoutine* MovementRoutineContainer::exists(const std::string& _name)
{
	auto movementRoutineFound = m_movementRoutines.find(_name);

	if (movementRoutineFound != m_movementRoutines.end())
		return movementRoutineFound->second;
	else
		return nullptr;
}

MovementRoutine* MovementRoutineContainer::exists(const MovementRoutine* _movement_routine)
{
	for (auto& routine : m_movementRoutines) 
		if (routine.second == _movement_routine)
			return routine.second;
	
	return nullptr;
}

MovementRoutine MovementRoutineContainer::getRoutine(const std::string& _name)
{
	if (exists(_name) != nullptr)
		return *m_movementRoutines[_name];
	else {
		printf("MovementRoutineContainer::getRoutine: Routine with given name does not exist\n");
		return MovementRoutine();
	}
}

MovementRoutine* MovementRoutineContainer::getRoutinePtr(const std::string& _name)
{
	auto* movementRoutineExists = exists(_name);

	if (movementRoutineExists == nullptr)
		printf("MovementRoutineContainer::getRoutine: Routine with given name does not exist\n");

	return movementRoutineExists;
}

MovementRoutine* MovementRoutineContainer::createRoutine(const std::string& _name)
{
	auto* movementRoutineExists = exists(_name);

	if (movementRoutineExists != nullptr) {
		printf("MovementRoutineContainer::createRoutine: Routine with given name already exists\n");
		return movementRoutineExists;
	}
	else {
		MovementRoutine* newMovementRoutine = new MovementRoutine(_name, m_movementRoutineEngine);
		m_movementRoutines.insert(std::make_pair(_name, newMovementRoutine));
		return newMovementRoutine;
	}
}

MovementRoutine* MovementRoutineContainer::createRoutine(const std::string& _name, MovementRoutine* _movement_routine)
{
	auto* movementRoutineExists = exists(_name);

	if (movementRoutineExists != nullptr) {
		printf("MovementRoutineContainer::createRoutine: Routine with given name already exists\n");
		return movementRoutineExists;
	}
	else {
		m_movementRoutines.insert(std::make_pair(_name, _movement_routine));
		return _movement_routine;
	}
}

void MovementRoutineContainer::clear()
{
	for (auto& routine : m_movementRoutines) 
		delete routine.second;
	m_movementRoutines.clear();
}

void MovementRoutineContainer::deleteRoutine(const std::string& _name)
{
	auto movementRoutineFound = this->m_movementRoutines.find(_name);

	if (movementRoutineFound != this->m_movementRoutines.end()) {
		delete movementRoutineFound->second;
		this->m_movementRoutines.erase(movementRoutineFound);
	}
}

const size_t& MovementRoutineContainer::getRoutineCount() const
{
	return m_movementRoutines.size();
}

const long long int& MovementRoutineContainer::size() const
{
	long long int size{ sizeof(this) };
	for (const auto& routine : m_movementRoutines) 
		size += routine.second->size();

	return size;
}

// - - - - - - - - - - - - - - - - - - - - ScalingRoutineContainer - - - - - - - - - - - - - - - - - - - - \\

// Constructors / Destructors
ScalingRoutineContainer::ScalingRoutineContainer() :
	RoutineContainer{}
	{}

ScalingRoutineContainer::ScalingRoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr) :
	RoutineContainer{ movementRoutineEnginePtr }
	{}

ScalingRoutineContainer::~ScalingRoutineContainer()
{
	for (auto& routine : scalingRoutines)
		delete routine.second;
	scalingRoutines.clear();
}

ScalingRoutine* ScalingRoutineContainer::exists(const std::string& _name)
{
	auto scalingRoutineFound = scalingRoutines.find(_name);

	if (scalingRoutineFound != scalingRoutines.end())
		return scalingRoutineFound->second;
	else
		return nullptr;
}

ScalingRoutine* ScalingRoutineContainer::exists(const ScalingRoutine* _scaling_routine)
{
	for (auto& routine : scalingRoutines)
		if (routine.second == _scaling_routine)
			return routine.second;

	return nullptr;
}

ScalingRoutine ScalingRoutineContainer::getRoutine(const std::string& _name)
{
	if (exists(_name) != nullptr)
		return *scalingRoutines[_name];
	else {
		printf("ScalingRoutineContainer::getRoutine: Routine with given name does not exist\n");
		return ScalingRoutine();
	}
}

ScalingRoutine* ScalingRoutineContainer::getRoutinePtr(const std::string& _name)
{
	auto* scalingRoutineExists = exists(_name);

	if (scalingRoutineExists == nullptr)
		printf("ScalingRoutineContainer::getRoutine: Routine with given name does not exist\n");

	return scalingRoutineExists;
}

ScalingRoutine* ScalingRoutineContainer::createRoutine(const std::string& _name)
{
	auto* scalingRoutineExists = exists(_name);

	if (scalingRoutineExists != nullptr) {
		printf("ScalingRoutineContainer::createRoutine: Routine with given name already exists\n");
		return scalingRoutineExists;
	}
	else {
		ScalingRoutine* newScalingRoutine = new ScalingRoutine(_name, m_movementRoutineEngine);
		scalingRoutines.insert(std::make_pair(_name, newScalingRoutine));
		return newScalingRoutine;
	}
}

ScalingRoutine* ScalingRoutineContainer::createRoutine(const std::string& _name, ScalingRoutine* _scaling_routine)
{
	auto* scalingRoutineExists = exists(_name);

	if (scalingRoutineExists != nullptr) {
		printf("ScalingRoutineContainer::createRoutine: Routine with given name already exists\n");
		return scalingRoutineExists;
	}
	else {
		scalingRoutines.insert(std::make_pair(_name, _scaling_routine));
		return _scaling_routine;
	}
}

void ScalingRoutineContainer::clear()
{
	for (auto& routine : scalingRoutines)
		delete routine.second;
	scalingRoutines.clear();
}

void ScalingRoutineContainer::deleteRoutine(const std::string& _name)
{
	auto scalingRoutineFound = this->scalingRoutines.find(_name);

	if (scalingRoutineFound != this->scalingRoutines.end()) {
		delete scalingRoutineFound->second;
		this->scalingRoutines.erase(scalingRoutineFound);
	}
	else {}
		//printf("ScalingRoutineContainer::deleteRoutine: Routine with given name does not exist : %s\n", _name.c_str());
}

const size_t& ScalingRoutineContainer::getRoutineCount() const
{
	return scalingRoutines.size();
}

const long long int& ScalingRoutineContainer::size() const
{
	long long int size{ sizeof(this) };
	for (const auto& routine : scalingRoutines)
		size += routine.second->size();

	return size;
}

// - - - - - - - - - - - - - - - - - - - - RotationRoutineContainer - - - - - - - - - - - - - - - - - - - - \\

// Constructors / Destructors
RotationRoutineContainer::RotationRoutineContainer() :
	RoutineContainer{}
	{}

RotationRoutineContainer::RotationRoutineContainer(MovementRoutineEngine* movementRoutineEnginePtr) :
	RoutineContainer{ movementRoutineEnginePtr }
	{}

RotationRoutineContainer::~RotationRoutineContainer()
{
	for (auto& routine : rotationRoutines)
		delete routine.second;
	rotationRoutines.clear();

}

RotationRoutine* RotationRoutineContainer::exists(const std::string& _name)
{
	auto rotationRoutineFound = rotationRoutines.find(_name);

	if (rotationRoutineFound != rotationRoutines.end())
		return rotationRoutineFound->second;
	else
		return nullptr;
}

RotationRoutine* RotationRoutineContainer::exists(const RotationRoutine* _rotation_routine)
{
	for (auto& routine : rotationRoutines)
		if (routine.second == _rotation_routine)
			return routine.second;

	return nullptr;
}

RotationRoutine RotationRoutineContainer::getRoutine(const std::string& _name)
{
	if (exists(_name) != nullptr)
		return *rotationRoutines[_name];
	else {
		printf("RotationRoutineContainer::getRoutine: Routine with given name does not exist\n");
		return RotationRoutine();
	}
}

RotationRoutine* RotationRoutineContainer::getRoutinePtr(const std::string& _name)
{
	auto* rotationRoutineExists = exists(_name);

	if (rotationRoutineExists == nullptr)
		printf("RotationRoutineContainer::getRoutine: Routine with given name does not exist\n");

	return rotationRoutineExists;
}

RotationRoutine* RotationRoutineContainer::createRoutine(const std::string& _name)
{
	auto* rotationRoutineExists = exists(_name);

	if (rotationRoutineExists != nullptr) {
		printf("RotationRoutineContainer::createRoutine: Routine with given name already exists\n");
		return rotationRoutineExists;
	}
	else {
		RotationRoutine* newRotationRoutine = new RotationRoutine(_name, m_movementRoutineEngine);
		rotationRoutines.insert(std::make_pair(_name, newRotationRoutine));
		return newRotationRoutine;
	}
}

RotationRoutine* RotationRoutineContainer::createRoutine(const std::string& _name, RotationRoutine* _rotation_routine)
{
	auto* rotationRoutineExists = exists(_name);

	if (rotationRoutineExists != nullptr) {
		printf("RotationRoutineContainer::createRoutine: Routine with given name already exists\n");
		return rotationRoutineExists;
	}
	else {
		rotationRoutines.insert(std::make_pair(_name, _rotation_routine));
		return _rotation_routine;
	}
}

void RotationRoutineContainer::clear()
{
	for (auto& routine : rotationRoutines)
		delete routine.second;
	rotationRoutines.clear();
}

void RotationRoutineContainer::deleteRoutine(const std::string& _name)
{
	auto rotationRoutineFound = this->rotationRoutines.find(_name);

	if (rotationRoutineFound != this->rotationRoutines.end()) {
		delete rotationRoutineFound->second;
		this->rotationRoutines.erase(rotationRoutineFound);
	}
}

const size_t& RotationRoutineContainer::getRoutineCount() const
{
	return rotationRoutines.size();
}

const long long int& RotationRoutineContainer::size() const
{
	long long int size{ sizeof(this) };
	for (const auto& routine : rotationRoutines)
		size += routine.second->size();

	return size;
}
