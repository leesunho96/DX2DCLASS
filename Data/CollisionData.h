#pragma once

class Marker;
class Line;

class CollisionData
{
public:
	CollisionData(vector<Marker*> markers, vector<Line*> lines);
	~CollisionData();
public:
	vector<Marker*> marker;
	vector<Line*> line;
};

