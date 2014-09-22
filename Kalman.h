/* Simplified Kalman filter implementation - actually a low pass filter
   Based on: http://interactive-matter.eu/blog/2009/12/18/filtering-sensor-data-with-a-kalman-filter/
*/

#ifndef _Kalman_h
#define _Kalman_h

typedef struct {
  double q; //process noise covariance
  double r; //measurement noise covariance
  double x; //value
  double p; //estimation error covariance
  double k; //kalman gain
} kalman_state;

kalman_state kalman_init(double q, double r, double p, double intial_value)
{
/* The variables are x for the filtered value, q for the process noise, 
   r for the sensor noise, p for the estimated error and k for the Kalman Gain. 
   The state of the filter is defined by the values of these variables.
   
   The initial values for p is not very important since it is adjusted
   during the process. It must be just high enough to narrow down.
   The initial value for the readout is also not very important, since
   it is updated during the process.
   But tweaking the values for the process noise and sensor noise
   is essential to get clear readouts.
*/
  kalman_state result; 
  result.q = q;            //process noise
  result.r = r;            //sensor noise
  result.p = p;            //estimated error
  result.x = intial_value; //filtered value

  return result;
}

void kalman_update(kalman_state* state, double measurement)
{
  //prediction update
  //omit x = x
  state->p = state->p + state->q;

  //measurement update
  state->k = state->p / (state->p + state->r);
  state->x = state->x + state->k * (measurement - state->x);
  state->p = (1 - state->k) * state->p;
}

#endif
