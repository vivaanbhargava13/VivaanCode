using namespace vex;

extern brain Brain;

// VEXcode devices
extern inertial gyroo;
extern motor intake;
extern motor catapult;
extern digital_out horizontal;
extern digital_out intakepistonb;
extern digital_out vertical;
extern controller Controller1;
extern rotation RotationRight;
extern rotation RotationLeft;
extern optical Opticall;
extern motor backleft;
extern motor middleleft;
extern motor frontleft;
extern motor backright;
extern motor middleright;
extern motor frontright;
extern motor cata2;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );