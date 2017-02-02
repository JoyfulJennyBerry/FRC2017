/*
 * DriveSystem.cpp
 */

#include "DriveSystem.h"
#include <Talon.h>

/**
 * Constructor for the DriveSystem that initializes the RobotDrive and InputMethod.
 *
 * @param input the pointer to the InputMethod to use.
 */
DriveSystem::DriveSystem(std::shared_ptr<InputMethod> input) : RobotSystem(input), currentRampForward(0) {
	drivetrain = std::make_unique<RobotDrive>(new Talon(1), new Talon(2), new Talon(3), new Talon(4));
}

DriveSystem::~DriveSystem() {

}

/**
 * Wrapper method for calling ArcadeDrive on the actual RobotDrive object for unit testing purposes.
 * 
 * @param forward the value for the forward power of the motors.
 * @param rotation the rotation value for motor power.
 * @param squared whether this should square rotation.
 */
void DriveSystem::drive(double forward, double rotation, bool squared) {
	drivetrain->ArcadeDrive(forward, rotation, squared);
}

/**
 * Allows one to control the drivetrain with forward input and sideways input.
 * Ramps the speed of the motors towards the desired input with a ramp constant, so that the motors do not draw too much current.
 *
 * @param desiredForwardValue the speed that the drivetrain should ramp towards when driving forward.
 * @param rotateValue the value that which the drivetrain should move sideways.
 * @param squared whether this should square the rotation value.
 */
void DriveSystem::arcadeControl(double desiredForwardValue, double rotateValue, bool squared) {
	if(desiredForwardValue != 0) {
		double change = desiredForwardValue - currentRampForward;
		//increments by ramp multiplier or sets it to the desiredRampForward if they are too close
		currentRampForward = abs(change) > MIN_INCREMENT ? currentRampForward + change * RAMP : desiredForwardValue;
	} else {
		currentRampForward = 0;
	}

	drive(currentRampForward, rotateValue, squared);
}

/**
 * Sets val to 0 if the absolute value of it is below 0.
 *
 */
void DriveSystem::modifyIfInDeadzone(double& val) {
	val = abs(val) <= DEADZONE ? 0 : val;
}

/**
 * Called by the teleopexecutor.
 * Gets input from the inputmethod and drives based on that input.
 */
void DriveSystem::run() {
	double desiredForwardValue = input->getForwardDistance();
	double desiredRotateValue = input->getSidewaysDistance();
	modifyIfInDeadzone(desiredForwardValue);
	modifyIfInDeadzone(desiredRotateValue);
	arcadeControl(desiredForwardValue, desiredRotateValue, true);
}


