#include "stdafx.h"
#include "CollisionData.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"

CollisionData::CollisionData(vector<Marker*> markers, vector<Line*> lines) : marker(markers), line(lines)
{
}

CollisionData::~CollisionData()
{
	for (auto a : line)
	{
		SAFE_DELETE(a);
	}
	for (auto a : marker)
	{
		SAFE_DELETE(a);
	}
}
