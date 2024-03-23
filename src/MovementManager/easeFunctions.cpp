#pragma once
#include "easeFunctions.h"

std::map<easeFunctions::Tmovement_function, double(*)(double)>	easeFunctions::movement_functions = {
												{easeFunctions::Tmovement_function::LINEAR, linear},
												{easeFunctions::Tmovement_function::IN_SINE, inSine},
												{easeFunctions::Tmovement_function::OUT_SINE, outSine},
												{easeFunctions::Tmovement_function::IN_OUT_SINE, inOutSine},
												{easeFunctions::Tmovement_function::IN_QUAD, inQuad},
												{easeFunctions::Tmovement_function::OUT_QUAD, outQuad},
												{easeFunctions::Tmovement_function::IN_OUT_QUAD, inOutQuad},
												{easeFunctions::Tmovement_function::IN_CUBIC, inCubic},
												{easeFunctions::Tmovement_function::OUT_CUBIC, outCubic},
												{easeFunctions::Tmovement_function::IN_OUT_CUBIC, inOutCubic},
												{easeFunctions::Tmovement_function::IN_QUART, inQuart},
												{easeFunctions::Tmovement_function::OUT_QUART, outQuart},
												{easeFunctions::Tmovement_function::IN_OUT_QUART, inOutQuart},
												{easeFunctions::Tmovement_function::IN_QUINT, inQuint},
												{easeFunctions::Tmovement_function::OUT_QUINT, outQuint},
												{easeFunctions::Tmovement_function::IN_OUT_QUINT, inOutQuint},
												{easeFunctions::Tmovement_function::IN_EXPO, inExpo},
												{easeFunctions::Tmovement_function::OUT_EXPO, outExpo},
												{easeFunctions::Tmovement_function::IN_OUT_EXPO, inOutExpo},
												{easeFunctions::Tmovement_function::IN_CIRC, inCirc},
												{easeFunctions::Tmovement_function::OUT_CIRC, outCirc},
												{easeFunctions::Tmovement_function::IN_OUT_CIRC, inOutCirc},
												{easeFunctions::Tmovement_function::IN_BACK, inBack},
												{easeFunctions::Tmovement_function::OUT_BACK, outBack},
												{easeFunctions::Tmovement_function::IN_OUT_BACK, inOutBack},
												{easeFunctions::Tmovement_function::IN_ELASTIC, inElastic},
												{easeFunctions::Tmovement_function::OUT_ELASTIC, outElastic},
												{easeFunctions::Tmovement_function::IN_OUT_ELASTIC, inOutElastic},
												{easeFunctions::Tmovement_function::IN_BOUNCE, inBounce},
												{easeFunctions::Tmovement_function::OUT_BOUNCE, outBounce},
												{easeFunctions::Tmovement_function::IN_OUT_BOUNCE, inOutBounce}
};

std::map<easeFunctions::Tmovement_function, std::string> easeFunctions::easeFunctionNames = {
	{easeFunctions::Tmovement_function::LINEAR, "LINEAR"},
	{easeFunctions::Tmovement_function::IN_SINE, "IN_SINE"},
	{easeFunctions::Tmovement_function::OUT_SINE, "OUT_SINE"},
	{easeFunctions::Tmovement_function::IN_OUT_SINE, "IN_OUT_SINE"},
	{easeFunctions::Tmovement_function::IN_QUAD, "IN_QUAD"},
	{easeFunctions::Tmovement_function::OUT_QUAD, "OUT_QUAD"},
	{easeFunctions::Tmovement_function::IN_OUT_QUAD, "IN_OUT_QUAD"},
	{easeFunctions::Tmovement_function::IN_CUBIC, "IN_CUBIC"},
	{easeFunctions::Tmovement_function::OUT_CUBIC, "OUT_CUBIC"},
	{easeFunctions::Tmovement_function::IN_OUT_CUBIC, "IN_OUT_CUBIC"},
	{easeFunctions::Tmovement_function::IN_QUART, "IN_QUART"},
	{easeFunctions::Tmovement_function::OUT_QUART, "OUT_QUART"},
	{easeFunctions::Tmovement_function::IN_OUT_QUART, "IN_OUT_QUART"},
	{easeFunctions::Tmovement_function::IN_QUINT, "IN_QUINT"},
	{easeFunctions::Tmovement_function::OUT_QUINT, "OUT_QUINT"},
	{easeFunctions::Tmovement_function::IN_OUT_QUINT, "IN_OUT_QUINT"},
	{easeFunctions::Tmovement_function::IN_EXPO, "IN_EXPO"},
	{easeFunctions::Tmovement_function::OUT_EXPO, "OUT_EXPO"},
	{easeFunctions::Tmovement_function::IN_OUT_EXPO, "IN_OUT_EXPO"},
	{easeFunctions::Tmovement_function::IN_CIRC, "IN_CIRC"},
	{easeFunctions::Tmovement_function::OUT_CIRC, "OUT_CIRC"},
	{easeFunctions::Tmovement_function::IN_OUT_CIRC, "IN_OUT_CIRC"},
	{easeFunctions::Tmovement_function::IN_BACK, "IN_BACK"},
	{easeFunctions::Tmovement_function::OUT_BACK, "OUT_BACK"},
	{easeFunctions::Tmovement_function::IN_OUT_BACK, "IN_OUT_BACK"},
	{easeFunctions::Tmovement_function::IN_ELASTIC, "IN_ELASTIC"},
	{easeFunctions::Tmovement_function::OUT_ELASTIC, "OUT_ELASTIC"},
	{easeFunctions::Tmovement_function::IN_OUT_ELASTIC, "IN_OUT_ELASTIC"},
	{easeFunctions::Tmovement_function::IN_BOUNCE, "IN_BOUNCE"},
	{easeFunctions::Tmovement_function::OUT_BOUNCE, "OUT_BOUNCE"},
	{easeFunctions::Tmovement_function::IN_OUT_BOUNCE, "IN_OUT_BOUNCE"}
};

easeFunctions::easeFunctions() {}

// Linear
double easeFunctions::linear(double x)
{
	return x;
}

// Sine
inline double easeFunctions::inSine(double x)
{
	return 1.0 - cos((x * M_PI) / 2.0);
}

inline double easeFunctions::outSine(double x)
{
	return sin((x * M_PI) / 2.0);
}

inline double easeFunctions::inOutSine(double x)
{
	return -(cos(M_PI * x) - 1.0) / 2.0;
}

// Quad
inline double easeFunctions::inQuad(double x)
{
	return x * x;
}

inline double easeFunctions::outQuad(double x)
{
	return 1.0 - (1.0 - x) * (1.0 - x);
}

inline double easeFunctions::inOutQuad(double x)
{
	return x < 0.5 ? 2.0 * x * x : 1.0 - pow(-2.0 * x + 2.0, 2.0) / 2.0;
}

// Cubic
inline double easeFunctions::inCubic(double x)
{
	return x * x * x;
}

inline double easeFunctions::outCubic(double x)
{
	return 1.0 - pow(1.0 - x, 3.0);
}

inline double easeFunctions::inOutCubic(double x)
{
	return x < 0.5 ? 4.0 * x * x * x : 1.0 - pow(-2.0 * x + 2.0, 3.0) / 2.0;
}

// Quart
inline double easeFunctions::inQuart(double x)
{
	return x * x * x * x;
}

inline double easeFunctions::outQuart(double x)
{
	return 1.0 - pow(1.0 - x, 4.0);
}

inline double easeFunctions::inOutQuart(double x)
{
	return x < 0.5 ? 8.0 * x * x * x * x : 1.0 - pow(-2.0 * x + 2.0, 4.0) / 2.0;
}

// Quint
inline double easeFunctions::inQuint(double x)
{
	return x * x * x * x * x;
}

inline double easeFunctions::outQuint(double x)
{
	return 1.0 - pow(1.0 - x, 5.0);
}

inline double easeFunctions::inOutQuint(double x)
{
	return x < 0.5 ? 16.0 * x * x * x * x * x : 1.0 - pow(-2.0 * x + 2.0, 5.0) / 2.0;
}

// Expo
inline double easeFunctions::inExpo(double x)
{
	return x == 0.0 ? 0.0 : pow(2.0, 10.0 * x - 10.0);
}

inline double easeFunctions::outExpo(double x)
{
	return x == 1.0 ? 1.0 : 1.0 - pow(2.0, -10.0 * x);
}

inline double easeFunctions::inOutExpo(double x)
{
	return x == 0.0
		? 0.0
		: x == 1.0
		? 1.0
		: x < 0.5
		? pow(2.0, 20.0 * x - 10.0) / 2.0
		: (2.0 - pow(2.0, -20.0 * x + 10.0)) / 2.0;
}

// Circ
inline double easeFunctions::inCirc(double x)
{
	if (x <= 0.0) return 0.0;
	if (x >= 1.0) return 1.0;
	return 1.0 - sqrt(1.0 - pow(x, 2.0));
}

inline double easeFunctions::outCirc(double x)
{
	return sqrt(1.0 - pow(x - 1.0, 2.0));
}

inline double easeFunctions::inOutCirc(double x)
{
	return x < 0.5
		? (1.0 - sqrt(1.0 - pow(2.0 * x, 2.0))) / 2.0
		: (sqrt(1.0 - pow(-2.0 * x + 2.0, 2.0)) + 1.0) / 2.0;
}

// Back
inline double easeFunctions::inBack(double x)
{
	constexpr static double c1 = 1.70158;
	constexpr static double c3 = c1 + 1.0;

	return c3 * x * x * x - c1 * x * x;
}

inline double easeFunctions::outBack(double x)
{
	constexpr static double c1 = 1.70158;
	constexpr static double c3 = c1 + 1.0;

	return 1 + c3 * pow(x - 1.0, 3.0) + c1 * pow(x - 1.0, 2.0);
}

inline double easeFunctions::inOutBack(double x)
{
	constexpr static double c1 = 1.70158;
	constexpr static double c2 = c1 * 1.525;

	return x < 0.5
		? (pow(2.0 * x, 2.0) * ((c2 + 1.0) * 2.0 * x - c2)) / 2.0
		: (pow(2.0 * x - 2.0, 2.0) * ((c2 + 1.0) * (x * 2.0 - 2.0) + c2) + 2.0) / 2.0;
}

// Elastic
inline double easeFunctions::inElastic(double x)
{
	constexpr static double c4 = (2 * M_PI) / 3;

	return x == 0.0 ? 0.0 : (x == 1.0 ? 1.0 : -pow(2.0, 10.0 * x - 10.0) * sin((x * 10.0 - 10.75) * c4));
}

inline double easeFunctions::outElastic(double x)
{
	constexpr static double c4 = (2 * M_PI) / 3;

	return x == 0.0 ? 0.0 : (x == 1.0 ? 1.0 : pow(2.0, -10.0 * x) * sin((x * 10.0 - 0.75) * c4) + 1.0);
}

inline double easeFunctions::inOutElastic(double x)
{
	constexpr static double c5 = (2 * M_PI) / 4.5;

	return x == 0.0 ? 0.0 : (x == 1.0 ? 1.0 : x < 0.5
		? -(pow(2.0, 20.0 * x - 10.0) * sin((20.0 * x - 11.125) * c5)) / 2.0
		: (pow(2.0, -20.0 * x + 10.0) * sin((20.0 * x - 11.125) * c5)) / 2.0 + 1.0);
}

// Bounce
inline double easeFunctions::outBounce(double x)
{
	constexpr static double n1 = 7.5625;
	constexpr static double d1 = 2.75;

	if (x < 1.0 / d1)
		return n1 * x * x;
	else if (x < 2.0 / d1)
		return n1 * (x -= 1.5 / d1) * x + 0.75;
	else if (x < 2.5 / d1)
		return n1 * (x -= 2.25 / d1) * x + 0.9375;
	else
		return n1 * (x -= 2.625 / d1) * x + 0.984375;
}

inline double easeFunctions::inBounce(double x)
{
	return 1.0 - outBounce(1.0 - x);
}

inline double easeFunctions::inOutBounce(double x)
{
	return x < 0.5 ? (1.0 - outBounce(1.0 - 2.0 * x)) / 2.0 : (1.0 + outBounce(2.0 * x - 1.0)) / 2.0;
}