#include "car.h"

namespace {
#define DIM 9
#define EDIM 9
#define MEDIM 9
typedef void (*Hfun)(double *, double *, double *);

double mass;

void set_mass(double x){ mass = x;}

double rotational_inertia;

void set_rotational_inertia(double x){ rotational_inertia = x;}

double center_to_front;

void set_center_to_front(double x){ center_to_front = x;}

double center_to_rear;

void set_center_to_rear(double x){ center_to_rear = x;}

double stiffness_front;

void set_stiffness_front(double x){ stiffness_front = x;}

double stiffness_rear;

void set_stiffness_rear(double x){ stiffness_rear = x;}
const static double MAHA_THRESH_25 = 3.8414588206941227;
const static double MAHA_THRESH_24 = 5.991464547107981;
const static double MAHA_THRESH_30 = 3.8414588206941227;
const static double MAHA_THRESH_26 = 3.8414588206941227;
const static double MAHA_THRESH_27 = 3.8414588206941227;
const static double MAHA_THRESH_29 = 3.8414588206941227;
const static double MAHA_THRESH_28 = 3.8414588206941227;
const static double MAHA_THRESH_31 = 3.8414588206941227;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_305546872645724212) {
   out_305546872645724212[0] = delta_x[0] + nom_x[0];
   out_305546872645724212[1] = delta_x[1] + nom_x[1];
   out_305546872645724212[2] = delta_x[2] + nom_x[2];
   out_305546872645724212[3] = delta_x[3] + nom_x[3];
   out_305546872645724212[4] = delta_x[4] + nom_x[4];
   out_305546872645724212[5] = delta_x[5] + nom_x[5];
   out_305546872645724212[6] = delta_x[6] + nom_x[6];
   out_305546872645724212[7] = delta_x[7] + nom_x[7];
   out_305546872645724212[8] = delta_x[8] + nom_x[8];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_7555510378622509445) {
   out_7555510378622509445[0] = -nom_x[0] + true_x[0];
   out_7555510378622509445[1] = -nom_x[1] + true_x[1];
   out_7555510378622509445[2] = -nom_x[2] + true_x[2];
   out_7555510378622509445[3] = -nom_x[3] + true_x[3];
   out_7555510378622509445[4] = -nom_x[4] + true_x[4];
   out_7555510378622509445[5] = -nom_x[5] + true_x[5];
   out_7555510378622509445[6] = -nom_x[6] + true_x[6];
   out_7555510378622509445[7] = -nom_x[7] + true_x[7];
   out_7555510378622509445[8] = -nom_x[8] + true_x[8];
}
void H_mod_fun(double *state, double *out_7774342810687298113) {
   out_7774342810687298113[0] = 1.0;
   out_7774342810687298113[1] = 0.0;
   out_7774342810687298113[2] = 0.0;
   out_7774342810687298113[3] = 0.0;
   out_7774342810687298113[4] = 0.0;
   out_7774342810687298113[5] = 0.0;
   out_7774342810687298113[6] = 0.0;
   out_7774342810687298113[7] = 0.0;
   out_7774342810687298113[8] = 0.0;
   out_7774342810687298113[9] = 0.0;
   out_7774342810687298113[10] = 1.0;
   out_7774342810687298113[11] = 0.0;
   out_7774342810687298113[12] = 0.0;
   out_7774342810687298113[13] = 0.0;
   out_7774342810687298113[14] = 0.0;
   out_7774342810687298113[15] = 0.0;
   out_7774342810687298113[16] = 0.0;
   out_7774342810687298113[17] = 0.0;
   out_7774342810687298113[18] = 0.0;
   out_7774342810687298113[19] = 0.0;
   out_7774342810687298113[20] = 1.0;
   out_7774342810687298113[21] = 0.0;
   out_7774342810687298113[22] = 0.0;
   out_7774342810687298113[23] = 0.0;
   out_7774342810687298113[24] = 0.0;
   out_7774342810687298113[25] = 0.0;
   out_7774342810687298113[26] = 0.0;
   out_7774342810687298113[27] = 0.0;
   out_7774342810687298113[28] = 0.0;
   out_7774342810687298113[29] = 0.0;
   out_7774342810687298113[30] = 1.0;
   out_7774342810687298113[31] = 0.0;
   out_7774342810687298113[32] = 0.0;
   out_7774342810687298113[33] = 0.0;
   out_7774342810687298113[34] = 0.0;
   out_7774342810687298113[35] = 0.0;
   out_7774342810687298113[36] = 0.0;
   out_7774342810687298113[37] = 0.0;
   out_7774342810687298113[38] = 0.0;
   out_7774342810687298113[39] = 0.0;
   out_7774342810687298113[40] = 1.0;
   out_7774342810687298113[41] = 0.0;
   out_7774342810687298113[42] = 0.0;
   out_7774342810687298113[43] = 0.0;
   out_7774342810687298113[44] = 0.0;
   out_7774342810687298113[45] = 0.0;
   out_7774342810687298113[46] = 0.0;
   out_7774342810687298113[47] = 0.0;
   out_7774342810687298113[48] = 0.0;
   out_7774342810687298113[49] = 0.0;
   out_7774342810687298113[50] = 1.0;
   out_7774342810687298113[51] = 0.0;
   out_7774342810687298113[52] = 0.0;
   out_7774342810687298113[53] = 0.0;
   out_7774342810687298113[54] = 0.0;
   out_7774342810687298113[55] = 0.0;
   out_7774342810687298113[56] = 0.0;
   out_7774342810687298113[57] = 0.0;
   out_7774342810687298113[58] = 0.0;
   out_7774342810687298113[59] = 0.0;
   out_7774342810687298113[60] = 1.0;
   out_7774342810687298113[61] = 0.0;
   out_7774342810687298113[62] = 0.0;
   out_7774342810687298113[63] = 0.0;
   out_7774342810687298113[64] = 0.0;
   out_7774342810687298113[65] = 0.0;
   out_7774342810687298113[66] = 0.0;
   out_7774342810687298113[67] = 0.0;
   out_7774342810687298113[68] = 0.0;
   out_7774342810687298113[69] = 0.0;
   out_7774342810687298113[70] = 1.0;
   out_7774342810687298113[71] = 0.0;
   out_7774342810687298113[72] = 0.0;
   out_7774342810687298113[73] = 0.0;
   out_7774342810687298113[74] = 0.0;
   out_7774342810687298113[75] = 0.0;
   out_7774342810687298113[76] = 0.0;
   out_7774342810687298113[77] = 0.0;
   out_7774342810687298113[78] = 0.0;
   out_7774342810687298113[79] = 0.0;
   out_7774342810687298113[80] = 1.0;
}
void f_fun(double *state, double dt, double *out_8991195739207826769) {
   out_8991195739207826769[0] = state[0];
   out_8991195739207826769[1] = state[1];
   out_8991195739207826769[2] = state[2];
   out_8991195739207826769[3] = state[3];
   out_8991195739207826769[4] = state[4];
   out_8991195739207826769[5] = dt*((-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]))*state[6] - 9.8100000000000005*state[8] + stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*state[1]) + (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*state[4])) + state[5];
   out_8991195739207826769[6] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*state[4])) + state[6];
   out_8991195739207826769[7] = state[7];
   out_8991195739207826769[8] = state[8];
}
void F_fun(double *state, double dt, double *out_4293350738310939355) {
   out_4293350738310939355[0] = 1;
   out_4293350738310939355[1] = 0;
   out_4293350738310939355[2] = 0;
   out_4293350738310939355[3] = 0;
   out_4293350738310939355[4] = 0;
   out_4293350738310939355[5] = 0;
   out_4293350738310939355[6] = 0;
   out_4293350738310939355[7] = 0;
   out_4293350738310939355[8] = 0;
   out_4293350738310939355[9] = 0;
   out_4293350738310939355[10] = 1;
   out_4293350738310939355[11] = 0;
   out_4293350738310939355[12] = 0;
   out_4293350738310939355[13] = 0;
   out_4293350738310939355[14] = 0;
   out_4293350738310939355[15] = 0;
   out_4293350738310939355[16] = 0;
   out_4293350738310939355[17] = 0;
   out_4293350738310939355[18] = 0;
   out_4293350738310939355[19] = 0;
   out_4293350738310939355[20] = 1;
   out_4293350738310939355[21] = 0;
   out_4293350738310939355[22] = 0;
   out_4293350738310939355[23] = 0;
   out_4293350738310939355[24] = 0;
   out_4293350738310939355[25] = 0;
   out_4293350738310939355[26] = 0;
   out_4293350738310939355[27] = 0;
   out_4293350738310939355[28] = 0;
   out_4293350738310939355[29] = 0;
   out_4293350738310939355[30] = 1;
   out_4293350738310939355[31] = 0;
   out_4293350738310939355[32] = 0;
   out_4293350738310939355[33] = 0;
   out_4293350738310939355[34] = 0;
   out_4293350738310939355[35] = 0;
   out_4293350738310939355[36] = 0;
   out_4293350738310939355[37] = 0;
   out_4293350738310939355[38] = 0;
   out_4293350738310939355[39] = 0;
   out_4293350738310939355[40] = 1;
   out_4293350738310939355[41] = 0;
   out_4293350738310939355[42] = 0;
   out_4293350738310939355[43] = 0;
   out_4293350738310939355[44] = 0;
   out_4293350738310939355[45] = dt*(stiffness_front*(-state[2] - state[3] + state[7])/(mass*state[1]) + (-stiffness_front - stiffness_rear)*state[5]/(mass*state[4]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[6]/(mass*state[4]));
   out_4293350738310939355[46] = -dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(mass*pow(state[1], 2));
   out_4293350738310939355[47] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4293350738310939355[48] = -dt*stiffness_front*state[0]/(mass*state[1]);
   out_4293350738310939355[49] = dt*((-1 - (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*pow(state[4], 2)))*state[6] - (-stiffness_front*state[0] - stiffness_rear*state[0])*state[5]/(mass*pow(state[4], 2)));
   out_4293350738310939355[50] = dt*(-stiffness_front*state[0] - stiffness_rear*state[0])/(mass*state[4]) + 1;
   out_4293350738310939355[51] = dt*(-state[4] + (-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(mass*state[4]));
   out_4293350738310939355[52] = dt*stiffness_front*state[0]/(mass*state[1]);
   out_4293350738310939355[53] = -9.8100000000000005*dt;
   out_4293350738310939355[54] = dt*(center_to_front*stiffness_front*(-state[2] - state[3] + state[7])/(rotational_inertia*state[1]) + (-center_to_front*stiffness_front + center_to_rear*stiffness_rear)*state[5]/(rotational_inertia*state[4]) + (-pow(center_to_front, 2)*stiffness_front - pow(center_to_rear, 2)*stiffness_rear)*state[6]/(rotational_inertia*state[4]));
   out_4293350738310939355[55] = -center_to_front*dt*stiffness_front*(-state[2] - state[3] + state[7])*state[0]/(rotational_inertia*pow(state[1], 2));
   out_4293350738310939355[56] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4293350738310939355[57] = -center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4293350738310939355[58] = dt*(-(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])*state[5]/(rotational_inertia*pow(state[4], 2)) - (-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])*state[6]/(rotational_inertia*pow(state[4], 2)));
   out_4293350738310939355[59] = dt*(-center_to_front*stiffness_front*state[0] + center_to_rear*stiffness_rear*state[0])/(rotational_inertia*state[4]);
   out_4293350738310939355[60] = dt*(-pow(center_to_front, 2)*stiffness_front*state[0] - pow(center_to_rear, 2)*stiffness_rear*state[0])/(rotational_inertia*state[4]) + 1;
   out_4293350738310939355[61] = center_to_front*dt*stiffness_front*state[0]/(rotational_inertia*state[1]);
   out_4293350738310939355[62] = 0;
   out_4293350738310939355[63] = 0;
   out_4293350738310939355[64] = 0;
   out_4293350738310939355[65] = 0;
   out_4293350738310939355[66] = 0;
   out_4293350738310939355[67] = 0;
   out_4293350738310939355[68] = 0;
   out_4293350738310939355[69] = 0;
   out_4293350738310939355[70] = 1;
   out_4293350738310939355[71] = 0;
   out_4293350738310939355[72] = 0;
   out_4293350738310939355[73] = 0;
   out_4293350738310939355[74] = 0;
   out_4293350738310939355[75] = 0;
   out_4293350738310939355[76] = 0;
   out_4293350738310939355[77] = 0;
   out_4293350738310939355[78] = 0;
   out_4293350738310939355[79] = 0;
   out_4293350738310939355[80] = 1;
}
void h_25(double *state, double *unused, double *out_3866573293983018031) {
   out_3866573293983018031[0] = state[6];
}
void H_25(double *state, double *unused, double *out_8649651555026301093) {
   out_8649651555026301093[0] = 0;
   out_8649651555026301093[1] = 0;
   out_8649651555026301093[2] = 0;
   out_8649651555026301093[3] = 0;
   out_8649651555026301093[4] = 0;
   out_8649651555026301093[5] = 0;
   out_8649651555026301093[6] = 1;
   out_8649651555026301093[7] = 0;
   out_8649651555026301093[8] = 0;
}
void h_24(double *state, double *unused, double *out_153052357553111030) {
   out_153052357553111030[0] = state[4];
   out_153052357553111030[1] = state[5];
}
void H_24(double *state, double *unused, double *out_6239166919880927387) {
   out_6239166919880927387[0] = 0;
   out_6239166919880927387[1] = 0;
   out_6239166919880927387[2] = 0;
   out_6239166919880927387[3] = 0;
   out_6239166919880927387[4] = 1;
   out_6239166919880927387[5] = 0;
   out_6239166919880927387[6] = 0;
   out_6239166919880927387[7] = 0;
   out_6239166919880927387[8] = 0;
   out_6239166919880927387[9] = 0;
   out_6239166919880927387[10] = 0;
   out_6239166919880927387[11] = 0;
   out_6239166919880927387[12] = 0;
   out_6239166919880927387[13] = 0;
   out_6239166919880927387[14] = 1;
   out_6239166919880927387[15] = 0;
   out_6239166919880927387[16] = 0;
   out_6239166919880927387[17] = 0;
}
void h_30(double *state, double *unused, double *out_1659484142568005082) {
   out_1659484142568005082[0] = state[4];
}
void H_30(double *state, double *unused, double *out_7278759560176001896) {
   out_7278759560176001896[0] = 0;
   out_7278759560176001896[1] = 0;
   out_7278759560176001896[2] = 0;
   out_7278759560176001896[3] = 0;
   out_7278759560176001896[4] = 1;
   out_7278759560176001896[5] = 0;
   out_7278759560176001896[6] = 0;
   out_7278759560176001896[7] = 0;
   out_7278759560176001896[8] = 0;
}
void h_26(double *state, double *unused, double *out_7905935200028178550) {
   out_7905935200028178550[0] = state[7];
}
void H_26(double *state, double *unused, double *out_6492566548922449922) {
   out_6492566548922449922[0] = 0;
   out_6492566548922449922[1] = 0;
   out_6492566548922449922[2] = 0;
   out_6492566548922449922[3] = 0;
   out_6492566548922449922[4] = 0;
   out_6492566548922449922[5] = 0;
   out_6492566548922449922[6] = 0;
   out_6492566548922449922[7] = 1;
   out_6492566548922449922[8] = 0;
}
void h_27(double *state, double *unused, double *out_8937440908645576750) {
   out_8937440908645576750[0] = state[3];
}
void H_27(double *state, double *unused, double *out_8993221201733124809) {
   out_8993221201733124809[0] = 0;
   out_8993221201733124809[1] = 0;
   out_8993221201733124809[2] = 0;
   out_8993221201733124809[3] = 1;
   out_8993221201733124809[4] = 0;
   out_8993221201733124809[5] = 0;
   out_8993221201733124809[6] = 0;
   out_8993221201733124809[7] = 0;
   out_8993221201733124809[8] = 0;
}
void h_29(double *state, double *unused, double *out_8662246846361070861) {
   out_8662246846361070861[0] = state[1];
}
void H_29(double *state, double *unused, double *out_6768528215861609712) {
   out_6768528215861609712[0] = 0;
   out_6768528215861609712[1] = 1;
   out_6768528215861609712[2] = 0;
   out_6768528215861609712[3] = 0;
   out_6768528215861609712[4] = 0;
   out_6768528215861609712[5] = 0;
   out_6768528215861609712[6] = 0;
   out_6768528215861609712[7] = 0;
   out_6768528215861609712[8] = 0;
}
void h_28(double *state, double *unused, double *out_3526379325757833113) {
   out_3526379325757833113[0] = state[0];
}
void H_28(double *state, double *unused, double *out_6595816840778411330) {
   out_6595816840778411330[0] = 1;
   out_6595816840778411330[1] = 0;
   out_6595816840778411330[2] = 0;
   out_6595816840778411330[3] = 0;
   out_6595816840778411330[4] = 0;
   out_6595816840778411330[5] = 0;
   out_6595816840778411330[6] = 0;
   out_6595816840778411330[7] = 0;
   out_6595816840778411330[8] = 0;
}
void h_31(double *state, double *unused, double *out_5442453495042682403) {
   out_5442453495042682403[0] = state[8];
}
void H_31(double *state, double *unused, double *out_7118774651155801398) {
   out_7118774651155801398[0] = 0;
   out_7118774651155801398[1] = 0;
   out_7118774651155801398[2] = 0;
   out_7118774651155801398[3] = 0;
   out_7118774651155801398[4] = 0;
   out_7118774651155801398[5] = 0;
   out_7118774651155801398[6] = 0;
   out_7118774651155801398[7] = 0;
   out_7118774651155801398[8] = 1;
}
#include <eigen3/Eigen/Dense>
#include <iostream>

typedef Eigen::Matrix<double, DIM, DIM, Eigen::RowMajor> DDM;
typedef Eigen::Matrix<double, EDIM, EDIM, Eigen::RowMajor> EEM;
typedef Eigen::Matrix<double, DIM, EDIM, Eigen::RowMajor> DEM;

void predict(double *in_x, double *in_P, double *in_Q, double dt) {
  typedef Eigen::Matrix<double, MEDIM, MEDIM, Eigen::RowMajor> RRM;

  double nx[DIM] = {0};
  double in_F[EDIM*EDIM] = {0};

  // functions from sympy
  f_fun(in_x, dt, nx);
  F_fun(in_x, dt, in_F);


  EEM F(in_F);
  EEM P(in_P);
  EEM Q(in_Q);

  RRM F_main = F.topLeftCorner(MEDIM, MEDIM);
  P.topLeftCorner(MEDIM, MEDIM) = (F_main * P.topLeftCorner(MEDIM, MEDIM)) * F_main.transpose();
  P.topRightCorner(MEDIM, EDIM - MEDIM) = F_main * P.topRightCorner(MEDIM, EDIM - MEDIM);
  P.bottomLeftCorner(EDIM - MEDIM, MEDIM) = P.bottomLeftCorner(EDIM - MEDIM, MEDIM) * F_main.transpose();

  P = P + dt*Q;

  // copy out state
  memcpy(in_x, nx, DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
}

// note: extra_args dim only correct when null space projecting
// otherwise 1
template <int ZDIM, int EADIM, bool MAHA_TEST>
void update(double *in_x, double *in_P, Hfun h_fun, Hfun H_fun, Hfun Hea_fun, double *in_z, double *in_R, double *in_ea, double MAHA_THRESHOLD) {
  typedef Eigen::Matrix<double, ZDIM, ZDIM, Eigen::RowMajor> ZZM;
  typedef Eigen::Matrix<double, ZDIM, DIM, Eigen::RowMajor> ZDM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, EDIM, Eigen::RowMajor> XEM;
  //typedef Eigen::Matrix<double, EDIM, ZDIM, Eigen::RowMajor> EZM;
  typedef Eigen::Matrix<double, Eigen::Dynamic, 1> X1M;
  typedef Eigen::Matrix<double, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor> XXM;

  double in_hx[ZDIM] = {0};
  double in_H[ZDIM * DIM] = {0};
  double in_H_mod[EDIM * DIM] = {0};
  double delta_x[EDIM] = {0};
  double x_new[DIM] = {0};


  // state x, P
  Eigen::Matrix<double, ZDIM, 1> z(in_z);
  EEM P(in_P);
  ZZM pre_R(in_R);

  // functions from sympy
  h_fun(in_x, in_ea, in_hx);
  H_fun(in_x, in_ea, in_H);
  ZDM pre_H(in_H);

  // get y (y = z - hx)
  Eigen::Matrix<double, ZDIM, 1> pre_y(in_hx); pre_y = z - pre_y;
  X1M y; XXM H; XXM R;
  if (Hea_fun){
    typedef Eigen::Matrix<double, ZDIM, EADIM, Eigen::RowMajor> ZAM;
    double in_Hea[ZDIM * EADIM] = {0};
    Hea_fun(in_x, in_ea, in_Hea);
    ZAM Hea(in_Hea);
    XXM A = Hea.transpose().fullPivLu().kernel();


    y = A.transpose() * pre_y;
    H = A.transpose() * pre_H;
    R = A.transpose() * pre_R * A;
  } else {
    y = pre_y;
    H = pre_H;
    R = pre_R;
  }
  // get modified H
  H_mod_fun(in_x, in_H_mod);
  DEM H_mod(in_H_mod);
  XEM H_err = H * H_mod;

  // Do mahalobis distance test
  if (MAHA_TEST){
    XXM a = (H_err * P * H_err.transpose() + R).inverse();
    double maha_dist = y.transpose() * a * y;
    if (maha_dist > MAHA_THRESHOLD){
      R = 1.0e16 * R;
    }
  }

  // Outlier resilient weighting
  double weight = 1;//(1.5)/(1 + y.squaredNorm()/R.sum());

  // kalman gains and I_KH
  XXM S = ((H_err * P) * H_err.transpose()) + R/weight;
  XEM KT = S.fullPivLu().solve(H_err * P.transpose());
  //EZM K = KT.transpose(); TODO: WHY DOES THIS NOT COMPILE?
  //EZM K = S.fullPivLu().solve(H_err * P.transpose()).transpose();
  //std::cout << "Here is the matrix rot:\n" << K << std::endl;
  EEM I_KH = Eigen::Matrix<double, EDIM, EDIM>::Identity() - (KT.transpose() * H_err);

  // update state by injecting dx
  Eigen::Matrix<double, EDIM, 1> dx(delta_x);
  dx  = (KT.transpose() * y);
  memcpy(delta_x, dx.data(), EDIM * sizeof(double));
  err_fun(in_x, delta_x, x_new);
  Eigen::Matrix<double, DIM, 1> x(x_new);

  // update cov
  P = ((I_KH * P) * I_KH.transpose()) + ((KT.transpose() * R) * KT);

  // copy out state
  memcpy(in_x, x.data(), DIM * sizeof(double));
  memcpy(in_P, P.data(), EDIM * EDIM * sizeof(double));
  memcpy(in_z, y.data(), y.rows() * sizeof(double));
}




}
extern "C" {

void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_25, H_25, NULL, in_z, in_R, in_ea, MAHA_THRESH_25);
}
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<2, 3, 0>(in_x, in_P, h_24, H_24, NULL, in_z, in_R, in_ea, MAHA_THRESH_24);
}
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_30, H_30, NULL, in_z, in_R, in_ea, MAHA_THRESH_30);
}
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_26, H_26, NULL, in_z, in_R, in_ea, MAHA_THRESH_26);
}
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_27, H_27, NULL, in_z, in_R, in_ea, MAHA_THRESH_27);
}
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_29, H_29, NULL, in_z, in_R, in_ea, MAHA_THRESH_29);
}
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_28, H_28, NULL, in_z, in_R, in_ea, MAHA_THRESH_28);
}
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<1, 3, 0>(in_x, in_P, h_31, H_31, NULL, in_z, in_R, in_ea, MAHA_THRESH_31);
}
void car_err_fun(double *nom_x, double *delta_x, double *out_305546872645724212) {
  err_fun(nom_x, delta_x, out_305546872645724212);
}
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7555510378622509445) {
  inv_err_fun(nom_x, true_x, out_7555510378622509445);
}
void car_H_mod_fun(double *state, double *out_7774342810687298113) {
  H_mod_fun(state, out_7774342810687298113);
}
void car_f_fun(double *state, double dt, double *out_8991195739207826769) {
  f_fun(state,  dt, out_8991195739207826769);
}
void car_F_fun(double *state, double dt, double *out_4293350738310939355) {
  F_fun(state,  dt, out_4293350738310939355);
}
void car_h_25(double *state, double *unused, double *out_3866573293983018031) {
  h_25(state, unused, out_3866573293983018031);
}
void car_H_25(double *state, double *unused, double *out_8649651555026301093) {
  H_25(state, unused, out_8649651555026301093);
}
void car_h_24(double *state, double *unused, double *out_153052357553111030) {
  h_24(state, unused, out_153052357553111030);
}
void car_H_24(double *state, double *unused, double *out_6239166919880927387) {
  H_24(state, unused, out_6239166919880927387);
}
void car_h_30(double *state, double *unused, double *out_1659484142568005082) {
  h_30(state, unused, out_1659484142568005082);
}
void car_H_30(double *state, double *unused, double *out_7278759560176001896) {
  H_30(state, unused, out_7278759560176001896);
}
void car_h_26(double *state, double *unused, double *out_7905935200028178550) {
  h_26(state, unused, out_7905935200028178550);
}
void car_H_26(double *state, double *unused, double *out_6492566548922449922) {
  H_26(state, unused, out_6492566548922449922);
}
void car_h_27(double *state, double *unused, double *out_8937440908645576750) {
  h_27(state, unused, out_8937440908645576750);
}
void car_H_27(double *state, double *unused, double *out_8993221201733124809) {
  H_27(state, unused, out_8993221201733124809);
}
void car_h_29(double *state, double *unused, double *out_8662246846361070861) {
  h_29(state, unused, out_8662246846361070861);
}
void car_H_29(double *state, double *unused, double *out_6768528215861609712) {
  H_29(state, unused, out_6768528215861609712);
}
void car_h_28(double *state, double *unused, double *out_3526379325757833113) {
  h_28(state, unused, out_3526379325757833113);
}
void car_H_28(double *state, double *unused, double *out_6595816840778411330) {
  H_28(state, unused, out_6595816840778411330);
}
void car_h_31(double *state, double *unused, double *out_5442453495042682403) {
  h_31(state, unused, out_5442453495042682403);
}
void car_H_31(double *state, double *unused, double *out_7118774651155801398) {
  H_31(state, unused, out_7118774651155801398);
}
void car_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
void car_set_mass(double x) {
  set_mass(x);
}
void car_set_rotational_inertia(double x) {
  set_rotational_inertia(x);
}
void car_set_center_to_front(double x) {
  set_center_to_front(x);
}
void car_set_center_to_rear(double x) {
  set_center_to_rear(x);
}
void car_set_stiffness_front(double x) {
  set_stiffness_front(x);
}
void car_set_stiffness_rear(double x) {
  set_stiffness_rear(x);
}
}

const EKF car = {
  .name = "car",
  .kinds = { 25, 24, 30, 26, 27, 29, 28, 31 },
  .feature_kinds = {  },
  .f_fun = car_f_fun,
  .F_fun = car_F_fun,
  .err_fun = car_err_fun,
  .inv_err_fun = car_inv_err_fun,
  .H_mod_fun = car_H_mod_fun,
  .predict = car_predict,
  .hs = {
    { 25, car_h_25 },
    { 24, car_h_24 },
    { 30, car_h_30 },
    { 26, car_h_26 },
    { 27, car_h_27 },
    { 29, car_h_29 },
    { 28, car_h_28 },
    { 31, car_h_31 },
  },
  .Hs = {
    { 25, car_H_25 },
    { 24, car_H_24 },
    { 30, car_H_30 },
    { 26, car_H_26 },
    { 27, car_H_27 },
    { 29, car_H_29 },
    { 28, car_H_28 },
    { 31, car_H_31 },
  },
  .updates = {
    { 25, car_update_25 },
    { 24, car_update_24 },
    { 30, car_update_30 },
    { 26, car_update_26 },
    { 27, car_update_27 },
    { 29, car_update_29 },
    { 28, car_update_28 },
    { 31, car_update_31 },
  },
  .Hes = {
  },
  .sets = {
    { "mass", car_set_mass },
    { "rotational_inertia", car_set_rotational_inertia },
    { "center_to_front", car_set_center_to_front },
    { "center_to_rear", car_set_center_to_rear },
    { "stiffness_front", car_set_stiffness_front },
    { "stiffness_rear", car_set_stiffness_rear },
  },
  .extra_routines = {
  },
};

ekf_lib_init(car)
