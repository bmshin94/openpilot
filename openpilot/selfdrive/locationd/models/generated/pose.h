#pragma once
#include "rednose/helpers/ekf.h"
extern "C" {
void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea);
void pose_err_fun(double *nom_x, double *delta_x, double *out_2056840914183716702);
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4454043914811945605);
void pose_H_mod_fun(double *state, double *out_5058757651909023675);
void pose_f_fun(double *state, double dt, double *out_7691273876108319397);
void pose_F_fun(double *state, double dt, double *out_6123810644866746828);
void pose_h_4(double *state, double *unused, double *out_6926576296604605753);
void pose_H_4(double *state, double *unused, double *out_6256705133791921779);
void pose_h_10(double *state, double *unused, double *out_9066166637456014375);
void pose_H_10(double *state, double *unused, double *out_8818018586628651595);
void pose_h_13(double *state, double *unused, double *out_8808739167586425245);
void pose_H_13(double *state, double *unused, double *out_4579407731600928908);
void pose_h_14(double *state, double *unused, double *out_5822426025914201853);
void pose_H_14(double *state, double *unused, double *out_3173916701496549483);
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt);
}