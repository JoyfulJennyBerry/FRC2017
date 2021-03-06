#ifndef TEST_TESTINPUTMETHOD_H_
#define TEST_TESTINPUTMETHOD_H_

#include "../src/input/InputMethod.h"

class TestInputMethod : public InputMethod {
public:
	TestInputMethod();
	virtual ~TestInputMethod();
	virtual double getForwardDistance();
	virtual double getSidewaysDistance();
	virtual bool toggleDrive();

	virtual bool shootToggle();

	virtual bool intake();
	virtual bool outtake();

	virtual bool toggleBlockHolder();
	virtual bool toggleLever();
    
    void setLeverToggle(bool toggle);
    void setBlockHolderToggle(bool toggle);

	void setDesiredForward(float val);
	void setFinished(bool finished);
	bool isFinished();
private:
	float desiredForwardVal;
	bool finished;
    bool toggleLeverSystem;
    bool toggleBlockSystem;
};

#endif
