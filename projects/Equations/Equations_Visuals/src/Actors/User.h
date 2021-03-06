#pragma once

#include "ofMain.h"
#include "Actor.h"

class User : public Actor
{
public:
	User(ofPoint inPoint);
	virtual ~User();

public:
	virtual void render() override;

public:
	void updatePositionAndVelocity(ofPoint inPos);
};

