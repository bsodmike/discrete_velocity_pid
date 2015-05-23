#include <string>
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

  void computeStep();
  void setGains();
};
