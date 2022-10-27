#include "pch.h"
#include "EnemyPaths.h"
#include "Vector2f.h"

std::vector<bezierUtils::FlightPath> GetEnemyPaths()
{
	std::vector<bezierUtils::FlightPath> enemyPaths;
	enemyPaths.push_back(CalculateFlightPath(bezierUtils::FlightPathData{
		{
			bezierUtils::BezierData{ Vector2f{0, 1}, Vector2f{2.66f, 1.5f}, Vector2f{8, 3}, Vector2f{8, 5} },
			bezierUtils::BezierData{ Vector2f{8, 5}, Vector2f{8, 8}, Vector2f{8, 8}, Vector2f{7, 8} },
			bezierUtils::BezierData{ Vector2f{7, 8}, Vector2f{6, 8}, Vector2f{6, 8}, Vector2f{6, 6.5f} },
			bezierUtils::BezierData{ Vector2f{6, 6.5f}, Vector2f{6, 5}, Vector2f{6, 5}, Vector2f{7, 5} },
			bezierUtils::BezierData{ Vector2f{7, 5}, Vector2f{8, 5}, Vector2f{9.33f, 6}, Vector2f{10, 8} },
		}
	}));
	enemyPaths.push_back(CalculateFlightPath(bezierUtils::FlightPathData{
		{
			bezierUtils::BezierData{ Vector2f{10, 1}, Vector2f{7.33f, 1.5f}, Vector2f{2, 3}, Vector2f{2, 5} },
			bezierUtils::BezierData{ Vector2f{2, 5}, Vector2f{2, 8}, Vector2f{2, 8}, Vector2f{3, 8} },
			bezierUtils::BezierData{ Vector2f{3, 8}, Vector2f{4, 8}, Vector2f{4, 8}, Vector2f{4, 6.5f} },
			bezierUtils::BezierData{ Vector2f{4, 6.5f}, Vector2f{4, 5}, Vector2f{4, 5}, Vector2f{3, 5} },
			bezierUtils::BezierData{ Vector2f{3, 5}, Vector2f{2, 5}, Vector2f{0.66f, 6}, Vector2f{0, 8} },
		}
	}));
	enemyPaths.push_back(CalculateFlightPath(bezierUtils::FlightPathData{
		{
			bezierUtils::BezierData{ Vector2f{5.5, 10}, Vector2f{6, -6}, Vector2f{-4, 4}, Vector2f{10, 6.5f} },
		}
	}));
	enemyPaths.push_back(CalculateFlightPath(bezierUtils::FlightPathData{
		{
			bezierUtils::BezierData{ Vector2f{4.5, 10}, Vector2f{4, -6}, Vector2f{14, 4}, Vector2f{0, 6.5f} },
		}
	}));
	return enemyPaths;
}

