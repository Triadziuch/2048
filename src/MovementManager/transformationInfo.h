#pragma once
#include <SFML/Graphics.hpp>
#include "VertexArray2.h"
#include "easeFunctions.h"
#include <math.h>

// - - - - - - - - - - - - - - - - - - - - transformationInfo - - - - - - - - - - - - - - - - - - - - \\
 
class transformationInfo {
public:
	bool		  m_repeat{};
	float		  m_currentTime{};
	float		  m_motionDuration{};
	float		  m_delayBefore{};
	float		  m_delayAfter{};
	float		  m_totalDuration{};
	double		  (*m_usedFunctionPtr)(double) {};

	// Constructors / Destructors
	transformationInfo() = default;
	transformationInfo(bool repeat, float motionDuration, float delayBefore, float delayAfter, easeFunctions::Tmovement_function usedFunctionType);
	transformationInfo(bool repeat, float motionDuration, float delayBefore, float delayAfter, double (*usedFunctionPtr)(double));
	transformationInfo(bool repeat, float _current__time, float motionDuration, float delayBefore, float delayAfter, double (*usedFunctionPtr)(double));
	transformationInfo(const transformationInfo& obj);
	virtual ~transformationInfo() = default;

	// Public functions
	void reset();
	const bool isDone() const;
	const bool isFinished() const;

	void setDelayBefore(const float delay, const bool reset = false);
	void setMotionDuration(const float duration, const  bool reset = false);
	void setDelayAfter(const float delay, const  bool reset = false);

	void setFunction(double (*usedFunctionPtr)(double));
	void setFunction(easeFunctions::Tmovement_function usedFunctionType);
};


// - - - - - - - - - - - - - - - - - - - - movementInfo - - - - - - - - - - - - - - - - - - - - \\

class movementInfo : public transformationInfo {
private:
	sf::Vector2f m_startingPos{};
	sf::Vector2f m_endingPos{};

	sf::Vector2f m_originalStartingPos{};
	sf::Vector2f m_originalEndingPos{};

public:
	// Constructors / Destructors
	movementInfo(sf::Vector2f startingPos, sf::Vector2f endingPos, float motionDuration, easeFunctions::Tmovement_function usedFunctionType, bool repeat, float delayBefore, float delayAfter);
	movementInfo(sf::Vector2f startingPos, sf::Vector2f endingPos, float motionDuration, double (*usedFunctionPtr)(double), bool repeat, float delayBefore, float delayAfter);
	movementInfo(const movementInfo& obj);

	// Update functions
	const bool update(sf::Transformable& transformable, const float dt);
	const sf::Vector2f updatePosition() const;
	void undoMovement(sf::Transformable& transformable);

	// Accessors
	sf::Vector2f& getStartingPos();
	const sf::Vector2f& getStartingPos() const;

	sf::Vector2f& getEndingPos();
	const sf::Vector2f& getEndingPos() const;
};



// - - - - - - - - - - - - - - - - - - - - scalingInfo - - - - - - - - - - - - - - - - - - - - \\

class scalingInfo : public transformationInfo {
private:
	sf::Vector2f m_startingScale{};
	sf::Vector2f m_endingScale{};

	sf::Vector2f m_originalStartingScale{};
	sf::Vector2f m_originalEndingScale{};

public:
	// Constructors / Destructors
	scalingInfo(sf::Vector2f startingScale, sf::Vector2f endingScale, float motionDuration, easeFunctions::Tmovement_function usedFunctionType, bool repeat, float delayBefore, float delayAfter);
	scalingInfo(sf::Vector2f startingScale, sf::Vector2f endingScale, float motionDuration, double(*usedFunctionPtr)(double), bool repeat, float delayBefore, float delayAfter);
	scalingInfo(const scalingInfo& obj);

	// Public functions
	void scale(const sf::Vector2f& scale);

	// Update functions
	const bool update(sf::Transformable& transformable, const float dt);
	const sf::Vector2f updateScale() const;
	void undoScaling(sf::Transformable& transformable);

	// Accessors
	sf::Vector2f& getStartingScale();
	const sf::Vector2f& getStartingScale() const;

	sf::Vector2f& getEndingScale();
	const sf::Vector2f& getEndingScale() const;
};


// - - - - - - - - - - - - - - - - - - - - rotationInfo - - - - - - - - - - - - - - - - - - - - \\

class rotationInfo : public transformationInfo {
private:
	float m_startingRotation{};
	float m_endingRotation{};

	float m_originalStartingRotation{};
	float m_originalEndingRotation{};

	bool m_clockwise = true;

public:
	// Constructors / Destructors
	rotationInfo(float startingRotation, float endingRotation, float motionDuration, easeFunctions::Tmovement_function usedFunctionType, bool repeat, float delayBefore, float delayAfter, bool clockwise);
	rotationInfo(float startingRotation, float endingRotation, float motionDuration, double(*usedFunctionPtr)(double), bool repeat, float delayBefore, float delayAfter, bool clockwise);
	rotationInfo(const rotationInfo& obj);

	// Update functions
	const bool update(sf::Transformable& transformable, const float dt);
	const float updateRotation() const;
	void undoRotation(sf::Transformable& transformable);

	// Accessors
	float& getStartingRotation();
	const float& getStartingRotation() const;

	float& getEndingRotation();
	const float& getEndingRotation() const;

	bool getClockwise() const;
};