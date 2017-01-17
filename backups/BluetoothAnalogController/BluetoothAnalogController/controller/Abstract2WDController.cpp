// 
// 
// 

#include "Abstract2WDController.h"

Abstract2WDController::Abstract2WDController()
{
	leftMotor = Motor(B_DIR, B_PWM, B_BRK);
	rightMotor = Motor(A_DIR, A_PWM, A_BRK);
}

void Abstract2WDController::Move()
{
	StartMotors();
	if (interruptor != NULL)
	{
		unsigned int waitTime = interruptor->GetCheckTIme();
		do
		{
			delay(waitTime);
		} while (!(interruptor->HasToInterrupt()));
		Stop();
	}
}

void Abstract2WDController::Stop()
{
	leftMotor.Stop();
	rightMotor.Stop();
}
