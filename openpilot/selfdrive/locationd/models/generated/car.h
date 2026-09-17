#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void car_update_25(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_24(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_30(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_26(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_27(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_29(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_28(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_update_31(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void car_err_fun(double *nom_x, double *delta_x, double *out_305546872645724212);
void car_inv_err_fun(double *nom_x, double *true_x, double *out_7555510378622509445);
void car_H_mod_fun(double *state, double *out_7774342810687298113);
void car_f_fun(double *state, double dt, double *out_8991195739207826769);
void car_F_fun(double *state, double dt, double *out_4293350738310939355);
void car_h_25(double *state, double *unused, double *out_3866573293983018031);
void car_H_25(double *state, double *unused, double *out_8649651555026301093);
void car_h_24(double *state, double *unused, double *out_153052357553111030);
void car_H_24(double *state, double *unused, double *out_6239166919880927387);
void car_h_30(double *state, double *unused, double *out_1659484142568005082);
void car_H_30(double *state, double *unused, double *out_7278759560176001896);
void car_h_26(double *state, double *unused, double *out_7905935200028178550);
void car_H_26(double *state, double *unused, double *out_6492566548922449922);
void car_h_27(double *state, double *unused, double *out_8937440908645576750);
void car_H_27(double *state, double *unused, double *out_8993221201733124809);
void car_h_29(double *state, double *unused, double *out_8662246846361070861);
void car_H_29(double *state, double *unused, double *out_6768528215861609712);
void car_h_28(double *state, double *unused, double *out_3526379325757833113);
void car_H_28(double *state, double *unused, double *out_6595816840778411330);
void car_h_31(double *state, double *unused, double *out_5442453495042682403);
void car_H_31(double *state, double *unused, double *out_7118774651155801398);
void car_predict(double *in_x, double *in_P, double *in_Q, double dt);
void car_set_mass(double x);
void car_set_rotational_inertia(double x);
void car_set_center_to_front(double x);
void car_set_center_to_rear(double x);
void car_set_stiffness_front(double x);
void car_set_stiffness_rear(double x);
}