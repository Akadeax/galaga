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

	struct BezierData
	{
		Vector2f a{}, b{}, c{}, d{};
	};

	struct FlightPath
	{
		std::vector<Vector2f> combinedBezierPoints{};
	};

	struct FlightPathData
	{
		static constexpr float size{ 10.f };
		std::vector<BezierData> data{};
	};

	Bezier CalculateBezier(Vector2f pointA, Vector2f pointB, Vector2f pointC, Vector2f pointD);
	Bezier CalculateBezier(BezierData data);

	FlightPath CalculateFlightPath(FlightPathData flightPathData);

	void DrawBezier(Bezier bezier, float lineWidth);
	void FillBezier(Bezier bezier);
	void DrawFlightPath(FlightPath path, int lineWidth = 1);

	float Lerp(float a, float b, float t);
	Vector2f Lerp(Vector2f a, Vector2f b, float t);
}
