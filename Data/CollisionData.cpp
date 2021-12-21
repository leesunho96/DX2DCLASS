#include "stdafx.h"
#include "CollisionData.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"

CollisionData::CollisionData(vector<Marker*> markers, vector<Line*> lines) : marker(markers), line(lines)
{
}
