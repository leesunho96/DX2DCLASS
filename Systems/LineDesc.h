#pragma once
#include "stdafx.h"
#include "Objects/Marker.h"
#include "Objects/Line.h"


class LineDesc
{
public:
	vector<Line*> lines;
	vector<Marker*> Markers;
};
