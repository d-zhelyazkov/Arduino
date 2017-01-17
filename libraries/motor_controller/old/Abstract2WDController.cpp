// 
// 
// 

#include "Abstract2WDController.h"

Abstract2WDController::Abstract2WDController()
{
	bMotor = new Motor(B_DIR, B_PWM, B_BRK);
	aMotor = new Motor(A_DIR, A_PWM, A_BRK);
	interruptor = NULL;
}

void Abstract2WDController::move()
{

	switch (steerDirection)
	{
	case SteerDirection::FORWARD:
		aMotor->Move(SpinDirection::FORW);
		bMotor->Move(SpinDirection::FORW);
		break;
	case SteerDirection::BACKWARD:
		aMotor->Move(SpinDirection::BACKW);
		bMotor->Move(SpinDirection::BACKW);
		break;
	case SteerDirection::LEFT:
		aMotor->Move(SpinDirection::BACKW);
		bMotor->Move(SpinDirection::FORW);
		break;
	case SteerDirection::RIGHT:
		aMotor->Move(SpinDirection::FORW);
		bMotor->Move(SpinDirection::BACKW);
		break;
	}

	if (interruptor != NULL)
	{
		unsigned int waitTime = interruptor->GetCheckTIme();
		while (!(interruptor->HasToInterrupt()))
			if (waitTime)
				delay(waitTime);

		stop();
	}
}

void Abstract2WDController::stop()
{
	bMotor->Stop();
	aMotor->Stop();
}

void Abstract2WDController::setInterruptor(AbstractInterruptor* interruptor) {
	this->interruptor = interruptor;
}

const char * getSteerDirectionStr(const SteerDirection diretion)
{
	switch (diretion)
	{
	case SteerDirection::FORWARD:
		return "FORWARD";
	case SteerDirection::BACKWARD:
		return "BACKWARD";
	case SteerDirection::LEFT:
		return "LEFT";
	case SteerDirection::RIGHT:
		return "RIGHT";
	}
}
