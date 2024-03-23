#pragma once
#define _USE_MATH_DEFINES
#include <string>
#include <math.h>
#include <map>

class easeFunctions
{
private:
	// Constructors / Destructors
	easeFunctions();

	constexpr static size_t m_functionCount = 31;

	// Linear
	static double linear(double x);

	// Sine
	static double inSine(double x);
	static double outSine(double x);
	static double inOutSine(double x);

	// Quad
	static double inQuad(double x);
	static double outQuad(double x);
	static double inOutQuad(double x);

	// Cubic
	static double inCubic(double x);
	static double outCubic(double x);
	static double inOutCubic(double x);

	// Quart
	static double inQuart(double x);
	static double outQuart(double x);
	static double inOutQuart(double x);

	// Quint
	static double inQuint(double x);
	static double outQuint(double x);
	static double inOutQuint(double x);

	// Expo
	static double inExpo(double x);
	static double outExpo(double x);
	static double inOutExpo(double x);

	// Circ
	static double inCirc(double x);
	static double outCirc(double x);
	static double inOutCirc(double x);

	// Back
	static double inBack(double x);
	static double outBack(double x);
	static double inOutBack(double x);

	// Elastic
	static double inElastic(double x);
	static double outElastic(double x);
	static double inOutElastic(double x);

	// Bounce
	static double outBounce(double x);
	static double inBounce(double x);
	static double inOutBounce(double x);

public:
	enum Tmovement_function : int {
		LINEAR,
		IN_SINE,
		OUT_SINE,
		IN_OUT_SINE,
		IN_QUAD,
		OUT_QUAD,
		IN_OUT_QUAD,
		IN_CUBIC,
		OUT_CUBIC,
		IN_OUT_CUBIC,
		IN_QUART,
		OUT_QUART,
		IN_OUT_QUART,
		IN_QUINT,
		OUT_QUINT,
		IN_OUT_QUINT,
		IN_EXPO,
		OUT_EXPO,
		IN_OUT_EXPO,
		IN_CIRC,
		OUT_CIRC,
		IN_OUT_CIRC,
		IN_BACK,
		OUT_BACK,
		IN_OUT_BACK,
		IN_ELASTIC,
		OUT_ELASTIC,
		IN_OUT_ELASTIC,
		IN_BOUNCE,
		OUT_BOUNCE,
		IN_OUT_BOUNCE
	};

	static std::map<easeFunctions::Tmovement_function, double(*)(double)> movement_functions;

	static Tmovement_function getTmovement(const size_t id) {
		if (id >= m_functionCount) {
			printf("ERROR: easeFunctions::getFunction - id out of range\n");
			return Tmovement_function::IN_SINE;
		}
		else
			return static_cast<Tmovement_function>(id);
	}

	static double(*getFunction(const size_t id))(double) {
		if (id >= m_functionCount) {
			printf("ERROR: easeFunctions::getFunction - id out of range\n");
			return movement_functions[easeFunctions::getTmovement(0)];
		}
		else
			return movement_functions[easeFunctions::getTmovement(id)];
	}

	static double(*getFunction(const easeFunctions::Tmovement_function Tfunction))(double) {
		return movement_functions[Tfunction];
	}

	static std::string getFunctionName(const easeFunctions::Tmovement_function Tfunction) {
		return easeFunctionNames[Tfunction];
	}

	static std::string getFunctionName(const size_t id) {
		return easeFunctionNames[easeFunctions::getTmovement(id)];
	}

private:
	static std::map<easeFunctions::Tmovement_function, std::string> easeFunctionNames;
};
