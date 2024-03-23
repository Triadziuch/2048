#pragma once
#include "MovementManager.h"

// Singleton initialization
MovementManager* MovementManager::sInstance = nullptr;

// Constructors / Destructors
MovementManager::MovementManager()
{
	movementRoutineEngine = MovementRoutineEngine::getInstance();
	movementRoutineEngine->setMovementManager(this);

	m_movementRoutineContainer = new MovementRoutineContainer();
	m_scalingRoutineContainer = new ScalingRoutineContainer();
	m_rotationRoutineContainer = new RotationRoutineContainer();
}

MovementManager::~MovementManager()
{
	this->deleteMovementRoutine();
	this->deleteScalingRoutine();
	this->deleteRotationRoutine();

	delete m_movementRoutineContainer;
}

inline void MovementManager::printDebug(const std::string& message) const
{
	if (debug)
		printf("MovementManager: %s\n", message.c_str());
}

MovementManager* MovementManager::getInstance()
{
	if (!sInstance)
		sInstance = new MovementManager();
	return sInstance;
}

// Update functions
void MovementManager::update(const float dt)
{
	this->movementRoutineEngine->update(dt);
}

void MovementManager::setFunction(sf::Transformable& transformable, easeFunctions::Tmovement_function usedFunctionType)
{
	auto movementRoutineFound = m_routineMovementActive.find(&transformable);
	if (movementRoutineFound != m_routineMovementActive.end())
		movementRoutineFound->second->setFunction(usedFunctionType);

	auto scalingRoutineFound = m_routineScalingActive.find(&transformable);
	if (scalingRoutineFound != m_routineScalingActive.end())
		scalingRoutineFound->second->setFunction(usedFunctionType);

	auto rotationRoutineFound = m_routineRotationActive.find(&transformable);
	if (rotationRoutineFound != m_routineRotationActive.end())
		rotationRoutineFound->second->setFunction(usedFunctionType);
}

void MovementManager::setDelayBefore(const float delay, const bool reset)
{
	if (delay < 0.f) return;

	for (auto& movementRoutine : m_routineMovement)
		movementRoutine.second->setDelayBefore(delay, reset);

	for (auto& scalingRoutine : m_routineScaling)
		scalingRoutine.second->setDelayBefore(delay, reset);

	for (auto& rotationRoutine : m_routineRotation)
		rotationRoutine.second->setDelayBefore(delay, reset);
}

void MovementManager::setDelayBefore(std::string& name, const float delay, const bool reset)
{
	if (delay < 0.f) return;

	auto movementRoutineFound = m_routineMovementMapped.find(name);
	if (movementRoutineFound != m_routineMovementMapped.end())
		for (const auto& movementRoutine : movementRoutineFound->second)
			movementRoutine->second->setDelayBefore(delay, reset);

	auto scalingRoutineFound = m_routineScalingMapped.find(name);
	if (scalingRoutineFound != m_routineScalingMapped.end())
		for (const auto& scalingRoutine : scalingRoutineFound->second)
			scalingRoutine->second->setDelayBefore(delay, reset);

	auto rotationRoutineFound = m_routineRotationMapped.find(name);
	if (rotationRoutineFound != m_routineRotationMapped.end())
		for (const auto& rotationRoutine : rotationRoutineFound->second)
			rotationRoutine->second->setDelayBefore(delay, reset);
}

void MovementManager::setDelayBefore(sf::Transformable& transformable, const float delay, const bool reset)
{
	if (delay < 0.f) return;

	auto movementRoutineFound = m_routineMovementActive.find(&transformable);
	if (movementRoutineFound != m_routineMovementActive.end())
		movementRoutineFound->second->setDelayBefore(delay, reset);

	auto scalingRoutineFound = m_routineScalingActive.find(&transformable);
	if (scalingRoutineFound != m_routineScalingActive.end())
		scalingRoutineFound->second->setDelayBefore(delay, reset);

	auto rotationRoutineFound = m_routineRotationActive.find(&transformable);
	if (rotationRoutineFound != m_routineRotationActive.end())
		rotationRoutineFound->second->setDelayBefore(delay, reset);
}

void MovementManager::setMotionDuration(const float time, const bool reset)
{
	if (time < 0.f) return;

	for (auto& movementRoutine : m_routineMovement)
		movementRoutine.second->setMotionDuration(time, reset);

	for (auto& scalingRoutine : m_routineScaling)
		scalingRoutine.second->setMotionDuration(time, reset);

	for (auto& rotationRoutine : m_routineRotation)
		rotationRoutine.second->setMotionDuration(time, reset);
}

void MovementManager::setMotionDuration(std::string& name, const float time, const bool reset)
{
	if (time < 0.f) return;

	auto movementRoutineFound = m_routineMovementMapped.find(name);
	if (movementRoutineFound != m_routineMovementMapped.end())
		for (const auto& movementRoutine : movementRoutineFound->second)
			movementRoutine->second->setMotionDuration(time, reset);

	auto scalingRoutineFound = m_routineScalingMapped.find(name);
	if (scalingRoutineFound != m_routineScalingMapped.end())
		for (const auto& scalingRoutine : scalingRoutineFound->second)
			scalingRoutine->second->setMotionDuration(time, reset);

	auto rotationRoutineFound = m_routineRotationMapped.find(name);
	if (rotationRoutineFound != m_routineRotationMapped.end())
		for (const auto& rotationRoutine : rotationRoutineFound->second)
			rotationRoutine->second->setMotionDuration(time, reset);
}

void MovementManager::setMotionDuration(sf::Transformable& transformable, const float time, const bool reset)
{
	if (time < 0.f) return;

	auto movementRoutineFound = m_routineMovementActive.find(&transformable);
	if (movementRoutineFound != m_routineMovementActive.end())
		movementRoutineFound->second->setMotionDuration(time, reset);

	auto scalingRoutineFound = m_routineScalingActive.find(&transformable);
	if (scalingRoutineFound != m_routineScalingActive.end())
		scalingRoutineFound->second->setMotionDuration(time, reset);

	auto rotationRoutineFound = m_routineRotationActive.find(&transformable);
	if (rotationRoutineFound != m_routineRotationActive.end())
		rotationRoutineFound->second->setMotionDuration(time, reset);
}

void MovementManager::setDelayAfter(const float delay, const bool reset)
{
	if (delay < 0.f) return;

	for (auto& movementRoutine : m_routineMovement)
		movementRoutine.second->setDelayAfter(delay, reset);

	for (auto& scalingRoutine : m_routineScaling)
		scalingRoutine.second->setDelayAfter(delay, reset);

	for (auto& rotationRoutine : m_routineRotation)
		rotationRoutine.second->setDelayAfter(delay, reset);
}

void MovementManager::setDelayAfter(std::string& name, const float delay, const bool reset)
{
	if (delay < 0.f) return;

	auto movementRoutineFound = m_routineMovementMapped.find(name);
	if (movementRoutineFound != m_routineMovementMapped.end())
		for (const auto& movementRoutine : movementRoutineFound->second)
			movementRoutine->second->setDelayAfter(delay, reset);

	auto scalingRoutineFound = m_routineScalingMapped.find(name);
	if (scalingRoutineFound != m_routineScalingMapped.end())
		for (const auto& scalingRoutine : scalingRoutineFound->second)
			scalingRoutine->second->setDelayAfter(delay, reset);

	auto rotationRoutineFound = m_routineRotationMapped.find(name);
	if (rotationRoutineFound != m_routineRotationMapped.end())
		for (const auto& rotationRoutine : rotationRoutineFound->second)
			rotationRoutine->second->setDelayAfter(delay, reset);
}

void MovementManager::setDelayAfter(sf::Transformable& transformable, const float delay, const bool reset)
{
	if (delay < 0.f) return;

	auto movementRoutineFound = m_routineMovementActive.find(&transformable);
	if (movementRoutineFound != m_routineMovementActive.end())
		movementRoutineFound->second->setDelayAfter(delay, reset);

	auto scalingRoutineFound = m_routineScalingActive.find(&transformable);
	if (scalingRoutineFound != m_routineScalingActive.end())
		scalingRoutineFound->second->setDelayAfter(delay, reset);

	auto rotationRoutineFound = m_routineRotationActive.find(&transformable);
	if (rotationRoutineFound != m_routineRotationActive.end())
		rotationRoutineFound->second->setDelayAfter(delay, reset);
}

void MovementManager::resetRoutines(sf::Transformable& transformable)
{
	auto movementRoutineFound = m_routineMovementActive.find(&transformable);
	if (movementRoutineFound != m_routineMovementActive.end())
		movementRoutineFound->second->reset(transformable);

	auto scalingRoutineFound = m_routineScalingActive.find(&transformable);
	if (scalingRoutineFound != m_routineScalingActive.end())
		scalingRoutineFound->second->reset(transformable);

	auto rotationRoutineFound = m_routineRotationActive.find(&transformable);
	if (rotationRoutineFound != m_routineRotationActive.end())
		rotationRoutineFound->second->reset(transformable);
}

// - - - - - - - - - - - - - - - - - - - - Movement  - - - - - - - - - - - - - - - - - - - - \\

MovementRoutine* MovementManager::createMovementRoutine(const std::string& _name)
{
	return this->m_movementRoutineContainer->createRoutine(_name);
}

MovementRoutine* MovementManager::getMovementRoutine(const std::string& _name)
{
	return this->m_movementRoutineContainer->getRoutinePtr(_name);
}

MovementRoutine* MovementManager::getMovementRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto m_movementRoutineContainerFound = m_routineMovement.find(&transformable);
	if (m_movementRoutineContainerFound != m_routineMovement.end()) {
		return m_movementRoutineContainerFound->second->exists(_name);
	}
	else {
		printDebug("getMovementRoutine: Routine for shape not found");
		return nullptr;
	}
}

MovementRoutine* MovementManager::linkMovementRoutine(sf::Transformable& transformable, const std::string& _name)
{
	// Check if routine with given name exists
	MovementRoutine* movementRoutineOriginal = m_movementRoutineContainer->getRoutinePtr(_name);

	if (movementRoutineOriginal == nullptr) {
		printDebug("linkMovementRoutine: Routine with name " + _name + " not found");
		return nullptr;
	}

	// Check if we linked a movement routine to this shape before
	auto m_movementRoutineContainerFound = m_routineMovement.find(&transformable);
	if (m_movementRoutineContainerFound != m_routineMovement.end()) {

		auto* movementRoutineFound = m_movementRoutineContainerFound->second->exists(_name);
		if (movementRoutineFound != nullptr) {
			printDebug("linkMovementRoutine: Routine with name " + _name + " already linked to shape");
			return movementRoutineFound;
		}
	}
	else {
		// If not, create a new movement routine container for this shape and link the movement routine to it
		MovementRoutineContainer* newMovementRoutineContainer = new MovementRoutineContainer(this->movementRoutineEngine);
		auto map_iterator = m_routineMovement.insert(std::make_pair(&transformable, newMovementRoutineContainer)).first;

		auto routineMappedFound = m_routineMovementMapped.find(_name);
		if (routineMappedFound != m_routineMovementMapped.end())
			routineMappedFound->second.emplace_back(map_iterator);
		else
			m_routineMovementMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, MovementRoutineContainer*>::iterator>{ map_iterator }));

		MovementRoutine* newMovementRoutine = new MovementRoutine(*movementRoutineOriginal);
		return newMovementRoutineContainer->createRoutine(_name, newMovementRoutine);
	}

	// If yes, create a new movement routine and link it to the existing movement routine container
	MovementRoutine* newMovementRoutine = new MovementRoutine(*movementRoutineOriginal);

	auto routineMappedFound = m_routineMovementMapped.find(_name);
	if (routineMappedFound != m_routineMovementMapped.end())
		routineMappedFound->second.emplace_back(m_movementRoutineContainerFound);
	else
		m_routineMovementMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, MovementRoutineContainer*>::iterator>{ m_movementRoutineContainerFound }));
	return m_movementRoutineContainerFound->second->createRoutine(_name, newMovementRoutine);
}

void MovementManager::unlinkMovementRoutine(sf::Transformable* transformable, const std::string& _name)
{
	// Stop the routine if it's active
	this->stopMovementRoutine(transformable, _name);

	// Delete the routine from m_routineMovement
	auto m_movementRoutineContainerFound = m_routineMovement.find(transformable);
	if (m_movementRoutineContainerFound != m_routineMovement.end()) {

		auto* movementRoutineFound = m_movementRoutineContainerFound->second->exists(_name);
		if (movementRoutineFound != nullptr) {
			m_movementRoutineContainerFound->second->deleteRoutine(_name);

			auto routineMappedFound = m_routineMovementMapped.find(_name);
			if (routineMappedFound != m_routineMovementMapped.end()) {
				routineMappedFound->second.erase(std::remove_if(routineMappedFound->second.begin(),
																routineMappedFound->second.end(),
																[&m_movementRoutineContainerFound](const auto& it) {return it == m_movementRoutineContainerFound; }),
												 routineMappedFound->second.end());

				if (routineMappedFound->second.empty())
					m_routineMovementMapped.erase(routineMappedFound);
			}
				
		}
			
		else
			printDebug("unlinkMovementRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("unlinkMovementRoutine: Routine for shape not found");
}

void MovementManager::startMovementRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto m_movementRoutineContainerFound = m_routineMovement.find(&transformable);
	if (m_movementRoutineContainerFound != m_routineMovement.end()) {
		auto* movementRoutineFound = m_movementRoutineContainerFound->second->exists(_name);

		if (movementRoutineFound != nullptr) {
			if (movementRoutineFound->start(transformable) && m_routineMovementActive.find(&transformable) == m_routineMovementActive.end()) {
				auto map_iterator = m_routineMovementActive.insert(std::make_pair(&transformable, movementRoutineFound)).first;

				auto routineActiveMappedFound = m_routineMovementActiveMapped.find(_name);
				if (routineActiveMappedFound != m_routineMovementActiveMapped.end())
					routineActiveMappedFound->second.emplace_back(map_iterator);
				else
					m_routineMovementActiveMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, MovementRoutine*>::iterator>{ map_iterator }));
			}
		}
		else
			printDebug("startMovementRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("startMovementRoutine: Routine for shape not found");
}

void MovementManager::pauseMovementRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto movementRoutineFound = m_routineMovementActive.find(&transformable);
	if (movementRoutineFound != m_routineMovementActive.end()) {
		if (movementRoutineFound->second->getName() == _name)
			movementRoutineFound->second->pause();
		else
			printDebug("pauseMovementRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("pauseMovementRoutine: Routine for shape not found");
}

void MovementManager::resumeMovementRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto movementRoutineFound = m_routineMovementActive.find(&transformable);
	if (movementRoutineFound != m_routineMovementActive.end()) {
		if (movementRoutineFound->second->getName() == _name)
			movementRoutineFound->second->resume();
		else
			printDebug("resumeMovementRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("resumeMovementRoutine: Routine for shape not found");
}

void MovementManager::resetMovementRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto movementRoutineFound = m_routineMovementActive.find(&transformable);
	if (movementRoutineFound != m_routineMovementActive.end()) {
		if (movementRoutineFound->second->getName() == _name)
			movementRoutineFound->second->reset(transformable);
		else
			printDebug("resetMovementRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("resetMovementRoutine: Routine for shape not found");
}

void MovementManager::stopMovementRoutine(sf::Transformable* transformable, const std::string& _name)
{
	auto movementRoutineFound = m_routineMovementActive.find(transformable);
	if (movementRoutineFound != m_routineMovementActive.end()) {
		if (movementRoutineFound->second->getName() == _name) {
			movementRoutineFound->second->stop(transformable);

			auto movementRoutineFoundMapped = m_routineMovementActiveMapped.find(_name);
			if (movementRoutineFoundMapped != m_routineMovementActiveMapped.end()) {
				movementRoutineFoundMapped->second.erase(std::remove_if(movementRoutineFoundMapped->second.begin(),
																		movementRoutineFoundMapped->second.end(),
																		[&movementRoutineFound](const auto& it) {return it == movementRoutineFound; }),
														 movementRoutineFoundMapped->second.end());

				if (movementRoutineFoundMapped->second.empty())
					m_routineMovementActiveMapped.erase(movementRoutineFoundMapped);
			}

			m_routineMovementActive.erase(movementRoutineFound);
		}
		else
			printDebug("stopMovementRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("stopMovementRoutine: Routine for shape not found");
}

void MovementManager::deleteMovementRoutine()
{
	m_routineMovementActiveMapped.clear();
	for (auto routine_active = m_routineMovementActive.begin(); routine_active != m_routineMovementActive.end();) {
		routine_active->second->stop(routine_active->first);
		routine_active = m_routineMovementActive.erase(routine_active);
	}

	m_routineMovementMapped.clear();
	for (auto routineContainer = m_routineMovement.begin(); routineContainer != m_routineMovement.end();) {
		routineContainer->second->clear();
		delete routineContainer->second;
		routineContainer = m_routineMovement.erase(routineContainer);
	}

	m_movementRoutineContainer->clear();
}

void MovementManager::deleteMovementRoutine(const std::string& _name)
{
	auto routineActiveFound = m_routineMovementActiveMapped.find(_name);
	if (routineActiveFound != m_routineMovementActiveMapped.end()) {

		for (const auto& active_routine : routineActiveFound->second) {
			active_routine->second->stop(active_routine->first);
			m_routineMovementActive.erase(active_routine);
		}
			
		routineActiveFound->second.clear();
		m_routineMovementActiveMapped.erase(routineActiveFound);
	}

	auto routineFound = m_routineMovementMapped.find(_name);
	if (routineFound != m_routineMovementMapped.end()) {
		for (auto routine : routineFound->second) {
			routine->second->deleteRoutine(_name);

			if (routine->second->getRoutineCount() == 0) {
				delete routine->second;
				m_routineMovement.erase(routine);
			}
		}

		routineFound->second.clear();
		m_routineMovementMapped.erase(routineFound);
	}

	m_movementRoutineContainer->deleteRoutine(_name);
}

const long long int MovementManager::getSizeMovement() const
{
	long long int size{};
	size += m_movementRoutineContainer->size() + sizeof(m_movementRoutineContainer);

	for (const auto& routineShape : m_routineMovement)
		size += routineShape.second->size() + sizeof(routineShape.second);

	for (const auto& routineActive : m_routineMovementActive)
		size += sizeof(routineActive.second);

	for (const auto& routineActiveMapped : m_routineMovementActiveMapped)
		size += routineActiveMapped.second.size() * sizeof(routineActiveMapped.second) + sizeof(routineActiveMapped.first);

	return size;
}

// - - - - - - - - - - - - - - - - - - - - Scaling  - - - - - - - - - - - - - - - - - - - - \\

ScalingRoutine* MovementManager::createScalingRoutine(const std::string& _name)
{
	return this->m_scalingRoutineContainer->createRoutine(_name);
}

ScalingRoutine* MovementManager::getScalingRoutine(const std::string& _name)
{
	return this->m_scalingRoutineContainer->getRoutinePtr(_name);
}

ScalingRoutine* MovementManager::getScalingRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto scalingRoutineContainerFound = m_routineScaling.find(&transformable);
	if (scalingRoutineContainerFound != m_routineScaling.end()) {
		return scalingRoutineContainerFound->second->exists(_name);
	}
	else
		printDebug("getScalingRoutine: Routine for shape not found");

	return nullptr;
}

ScalingRoutine* MovementManager::linkScalingRoutine(sf::Transformable& transformable, const std::string& _name)
{
	// Check if routine with given name exists
	ScalingRoutine* scalingRoutineOriginal = m_scalingRoutineContainer->getRoutinePtr(_name);

	if (scalingRoutineOriginal == nullptr) {
		printDebug("linkScalingRoutine: Routine with name " + _name + " not found");
		return nullptr;
	}

	// Check if we linked a scaling routine to this shape before
	auto m_scalingRoutineContainerFound = m_routineScaling.find(&transformable);
	if (m_scalingRoutineContainerFound != m_routineScaling.end()) {

		auto* scalingRoutineFound = m_scalingRoutineContainerFound->second->exists(_name);
		if (scalingRoutineFound != nullptr) {
			printDebug("linkScalingRoutine: Routine with name " + _name + " already linked to shape");
			return scalingRoutineFound;
		}
	}
	else {
		// If not, create a new scaling routine container for this shape and link the scaling routine to it
		ScalingRoutineContainer* newScalingRoutineContainer = new ScalingRoutineContainer(this->movementRoutineEngine);
		auto map_iterator = m_routineScaling.insert(std::make_pair(&transformable, newScalingRoutineContainer)).first;

		auto routineMappedFound = m_routineScalingMapped.find(_name);
		if (routineMappedFound != m_routineScalingMapped.end())
			routineMappedFound->second.emplace_back(map_iterator);
		else
			m_routineScalingMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, ScalingRoutineContainer*>::iterator>{ map_iterator }));

		ScalingRoutine* newScalingRoutine = new ScalingRoutine(*scalingRoutineOriginal);
		return newScalingRoutineContainer->createRoutine(_name, newScalingRoutine);
	}

	// If yes, create a new scaling routine and link it to the existing scaling routine container
	ScalingRoutine* newScalingRoutine = new ScalingRoutine(*scalingRoutineOriginal);

	auto routineMappedFound = m_routineScalingMapped.find(_name);
	if (routineMappedFound != m_routineScalingMapped.end())
		routineMappedFound->second.emplace_back(m_scalingRoutineContainerFound);
	else
		m_routineScalingMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, ScalingRoutineContainer*>::iterator>{ m_scalingRoutineContainerFound }));

	return m_scalingRoutineContainerFound->second->createRoutine(_name, newScalingRoutine);
}

void MovementManager::unlinkScalingRoutine(sf::Transformable* transformable, const std::string& _name)
{
	// Stop the routine if it's active
	this->stopScalingRoutine(transformable, _name);

	// Delete the routine from m_routineScaling
	auto m_scalingRoutineContainerFound = m_routineScaling.find(transformable);
	if (m_scalingRoutineContainerFound != m_routineScaling.end()) {

		auto* scalingRoutineFound = m_scalingRoutineContainerFound->second->exists(_name);
		if (scalingRoutineFound != nullptr) {
			m_scalingRoutineContainerFound->second->deleteRoutine(_name);

			auto routineMappedFound = m_routineScalingMapped.find(_name);
			if (routineMappedFound != m_routineScalingMapped.end()) {
				routineMappedFound->second.erase(std::remove_if(routineMappedFound->second.begin(),
																routineMappedFound->second.end(),
																[&m_scalingRoutineContainerFound](const auto& it) {return it == m_scalingRoutineContainerFound; }),
												 routineMappedFound->second.end());

				if (routineMappedFound->second.empty())
					m_routineScalingMapped.erase(routineMappedFound);
			}
		}
		else
			printDebug("unlinkScalingRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("unlinkScalingRoutine: Routine for shape not found");
}

void MovementManager::startScalingRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto m_scalingRoutineContainerFound = m_routineScaling.find(&transformable);
	if (m_scalingRoutineContainerFound != m_routineScaling.end()) {

		auto* scalingRoutineFound = m_scalingRoutineContainerFound->second->exists(_name);
		if (scalingRoutineFound != nullptr) {

			if (scalingRoutineFound->start(transformable) && m_routineScalingActive.find(&transformable) == m_routineScalingActive.end()) {
				auto map_iterator = m_routineScalingActive.insert(std::make_pair(&transformable, scalingRoutineFound)).first;

				auto routineActiveMappedFound = m_routineScalingActiveMapped.find(_name);
				if (routineActiveMappedFound != m_routineScalingActiveMapped.end())
					routineActiveMappedFound->second.emplace_back(map_iterator);
				else
					m_routineScalingActiveMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, ScalingRoutine*>::iterator>{ map_iterator }));
			}
		}
		else
			printDebug("startScalingRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("startScalingRoutine: Routine for shape not found");
}

void MovementManager::pauseScalingRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto scalingRoutineFound = m_routineScalingActive.find(&transformable);
	if (scalingRoutineFound != m_routineScalingActive.end()) {
		if (scalingRoutineFound->second->getName() == _name)
			scalingRoutineFound->second->pause();
		else
			printDebug("pauseScalingRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("pauseScalingRoutine: Routine for shape not found");
}

void MovementManager::resumeScalingRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto scalingRoutineFound = m_routineScalingActive.find(&transformable);
	if (scalingRoutineFound != m_routineScalingActive.end()) {
		if (scalingRoutineFound->second->getName() == _name)
			scalingRoutineFound->second->resume();
		else
			printDebug("resumeScalingRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("resumeScalingRoutine: Routine for shape not found");
}

void MovementManager::resetScalingRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto scalingRoutineFound = m_routineScalingActive.find(&transformable);
	if (scalingRoutineFound != m_routineScalingActive.end()) {
		if (scalingRoutineFound->second->getName() == _name)
			scalingRoutineFound->second->reset(transformable);
		else
			printDebug("resetScalingRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("resetScalingRoutine: Routine for shape not found");
}

void MovementManager::stopScalingRoutine(sf::Transformable* transformable, const std::string& _name)
{
	auto scalingRoutineFound = m_routineScalingActive.find(transformable);
	if (scalingRoutineFound != m_routineScalingActive.end()) {
		if (scalingRoutineFound->second->getName() == _name) {
			scalingRoutineFound->second->stop(transformable);
			
			auto scalingRoutineFoundMapped = m_routineScalingActiveMapped.find(_name);
			if (scalingRoutineFoundMapped != m_routineScalingActiveMapped.end()) {
				scalingRoutineFoundMapped->second.erase(std::remove_if(scalingRoutineFoundMapped->second.begin(),
																		scalingRoutineFoundMapped->second.end(),
																		[&scalingRoutineFound](const auto& it) {return it == scalingRoutineFound; }),
														scalingRoutineFoundMapped->second.end());

				if (scalingRoutineFoundMapped->second.empty())
					m_routineScalingActiveMapped.erase(scalingRoutineFoundMapped);
			}

			m_routineScalingActive.erase(scalingRoutineFound);
		}
		else
			printDebug("stopScalingRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("stopScalingRoutine: Routine for shape not found");
}

void MovementManager::deleteScalingRoutine()
{
	m_routineScalingActiveMapped.clear();
	for (auto routine_active = m_routineScalingActive.begin(); routine_active != m_routineScalingActive.end();) {
		routine_active->second->stop(routine_active->first);
		routine_active = m_routineScalingActive.erase(routine_active);
	}

	m_routineScalingMapped.clear();
	for (auto routineContainer = m_routineScaling.begin(); routineContainer != m_routineScaling.end();) {
		routineContainer->second->clear();
		delete routineContainer->second;
		routineContainer = m_routineScaling.erase(routineContainer);
	}

	m_scalingRoutineContainer->clear();
}

void MovementManager::deleteScalingRoutine(const std::string& _name)
{
	auto routineActiveFound = m_routineScalingActiveMapped.find(_name);
	if (routineActiveFound != m_routineScalingActiveMapped.end()) {
		for (const auto& active_routine : routineActiveFound->second) {
			active_routine->second->stop(active_routine->first);
			m_routineScalingActive.erase(active_routine);
		}

		routineActiveFound->second.clear();
		m_routineScalingActiveMapped.erase(routineActiveFound);
	}

	auto routineFound = m_routineScalingMapped.find(_name);
	if (routineFound != m_routineScalingMapped.end()) {
		for (auto routine : routineFound->second) {
			routine->second->deleteRoutine(_name);

			if (routine->second->getRoutineCount() == 0) {
				delete routine->second;
				m_routineScaling.erase(routine);
			}
		}

		routineFound->second.clear();
		m_routineScalingMapped.erase(routineFound);
	}

	m_scalingRoutineContainer->deleteRoutine(_name);
}

const long long int MovementManager::getSizeScaling() const
{
	long long int size{};
	size += m_scalingRoutineContainer->size() + sizeof(m_scalingRoutineContainer);

	for (const auto& routineShape : m_routineScaling)
		size += routineShape.second->size() + sizeof(routineShape.second);

	for (const auto& routineActive : m_routineScalingActive)
		size += sizeof(routineActive.second);

	return size;
}

// - - - - - - - - - - - - - - - - - - - - Rotation  - - - - - - - - - - - - - - - - - - - - \\

RotationRoutine* MovementManager::createRotationRoutine(const std::string& _name)
{
	return this->m_rotationRoutineContainer->createRoutine(_name);
}

RotationRoutine* MovementManager::getRotationRoutine(const std::string& _name)
{
	return this->m_rotationRoutineContainer->getRoutinePtr(_name);
}

RotationRoutine* MovementManager::getRotationRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto rotationRoutineContainerFound = m_routineRotation.find(&transformable);

	if (rotationRoutineContainerFound != m_routineRotation.end())
		return rotationRoutineContainerFound->second->exists(_name);
	else
		printDebug("getRotationRoutine: Routine for shape not found");

	return nullptr;

}

RotationRoutine* MovementManager::linkRotationRoutine(sf::Transformable& transformable, const std::string& _name)
{
	// Check if routine with given name exists
	RotationRoutine* rotationRoutineOriginal = m_rotationRoutineContainer->getRoutinePtr(_name);

	if (rotationRoutineOriginal == nullptr) {
		printDebug("linkRotationRoutine: Routine with name " + _name + " not found");
		return nullptr;
	}

	// Check if we linked a rotation routine to this shape before
	auto m_rotationRoutineContainerFound = m_routineRotation.find(&transformable);
	if (m_rotationRoutineContainerFound != m_routineRotation.end()) {

		auto* rotationRoutineFound = m_rotationRoutineContainerFound->second->exists(_name);
		if (rotationRoutineFound != nullptr) {
			printDebug("linkRotationRoutine: Routine with name " + _name + " already linked to shape");
			return rotationRoutineFound;
		}
	}
	else {
		// If not, create a new rotation routine container for this shape and link the rotation routine to it
		RotationRoutineContainer* newRotationRoutineContainer = new RotationRoutineContainer(this->movementRoutineEngine);
		auto map_iterator = m_routineRotation.insert(std::make_pair(&transformable, newRotationRoutineContainer)).first;


		auto routineMappedFound = m_routineRotationMapped.find(_name);
		if (routineMappedFound != m_routineRotationMapped.end())
			routineMappedFound->second.emplace_back(map_iterator);
		else
			m_routineRotationMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, RotationRoutineContainer*>::iterator>{ map_iterator }));

		RotationRoutine* newRotationRoutine = new RotationRoutine(*rotationRoutineOriginal);
		return newRotationRoutineContainer->createRoutine(_name, newRotationRoutine);
	}

	// If yes, create a new rotation routine and link it to the existing rotation routine container
	RotationRoutine* newRotationRoutine = new RotationRoutine(*rotationRoutineOriginal);

	auto routineMappedFound = m_routineRotationMapped.find(_name);
	if (routineMappedFound != m_routineRotationMapped.end())
		routineMappedFound->second.emplace_back(m_rotationRoutineContainerFound);
	else
		m_routineRotationMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, RotationRoutineContainer*>::iterator>{ m_rotationRoutineContainerFound }));

	return m_rotationRoutineContainerFound->second->createRoutine(_name, newRotationRoutine);
}

void MovementManager::unlinkRotationRoutine(sf::Transformable* transformable, const std::string& _name)
{
	// Stop the routine if it's active
	this->stopRotationRoutine(transformable, _name);

	// Delete the routine from m_routineRotation
	auto m_rotationRoutineContainerFound = m_routineRotation.find(transformable);
	if (m_rotationRoutineContainerFound != m_routineRotation.end()) {

		auto* rotationRoutineFound = m_rotationRoutineContainerFound->second->exists(_name);
		if (rotationRoutineFound != nullptr) {
			m_rotationRoutineContainerFound->second->deleteRoutine(_name);

			auto routineMappedFound = m_routineRotationMapped.find(_name);
			if (routineMappedFound != m_routineRotationMapped.end()) {
				routineMappedFound->second.erase(std::remove_if(routineMappedFound->second.begin(),
																routineMappedFound->second.end(),
																[&m_rotationRoutineContainerFound](const auto& it) {return it == m_rotationRoutineContainerFound; }),
												 routineMappedFound->second.end());

				if (routineMappedFound->second.empty())
					m_routineRotationMapped.erase(routineMappedFound);
			}
		}
		else
			printDebug("unlinkRotationRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("unlinkRotationRoutine: Routine for shape not found");
}

void MovementManager::startRotationRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto m_rotationRoutineContainerFound = m_routineRotation.find(&transformable);
	if (m_rotationRoutineContainerFound != m_routineRotation.end()) {

		auto* rotationRoutineFound = m_rotationRoutineContainerFound->second->exists(_name);
		if (rotationRoutineFound != nullptr) {

			if (rotationRoutineFound->start(transformable) && m_routineRotationActive.find(&transformable) == m_routineRotationActive.end()) {
				auto map_iterator = m_routineRotationActive.insert(std::make_pair(&transformable, rotationRoutineFound)).first;

				auto routineActiveMappedFound = m_routineRotationActiveMapped.find(_name);
				if (routineActiveMappedFound != m_routineRotationActiveMapped.end())
					routineActiveMappedFound->second.emplace_back(map_iterator);
				else
					m_routineRotationActiveMapped.insert(std::make_pair(_name, std::vector<std::map<sf::Transformable*, RotationRoutine*>::iterator>{ map_iterator }));
			}
		}
		else
			printDebug("startRotationRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("startRotationRoutine: Routine for shape not found");
}

void MovementManager::pauseRotationRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto rotationRoutineFound = m_routineRotationActive.find(&transformable);
	if (rotationRoutineFound != m_routineRotationActive.end()) {
		if (rotationRoutineFound->second->getName() == _name)
			rotationRoutineFound->second->pause();
		else
			printDebug("pauseRotationRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("pauseRotationRoutine: Routine for shape not found");
}

void MovementManager::resumeRotationRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto rotationRoutineFound = m_routineRotationActive.find(&transformable);
	if (rotationRoutineFound != m_routineRotationActive.end()) {
		if (rotationRoutineFound->second->getName() == _name)
			rotationRoutineFound->second->resume();
		else
			printDebug("resumeRotationRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("resumeRotationRoutine: Routine for shape not found");
}

void MovementManager::resetRotationRoutine(sf::Transformable& transformable, const std::string& _name)
{
	auto rotationRoutineFound = m_routineRotationActive.find(&transformable);
	if (rotationRoutineFound != m_routineRotationActive.end()) {
		if (rotationRoutineFound->second->getName() == _name)
			rotationRoutineFound->second->reset(transformable);
		else
			printDebug("resetRotationRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("resetRotationRoutine: Routine for shape not found");
}

void MovementManager::stopRotationRoutine(sf::Transformable* transformable, const std::string& _name)
{
	auto rotationRoutineFound = m_routineRotationActive.find(transformable);
	if (rotationRoutineFound != m_routineRotationActive.end()) {
		if (rotationRoutineFound->second->getName() == _name) {
			rotationRoutineFound->second->stop(transformable);
			
			auto rotationRoutineFoundMapped = m_routineRotationActiveMapped.find(_name);
			if (rotationRoutineFoundMapped != m_routineRotationActiveMapped.end()) {
				rotationRoutineFoundMapped->second.erase(std::remove_if(rotationRoutineFoundMapped->second.begin(),
																		rotationRoutineFoundMapped->second.end(),
																		[&rotationRoutineFound](const auto& it) {return it == rotationRoutineFound; }),
														 rotationRoutineFoundMapped->second.end());

				if (rotationRoutineFoundMapped->second.empty())
					m_routineRotationActiveMapped.erase(rotationRoutineFoundMapped);
			}

			m_routineRotationActive.erase(rotationRoutineFound);
		}
		else
			printDebug("stopRotationRoutine: Routine with name " + _name + " not found");
	}
	else
		printDebug("stopRotationRoutine: Routine for shape not found");
}

void MovementManager::deleteRotationRoutine()
{
	m_routineRotationActiveMapped.clear();
	for (auto routine_active = m_routineRotationActive.begin(); routine_active != m_routineRotationActive.end();) {
		routine_active->second->stop(routine_active->first);
		routine_active = m_routineRotationActive.erase(routine_active);
	}

	m_routineRotationMapped.clear();
	for (auto routineContainer = m_routineRotation.begin(); routineContainer != m_routineRotation.end();) {
		routineContainer->second->clear();
		delete routineContainer->second;
		routineContainer = m_routineRotation.erase(routineContainer);
	}

	m_rotationRoutineContainer->clear();
}

void MovementManager::deleteRotationRoutine(const std::string& _name)
{
	auto routineActiveFound = m_routineRotationActiveMapped.find(_name);
	if (routineActiveFound != m_routineRotationActiveMapped.end()) {
		for (const auto& active_routine : routineActiveFound->second) {
			active_routine->second->stop(active_routine->first);
			m_routineRotationActive.erase(active_routine);
		}

		routineActiveFound->second.clear();
		m_routineRotationActiveMapped.erase(routineActiveFound);
	}

	auto routineFound = m_routineRotationMapped.find(_name);
	if (routineFound != m_routineRotationMapped.end()) {
		for (auto routine : routineFound->second) {
			routine->second->deleteRoutine(_name);

			if (routine->second->getRoutineCount() == 0) {
				delete routine->second;
				m_routineRotation.erase(routine);
			}
		}

		routineFound->second.clear();
		m_routineRotationMapped.erase(routineFound);
	}

	m_rotationRoutineContainer->deleteRoutine(_name);
}

const long long int MovementManager::getSizeRotation() const
{
	long long int size{};
	size += m_rotationRoutineContainer->size() + sizeof(m_rotationRoutineContainer);

	for (const auto& routineShape : m_routineRotation)
		size += routineShape.second->size() + sizeof(routineShape.second);

	for (const auto& routineActive : m_routineRotationActive)
		size += sizeof(routineActive.second);

	return size;
}

void MovementManager::setDebug(const bool debug)
{
	this->debug = debug;
}
