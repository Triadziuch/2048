#pragma once
#include "TransformationRoutine.h"
#include "MovementContainer.h"

// - - - - - - - - - - - - - - - - - - - - TransformationRoutine - - - - - - - - - - - - - - - - - - - - \\

// Constructors / Destructors
TransformationRoutine::TransformationRoutine(const std::string& name, MovementRoutineEngine* movementRoutineEnginePtr) :
	m_movementRoutineEngine{ movementRoutineEnginePtr },
	m_routineName{ name },
	m_current{},
	m_count{},
	m_isActive{},
	m_isLooping{},
	m_isPaused{},
	m_adjustStartToCurrentTransform{},
	m_adjustAllToCurrentTransform{},
	m_pauseAtStart{},
	m_pauseAfterChangingMovements{}
{}

TransformationRoutine::TransformationRoutine(const TransformationRoutine& obj) :
	m_movementRoutineEngine{ obj.m_movementRoutineEngine },
	m_routineName{ obj.m_routineName },
	m_current{ obj.m_current },
	m_count{ obj.m_count },
	m_isActive{ obj.m_isActive },
	m_isLooping{ obj.m_isLooping },
	m_isPaused{ obj.m_isPaused },
	m_adjustStartToCurrentTransform{ obj.m_adjustStartToCurrentTransform },
	m_adjustAllToCurrentTransform{ obj.m_adjustAllToCurrentTransform },
	m_pauseAtStart{ obj.m_pauseAtStart },
	m_pauseAfterChangingMovements{ obj.m_pauseAfterChangingMovements }
{}

TransformationRoutine::~TransformationRoutine() {
	m_movementRoutineEngine = nullptr;
	m_transformations.clear();
}

void TransformationRoutine::setLooping(bool looping)
{
	m_isLooping = looping;
}

void TransformationRoutine::setPauseAtStart(bool pauseAtStart)
{
	m_pauseAtStart = pauseAtStart;
}

void TransformationRoutine::setPauseAfterChangingMovements(bool pauseAfterChangingMovements)
{
	m_pauseAfterChangingMovements = pauseAfterChangingMovements;
}

void TransformationRoutine::adjustStartToCurrentTransform(bool adjust)
{
	m_adjustStartToCurrentTransform = adjust;
}

void TransformationRoutine::adjustAllToCurrentTransform(bool adjust)
{
	m_adjustAllToCurrentTransform = adjust;
}

void TransformationRoutine::setDelayBefore(const float delay, const bool reset)
{
	for (auto transformation : m_transformations)
		transformation->setDelayBefore(delay, reset);
}

void TransformationRoutine::setMotionDuration(const float animationTime, const bool reset)
{
	for (auto transformation : m_transformations)
		transformation->setMotionDuration(animationTime, reset);
}

void TransformationRoutine::setDelayAfter(const float delay, const bool reset)
{
	for (auto transformation : m_transformations)
		transformation->setDelayAfter(delay, reset);
}

void TransformationRoutine::setFunction(easeFunctions::Tmovement_function usedFunctionType)
{
	for (auto& transformation : m_transformations)
		transformation->setFunction(usedFunctionType);
}

void TransformationRoutine::setFunction(easeFunctions::Tmovement_function usedFunctionType, const size_t transformation_id)
{
	if (transformation_id < m_count)
		m_transformations[transformation_id]->setFunction(usedFunctionType);
}

void TransformationRoutine::setFunction(double(*usedFunctionPtr)(double))
{
	for (auto& transformation : m_transformations)
		transformation->setFunction(usedFunctionPtr);
}

void TransformationRoutine::setFunction(double(*usedFunctionPtr)(double), const size_t transformation_id)
{
	if (transformation_id < m_count)
		m_transformations[transformation_id]->setFunction(usedFunctionPtr);
}

void TransformationRoutine::pause()
{
	m_isPaused = true;
}

void TransformationRoutine::reset()
{
	for (auto& transformation : m_transformations)
		transformation->reset();

	m_current = 0;
	m_isActive = false;
	m_isPaused = m_pauseAfterChangingMovements;
}

void TransformationRoutine::resume()
{
	m_isPaused = false;
}

std::string& TransformationRoutine::getName()
{
	return m_routineName;
}

const std::string& TransformationRoutine::getName() const
{
	return m_routineName;
}

// - - - - - - - - - - - - - - - - - - - - MovementRoutine - - - - - - - - - - - - - - - - - - - - \\

// Private functions
void MovementRoutine::adjustStartToCurrent(const sf::Vector2f& currentPosition)
{
	if (m_routineMovements.size() == 0) return;

	const sf::Vector2f offset = currentPosition - m_routineMovements.front()->getStartingPos();
	m_routineMovements.front()->getStartingPos() += offset;
}

void MovementRoutine::adjustAllToCurrent(const sf::Vector2f& currentPosition)
{
	if (m_routineMovements.size() == 0) return;

	const sf::Vector2f offset = currentPosition - m_routineMovements.front()->getStartingPos();
	for (auto& movement : m_routineMovements) {
		movement->getStartingPos() += offset;
		movement->getEndingPos() += offset;
	}
}

// Constructors / Destructors
MovementRoutine::MovementRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr) :
	TransformationRoutine{ name, movementRoutineEnginePtr }
{}

MovementRoutine::MovementRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, movementInfo* movement) :
	TransformationRoutine{ name, movementRoutineEnginePtr }
{
	m_routineMovements.emplace_back(movement);
	m_transformations.emplace_back(static_cast<transformationInfo*>(movement));
	++m_count;
}

MovementRoutine::MovementRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, const std::vector<movementInfo*> movements) :
	TransformationRoutine{ name, movementRoutineEnginePtr },
	m_routineMovements{ movements }
{
	for (const auto& movement : m_routineMovements)
		m_transformations.emplace_back(static_cast<transformationInfo*>(movement));
	m_count = m_routineMovements.size();
}

MovementRoutine::MovementRoutine(const MovementRoutine& obj) :
	TransformationRoutine{ obj }
{
	for (const auto& movement : obj.m_routineMovements) {
		m_routineMovements.emplace_back(new movementInfo(*movement));
		m_transformations.emplace_back(static_cast<transformationInfo*>(m_routineMovements.back()));
	}
}

MovementRoutine::~MovementRoutine() {
	for (auto& movement : m_routineMovements)
		delete movement;
	m_routineMovements.clear();
	m_transformations.clear();
}

// Update functions
const bool MovementRoutine::update(sf::Transformable& transformable, const float dt)
{
	if (m_isPaused) return true;

	if (!m_routineMovements[m_current]->update(transformable, dt) && !goToNextMovement(transformable))
		return false;

	return true;
}

// Public functions
void MovementRoutine::addMovement(movementInfo* movement)
{
	m_routineMovements.emplace_back(movement);
	m_transformations.emplace_back(static_cast<transformationInfo*>(movement));
	++m_count;
}

void MovementRoutine::removeMovement(movementInfo* movement)
{
	auto it = std::find(m_routineMovements.begin(), m_routineMovements.end(), movement);

	if (it != m_routineMovements.end()) {
		m_routineMovements.erase(it);
		--m_count;
	}

	auto it2 = std::find(m_transformations.begin(), m_transformations.end(), movement);
	if (it2 != m_transformations.end())
		m_transformations.erase(it2);
}

void MovementRoutine::clear()
{
	m_routineMovements.clear();
	m_transformations.clear();
	m_current = 0;
	m_count = 0;
	m_isActive = false;
	m_isPaused = false;
	m_isLooping = false;
}

const bool MovementRoutine::start(sf::Transformable& transformable)
{
	if (m_routineMovements.size() != 0) {
		if (m_adjustAllToCurrentTransform) { adjustAllToCurrent(transformable.getPosition()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getPosition()); }

		TransformationRoutine::reset();

		m_current = 0;
		m_isActive = true;
		m_movementRoutineEngine->addMovement(&transformable, this);
		return true;
	}

	return false;
}

void MovementRoutine::reset(sf::Transformable& transformable)
{
	TransformationRoutine::reset();
	transformable.setPosition(m_routineMovements.front()->getStartingPos());
}

void MovementRoutine::stop(sf::Transformable* transformable)
{
	TransformationRoutine::reset();
	m_movementRoutineEngine->stopMovement(transformable);
}

void MovementRoutine::move(const sf::Vector2f& offset)
{
	for (auto& movement : m_routineMovements) {
		movement->getStartingPos() += offset;
		movement->getEndingPos() += offset;
	}
}

movementInfo* MovementRoutine::getCurrentMovement() const
{
	return m_current < m_count ? m_routineMovements[m_current] : nullptr;
}

const bool MovementRoutine::goToNextMovement(const sf::Transformable& transformable)
{
	if (m_current < m_count - 1) {
		++m_current;
		m_isPaused = m_pauseAfterChangingMovements;
		return true;
	}
	else {
		if (m_adjustAllToCurrentTransform) { adjustAllToCurrent(transformable.getPosition()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getPosition()); }
		TransformationRoutine::reset();

		if (m_isLooping) {
			m_isActive = true;
			return true;
		}

		return false;
	}
}

movementInfo* MovementRoutine::operator[](const size_t& index) const
{
	return index < m_count ? m_routineMovements[index] : nullptr;
}

const long long int& MovementRoutine::size() const
{
	long long int size{};
	for (const auto& movement : m_routineMovements)
		size += sizeof(*movement);
	return size + sizeof(this);
}

// - - - - - - - - - - - - - - - - - - - - ScalingRoutine - - - - - - - - - - - - - - - - - - - - \\

// Private functions
void ScalingRoutine::adjustStartToCurrent(const sf::Vector2f& currentScale)
{
	if (m_routineScalings.size() == 0) return;
	m_routineScalings.front()->getStartingScale() = currentScale;
}

void ScalingRoutine::adjustAllToCurrent(const sf::Vector2f& currentScale)
{
	if (m_routineScalings.size() == 0) return;

	const sf::Vector2f& starting_scale = m_routineScalings.front()->getStartingScale();
	const sf::Vector2f proportion{ currentScale.x / starting_scale.x, currentScale.y / starting_scale.y };

	if (proportion == sf::Vector2f{ 1.f, 1.f }) return;

	for (auto& scaling : m_routineScalings)
		scaling->scale(proportion);
}

// Constructors / Destructors
ScalingRoutine::ScalingRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr) :
	TransformationRoutine{ name, movementRoutineEnginePtr }
{}

ScalingRoutine::ScalingRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, scalingInfo* scaling) :
	TransformationRoutine{ name, movementRoutineEnginePtr }
{
	m_routineScalings.emplace_back(scaling);
	m_transformations.emplace_back(static_cast<transformationInfo*>(scaling));
	++m_count;
}

ScalingRoutine::ScalingRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, const std::vector<scalingInfo*> scalings) :
	TransformationRoutine{ name, movementRoutineEnginePtr },
	m_routineScalings{ scalings }
{
	for (const auto& scaling : m_routineScalings)
		m_transformations.emplace_back(static_cast<transformationInfo*>(scaling));
	m_count = m_routineScalings.size();
}

ScalingRoutine::ScalingRoutine(const ScalingRoutine& obj) :
	TransformationRoutine{ obj }
{
	for (const auto& scaling : obj.m_routineScalings) {
		m_routineScalings.emplace_back(new scalingInfo(*scaling));
		m_transformations.emplace_back(static_cast<transformationInfo*>(m_routineScalings.back()));
	}
	m_count = m_routineScalings.size();
}

ScalingRoutine::~ScalingRoutine()
{
	for (auto& scaling : m_routineScalings)
		delete scaling;
	m_routineScalings.clear();
	m_transformations.clear();
}

// Update functions
const bool ScalingRoutine::update(sf::Transformable& transformable, const float dt)
{
	if (m_isPaused) return true;

	if (!m_routineScalings[m_current]->update(transformable, dt) && !goToNextScaling(transformable))
		return false;

	return true;
}

// Public functions
void ScalingRoutine::addScaling(scalingInfo* scaling)
{
	m_routineScalings.emplace_back(scaling);
	m_transformations.emplace_back(static_cast<transformationInfo*>(scaling));
	++m_count;
}

void ScalingRoutine::removeScaling(scalingInfo* scaling)
{
	auto it = std::find(m_routineScalings.begin(), m_routineScalings.end(), scaling);

	if (it != m_routineScalings.end()) {
		m_routineScalings.erase(it);
		--m_count;
	}

	auto it2 = std::find(m_transformations.begin(), m_transformations.end(), scaling);
	if (it2 != m_transformations.end())
		m_transformations.erase(it2);
}

void ScalingRoutine::clear()
{
	m_routineScalings.clear();
	m_transformations.clear();
	m_current = 0;
	m_count = 0;
	m_isActive = false;
	m_isPaused = false;
	m_isLooping = false;
}

const bool ScalingRoutine::start(sf::Transformable& transformable)
{
	if (m_routineScalings.size() != 0) {
		if (m_adjustAllToCurrentTransform) { adjustAllToCurrent(transformable.getScale()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getScale()); }
		TransformationRoutine::reset();

		m_current = 0;
		m_isActive = true;
		m_movementRoutineEngine->addScaling(&transformable, this);
		return true;
	}

	return false;
}

void ScalingRoutine::reset(sf::Transformable& transformable)
{
	TransformationRoutine::reset();
	transformable.setScale(m_routineScalings.front()->getStartingScale());
}

void ScalingRoutine::stop(sf::Transformable* transformable)
{
	TransformationRoutine::reset();
	m_movementRoutineEngine->stopScaling(transformable);
}

scalingInfo* ScalingRoutine::getCurrentScaling() const
{
	return m_current < m_count ? m_routineScalings[m_current] : nullptr;
}

const bool ScalingRoutine::goToNextScaling(const sf::Transformable& transformable)
{
	if (m_current < m_count - 1) {
		++m_current;
		m_isPaused = m_pauseAfterChangingMovements;
		return true;
	}
	else {
		if (m_adjustAllToCurrentTransform) { adjustAllToCurrent(transformable.getScale()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getScale()); }
		TransformationRoutine::reset();

		if (m_isLooping) {
			m_isActive = true;
			return true;
		}

		return false;
	}
}

ScalingRoutine* ScalingRoutine::goToScaling(const sf::Transformable& transformable, const size_t scaling_id)
{
	if (scaling_id < m_count) {
		m_current = scaling_id;
		m_isPaused = m_pauseAfterChangingMovements;
	}
	return this;
}

const long long int& ScalingRoutine::size() const
{
	long long int size{};
	for (const auto& scaling : m_routineScalings) size += sizeof(*scaling);
	return size + sizeof(this);
}

// - - - - - - - - - - - - - - - - - - - - RotationRoutine - - - - - - - - - - - - - - - - - - - - \\

// Private functions
void RotationRoutine::adjustStartToCurrent(float currentRotation)
{
	if (m_routineRotations.size() == 0) return;

	const rotationInfo& rotation = *m_routineRotations.front();

	if (!m_wasLastClockwise) {
		if (rotation.getClockwise()) {
			if (currentRotation > rotation.getEndingRotation())
				currentRotation -= 360.f;
		}
		else {
			currentRotation -= 360.f;
			currentRotation *= -1.f;

			if (currentRotation > rotation.getEndingRotation())
				currentRotation -= 360.f;
		}
	}
	else {
		if (rotation.getClockwise()) {
			if (currentRotation > rotation.getEndingRotation())
				currentRotation -= 360.f;
		}
		else if (rotation.getClockwise() == false) {
			currentRotation -= 360.f;
			currentRotation *= -1.f;

			if (currentRotation > rotation.getEndingRotation())
				currentRotation -= 360.f;
		}
	}

	if (rotation.getClockwise())
		m_routineRotations.front()->getStartingRotation() = currentRotation;
	else
		m_routineRotations.front()->getStartingRotation() = 360.f - currentRotation;
}

void RotationRoutine::adjustAllToCurrent(const float currentRotation)
{
	if (m_routineRotations.size() == 0) return;

	float rotation_offset = currentRotation - m_routineRotations.front()->getStartingRotation();

	if (!m_routineRotations.front()->getClockwise())
		rotation_offset = 360.f + rotation_offset;

	if (rotation_offset == 0.f || rotation_offset == 360.f) return;

	for (auto& rotation : m_routineRotations) {
		float& new_starting_rotation = rotation->getStartingRotation();
		float& new_ending_rotation = rotation->getEndingRotation();

		new_starting_rotation += rotation_offset;
		new_ending_rotation += rotation_offset;
	}
}

// Constructors / Destructors
RotationRoutine::RotationRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr) :
	TransformationRoutine{ name, movementRoutineEnginePtr }
{}

RotationRoutine::RotationRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, rotationInfo* rotation) :
	TransformationRoutine{ name, movementRoutineEnginePtr }
{
	m_routineRotations.emplace_back(rotation);
	m_transformations.emplace_back(static_cast<transformationInfo*>(rotation));
	++m_count;
}

RotationRoutine::RotationRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, const std::vector<rotationInfo*> rotations) :
	TransformationRoutine{ name, movementRoutineEnginePtr },
	m_routineRotations{ rotations }
{
	for (const auto& rotation : m_routineRotations)
		m_transformations.emplace_back(static_cast<transformationInfo*>(rotation));
	m_count = m_routineRotations.size();
}

RotationRoutine::RotationRoutine(const RotationRoutine& obj) :
	TransformationRoutine{ obj },
	m_wasLastClockwise{ obj.m_wasLastClockwise }
{
	for (const auto& rotation : obj.m_routineRotations) {
		m_routineRotations.emplace_back(new rotationInfo(*rotation));
		m_transformations.emplace_back(static_cast<transformationInfo*>(m_routineRotations.back()));
	}
	m_count = m_routineRotations.size();
}

RotationRoutine::~RotationRoutine()
{
	for (auto& rotation : m_routineRotations)
		delete rotation;
	m_routineRotations.clear();
	m_transformations.clear();
}

// Update functions
const bool RotationRoutine::update(sf::Transformable& transformable, const float dt)
{
	if (m_isPaused) return true;

	if (!m_routineRotations[m_current]->update(transformable, dt) && !goToNextRotation(transformable))
		return false;

	return true;
}

// Public functions
void RotationRoutine::addRotation(rotationInfo* rotation)
{
	m_wasLastClockwise = rotation->getClockwise();
	m_routineRotations.emplace_back(rotation);
	m_transformations.emplace_back(static_cast<transformationInfo*>(rotation));
	++m_count;
}

void RotationRoutine::removeRotation(rotationInfo* rotation)
{
	auto it = std::find(m_routineRotations.begin(), m_routineRotations.end(), rotation);
	if (it != m_routineRotations.end()) {
		m_routineRotations.erase(it);
		--m_count;
	}

	auto it2 = std::find(m_transformations.begin(), m_transformations.end(), rotation);
	if (it2 != m_transformations.end())
		m_transformations.erase(it2);
}

void RotationRoutine::clear()
{
	m_routineRotations.clear();
	m_transformations.clear();
	m_current = 0;
	m_count = 0;
	m_isActive = false;
	m_isPaused = false;
	m_isLooping = false;
}

const bool RotationRoutine::start(sf::Transformable& transformable)
{
	if (m_routineRotations.size() != 0) {
		if (m_adjustAllToCurrentTransform) { adjustAllToCurrent(transformable.getRotation()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getRotation()); }
		TransformationRoutine::reset();

		m_current = 0;
		m_isActive = true;
		m_movementRoutineEngine->addRotation(&transformable, this);
		return true;
	}

	return false;
}

void RotationRoutine::reset(sf::Transformable& transformable)
{
	TransformationRoutine::reset();
	transformable.setRotation(m_routineRotations.front()->getStartingRotation());
}

void RotationRoutine::stop(sf::Transformable* transformable)
{
	TransformationRoutine::reset();
	m_movementRoutineEngine->stopRotation(transformable);
}

rotationInfo* RotationRoutine::getCurrentRotation() const
{
	return m_current < m_count ? m_routineRotations[m_current] : nullptr;
}

const bool RotationRoutine::goToNextRotation(const sf::Transformable& transformable)
{
	if (m_current < m_count - 1) {
		m_wasLastClockwise = m_routineRotations[m_current]->getClockwise();
		m_isPaused = m_pauseAfterChangingMovements;
		++m_current;
		return true;
	}
	else {
		m_wasLastClockwise = m_routineRotations[m_current]->getClockwise();
		if (m_adjustAllToCurrentTransform) { adjustAllToCurrent(transformable.getRotation()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getRotation()); }
		TransformationRoutine::reset();

		if (m_isLooping) {
			m_isActive = true;
			return true;
		}

		return false;
	}
}

const long long int& RotationRoutine::size() const
{
	long long int size{};
	for (const auto& rotation : m_routineRotations) size += sizeof(*rotation);
	return size + sizeof(this);
}