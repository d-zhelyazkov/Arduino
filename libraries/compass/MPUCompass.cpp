#include "MPUCompass.h"
#include "Wire.h"
#include "Interrupt.h"

#define INT_FIFO_OVERFLOW 0x10
#define INT_DMP_DATA_READY 0x02

#define FIFO_SIZE 1024


bool dmpReady = false;  // set true if DMP init was successful
uint16_t packetSize;	// expected DMP packet size (default is 42 bytes)
uint8_t fifoBuffer[64];		// FIFO storage buffer
// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

byte interruptPin;
bool initialized = false;

class MPUInterrupt : public Interrupt{
public:
	MPUInterrupt() : Interrupt(interruptPin, ONRISING) {}

	void interruptServiceRoutine() {
		if (!dmpReady) return;

		byte mpuIntStatus = mpu.getIntStatus();
		// check for overflow (this should never happen unless our code is too inefficient)
		if ((mpuIntStatus & INT_FIFO_OVERFLOW) || mpu.getFIFOCount() == FIFO_SIZE) {
			// reset so we can continue cleanly
			mpu.resetFIFO();
			Serial.println("FIFO overflow!");

		}
		// otherwise, check for DMP data ready interrupt (this should happen frequently)
		else if (mpuIntStatus & INT_DMP_DATA_READY) {
			// wait for correct available data length, should be a VERY short wait
			while (mpu.getFIFOCount() < packetSize);

			// read a packet from FIFO
			mpu.getFIFOBytes(fifoBuffer, packetSize);
		}
	}
} mpuInterrupt;


void mpuInitialize() {

	if (initialized)
		return;

	// join I2C bus (I2Cdev library doesn't do this automatically)
	Wire.begin();
	TWBR = 24; // 400kHz I2C clock (200kHz if CPU is 8MHz)

			   // initialize device
	Serial.println("Initializing I2C devices...");
	mpu.initialize();

	// verify connection
	Serial.println("Testing device connections...");
	Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

	// load and configure the DMP
	Serial.println("Initializing DMP...");
	uint8_t devStatus = mpu.dmpInitialize();

	// supply your own gyro offsets here, scaled for min sensitivity
	mpu.setXGyroOffset(220);
	mpu.setYGyroOffset(76);
	mpu.setZGyroOffset(-85);
	mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

							   // make sure it worked (returns 0 if so)
	if (devStatus == 0) {
		// turn on the DMP, now that it's ready
		Serial.println("Enabling DMP...");
		mpu.setDMPEnabled(true);

		// set our DMP Ready flag so the main loop() function knows it's okay to use it
		Serial.println("DMP ready!");
		dmpReady = true;
		// get expected DMP packet size for later comparison
		packetSize = mpu.dmpGetFIFOPacketSize();
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

	initialized = true;
}

MPUCompass::MPUCompass(byte intPin) 
{
	interruptPin = intPin;
	mpuInitialize();
}


MPUCompass::~MPUCompass()
{
	stopListening();
}

void MPUCompass::startListening()
{
	if (!dmpReady)
		return;

	// enable Arduino interrupt detection
	Serial.println("Enabling interrupt detection ...");
	attachInterrupt(&mpuInterrupt);
}

void MPUCompass::stopListening()
{
	deattachInterrupt(&mpuInterrupt);
}

float MPUCompass::getDirectionInRadians()
{
	Quaternion q;           // [w, x, y, z]         quaternion container
	mpu.dmpGetQuaternion(&q, fifoBuffer);

	float buf = q.x;
	q.x = q.y;
	q.y = buf;

	float euler[3];         // [psi, theta, phi]    Euler angle container
	mpu.dmpGetEuler(euler, &q);

	return euler[0];
}
