
#include "NormalInterruptor.h"
#include "Controller2WD.h"

Controller2WD controller = Controller2WD(740, 3.250, 13.4, 127, new NormalInterruptor());;

void setup()
{
}

void loop()
{
	for (int i = 0; i < 10; i++)
	{
		controller.Turn(180);
		delay(1000);
	}
	delay(5000);
}
