#pragma once

/*!
\file World.h
*/

#include <Box2D/Box2D.h>
#include <iostream>

using namespace std;

#define DEGTORAD	0.0174532925199432957f
#define RADTODEG	57.295779513082320876f
#define PI			3.141592654

#define B2UP	b2Vec2(0.f, -1.f)
#define B2DOWN	b2Vec2(0.f, 1.f)
#define B2LEFT	b2Vec2(-1.f, 0.f)
#define B2RIGHT	b2Vec2(1.f, 0.f)

const static float zoomInFactor = 0.9f;
const static float zoomOutFactor = 1.f / zoomInFactor;