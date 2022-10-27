#include "pch.h"
#include "BezierGenerator.h"

#include "constants.h"
#include <iostream>

#include "constants.h"
#include "utils.h"

using namespace bezierUtils;

Bezier bezierUtils::CalculateBezier(Vector2f pointA, Vector2f pointB, Vector2f pointC, Vector2f pointD)
{
	std::vector<Vector2f> bezierPoints = std::vector<Vector2f>(BEZIER_STEPS_AMOUNT);
	Vector2f AB_Lerp{};
	Vector2f BC_Lerp{};
	Vector2f CD_Lerp{};
	Vector2f AB_BC_Lerp{};
	Vector2f BC_CD_Lerp{};
	Vector2f curvePoint{};

	for (int i{}; i < BEZIER_STEPS_AMOUNT; i++)
	{
		const float multiplier{ (1.f / (BEZIER_STEPS_AMOUNT-1)) * i };
		//the lerps for the first 3 lines
		AB_Lerp = Lerp(pointA, pointB, multiplier);
		BC_Lerp = Lerp(pointB, pointC, multiplier);
		CD_Lerp = Lerp(pointC, pointD, multiplier);
		//the lerps for the 2 created lines
		AB_BC_Lerp = Lerp(AB_Lerp, BC_Lerp, multiplier);
		BC_CD_Lerp = Lerp(BC_Lerp, CD_Lerp, multiplier);
		//the point of the curve
		curvePoint = Lerp(AB_BC_Lerp, BC_CD_Lerp, multiplier);
		bezierPoints[i] = curvePoint;
	}

	return Bezier{ bezierPoints };
}

Bezier bezierUtils::CalculateBezier(BezierData data)
{
	return CalculateBezier(data.a, data.b, data.c, data.d);
}

float bezierUtils::Lerp(float a, float b, float multiplier)
{
	return a + (b - a) * multiplier;
}

Vector2f bezierUtils::Lerp(Vector2f a, Vector2f b, float multiplier)
{
	const float x = Lerp(a.x, b.x, multiplier);
	const float y = Lerp(a.y, b.y, multiplier);
	return Vector2f{ x,y };
}

FlightPath bezierUtils::CalculateFlightPath(FlightPathData flightPathData)
{
	std::vector<Bezier> beziers{ flightPathData.data.size() };
	for(int i{ 0 }; i < flightPathData.data.size(); ++i)
	{
		beziers[i] = CalculateBezier(flightPathData.data[i]);
	}

	constexpr float scaleX{ g_WindowWidth / FlightPathData::size };
	constexpr float scaleY{ g_WindowHeight / FlightPathData::size };

	std::vector<Vector2f> combinedPoints{};
	for (int i{ 0 }; i < flightPathData.data.size(); ++i)
	{
		std::vector<Vector2f>& currentPoints{ beziers[i].curvePoints };
		combinedPoints.insert(combinedPoints.end(), currentPoints.begin(), currentPoints.end());
	}

	std::cout << "Len: " << combinedPoints.size() << std::endl;

	return FlightPath{ combinedPoints };
}


void bezierUtils::DrawBezier(Bezier bezier, float lineWidth)
{
	for (int i{}; i < BEZIER_STEPS_AMOUNT - 1; i++)
	{
		utils::DrawLine(bezier.curvePoints[i].ToPoint2f(), bezier.curvePoints[i + 1].ToPoint2f(), lineWidth);
	}
}

void bezierUtils::FillBezier(Bezier bezier)
{
	std::vector<Point2f> converted{bezier.curvePoints.size()};
	for(int i{}; i < bezier.curvePoints.size(); ++i)
	{
		converted[i] = bezier.curvePoints[i].ToPoint2f();
	}

	utils::FillPolygon(converted);
}

void bezierUtils::DrawFlightPath(FlightPath path, int lineWidth)
{
	constexpr float scaleX{ g_WindowWidth / FlightPathData::size };
	constexpr float scaleY{ g_WindowHeight / FlightPathData::size };

	for (int i{}; i < path.combinedBezierPoints.size() - 1; i++)
	{
		utils::DrawLine((path.combinedBezierPoints[i] * scaleX).ToPoint2f(), (path.combinedBezierPoints[i + 1] * scaleY).ToPoint2f(), static_cast<float>(lineWidth));
	}
}
