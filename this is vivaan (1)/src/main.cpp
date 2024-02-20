// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// gyroo                inertial      6               
// intake               motor         15              
// catapult             motor         4               
// horizontal           digital_out   G               
// intakepistonb        digital_out   B               
// vertical             digital_out   H               
// Controller1          controller                    
// RotationRight        rotation      21              
// RotationLeft         rotation      3               
// Opticall             optical       2               
// backleft             motor         17              
// middleleft           motor         16              
// frontleft            motor         12              
// backright            motor         18              
// middleright          motor         13              
// frontright           motor         1               
// cata2                motor         19              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "functions.h"

using namespace vex;

// A global instance of competition
competition Competition;

// reform of old function
void forwardPIDD(int setpoint, int speed) {
  backleft.setPosition(0,degrees);
  float input = backleft.position(degrees);
  float power;
  float kP = 0.14 * (.01 * speed);
  // float kI = 0.0002;
  float kD = 0.5;
  
  float error = setpoint - input;
  // float integral = 0;
  float derivative = 0;
  float prevError = 0;
  
  float i = 1;
  while (abs(error) > i) {
    input = backleft.position(degrees);
    error = setpoint - input;
      float P = kP * error;
        // integral += error;
      // float I = kI * integral;
        derivative = error - prevError;
      float D = kD * derivative;
      power = P + D; 
  
    frontleft.spin(forward, power, pct);
    frontright.spin(forward, power, pct);
    middleleft.spin(forward, power, pct);
    middleright.spin(forward, power, pct);
    backleft.spin(forward, power, pct);
    backright.spin(forward, power, pct);
    prevError = error;
    wait(10, msec);
  }
    stopBase(); // Stop the drivetrain when the loop exits
}

void curvePID(int setpoint, int speedLeft, int speedRight) {
  backleft.setPosition(0,degrees);
  float input = backleft.position(degrees);
  float rightpower;
  float leftpower;
  float lkP = 0.14 * (.01 * speedLeft);
  float rkP = 0.14 * (.01 * speedRight);
  // float kI = 0.0002;
  float kD = 0.5;
  
  float error = setpoint - input;
  // float integral = 0;
  float derivative = 0;
  float prevError = 0;
  
  float i = 1;
  while (abs(error) > i) {
    input = backleft.position(degrees);
    error = setpoint - input;
      float lP = lkP * error*(0.5625);
      float rP = rkP * error*(0.5625);
      // integral += error;
      // float I = kI * integral;
      derivative = error - prevError;
      float D = kD * derivative;
      rightpower = rP + D; 
      leftpower = lP + D;
  
    frontleft.spin(forward, leftpower, pct);
    frontright.spin(forward, rightpower, pct);
    middleleft.spin(forward, leftpower, pct);
    middleright.spin(forward, rightpower, pct);
    backleft.spin(forward, leftpower, pct);
    backright.spin(forward, rightpower, pct);
    prevError = error;  
    wait(10, msec);
  }
    stopBase(); // Stop the drivetrain when the loop exits
}


void sensordisplays () {
  while (true) {
    // Brain.Screen.printAt(15, 15, "%f", RotationRight.position(degrees));
    // Brain.Screen.printAt(30, 30, "%f", RotationLeft.position(degrees));
    // Brain.Screen.printAt(45, 45, "%f", gyroo.heading(degrees));
    // Brain.Screen.printAt(60, 60, "Hue: %.2f", Opticall.hue());
    wait(10,msec);
    Brain.Screen.clearScreen();
  }
}

void clearmotors () {
  frontleft.resetPosition();
  frontright.resetPosition();
  backleft.resetPosition();
  backright.resetPosition();
  middleleft.resetPosition();
  middleright.resetPosition();
}

void clearall() {
  clearmotors();
  gyroo.resetHeading();
  RotationLeft.resetPosition();
  RotationRight.resetPosition();
}

void sWings(int setpoint) {
  horizontal.set(setpoint);
}

void vWings(int setpoint) {
  vertical.set(setpoint);
}

void punch(){
  while(true){
    while (Controller1.ButtonY.pressing()) {
      catapult.spin(forward, 83, pct);
      cata2.spin(forward, 83, pct);
    }  
    catapult.stop(hold);
    cata2.stop(hold);
  }
}

void pre() {
  clearall();
  // thread d(autofire);
  //Controller1.Screen.setCursor(2,2);
  //Controller1.Screen.print("Calibrating sensors...");
  gyroo.calibrate();
  wait(2.5, seconds);
  //Controller1.Screen.setCursor(2,2);
  //Controller1.Screen.print("      We're live!       ");
  wait(2, seconds);
  //Controller1.Screen.setCursor(2,2);
  //Controller1.Screen.print("      Go Luca !!!       ");
}

// void offensive() {
//   // start in the centre of the middle start tile w/ preload
  
//   forwardPIDD(2000, 100);
//   turnPID(-90, 90, -1);
//     clearmotors();
  
//   // score
//   intake.spin(reverse, 100, pct);
//   forwardPIDD(105, 100);
//     wait(.01, sec);

//   // collect triball a
//   forwardPIDD(-300, 100);
//   clearmotors();
//   turnPID(-5, 90, -1);
//     clearmotors();
//   intake.spin(forward, 100, pct);
//   forwardPIDD(350, 100);
//     clearmotors();
//     wait(.05, sec);

//   // score
//   forwardPIDD(-350, 100);
//     clearmotors();
//   turnPID(-90, 90, -1);
//     clearmotors();
//     intake.spin(reverse, 100, pct);
//   forwardPIDD(500, 95);
//     wait(.05, sec);
//     clearmotors();

//   // collect triball b
//   forwardPIDD(-1050, 100);
//     clearmotors();
//   turnPID(0, 90, -1);
//     clearmotors();
//   intake.spin(forward, 100, pct);
//   forwardPIDD(200, 100);
//     wait(.1, sec);
//     clearmotors();
  
//   // score
//   forwardPIDD(-200, 100);
//     clearmotors();
//   turnPID(-90, 90, -1);
//     clearmotors();
//   intake.spin(reverse, 100, pct);
//   forwardPIDD(1050, 100);
//     wait(.05, sec);
//     intake.stop();
//     clearmotors();

//   // get triball c
//   forwardPIDD(-200, 100); 
//     clearmotors();
//   turnPID(95, 85, -1);
//     clearmotors();
//     intake.spin(forward, 100, pct);
//   forwardPIDD(1000, 100);
//     clearmotors();
  
//   // score
//   // forwardPIDD(-1000, 95);
//   //   clearmotors();
//   // turnPID(0, 85, -1);
//   //   clearmotors();
//   // intake.spin(reverse, 100, pct);
//   // forwardPIDD(200, 100);
//   //   clearmotors();
//   //   wait(.2, sec);

//   //attack bar
//   forwardPIDD(-200, 100);
//   turnPID(100, 85, -1);
//   forwardPIDD(-1500, 100);
//   //end
// }


void vivaanOff(){
  sWings(true);
  wait(1, sec);
  sWings(false);
  forwardPIDD(1920, 100);
  intake.spin(forward, 100, pct);
  forwardPIDD(200, 100);
  wait(150, msec);
  turnPID(-100, 100, -1);
  gyroo.setHeading(-90, degrees);
  intake.stop();
  wait(10, msec);
  intake.spin(reverse, 100, pct);
  wait(150, msec);
  forwardPIDD(350, 100);
  forwardPIDD(-100, 100);
  intake.stop();
  turnPID(98, 100, -1);
  intake.spin(forward, 100, pct);
  forwardPIDD(1200, 100);
  wait(100, msec);


  // vivaan: trying third route instead of this one lol
  // vWings(true);
  // wait(.25, seconds);
  // turnPID(-40, 100, -1);
  // vWings(false);
  // turnPID(19.5, 100, -1);
  // forwardPIDD(1850, 100);
  // turnPID(-87.5, 100, -1);
  // wait(25, msec);
  // intake.spin(reverse, 100, pct);
  // wait(87, msec);
  // forwardPIDD(200, 100);
  // wait(10, msec);
  // intake.stop();
  // forwardPIDD(-50, 100);
  // turnPID(40.5, 100, -1);
  // intake.spin(forward, 100, pct);
  // forwardPIDD(350, 100);
  // wait(25, msec);
  // turnPID(-90, 100, -1);
  // intake.stop();
  // sWings(true);
  // intake.spin(reverse, 100, pct);
  // forwardPIDD(480, 100);
  // wait(10, msec);
  // sWings(false);
  // forwardPIDD(-200, 100);
  // forwardPIDD(200, 100);
  // forwardPIDD(-200, 100);
  // turnPID(-45, 100, -1);
  // wait(10, msec);
  // forwardPIDD(-1300, 100);
  // turnPID(0, 100, -1);
  // vWings(true);

  // vivaan: trying new route
    // //turn back towards the goal
    // turnPID(-36, 100, -1);
    // forwardPIDD(1000, 100);
    // // turn to face the goal straight and then outtake triball
    // turnPID(0, 100, -1);
    // intake.spin(reverse, 100, pct);
    // wait(.1, sec);     
    // forwardPIDD(300, 100);
    // intake.stop();
    // // go forward, then drive towards the middle of the field
    // forwardPIDD(-575, 75);
    // turnPID(90, 100, -1);
    // curvePID(750, 100, 50);
    // turnPID(43.5, 100, -1);
    // forwardPIDD(1550, 100);
    // wait(10, msec);
    // turnPID(0, 100, -1);
    // intake.spin(forward, 100, pct);
    // forwardPIDD(200, 100);
    // wait(.2, sec);
    // turnPID(-90, 100, -1);
    // intake.stop();
    // forwardPIDD(450, 100);
    // intake.spin(reverse, 100, pct);
    // forwardPIDD(200, 100);
    // forwardPIDD(-200, 100);
    // intake.stop();
    // turnPID(-45, 100, -1);
    // forwardPIDD(-1500, 100);
    // vWings(true);

}

void vivaanDef(){
  vWings(true);
  wait(.7, seconds);
  turnPID(40, 100, -1);
  vWings(false);
  wait(.13, seconds);
  turnPID(37, 100, -1);
  wait(5, msec);
  forwardPIDD(1000, 100);
  wait(5, msec);
  turnPID(0, 100, -1);
  wait(5, msec);
  intake.spin(reverse, 100, pct);
  forwardPIDD(100, 100);
  wait(.35, seconds);
  forwardPIDD(-400, 100);
  intake.stop();
  turnPID(180, 100, -1);
  forwardPIDD(-375, 100);
  wait(10, msec);
  forwardPIDD(200, 75);
  turnPID(-120, 100, -1);
  forwardPIDD(1400, 100);
  turnPID(-92 , 100, -1);
  forwardPIDD(1025, 100);
  //wait(.23, seconds);
  //forwardPIDD(300, 100);
  //clearmotors();
  //forwardPIDD(-25, -100);
  //clearall();
  //turnPID(-60, 100, -1);
  //forwardPIDD(1250, 100);
  //turnPID(-90, 100, -1);
  //forwardPIDD(1200, 100);
  intake.spin(reverse, 100, pct);
}

void defensive() {
  // SCORE PRELOAD
  forwardPIDD(2000, 105);
	  clearmotors();
  turnPID(87.5, 95, -1); 
  intake.spin(reverse, 100, pct);
  wait(.5, sec);
  forwardPIDD(200, 95);
  clearmotors();
  intake.stop();
  forwardPIDD(-200, 95);
  clearmotors();
  forwardPIDD(100,100);
	clearmotors();
  forwardPIDD(-275, 100);
  wait(.1, seconds);
  sWings(true);
  turnPID(-87.5, 95, -1);
  wait(.3, seconds);
  turnPID(180, 90, -1);
  sWings(false);
  forwardPIDD(2000, 100);







// vivaan: gonna comment the rest of this code out so that i can try a different more disruptive auton
  // //GET TRIBAL IN CENTER OF BORDER
  // forwardPIDD(-400, 105);
  // 	  clearmotors();
  // intake.spin(forward, 100, pct);
  // turnPID(12.5, 95, -1);
  // forwardPIDD(300, 95);

  // // push over bar
  // forwardPIDD(0,  100);
  //   clearmotors();
  // turnPID(-87.5, 95, -1);
  // intake.spin(reverse, 100, pct);
  //   sWings(false); // deploy wings to get other tribal as well and save time
  // forwardPIDD(800, 105);
  // sWings(true);

  // // fold back up and get backbar tribal
  //   clearall();
  // forwardPIDD(-200, 100);
	// clearmotors();
  // turnPID(45, 95, -1);
  //   clearall();
  // forwardPIDD(-2000, 120);
  // sWings(false);

  // // spin to knock it out
  // turnPID(360, 100, -1);
  //   clearall();
  // // touch the bar
  // forwardPIDD(0, 110);
  // turnPID(-65, 90, -1);

  // // Touch it 😈 hEE HEE HAW
  // forwardPIDD(-1000, 100);

  // // *end*
}

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  pre();
  thread a(sensordisplays);
}

/*---------------------------------------------------------------------------*/
/*                              Auton Task                                  */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  vivaanOff();
}

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/

int caxis1 = 1;
int caxis3 = 1;
int caxis1B = 1;

void usercontrol(void) {
  // intakepistonb.set(true);
  catapult.setStopping(hold);
  stopBase();
  while (true) {
  //CODE BELOW, IF YOU WANT TO REMOVE EXPONENTIAL TURNING, COMMENT IT ALL OUT
  //BUT LEAVE THE TOP IF STATEMENT, THEN write caxis1=Conroller1.Axis1.position
    thread p(punch);
    
    middleleft.spin(forward, (Controller1.Axis3.position(percent) + Controller1.Axis1.position(pct)), percent);
    middleright.spin(forward, (Controller1.Axis3.position(percent) - Controller1.Axis1.position(pct)), percent);
    frontleft.spin(forward, (Controller1.Axis3.position(percent) + Controller1.Axis1.position(pct)), percent);
    frontright.spin(forward, (Controller1.Axis3.position(percent) - Controller1.Axis1.position(pct)), percent);
    backright.spin(forward, (Controller1.Axis3.position(percent) - Controller1.Axis1.position(pct)), percent);
    backleft.spin(forward, (Controller1.Axis3.position(percent) + Controller1.Axis1.position(pct)), percent);

  if((Controller1.Axis3.position()>-5 && Controller1.Axis3.position()<5) && (Controller1.Axis1.position()>-5 && Controller1.Axis1.position()<5)){
    middleright.stop(coast),
    middleleft.stop(coast),
    frontright.stop(coast),
    frontleft.stop(coast),
    backright.stop(coast),
    backleft.stop(coast);
  }
    if (Controller1.ButtonR2.pressing()) {
      (intake.spin(reverse, 90, pct));
    } else if (Controller1.ButtonR1.pressing()) {
      (intake.spin(forward, 90, pct));
    } else {
      intake.stop();
    }
    // pneu wings
    if (Controller1.ButtonUp.pressing()) {
      horizontal.set(false);
    } else if (Controller1.ButtonLeft.pressing()) {
      horizontal.set(true);
    }
    if (Controller1.ButtonRight.pressing()){
      vertical.set(false);
    } else if (Controller1.ButtonDown.pressing()){
      vertical.set(true);
    }
  }
  while (1) {

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

// Main will set up the competition functions and callbacks.

int main() { 
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}