#define _USE_MATH_DEFINES
#include "autostrafer.h"
#include <math.h>
#include "../../include/CUserCmd.h"

float autostrafer::AngleDelta(float velocity)
{
	return (180 / M_PI) * atan(30 / velocity);
}
float autostrafer::NormalizeAngle(float x)
{
	x = fmod(x + 180, 360);
	if (x < 0)
		x += 360;
	return x - 180;
}
float autostrafer::Velocity(float x, float y)
{
	return sqrt(x*x + y*y);
}
void autostrafer::Strafe(CUserCmd *cmd, float velx, float vely)
{
	float vel = Velocity(velx, vely);
	//if(count > 50)
	//{
	//	direction = !direction;
	//	count = 0;
	//}
	cmd->viewangles.y = NormalizeAngle(cmd->viewangles.y  + (AngleDelta(vel)));
	if (direction)
	{
		cmd->sidemove = 400;
	}
	else
	{
		cmd->sidemove = -400;
	}
	count++;
}
