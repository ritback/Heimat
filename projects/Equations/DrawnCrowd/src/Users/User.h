#pragma once

#include "ofMain.h"
#include "Flock/DrawnPerson.h"

class User : public DrawnPerson
{
public:
	User(ofPoint inPoint);
	virtual ~User();

public:
	virtual void render() override;
    virtual void updatePosition() override;

public:
	void updatePositionAndVelocity(ofPoint inPos);
	ofPoint getPos();
};

