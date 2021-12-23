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
	present_Time += Timer->Elapsed();
	if (present_Time >= max_Time)
		isOver = true;
}

bool StopWatch::IsOver()
{
	return isOver;
}
