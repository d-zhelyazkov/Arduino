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
	startMotors();
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
