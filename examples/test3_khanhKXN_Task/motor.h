// #pragma once

// #include <Makerlabvn_I2C_Motor_Driver.h>
// #include "kxnTask.h"
// // #typedef void (*myFunction)();

// DEFINE_TASK_STATE(motor){
//     motor_ON,
//     motor_OFF,
// };

// CREATE_TASK(motor)

// void motor()

// void setup()
// {

//     stop();
// }

// void loop()
// {
//     switch (getState())
//     {
//     case motor_ON:
//         /*code*/
//         kDelay(0);
//         setState(motor_OFF);
//         break;

//     case motor_OFF:
//         /*code*/
//         kDelay(0);
//         setState(motor_ON);
//         break;

//     default:
//         break;
//     }
// }

// void start()
// {
//     kxnTaskManager.add(this);
//     setState(motor_ON);
// }

// void stop()
// {
//     kDelay(0);
//     setStateIdle();
// }

// void runFast(){

// }

// END
