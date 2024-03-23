#pragma once
#include "transformationInfo.h"

// - - - - - - - - - - - - - - - - - - - - transformationInfo - - - - - - - - - - - - - - - - - - - - \\

// Constructors / Destructors
transformationInfo::transformationInfo(bool repeat, float motionDuration, float delayBefore, float delayAfter, easeFunctions::Tmovement_function usedFunctionType) :
	m_repeat{ repeat }, 
	m_motionDuration{ motionDuration }, 
	m_delayBefore{ delayBefore }, 
	m_delayAfter{ delayAfter }, 
	m_usedFunctionPtr{ easeFunctions::movement_functions[usedFunctionType] },
	m_totalDuration{ delayBefore + motionDuration + delayAfter }
	{}

transformationInfo::transformationInfo(bool repeat, float motionDuration, float delayBefore, float delayAfter, double (*usedFunctionPtr)(double)) :
	m_repeat{ repeat }, 
	m_motionDuration{ motionDuration }, 
	m_delayBefore{ delayBefore }, 
	m_delayAfter{ delayAfter }, 
	m_usedFunctionPtr{ usedFunctionPtr }, 
	m_totalDuration{ delayBefore + motionDuration + delayAfter }
	{}

transformationInfo::transformationInfo(bool repeat, float _current__time, float motionDuration, float delayBefore, float delayAfter, double(*usedFunctionPtr)(double)) :
	m_repeat{ repeat }, 
	m_currentTime{ _current__time }, 
	m_motionDuration{ motionDuration }, 
	m_delayBefore{ delayBefore }, 
	m_delayAfter{ delayAfter }, 
	m_usedFunctionPtr{ usedFunctionPtr }, 
	m_totalDuration{ delayBefore + motionDuration + delayAfter } 
	{}

transformationInfo::transformationInfo(const transformationInfo& obj) :
	m_repeat{ obj.m_repeat }, 
	m_currentTime{ obj.m_currentTime }, 
	m_motionDuration{ obj.m_motionDuration }, 
	m_delayBefore{ obj.m_delayBefore }, 
	m_delayAfter{ obj.m_delayAfter }, 
	m_usedFunctionPtr{ obj.m_usedFunctionPtr }, 
	m_totalDuration{ obj.m_totalDuration } 
	{}

// Public functions
void transformationInfo::reset()
{
	m_currentTime = 0.f;
}

inline const bool transformationInfo::isDone() const
{
	return (m_currentTime - m_delayBefore >= m_motionDuration);
}

const bool transformationInfo::isFinished() const
{
	return (m_currentTime >= m_totalDuration);
}

// Mutators
void transformationInfo::setDelayBefore(const float delay, const bool reset)
{
	if (delay < 0.f) return;

	if (reset)
		m_currentTime = 0.f;
	else if (m_currentTime > m_delayBefore && m_motionDuration != 0.f) {
		const float timeFactor = (m_currentTime - m_delayBefore) / m_motionDuration;
		m_currentTime = delay + timeFactor * m_motionDuration;
	}

	m_delayBefore = delay;
	m_totalDuration = m_delayBefore + m_motionDuration + m_delayAfter;

	if (m_currentTime > m_totalDuration)
		m_currentTime = m_totalDuration;
}

void transformationInfo::setMotionDuration(const float duration, const bool reset)
{
	if (duration < 0.f) return;

	if (reset) 
		m_currentTime = 0.f;
	else if (m_currentTime > m_delayBefore && m_motionDuration != 0.f) {
		const float timeFactor = (m_currentTime - m_delayBefore) / m_motionDuration;
		m_currentTime = m_delayBefore + timeFactor * duration;
	}

	m_motionDuration = duration;
	m_totalDuration = m_delayBefore + m_motionDuration + m_delayAfter;

	if (m_currentTime > m_totalDuration)
		m_currentTime = m_totalDuration;
}

void transformationInfo::setDelayAfter(const float delay, const bool reset)
{
	if (delay <= 0.f) return;

	if (reset)
		m_currentTime = 0.f;
	else if (m_currentTime > m_delayBefore + m_motionDuration && m_delayAfter != 0.f) {
		const float timeFactor = (m_currentTime - m_delayBefore - m_motionDuration) / m_delayAfter;
		m_currentTime = m_delayBefore + m_motionDuration + timeFactor * delay;
	}

	m_delayAfter = delay;
	m_totalDuration = m_delayBefore + m_motionDuration + m_delayAfter;

	if (m_currentTime > m_totalDuration)
		m_currentTime = m_totalDuration;
}

void transformationInfo::setFunction(double(*usedFunctionPtr)(double))
{
	m_usedFunctionPtr = usedFunctionPtr;
}

void transformationInfo::setFunction(easeFunctions::Tmovement_function usedFunctionType)
{
	m_usedFunctionPtr = easeFunctions::movement_functions[usedFunctionType];
}

// - - - - - - - - - - - - - - - - - - - - movementInfo - - - - - - - - - - - - - - - - - - - - \\

movementInfo::movementInfo(sf::Vector2f startingPos, sf::Vector2f endingPos, float motionDuration, easeFunctions::Tmovement_function usedFunctionType, bool repeat, float delayBefore, float delayAfter) :
	transformationInfo{ repeat, motionDuration, delayBefore, delayAfter, usedFunctionType }, 
	m_originalStartingPos{ startingPos },
	m_originalEndingPos{ endingPos },
	m_startingPos{ startingPos },
	m_endingPos{ endingPos }
	{}

// Constructors / Destructors
movementInfo::movementInfo(sf::Vector2f startingPos, sf::Vector2f endingPos, float motionDuration, double(*usedFunctionPtr)(double), bool repeat, float delayBefore, float delayAfter) :
	transformationInfo{ repeat, motionDuration, delayBefore, delayAfter, usedFunctionPtr },
	m_originalStartingPos{ startingPos },
	m_originalEndingPos{ endingPos },
	m_startingPos{ startingPos },
	m_endingPos{ endingPos }
	{}

movementInfo::movementInfo(const movementInfo & obj) :
	transformationInfo{ obj.m_repeat, obj.m_currentTime, obj.m_motionDuration, obj.m_delayBefore, obj.m_delayAfter, obj.m_usedFunctionPtr },
	m_originalStartingPos{ obj.m_originalStartingPos },
	m_originalEndingPos{ obj.m_originalEndingPos },
	m_startingPos{ obj.m_startingPos },
	m_endingPos{ obj.m_endingPos }
	{}

const bool movementInfo::update(sf::Transformable& transformable, const float dt)
{
	m_currentTime += dt;

	if (isDone()) {
		if (m_currentTime - m_delayBefore - dt < m_motionDuration)
			transformable.setPosition(m_endingPos);
		else if (isFinished()) {
			if (m_repeat) {
				transformable.setPosition(m_startingPos);
				m_currentTime -= m_totalDuration;
			}
			else
				return false;
		}
	}
	else {
		if (m_currentTime > m_delayBefore) 
			transformable.setPosition(updatePosition());
		else if (m_currentTime == dt)
			transformable.setPosition(m_startingPos);
	}

	return true;
}

// Update functions
const sf::Vector2f movementInfo::updatePosition() const
{
	const float ease_function_value = static_cast<float>(m_usedFunctionPtr(static_cast<double>((m_currentTime - m_delayBefore) / m_motionDuration)));
	return sf::Vector2f{ ease_function_value * (m_endingPos.x - m_startingPos.x) + m_startingPos.x,
						 ease_function_value * (m_endingPos.y - m_startingPos.y) + m_startingPos.y };
}

void movementInfo::undoMovement(sf::Transformable& transformable)
{
	m_currentTime = 0.f;
	m_startingPos = m_originalStartingPos;
	m_endingPos = m_originalEndingPos;
	transformable.setPosition(m_originalStartingPos);
}

// Accessors
sf::Vector2f& movementInfo::getStartingPos()
{
	return m_startingPos;
}

const sf::Vector2f& movementInfo::getStartingPos() const
{
	return m_startingPos;
}

sf::Vector2f& movementInfo::getEndingPos()
{
	return m_endingPos;
}

const sf::Vector2f& movementInfo::getEndingPos() const
{
	return m_endingPos;
}

// - - - - - - - - - - - - - - - - - - - - scalingInfo - - - - - - - - - - - - - - - - - - - - \\

scalingInfo::scalingInfo(sf::Vector2f startingScale, sf::Vector2f endingScale, float motionDuration, easeFunctions::Tmovement_function usedFunctionType, bool repeat, float delayBefore, float delayAfter) :
	transformationInfo{ repeat, motionDuration, delayBefore, delayAfter, usedFunctionType },
	m_originalStartingScale{ startingScale },
	m_originalEndingScale{ endingScale },
	m_startingScale{ startingScale },
	m_endingScale{ endingScale }
	{}

// Constructors / Destructors
scalingInfo::scalingInfo(sf::Vector2f startingScale, sf::Vector2f endingScale, float motionDuration, double(*usedFunctionPtr)(double), bool repeat, float delayBefore, float delayAfter) :
	transformationInfo{ repeat, motionDuration, delayBefore, delayAfter, usedFunctionPtr },
	m_originalStartingScale{ startingScale },
	m_originalEndingScale{ endingScale },
	m_startingScale{ startingScale },
	m_endingScale{ endingScale }
	{}

scalingInfo::scalingInfo(const scalingInfo & obj) :
	transformationInfo{ obj.m_repeat, obj.m_currentTime, obj.m_motionDuration, obj.m_delayBefore, obj.m_delayAfter, obj.m_usedFunctionPtr },
	m_originalStartingScale{ obj.m_originalStartingScale },
	m_originalEndingScale{ obj.m_originalEndingScale },
	m_startingScale{ obj.m_startingScale },
	m_endingScale{ obj.m_endingScale }
	{}

// Public functions
void scalingInfo::scale(const sf::Vector2f& scale)
{
	m_startingScale.x *= scale.x;
	m_startingScale.y *= scale.y;
	m_endingScale.x *= scale.x;
	m_endingScale.y *= scale.y;
}

const bool scalingInfo::update(sf::Transformable& transformable, const float dt)
{
	m_currentTime += dt;

	if (isDone()) {
		if (m_currentTime - m_delayBefore - dt < m_motionDuration)
			transformable.setScale(m_endingScale);
		else if (isFinished()) {
			if (m_repeat) {
				transformable.setScale(m_startingScale);
				m_currentTime -= m_totalDuration;
			}
			else
				return false;
		}
	}
	else {
		if (m_currentTime > m_delayBefore)
			transformable.setScale(updateScale());
		else if (m_currentTime == dt)
			transformable.setScale(m_startingScale);
	}

	return true;
}

const sf::Vector2f scalingInfo::updateScale() const
{
	const float ease_function_value = static_cast<float>(m_usedFunctionPtr(static_cast<double>((m_currentTime - m_delayBefore) / m_motionDuration)));
	return sf::Vector2f{ ease_function_value * (m_endingScale.x - m_startingScale.x) + m_startingScale.x,
						 ease_function_value * (m_endingScale.y - m_startingScale.y) + m_startingScale.y };
}

void scalingInfo::undoScaling(sf::Transformable& transformable)
{
	m_currentTime = 0.f;
	m_startingScale = m_originalStartingScale;
	m_endingScale = m_originalEndingScale;
	transformable.setScale(m_originalStartingScale);
}

// Accessors
sf::Vector2f& scalingInfo::getStartingScale()
{
	return m_startingScale;
}

const sf::Vector2f& scalingInfo::getStartingScale() const
{
	return m_startingScale;
}

sf::Vector2f& scalingInfo::getEndingScale()
{
	return m_endingScale;
}

const sf::Vector2f& scalingInfo::getEndingScale() const
{
	return m_endingScale;
}


// - - - - - - - - - - - - - - - - - - - - rotationInfo - - - - - - - - - - - - - - - - - - - - \\

rotationInfo::rotationInfo(float startingRotation, float endingRotation, float motionDuration, easeFunctions::Tmovement_function usedFunctionType, bool repeat, float delayBefore, float delayAfter, bool clockwise) :
	transformationInfo{ repeat, motionDuration, delayBefore, delayAfter, usedFunctionType },
	m_clockwise(clockwise)
{
	if (m_clockwise) {
		m_originalStartingRotation = startingRotation;
		m_originalEndingRotation = endingRotation;

		m_startingRotation = m_originalStartingRotation;
		m_endingRotation = m_originalEndingRotation;
	}
	else {
		m_originalStartingRotation = 360.f - startingRotation;
		m_originalEndingRotation = 360.f - endingRotation;

		m_startingRotation = m_originalStartingRotation;
		m_endingRotation = m_originalEndingRotation;
	}
}

// Constructors / Destructors
rotationInfo::rotationInfo(float startingRotation, float endingRotation, float motionDuration, double(*usedFunctionPtr)(double), bool repeat, float delayBefore, float delayAfter, bool clockwise) :
	transformationInfo{ repeat, motionDuration, delayBefore, delayAfter, usedFunctionPtr },
	m_clockwise(clockwise) 
{
	if (m_clockwise) {
		m_originalStartingRotation = startingRotation;
		m_originalEndingRotation = endingRotation;

		m_startingRotation = m_originalStartingRotation;
		m_endingRotation = m_originalEndingRotation;
	}
	else {
		m_originalStartingRotation = 360.f - startingRotation;
		m_originalEndingRotation = 360.f - endingRotation;

		m_startingRotation = m_originalStartingRotation;
		m_endingRotation = m_originalEndingRotation;
	}
}

rotationInfo::rotationInfo(const rotationInfo& obj) :
	transformationInfo{ obj.m_repeat, obj.m_currentTime, obj.m_motionDuration, obj.m_delayBefore, obj.m_delayAfter, obj.m_usedFunctionPtr },
	m_clockwise{ obj.m_clockwise },
	m_originalStartingRotation{ obj.m_originalStartingRotation },
	m_originalEndingRotation{ obj.m_originalEndingRotation },
	m_startingRotation{ obj.m_originalStartingRotation },
	m_endingRotation{ obj.m_originalEndingRotation }
	{}

const bool rotationInfo::update(sf::Transformable& transformable, const float dt)
{
	m_currentTime += dt;

	if (isDone()) {
		if (m_currentTime - m_delayBefore - dt < m_motionDuration)
			transformable.setRotation(m_endingRotation);
		else if (isFinished()) {
			if (m_repeat) {
				transformable.setRotation(m_startingRotation);
				m_currentTime -= m_totalDuration;
			}
			else
				return false;
		}
	}
	else {
		if (m_currentTime > m_delayBefore)
			transformable.setRotation(updateRotation());
		else if (m_currentTime == dt)
			transformable.setRotation(m_startingRotation);
	}

	return true;
}

// Update functions
const float rotationInfo::updateRotation() const
{
	return static_cast<const float>(m_usedFunctionPtr(static_cast<double>((m_currentTime - m_delayBefore) / m_motionDuration))) * (m_endingRotation - m_startingRotation) + m_startingRotation;
}

void rotationInfo::undoRotation(sf::Transformable& transformable)
{
	m_currentTime = 0.f;
	m_startingRotation = m_originalStartingRotation;
	m_endingRotation = m_originalEndingRotation;
	transformable.setRotation(m_originalStartingRotation);
}

// Accessors
float& rotationInfo::getStartingRotation()
{
	return m_startingRotation;
}

const float& rotationInfo::getStartingRotation() const
{
	return m_startingRotation;
}

float& rotationInfo::getEndingRotation()
{
	return m_endingRotation;
}

const float& rotationInfo::getEndingRotation() const
{
	return m_endingRotation;
}

bool rotationInfo::getClockwise() const
{
	return m_clockwise;
}