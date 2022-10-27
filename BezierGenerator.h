#pragma once
#include <vector>

namespace bezierUtils
{
	constexpr int BEZIER_STEPS_AMOUNT{ 101 };

	struct Bezier
	{
		std::vector<Point2f> curvePoints = std::vector<Point2f>(BEZIER_STEPS_AMOUNT);
	};

	struct FlightPath
	{
		std::vector<Bezier> paths;
		float pathWidth{}, pathHeight{}, windowWidth{}, windowHeight{}, xScaling{}, yScaling{};
		int usedPaths{};
	};

	Bezier CalculateBezier(Point2f pointA, Point2f pointB, Point2f pointC, Point2f pointD);
	float Lerp(float a, float b, float multiplier);
	Point2f Lerp(Point2f a, Point2f b, float multiplier);
	void DrawBezier(Bezier bezier, float lineWidth);
	void FillBezier(Bezier bezier);
}