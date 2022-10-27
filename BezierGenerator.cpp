#include "pch.h"
#include "BezierGenerator.h"
#include "utils.h"

using namespace bezierUtils;

Bezier bezierUtils::CalculateBezier(Point2f pointA, Point2f pointB, Point2f pointC, Point2f pointD)
{
	std::vector<Point2f> calculatedBezier = std::vector<Point2f>(BEZIER_STEPS_AMOUNT);
	Point2f AB_Lerp{};
	Point2f BC_Lerp{};
	Point2f CD_Lerp{};
	Point2f AB_BC_Lerp{};
	Point2f BC_CD_Lerp{};
	Point2f curvePoint{};

	for (int i{}; i < BEZIER_STEPS_AMOUNT; i++)
	{
		const float multiplier{ (1.f / BEZIER_STEPS_AMOUNT) * i };
		//the lerps for the first 3 lines
		AB_Lerp = Lerp(pointA, pointB, multiplier);
		BC_Lerp = Lerp(pointB, pointC, multiplier);
		CD_Lerp = Lerp(pointC, pointD, multiplier);
		//the lerps for the 2 created lines
		AB_BC_Lerp = Lerp(AB_Lerp, BC_Lerp, multiplier);
		BC_CD_Lerp = Lerp(BC_Lerp, CD_Lerp, multiplier);
		//the point of the curve
		curvePoint = Lerp(AB_BC_Lerp, BC_CD_Lerp, multiplier);
		calculatedBezier[i] = curvePoint;
	}
	Bezier solution{};
	solution.curvePoints = calculatedBezier;
	return solution;
}

float bezierUtils::Lerp(float a, float b, float multiplier)
{
	return (a + (b - a) * multiplier);
}

Point2f bezierUtils::Lerp(Point2f a, Point2f b, float multiplier)
{
	float x = Lerp(a.x, b.x, multiplier);
	float y = Lerp(a.y, b.y, multiplier);
	return Point2f{ x,y };
}


void bezierUtils::DrawBezier(Bezier bezier, float lineWidth)
{
	for (int i{}; i < BEZIER_STEPS_AMOUNT - 1; i++)
	{
		utils::DrawLine(bezier.curvePoints[i], bezier.curvePoints[i + 1], lineWidth);
	}
}

void bezierUtils::FillBezier(Bezier bezier)
{
	utils::FillPolygon(bezier.curvePoints);
}
