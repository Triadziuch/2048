#pragma once
#include "MovementManager.h"
#include "MovementContainer.h"
#include "TransformationRoutine.h"

// Singleton initialization
MovementContainer* MovementContainer::sInstance = nullptr;

// Default constructor
MovementContainer* MovementContainer::getInstance()
{
	if (!sInstance)
		sInstance = new MovementContainer();
	return sInstance;
}

// Update functions
void MovementContainer::update(float dt)
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& movementRoutine = std::get<0>(*transforms->second);
		if (movementRoutine != nullptr)
			if (!movementRoutine->update(*transforms->first, dt)) {
				movementRoutine = nullptr;
				delete movementRoutine;
			}

		auto& scalingRoutine = std::get<1>(*transforms->second);
		if (scalingRoutine != nullptr)
			if (!scalingRoutine->update(*transforms->first, dt)) {
				scalingRoutine = nullptr;
				delete scalingRoutine;
			}

		auto& rotationRoutine = std::get<2>(*transforms->second);
		if (rotationRoutine != nullptr)
			if (!rotationRoutine->update(*transforms->first, dt)) {
				rotationRoutine = nullptr;
				delete rotationRoutine;
			}


		if (!movementRoutine && !scalingRoutine && !rotationRoutine) {
			delete transforms->second;
			transforms = m_Transforms.erase(transforms);
		}
		else
			++transforms;
	}
}

// Public functions

// Movement functions
const movementInfo* MovementContainer::addMovement(sf::Transformable* transformable, movementInfo* _movementInfo)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end() && std::get<0>(*transformsFound->second) != nullptr) {
		printf("MovementRoutineEngine::addMovement: MovementRoutine already exists for this shape\n");
		return nullptr;
	}
	else if (transformsFound == transformsMap.end()) {
		auto routinesTuplePtr = new std::tuple<movementInfo*, scalingInfo*, rotationInfo*>(_movementInfo, nullptr, nullptr);
		transformsMap.insert(std::make_pair(transformable, routinesTuplePtr));
	}
	else {
		auto& routinesTuplePtr = transformsFound->second;
		std::get<0>(*routinesTuplePtr) = _movementInfo;
	}

	return _movementInfo;
}

void MovementContainer::undoMovement()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& movement = std::get<0>(*transforms->second);
		if (movement != nullptr) {
			movement->undoMovement(*transforms->first);
			movement = nullptr;
			delete movement;
		}
	}
}

void MovementContainer::undoMovement(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end()) {
		auto& movement = std::get<0>(*transformsFound->second);
		if (movement != nullptr) {
			movement->undoMovement(*transformable);
			movement = nullptr;
			delete movement;
		}
	}
}

void MovementContainer::resetMovement()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& movement = std::get<0>(*transforms->second);
		if (movement != nullptr) {
			transforms->first->setPosition(movement->getStartingPos());
			movement->reset();
		}
	}
}

void MovementContainer::resetMovement(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

}

void MovementContainer::stopMovement()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& movement = std::get<0>(*transforms->second);
		if (movement != nullptr) {
			movement = nullptr;
			delete movement;
		}

		if (std::get<1>(*transforms->second) == nullptr && std::get<2>(*transforms->second) == nullptr) {
			delete transforms->second;
			transforms = this->m_Transforms.erase(transforms);
		}
		else
			++transforms;
	}
}

void MovementContainer::stopMovement(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end()) {
		auto& movement = std::get<0>(*transformsFound->second);
		if (movement != nullptr) {
			movement = nullptr;
			delete movement;
		}

		if (std::get<1>(*transformsFound->second) == nullptr && std::get<2>(*transformsFound->second) == nullptr) {
			delete transformsFound->second;
			transformsMap.erase(transformsFound);
		}
	}
}

// Scaling functions
const scalingInfo* MovementContainer::addScaling(sf::Transformable* transformable, scalingInfo* _scalingInfo)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end() && std::get<1>(*transformsFound->second) != nullptr) {
		printf("MovementRoutineEngine::addScaling: ScalingRoutine already exists for this shape\n");
		return nullptr;
	}
	else if (transformsFound == transformsMap.end()) {
		auto routinesTuplePtr = new std::tuple<movementInfo*, scalingInfo*, rotationInfo*>(nullptr, _scalingInfo, nullptr);
		transformsMap.insert(std::make_pair(transformable, routinesTuplePtr));
	}
	else {
		auto& routinesTuplePtr = transformsFound->second;
		std::get<1>(*routinesTuplePtr) = _scalingInfo;
	}
}

void MovementContainer::undoScaling()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& scaling = std::get<1>(*transforms->second);
		if (scaling != nullptr) {
			scaling->undoScaling(*transforms->first);
			scaling = nullptr;
			delete scaling;
		}
	}
}

void MovementContainer::undoScaling(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end()) {
		auto& scaling = std::get<1>(*transformsFound->second);
		if (scaling != nullptr) {
			scaling->undoScaling(*transformable);
			scaling = nullptr;
			delete scaling;
		}
	}
}

void MovementContainer::resetScaling()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& scaling = std::get<1>(*transforms->second);
		if (scaling != nullptr) {
			transforms->first->setScale(scaling->getStartingScale());
			scaling->reset();
		}
	}
}

void MovementContainer::resetScaling(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end()) {
		auto& scaling = std::get<1>(*transformsFound->second);
		if (scaling != nullptr) {
			transformable->setScale(scaling->getStartingScale());
			scaling->reset();
		}
	}
}

void MovementContainer::stopScaling()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& scaling = std::get<1>(*transforms->second);
		if (scaling != nullptr) {
			scaling = nullptr;
			delete scaling;
		}

		if (std::get<0>(*transforms->second) == nullptr && std::get<2>(*transforms->second) == nullptr) {
			delete transforms->second;
			transforms = this->m_Transforms.erase(transforms);
		}
		else
			++transforms;
	}
}

void MovementContainer::stopScaling(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end()) {
		auto& scaling = std::get<1>(*transformsFound->second);
		if (scaling != nullptr) {
			scaling = nullptr;
			delete scaling;
		}

		if (std::get<0>(*transformsFound->second) == nullptr && std::get<2>(*transformsFound->second) == nullptr) {
			delete transformsFound->second;
			transformsMap.erase(transformsFound);
		}
	}
}

// Rotation functions
const rotationInfo* MovementContainer::addRotation(sf::Transformable* transformable, rotationInfo* _rotationInfo)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end() && std::get<2>(*transformsFound->second) != nullptr) {
		printf("MovementRoutineEngine::addRotation: RotationRoutine already exists for this shape\n");
		return nullptr;
	}
	else if (transformsFound == transformsMap.end()) {
		auto routinesTuplePtr = new std::tuple<movementInfo*, scalingInfo*, rotationInfo*>(nullptr, nullptr, _rotationInfo);
		transformsMap.insert(std::make_pair(transformable, routinesTuplePtr));
	}
	else {
		auto& routinesTuplePtr = transformsFound->second;
		std::get<2>(*routinesTuplePtr) = _rotationInfo;
	}
}

void MovementContainer::undoRotation()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& rotation = std::get<2>(*transforms->second);
		if (rotation != nullptr) {
			rotation->undoRotation(*transforms->first);
			rotation = nullptr;
			delete rotation;
		}
	}
}

void MovementContainer::undoRotation(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end()) {
		auto& rotation = std::get<2>(*transformsFound->second);
		if (rotation != nullptr) {
			rotation->undoRotation(*transformable);
			rotation = nullptr;
			delete rotation;
		}
	}
}

void MovementContainer::resetRotation()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& rotation = std::get<2>(*transforms->second);
		if (rotation != nullptr) {
			transforms->first->setRotation(rotation->getStartingRotation());
			rotation->reset();
		}
	}
}

void MovementContainer::resetRotation(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end()) {
		auto& rotation = std::get<2>(*transformsFound->second);
		if (rotation != nullptr) {
			transformable->setRotation(rotation->getStartingRotation());
			rotation->reset();
		}
	}
}

void MovementContainer::stopRotation()
{
	for (auto transforms = this->m_Transforms.begin(); transforms != this->m_Transforms.end();) {
		auto& rotation = std::get<2>(*transforms->second);
		if (rotation != nullptr) {
			rotation = nullptr;
			delete rotation;
		}

		if (std::get<0>(*transforms->second) == nullptr && std::get<1>(*transforms->second) == nullptr) {
			delete transforms->second;
			transforms = this->m_Transforms.erase(transforms);
		}
		else
			++transforms;
	}
}

void MovementContainer::stopRotation(sf::Transformable* transformable)
{
	auto& transformsMap = sInstance->m_Transforms;
	auto transformsFound = transformsMap.find(transformable);

	if (transformsFound != transformsMap.end()) {
		auto& rotation = std::get<2>(*transformsFound->second);
		if (rotation != nullptr) {
			rotation = nullptr;
			delete rotation;
		}

		if (std::get<0>(*transformsFound->second) == nullptr && std::get<1>(*transformsFound->second) == nullptr) {
			delete transformsFound->second;
			transformsMap.erase(transformsFound);
		}
	}
}

const bool MovementContainer::isMoving(sf::Transformable* transformable)
{
	auto transformsFound = this->m_Transforms.find(transformable);
	if (transformsFound != this->m_Transforms.end() && std::get<0>(*transformsFound->second))
		return true;
	return false;
}

const bool MovementContainer::isScaling(sf::Transformable* transformable)
{
	auto transformsFound = this->m_Transforms.find(transformable);
	if (transformsFound != this->m_Transforms.end() && std::get<1>(*transformsFound->second))
		return true;
	return false;
}

const bool MovementContainer::isRotating(sf::Transformable* transformable)
{
	auto transformsFound = this->m_Transforms.find(transformable);
	if (transformsFound != this->m_Transforms.end() && std::get<2>(*transformsFound->second))
		return true;
	return false;
}
// ---------------------------------------------------------------------------------------------------------------------------

// Singleton initialization
MovementRoutineEngine* MovementRoutineEngine::sInstance = nullptr;

MovementRoutineEngine* MovementRoutineEngine::getInstance()
{
	if (!sInstance)
		sInstance = new MovementRoutineEngine();
	return sInstance;
}

void MovementRoutineEngine::setMovementManager(MovementManager* _movementManager)
{
	this->movementManager = _movementManager;
}

void MovementRoutineEngine::update(float dt)
{
	int it = 0;
	for (auto routines = this->m_Routines.begin(); routines != this->m_Routines.end();) {
		++it;
		auto& movementRoutine = std::get<0>(*routines->second);
		if (movementRoutine != nullptr) 
			if (!movementRoutine->update(*routines->first, dt))
				movementRoutine = nullptr;

		auto& scalingRoutine = std::get<1>(*routines->second);
		if (scalingRoutine != nullptr)
			if (!scalingRoutine->update(*routines->first, dt))
				scalingRoutine = nullptr;

		auto& rotationRoutine = std::get<2>(*routines->second);
		if (rotationRoutine != nullptr) 
			if (!rotationRoutine->update(*routines->first, dt))
				rotationRoutine = nullptr;
			

		if (!movementRoutine && !scalingRoutine && !rotationRoutine) {
			delete routines->second;
			routines = m_Routines.erase(routines);
		}
		else
			++routines;
	}
}

const MovementRoutine* MovementRoutineEngine::addMovement(sf::Transformable* transformable, MovementRoutine* _movementRoutine)
{
	auto& routinesMap = sInstance->m_Routines;
	auto routinesFound = routinesMap.find(transformable);

	if (routinesFound != routinesMap.end() && std::get<0>(*routinesFound->second) != nullptr) {
		printf("MovementRoutineEngine::addMovement: MovementRoutine already exists for this shape\n");
		return nullptr;
	}
	else if (routinesFound == routinesMap.end()) {
		auto routinesTuplePtr = new std::tuple<MovementRoutine*, ScalingRoutine*, RotationRoutine*>(_movementRoutine, nullptr, nullptr);
		routinesMap.insert(std::make_pair(transformable, routinesTuplePtr));
	}
	else {
		auto& routinesTuplePtr = routinesFound->second;
		std::get<0>(*routinesTuplePtr) = _movementRoutine;
	}

	return _movementRoutine;
}

void MovementRoutineEngine::undoMovement()
{
}

void MovementRoutineEngine::undoMovement(sf::Transformable* transformable)
{
}

void MovementRoutineEngine::resetMovement()
{
	for (auto routines = this->m_Routines.begin(); routines != this->m_Routines.end();) {
		auto& routinesTuple = routines->second;
		auto& movement = std::get<0>(*routinesTuple);

		if (movement) {
			movement->reset();
			routines->first->setPosition(movement->getCurrentMovement()->getStartingPos());
		}
	}
}

void MovementRoutineEngine::stopMovement()
{
	for (auto routines = this->m_Routines.begin(); routines != this->m_Routines.end();) {
		auto& routinesTuple = routines->second;
		std::get<0>(*routinesTuple) = nullptr;

		if (std::get<1>(*routinesTuple) == nullptr && std::get<2>(*routinesTuple) == nullptr) {
			delete routines->second;
			routines = this->m_Routines.erase(routines);
		}
		else
			++routines;
	}
}

void MovementRoutineEngine::stopMovement(sf::Transformable* transformable)
{
	auto& routinesMap = sInstance->m_Routines;
	auto routinesFound = routinesMap.find(transformable);

	if (routinesFound != routinesMap.end()) {
		auto& routinesTuple = routinesFound->second;
		std::get<0>(*routinesTuple) = nullptr;

		if (std::get<1>(*routinesTuple) == nullptr && std::get<2>(*routinesTuple) == nullptr) {
			delete routinesFound->second;
			routinesMap.erase(routinesFound);
		}
	}
}

const ScalingRoutine* MovementRoutineEngine::addScaling(sf::Transformable* transformable, ScalingRoutine* _scalingRoutine)
{
	auto& routinesMap = sInstance->m_Routines;
	auto routinesFound = routinesMap.find(transformable);

	if (routinesFound != routinesMap.end() && std::get<1>(*routinesFound->second) != nullptr) {
		printf("MovementRoutineEngine::addScaling: ScalingRoutine already exists for this shape\n");
		return nullptr;
	}
	else if (routinesFound == routinesMap.end()) {
		auto routinesTuplePtr = new std::tuple<MovementRoutine*, ScalingRoutine*, RotationRoutine*>(nullptr, _scalingRoutine, nullptr);
		routinesMap.insert(std::make_pair(transformable, routinesTuplePtr));
	}
	else {
		auto& routinesTuplePtr = routinesFound->second;
		std::get<1>(*routinesTuplePtr) = _scalingRoutine;
	}

	return _scalingRoutine;
}

void MovementRoutineEngine::undoScaling()
{
}

void MovementRoutineEngine::undoScaling(sf::Transformable* transformable)
{
}

void MovementRoutineEngine::resetScaling()
{
	for (auto routines = this->m_Routines.begin(); routines != this->m_Routines.end();) {
		auto& routinesTuple = routines->second;
		auto& scaling = std::get<1>(*routinesTuple);

		if (scaling) {
			scaling->reset();
			routines->first->setScale(scaling->getCurrentScaling()->getStartingScale());
		}
	}
}

void MovementRoutineEngine::stopScaling()
{
	for (auto routines = this->m_Routines.begin(); routines != this->m_Routines.end();) {
		auto& routinesTuple = routines->second;
		std::get<1>(*routinesTuple) = nullptr;

		if (std::get<0>(*routinesTuple) == nullptr && std::get<2>(*routinesTuple) == nullptr) {
			delete routines->second;
			routines = this->m_Routines.erase(routines);
		}
		else
			++routines;
	}
}

void MovementRoutineEngine::stopScaling(sf::Transformable* transformable)
{
	auto& routinesMap = sInstance->m_Routines;
	auto routinesFound = routinesMap.find(transformable);

	if (routinesFound != routinesMap.end()) {
		auto& routinesTuple = routinesFound->second;
		std::get<1>(*routinesTuple) = nullptr;

		if (std::get<0>(*routinesTuple) == nullptr && std::get<2>(*routinesTuple) == nullptr) {
			delete routinesFound->second;
			routinesMap.erase(routinesFound);
		}
	}
}

const RotationRoutine* MovementRoutineEngine::addRotation(sf::Transformable* transformable, RotationRoutine* _rotationRoutine)
{
	auto& routinesMap = sInstance->m_Routines;
	auto routinesFound = routinesMap.find(transformable);

	if (routinesFound != routinesMap.end() && std::get<2>(*routinesFound->second) != nullptr) {
		printf("MovementRoutineEngine::addRotation: RotationRoutine already exists for this shape\n");
		return nullptr;
	}
	else if (routinesFound == routinesMap.end()) {
		auto routinesTuplePtr = new std::tuple<MovementRoutine*, ScalingRoutine*, RotationRoutine*>(nullptr, nullptr, _rotationRoutine);
		routinesMap.insert(std::make_pair(transformable, routinesTuplePtr));
	}
	else {
		auto& routinesTuplePtr = routinesFound->second;
		std::get<2>(*routinesTuplePtr) = _rotationRoutine;
	}

	return _rotationRoutine;
}

void MovementRoutineEngine::undoRotation()
{
}

void MovementRoutineEngine::undoRotation(sf::Transformable* transformable)
{
}

void MovementRoutineEngine::resetRotation()
{
	for (auto routines = this->m_Routines.begin(); routines != this->m_Routines.end();) {
		auto& routinesTuple = routines->second;
		auto& rotation = std::get<2>(*routinesTuple);

		if (rotation) {
			rotation->reset();
			routines->first->setRotation(rotation->getCurrentRotation()->getStartingRotation());
		}
	}
}

void MovementRoutineEngine::stopRotation()
{
	for (auto routines = this->m_Routines.begin(); routines != this->m_Routines.end();) {
		auto& routinesTuple = routines->second;
		std::get<2>(*routinesTuple) = nullptr;

		if (std::get<0>(*routinesTuple) == nullptr && std::get<1>(*routinesTuple) == nullptr) {
			delete routines->second;
			routines = this->m_Routines.erase(routines);
		}
	}
}

void MovementRoutineEngine::stopRotation(sf::Transformable* transformable)
{
	auto& routinesMap = sInstance->m_Routines;
	auto routinesFound = routinesMap.find(transformable);

	if (routinesFound != routinesMap.end()) {
		auto& routinesTuple = routinesFound->second;
		std::get<2>(*routinesTuple) = nullptr;

		if (std::get<0>(*routinesTuple) == nullptr && std::get<1>(*routinesTuple) == nullptr) {
			delete routinesFound->second;
			routinesMap.erase(routinesFound);
		}
	}
}

const bool MovementRoutineEngine::isMoving(sf::Transformable* transformable)
{
	return false;
}

const bool MovementRoutineEngine::isScaling(sf::Transformable* transformable)
{
	return false;
}

const bool MovementRoutineEngine::isRotating(sf::Transformable* transformable)
{
	return false;
}