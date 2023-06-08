#pragma once
#include <math.h>
#include "../../include/CUserCmd.h"
namespace autostrafer
{
	static bool direction = 0;
	static int count = 0;
	float AngleDelta(float velocity);
	float NormalizeAngle(float angle);
	float Velocity(float x, float y);
	void Strafe(CUserCmd* cmd, float velx, float vely);
}