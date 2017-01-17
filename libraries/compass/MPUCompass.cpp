#include "MPUCompass.h"
#include "Wire.h"

bool dmpReady = false;  // set true if DMP init was successful
uint16_t packetSize;	// expected DMP packet size (default is 42 bytes)

MPUCompass::MPUCompass()
{
	mpu = new MPU6050();

	// join I2C bus (I2Cdev library doesn't do this automatically)
	Wire.begin();
	TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)

			   // initialize device
	Serial.println("Initializing I2C devices...");
	mpu->initialize();

	// verify connection
	Serial.println("Testing device connections...");
	Serial.println(mpu->testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

	// load and configure the DMP
	Serial.println("Initializing DMP...");
	uint8_t devStatus = mpu->dmpInitialize();

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu->setXGyroOffset(220);
	mpu->setYGyroOffset(76);
	mpu->setZGyroOffset(-85);
	mpu->setZAccelOffset(1788); // 1688 factory default for my test chip

	// make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		Serial.println("Enabling DMP...");
		mpu->setDMPEnabled(true);

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		Serial.println("DMP ready! Waiting for first interrupt...");
		dmpReady = true;
		// get expected DMP packet size for later comparison
		packetSize = mpu->dmpGetFIFOPacketSize();
		Serial.print("packet size: "); Serial.println(packetSize);
	}
	else {
		// ERROR!
		// 1 = initial memory load failed
		// 2 = DMP configuration updates failed
		// (if it's going to break, usually the code will be 1)
		Serial.print("DMP Initialization failed (code ");
		Serial.print(devStatus);
		Serial.println(")");
	}


}


MPUCompass::~MPUCompass()
{
	delete(mpu);
}

float MPUCompass::getDirectionInRadians()
{
	if (!dmpReady) return 0.0f;

	//Serial.print("FIFO: "); Serial.println(mpu->getFIFOCount());
	if (mpu->getFIFOCount() == 1024)
		mpu->resetFIFO();
	//Serial.print("FIFO: "); Serial.println(mpu->getFIFOCount());
	while (mpu->getFIFOCount() < packetSize);
	//Serial.print("FIFO: "); Serial.println(mpu->getFIFOCount());

	// read a packet from FIFO
	uint8_t fifoBuffer[64];		// FIFO storage buffer
	mpu->getFIFOBytes(fifoBuffer, packetSize);

	Quaternion q;           // [w, x, y, z]         quaternion container
	mpu->dmpGetQuaternion(&q, fifoBuffer);

	float buf = q.x;
	q.x = q.y;
	q.y = buf;

	float euler[3];         // [psi, theta, phi]    Euler angle container
	mpu->dmpGetEuler(euler, &q);

	return euler[0];
}
