#pragma once

class Marker;
class Line;

class CollisionData
{
public:
	CollisionData(vector<Marker*> markers, vector<Line*> lines);
public:
	vector<Marker*> marker;
	vector<Line*> line;
};

