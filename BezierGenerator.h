#pragma once
#include <vector>

#include "Vector2f.h"

namespace bezierUtils
{
	constexpr int BEZIER_STEPS_AMOUNT{ 101 };

	struct Bezier
	{
		std::vector<Vector2f> curvePoints = std::vector<Vector2f>(BEZIER_STEPS_AMOUNT);
	};

	struct FlightPath
	{
		std::vector<Bezier> paths;
		float pathWidth{}, pathHeight{}, windowWidth{}, windowHeight{}, xScaling{}, yScaling{};
	};

	Bezier CalculateBezier(Vector2f pointA, Vector2f pointB, Vector2f pointC, Vector2f pointD);
	float Lerp(float a, float b, float multiplier);
	Vector2f Lerp(Vector2f a, Vector2f b, float multiplier);
	void DrawBezier(Bezier bezier, float lineWidth);
	void FillBezier(Bezier bezier);
}
