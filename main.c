/* Name: main.c
 * Author: Michael de Silva <michael@mwdesilva.com>
 * Copyright: MIT License
 */

#include <iostream>
#include <fstream>
using namespace std;

class PID {
public:
  float Kp;            // Loop gain parameter
  float Ti;            // Integrator time constant
  float Td;            // Differentiator time constant
  float delT;          // Update time interval

  // Setpoint parameters
  float input;         // Input from A/D converter
  float setpt;         // Regulated level to maintain
  float output;
  float output_max;
  float control0;
  float control1;

  float e0, e1, e2;

  void computeStep() {
    float q0, q1, q2 = 0;

    e2 = e1;
    e1 = e0;
    // Assume the A/D reading is exactly that of the previous output
    e0 = setpt - (output * 0.1);
    cout << "e0: " << e0 << ", e1: " << e1 << ", e2: " << e2 << '\n';

    q0 = Kp * (1 + (delT/Ti) + (Td/delT));
    q1 = (-1 * (Kp)) * (1 + ((2 * Td)/delT));
    q2 = (Kp * Td) / delT;
    cout << "q0: " << q0 << ", q1: " << q1 << ", q2: " << q2 << '\n';

    control1 = control0;

    control0 = ((q0 * e0)+(q1 * e1)+(q2 * e2));
    cout << "control0: " << control0 << ", control1: " << control1 << '\n';

    output = control0 + control1;

    // Set max saturation of output
    if (output > output_max){
      output = output_max;
    } else if (output < 0) {
      output = 0;
    }
    cout << "absolute control: " << output << "\n\n";
  }
};

int main (){
  PID pid;
  pid.Kp = 4;
  pid.Ti = 72;
  pid.Td = 0.01;
  pid.delT = 10;
  pid.e0 = pid.e1 = pid.e2 = 0;

  pid.setpt = 1000;
  pid.input = 20;
  pid.output = 80;
  pid.output_max = 2000;

  ofstream plot;
  plot.open("plot.dat");

  for(int i = 0; i < 40; i++){
    pid.computeStep();
    plot << i << '\t' << pid.output << '\t' << pid.e0 << '\t' << pid.e1 << '\t' << pid.e2  << '\n';
  }

  plot.close();

  return 0;
}



