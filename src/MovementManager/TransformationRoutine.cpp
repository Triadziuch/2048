#pragma once
#include "TransformationRoutine.h"
#include "MovementContainer.h"

// - - - - - - - - - - - - - - - - - - - - TransformationRoutine - - - - - - - - - - - - - - - - - - - - \\

// Constructors / Destructors
TransformationRoutine::TransformationRoutine() :
	m_movementRoutineEngine{ nullptr }, 
	m_routineName{}, 
	m_current{}, 
	m_count{}, 
	m_isActive{}, 
	m_isLooping{}, 
	m_isPaused{}, 
	m_adjustStartToCurrentTransform{}, 
	m_adjustAllToCurrentTransform{} ,
	m_pauseAtStart{},
	m_pauseAfterChangingMovements{}
	{}

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
	m_adjustAllToCurrentTransform{ obj.m_adjustAllToCurrentTransform } ,
	m_pauseAtStart{ obj.m_pauseAtStart },
	m_pauseAfterChangingMovements{ obj.m_pauseAfterChangingMovements }
	{}

TransformationRoutine::~TransformationRoutine() {
	m_movementRoutineEngine = nullptr;
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

void TransformationRoutine::pause()
{
	m_isPaused = true;
}

void TransformationRoutine::resume()
{
	m_isPaused = false;
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
		movement->getEndingPos()   += offset;
	}
}

// Constructors / Destructors
MovementRoutine::MovementRoutine() :
	TransformationRoutine{}, 
	m_routineMovements{}
	{}

MovementRoutine::MovementRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr) :
	TransformationRoutine{ name, movementRoutineEnginePtr } 
	{}

MovementRoutine::MovementRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, movementInfo* movement) :
	TransformationRoutine{ name, movementRoutineEnginePtr } 
{
	m_routineMovements.emplace_back(movement);
	++m_count;
}

MovementRoutine::MovementRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, const std::vector<movementInfo*> movements) :
	TransformationRoutine{ name, movementRoutineEnginePtr },
	m_routineMovements{ movements }
	{}

MovementRoutine::MovementRoutine(const MovementRoutine& obj) : 
	TransformationRoutine{ obj } 
{
	for (const auto& movement : obj.m_routineMovements)
		m_routineMovements.emplace_back(new movementInfo(*movement));
}

MovementRoutine::~MovementRoutine() { 
	for (auto& movement : m_routineMovements) 
		delete movement;
	m_routineMovements.clear();
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
	++m_count;
}

void MovementRoutine::removeMovement(movementInfo* movement)
{
	auto it = std::find(m_routineMovements.begin(), m_routineMovements.end(), movement);

	if (it != m_routineMovements.end()) {
		m_routineMovements.erase(it);
		--m_count;
	}
}

void MovementRoutine::clear()
{
	m_routineMovements.clear();
	m_current	= 0;
	m_count		= 0;
	m_isActive	= false;
	m_isPaused	= false;
	m_isLooping = false;
}

void MovementRoutine::reset()
{
	for (auto& movement : m_routineMovements)
		movement->reset();

	m_current  = 0;
	m_isActive = false;
	m_isPaused = m_pauseAfterChangingMovements;
}

const bool MovementRoutine::start(sf::Transformable& transformable)
{
	if (m_routineMovements.size() != 0) {
		if (m_adjustAllToCurrentTransform)		  { adjustAllToCurrent(transformable.getPosition()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getPosition()); }

		reset();

		m_current = 0;
		m_isActive = true;
		m_movementRoutineEngine->addMovement(&transformable, this);
		return true;
	}

	return false;
}

void MovementRoutine::reset(sf::Transformable& transformable)
{
	reset();
	transformable.setPosition(m_routineMovements.front()->getStartingPos());
}

void MovementRoutine::stop(sf::Transformable* transformable)
{
	reset();
	m_movementRoutineEngine->stopMovement(transformable);
}

void MovementRoutine::move(const sf::Vector2f& offset)
{
	for (auto& movement : m_routineMovements) {
		movement->getStartingPos() += offset;
		movement->getEndingPos()   += offset;
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
		if (m_adjustAllToCurrentTransform)		  { adjustAllToCurrent(transformable.getPosition()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getPosition()); }
		reset();

		if (m_isLooping) {
			m_isActive = true;
			return true;
		}

		return false;
	}
}

void MovementRoutine::setFunction(easeFunctions::Tmovement_function usedFunctionType)
{
	for (auto& movement: m_routineMovements)
		movement->setFunction(usedFunctionType);
}

void MovementRoutine::setFunction(easeFunctions::Tmovement_function usedFunctionType, const size_t movement_id)
{
	if (movement_id < m_count)
		m_routineMovements[movement_id]->setFunction(usedFunctionType);
}

void MovementRoutine::setFunction(double(*usedFunctionPtr)(double))
{
	for (auto& movement : m_routineMovements)
		movement->setFunction(usedFunctionPtr);
}

void MovementRoutine::setFunction(double(*usedFunctionPtr)(double), const size_t movement_id)
{
	if (movement_id < m_count)
		m_routineMovements[movement_id]->setFunction(usedFunctionPtr);
}

void MovementRoutine::setAnimationTime(const float animationTime)
{
	for (auto& movement : m_routineMovements)
		movement->setAnimationTime(animationTime);	
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
void ScalingRoutine::adjustStartToCurrent(const sf::Vector2f& current_scale)
{
	if (m_routineScalings.size() == 0) return;
	m_routineScalings.front()->getStartingScale() = current_scale;
}

void ScalingRoutine::adjustAllToCurrent(const sf::Vector2f& current_scale)
{
	if (m_routineScalings.size() == 0) return;

	const sf::Vector2f& starting_scale = m_routineScalings.front()->getStartingScale();
	const sf::Vector2f proportion{ current_scale.x / starting_scale.x, current_scale.y / starting_scale.y};

	if (proportion == sf::Vector2f{ 1.f, 1.f }) return;

	for (auto& scaling : m_routineScalings)
		scaling->scale(proportion);
}

// Constructors / Destructors
ScalingRoutine::ScalingRoutine() :
	TransformationRoutine{}, 
	m_routineScalings{}
	{}

ScalingRoutine::ScalingRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr) :
	TransformationRoutine{ name, movementRoutineEnginePtr } 
	{}

ScalingRoutine::ScalingRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, scalingInfo* scaling) :
	TransformationRoutine{ name, movementRoutineEnginePtr } 
{ 
	m_routineScalings.emplace_back(scaling);
}

ScalingRoutine::ScalingRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, const std::vector<scalingInfo*> scalings) :
	TransformationRoutine{ name, movementRoutineEnginePtr },
	m_routineScalings{ scalings }
	{}

ScalingRoutine::ScalingRoutine(const ScalingRoutine & obj) : 
	TransformationRoutine{ obj } 
{
	for (const auto& scaling : obj.m_routineScalings)
		m_routineScalings.emplace_back(new scalingInfo(*scaling));
}

ScalingRoutine::~ScalingRoutine()
{
	for (auto& scaling : m_routineScalings) 
		delete scaling; 
	m_routineScalings.clear();
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
	++m_count;
}

void ScalingRoutine::removeScaling(scalingInfo* scaling)
{
	auto it = std::find(m_routineScalings.begin(), m_routineScalings.end(), scaling);

	if (it != m_routineScalings.end()) {
		m_routineScalings.erase(it); 
		--m_count;
	}
}

void ScalingRoutine::clear()
{
	m_routineScalings.clear();
	m_current = 0;
	m_count = 0;
	m_isActive = false;
	m_isPaused = false;
	m_isLooping = false;
}

void ScalingRoutine::reset()
{
	for (auto& scaling : m_routineScalings)
		scaling->reset();

	m_current = 0;
	m_isActive = false;
	m_isPaused = m_pauseAfterChangingMovements;
}

const bool ScalingRoutine::start(sf::Transformable& transformable)
{
	if (m_routineScalings.size() != 0) {
		if (m_adjustAllToCurrentTransform)		  { adjustAllToCurrent(transformable.getScale()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getScale()); }
		reset();

		m_current = 0;
		m_isActive = true;
		m_movementRoutineEngine->addScaling(&transformable, this);
		return true;
	}

	return false;
}

void ScalingRoutine::reset(sf::Transformable& transformable)
{
	reset();
	transformable.setScale(m_routineScalings.front()->getStartingScale());
}

void ScalingRoutine::stop(sf::Transformable* transformable)
{
	reset();
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
		if (m_adjustAllToCurrentTransform)		  { adjustAllToCurrent(transformable.getScale()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getScale()); }
		reset();

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

void ScalingRoutine::setFunction(easeFunctions::Tmovement_function usedFunctionType)
{
	for (auto& scaling : m_routineScalings)
		scaling->setFunction(usedFunctionType);
}

void ScalingRoutine::setFunction(easeFunctions::Tmovement_function usedFunctionType, const size_t scaling_id)
{
	if (scaling_id < m_count)
		m_routineScalings[scaling_id]->setFunction(usedFunctionType);
}

void ScalingRoutine::setFunction(double(*usedFunctionPtr)(double))
{
	for (auto& scaling : m_routineScalings)
		scaling->setFunction(usedFunctionPtr);
}

void ScalingRoutine::setFunction(double(*usedFunctionPtr)(double), const size_t scaling_id)
{
	if (scaling_id < m_count)
		m_routineScalings[scaling_id]->setFunction(usedFunctionPtr);
}

void ScalingRoutine::setAnimationTime(const float animationTime)
{
	for (auto& scaling : m_routineScalings)
		scaling->setAnimationTime(animationTime);
}

const long long int& ScalingRoutine::size() const
{
	long long int size{};
	for (const auto& scaling : m_routineScalings) size += sizeof(*scaling);
	return size + sizeof(this);
}

// - - - - - - - - - - - - - - - - - - - - RotationRoutine - - - - - - - - - - - - - - - - - - - - \\

// Private functions
void RotationRoutine::adjustStartToCurrent(float current_rotation)
{
	if (m_routineRotations.size() == 0) return;

	const rotationInfo& rotation = *m_routineRotations.front();

	if (!was_last_clockwise) {
		if (rotation.getClockwise()) {
			if (current_rotation > rotation.getEndingRotation())
				current_rotation -= 360.f;
		}
		else {
			current_rotation -= 360.f;
			current_rotation *= -1.f;

			if (current_rotation > rotation.getEndingRotation())
				current_rotation -= 360.f;
		}
	}
	else {
		if (rotation.getClockwise()) {
			if (current_rotation > rotation.getEndingRotation())
				current_rotation -= 360.f;
		}
		else if (rotation.getClockwise() == false) {
			current_rotation -= 360.f;
			current_rotation *= -1.f;

			if (current_rotation > rotation.getEndingRotation())
				current_rotation -= 360.f;
		}
	}

	if (rotation.getClockwise())
		m_routineRotations.front()->getStartingRotation() = current_rotation;
	else
		m_routineRotations.front()->getStartingRotation() = 360.f - current_rotation;
}

void RotationRoutine::adjustAllToCurrent(const float current_rotation)
{
	if (m_routineRotations.size() == 0) return;

	float rotation_offset = current_rotation - m_routineRotations.front()->getStartingRotation();

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
RotationRoutine::RotationRoutine() :
	TransformationRoutine{}, 
	m_routineRotations{}
	{}

RotationRoutine::RotationRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr) :
	TransformationRoutine{ name, movementRoutineEnginePtr } 
	{}

RotationRoutine::RotationRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, rotationInfo* rotation) :
	TransformationRoutine{ name, movementRoutineEnginePtr } 
{
	m_routineRotations.emplace_back(rotation);
	++m_count;
}

RotationRoutine::RotationRoutine(const std::string& name, MovementRoutineEngine* const movementRoutineEnginePtr, const std::vector<rotationInfo*> rotations) :
	TransformationRoutine{ name, movementRoutineEnginePtr },
	m_routineRotations{ rotations }
	{}

RotationRoutine::RotationRoutine(const RotationRoutine& obj) :
	TransformationRoutine{ obj },
	was_last_clockwise{ obj.was_last_clockwise }
{
	for (const auto& rotation : obj.m_routineRotations)
		m_routineRotations.emplace_back(new rotationInfo(*rotation));
}

RotationRoutine::~RotationRoutine()
{
	for (auto& rotation : m_routineRotations) 
		delete rotation; 
	m_routineRotations.clear();
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
	was_last_clockwise = rotation->getClockwise();
	m_routineRotations.emplace_back(rotation);
	++m_count;
}

void RotationRoutine::removeRotation(rotationInfo* rotation)
{
	auto it = std::find(m_routineRotations.begin(), m_routineRotations.end(), rotation);
	if (it != m_routineRotations.end()) { 
		m_routineRotations.erase(it); 
		--m_count;
	}
}

void RotationRoutine::clear()
{
	m_routineRotations.clear();
	m_current = 0;
	m_count = 0;
	m_isActive = false;
	m_isPaused = false;
	m_isLooping = false;
}

void RotationRoutine::reset()
{
	for (auto& rotation : m_routineRotations)
		rotation->reset();

	m_current = 0;
	m_isActive = false;
	m_isPaused = m_pauseAfterChangingMovements;
}

const bool RotationRoutine::start(sf::Transformable& transformable)
{
	if (m_routineRotations.size() != 0) {
		if (m_adjustAllToCurrentTransform)		  { adjustAllToCurrent(transformable.getRotation()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getRotation()); }
		reset();

		m_current = 0;
		m_isActive = true;
		m_movementRoutineEngine->addRotation(&transformable, this);
		return true;
	}

	return false;
}

void RotationRoutine::reset(sf::Transformable& transformable)
{
	reset();
	transformable.setRotation(m_routineRotations.front()->getStartingRotation());
}

void RotationRoutine::stop(sf::Transformable* transformable)
{
	reset();
	m_movementRoutineEngine->stopRotation(transformable);
}

rotationInfo* RotationRoutine::getCurrentRotation() const
{
	return m_current < m_count ? m_routineRotations[m_current] : nullptr;
}

const bool RotationRoutine::goToNextRotation(const sf::Transformable& transformable)
{
	if (m_current < m_count - 1) {
		was_last_clockwise = m_routineRotations[m_current]->getClockwise();
		m_isPaused = m_pauseAfterChangingMovements;
		++m_current;
		return true;
	}
	else {
		was_last_clockwise = m_routineRotations[m_current]->getClockwise();
		if (m_adjustAllToCurrentTransform)		  { adjustAllToCurrent(transformable.getRotation()); }
		else if (m_adjustStartToCurrentTransform) { adjustStartToCurrent(transformable.getRotation()); }
		reset();

		if (m_isLooping) {
			m_isActive = true;
			return true;
		}

		return false;
	}
}

void RotationRoutine::setFunction(easeFunctions::Tmovement_function usedFunctionType)
{
	for (auto& rotation : m_routineRotations)
		rotation->setFunction(usedFunctionType);
}

void RotationRoutine::setFunction(easeFunctions::Tmovement_function usedFunctionType, const size_t rotation_id)
{
	if (rotation_id < m_count)
		m_routineRotations[rotation_id]->setFunction(usedFunctionType);
}

void RotationRoutine::setFunction(double(*usedFunctionPtr)(double))
{
	for (auto& rotation : m_routineRotations)
		rotation->setFunction(usedFunctionPtr);
}

void RotationRoutine::setFunction(double(*usedFunctionPtr)(double), const size_t rotation_id)
{
	if (rotation_id < m_count)
		m_routineRotations[rotation_id]->setFunction(usedFunctionPtr);
}

void RotationRoutine::setAnimationTime(const float animationTime)
{
	for (auto& rotation : m_routineRotations)
		rotation->setAnimationTime(animationTime);
}

const long long int& RotationRoutine::size() const
{
	long long int size{};
	for (const auto& rotation : m_routineRotations) size += sizeof(*rotation);
	return size + sizeof(this);
}