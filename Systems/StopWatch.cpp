#include "stdafx.h"
#include "StopWatch.h"

StopWatch::StopWatch()
{
}

StopWatch::~StopWatch()
{
}

void StopWatch::Update()
{
	if (isOver)
		return;
	if(Timer->Elapsed() < 10.0f)
		present_Time += Timer->Elapsed();
	if (present_Time >= max_Time)
		isOver = true;
}

bool StopWatch::IsOver()
{
	return isOver;
}

bool StopWatch::IsOver(float inputtime)
{
	return present_Time >= inputtime ? true : false;
}
