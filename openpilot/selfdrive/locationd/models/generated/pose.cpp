#include "pose.h"

namespace {
#define DIM 18
#define EDIM 18
#define MEDIM 18
typedef void (*Hfun)(double *, double *, double *);
const static double MAHA_THRESH_4 = 7.814727903251177;
const static double MAHA_THRESH_10 = 7.814727903251177;
const static double MAHA_THRESH_13 = 7.814727903251177;
const static double MAHA_THRESH_14 = 7.814727903251177;

/******************************************************************************
 *                      Code generated with SymPy 1.14.0                      *
 *                                                                            *
 *              See http://www.sympy.org/ for more information.               *
 *                                                                            *
 *                         This file is part of 'ekf'                         *
 ******************************************************************************/
void err_fun(double *nom_x, double *delta_x, double *out_2056840914183716702) {
   out_2056840914183716702[0] = delta_x[0] + nom_x[0];
   out_2056840914183716702[1] = delta_x[1] + nom_x[1];
   out_2056840914183716702[2] = delta_x[2] + nom_x[2];
   out_2056840914183716702[3] = delta_x[3] + nom_x[3];
   out_2056840914183716702[4] = delta_x[4] + nom_x[4];
   out_2056840914183716702[5] = delta_x[5] + nom_x[5];
   out_2056840914183716702[6] = delta_x[6] + nom_x[6];
   out_2056840914183716702[7] = delta_x[7] + nom_x[7];
   out_2056840914183716702[8] = delta_x[8] + nom_x[8];
   out_2056840914183716702[9] = delta_x[9] + nom_x[9];
   out_2056840914183716702[10] = delta_x[10] + nom_x[10];
   out_2056840914183716702[11] = delta_x[11] + nom_x[11];
   out_2056840914183716702[12] = delta_x[12] + nom_x[12];
   out_2056840914183716702[13] = delta_x[13] + nom_x[13];
   out_2056840914183716702[14] = delta_x[14] + nom_x[14];
   out_2056840914183716702[15] = delta_x[15] + nom_x[15];
   out_2056840914183716702[16] = delta_x[16] + nom_x[16];
   out_2056840914183716702[17] = delta_x[17] + nom_x[17];
}
void inv_err_fun(double *nom_x, double *true_x, double *out_4454043914811945605) {
   out_4454043914811945605[0] = -nom_x[0] + true_x[0];
   out_4454043914811945605[1] = -nom_x[1] + true_x[1];
   out_4454043914811945605[2] = -nom_x[2] + true_x[2];
   out_4454043914811945605[3] = -nom_x[3] + true_x[3];
   out_4454043914811945605[4] = -nom_x[4] + true_x[4];
   out_4454043914811945605[5] = -nom_x[5] + true_x[5];
   out_4454043914811945605[6] = -nom_x[6] + true_x[6];
   out_4454043914811945605[7] = -nom_x[7] + true_x[7];
   out_4454043914811945605[8] = -nom_x[8] + true_x[8];
   out_4454043914811945605[9] = -nom_x[9] + true_x[9];
   out_4454043914811945605[10] = -nom_x[10] + true_x[10];
   out_4454043914811945605[11] = -nom_x[11] + true_x[11];
   out_4454043914811945605[12] = -nom_x[12] + true_x[12];
   out_4454043914811945605[13] = -nom_x[13] + true_x[13];
   out_4454043914811945605[14] = -nom_x[14] + true_x[14];
   out_4454043914811945605[15] = -nom_x[15] + true_x[15];
   out_4454043914811945605[16] = -nom_x[16] + true_x[16];
   out_4454043914811945605[17] = -nom_x[17] + true_x[17];
}
void H_mod_fun(double *state, double *out_5058757651909023675) {
   out_5058757651909023675[0] = 1.0;
   out_5058757651909023675[1] = 0.0;
   out_5058757651909023675[2] = 0.0;
   out_5058757651909023675[3] = 0.0;
   out_5058757651909023675[4] = 0.0;
   out_5058757651909023675[5] = 0.0;
   out_5058757651909023675[6] = 0.0;
   out_5058757651909023675[7] = 0.0;
   out_5058757651909023675[8] = 0.0;
   out_5058757651909023675[9] = 0.0;
   out_5058757651909023675[10] = 0.0;
   out_5058757651909023675[11] = 0.0;
   out_5058757651909023675[12] = 0.0;
   out_5058757651909023675[13] = 0.0;
   out_5058757651909023675[14] = 0.0;
   out_5058757651909023675[15] = 0.0;
   out_5058757651909023675[16] = 0.0;
   out_5058757651909023675[17] = 0.0;
   out_5058757651909023675[18] = 0.0;
   out_5058757651909023675[19] = 1.0;
   out_5058757651909023675[20] = 0.0;
   out_5058757651909023675[21] = 0.0;
   out_5058757651909023675[22] = 0.0;
   out_5058757651909023675[23] = 0.0;
   out_5058757651909023675[24] = 0.0;
   out_5058757651909023675[25] = 0.0;
   out_5058757651909023675[26] = 0.0;
   out_5058757651909023675[27] = 0.0;
   out_5058757651909023675[28] = 0.0;
   out_5058757651909023675[29] = 0.0;
   out_5058757651909023675[30] = 0.0;
   out_5058757651909023675[31] = 0.0;
   out_5058757651909023675[32] = 0.0;
   out_5058757651909023675[33] = 0.0;
   out_5058757651909023675[34] = 0.0;
   out_5058757651909023675[35] = 0.0;
   out_5058757651909023675[36] = 0.0;
   out_5058757651909023675[37] = 0.0;
   out_5058757651909023675[38] = 1.0;
   out_5058757651909023675[39] = 0.0;
   out_5058757651909023675[40] = 0.0;
   out_5058757651909023675[41] = 0.0;
   out_5058757651909023675[42] = 0.0;
   out_5058757651909023675[43] = 0.0;
   out_5058757651909023675[44] = 0.0;
   out_5058757651909023675[45] = 0.0;
   out_5058757651909023675[46] = 0.0;
   out_5058757651909023675[47] = 0.0;
   out_5058757651909023675[48] = 0.0;
   out_5058757651909023675[49] = 0.0;
   out_5058757651909023675[50] = 0.0;
   out_5058757651909023675[51] = 0.0;
   out_5058757651909023675[52] = 0.0;
   out_5058757651909023675[53] = 0.0;
   out_5058757651909023675[54] = 0.0;
   out_5058757651909023675[55] = 0.0;
   out_5058757651909023675[56] = 0.0;
   out_5058757651909023675[57] = 1.0;
   out_5058757651909023675[58] = 0.0;
   out_5058757651909023675[59] = 0.0;
   out_5058757651909023675[60] = 0.0;
   out_5058757651909023675[61] = 0.0;
   out_5058757651909023675[62] = 0.0;
   out_5058757651909023675[63] = 0.0;
   out_5058757651909023675[64] = 0.0;
   out_5058757651909023675[65] = 0.0;
   out_5058757651909023675[66] = 0.0;
   out_5058757651909023675[67] = 0.0;
   out_5058757651909023675[68] = 0.0;
   out_5058757651909023675[69] = 0.0;
   out_5058757651909023675[70] = 0.0;
   out_5058757651909023675[71] = 0.0;
   out_5058757651909023675[72] = 0.0;
   out_5058757651909023675[73] = 0.0;
   out_5058757651909023675[74] = 0.0;
   out_5058757651909023675[75] = 0.0;
   out_5058757651909023675[76] = 1.0;
   out_5058757651909023675[77] = 0.0;
   out_5058757651909023675[78] = 0.0;
   out_5058757651909023675[79] = 0.0;
   out_5058757651909023675[80] = 0.0;
   out_5058757651909023675[81] = 0.0;
   out_5058757651909023675[82] = 0.0;
   out_5058757651909023675[83] = 0.0;
   out_5058757651909023675[84] = 0.0;
   out_5058757651909023675[85] = 0.0;
   out_5058757651909023675[86] = 0.0;
   out_5058757651909023675[87] = 0.0;
   out_5058757651909023675[88] = 0.0;
   out_5058757651909023675[89] = 0.0;
   out_5058757651909023675[90] = 0.0;
   out_5058757651909023675[91] = 0.0;
   out_5058757651909023675[92] = 0.0;
   out_5058757651909023675[93] = 0.0;
   out_5058757651909023675[94] = 0.0;
   out_5058757651909023675[95] = 1.0;
   out_5058757651909023675[96] = 0.0;
   out_5058757651909023675[97] = 0.0;
   out_5058757651909023675[98] = 0.0;
   out_5058757651909023675[99] = 0.0;
   out_5058757651909023675[100] = 0.0;
   out_5058757651909023675[101] = 0.0;
   out_5058757651909023675[102] = 0.0;
   out_5058757651909023675[103] = 0.0;
   out_5058757651909023675[104] = 0.0;
   out_5058757651909023675[105] = 0.0;
   out_5058757651909023675[106] = 0.0;
   out_5058757651909023675[107] = 0.0;
   out_5058757651909023675[108] = 0.0;
   out_5058757651909023675[109] = 0.0;
   out_5058757651909023675[110] = 0.0;
   out_5058757651909023675[111] = 0.0;
   out_5058757651909023675[112] = 0.0;
   out_5058757651909023675[113] = 0.0;
   out_5058757651909023675[114] = 1.0;
   out_5058757651909023675[115] = 0.0;
   out_5058757651909023675[116] = 0.0;
   out_5058757651909023675[117] = 0.0;
   out_5058757651909023675[118] = 0.0;
   out_5058757651909023675[119] = 0.0;
   out_5058757651909023675[120] = 0.0;
   out_5058757651909023675[121] = 0.0;
   out_5058757651909023675[122] = 0.0;
   out_5058757651909023675[123] = 0.0;
   out_5058757651909023675[124] = 0.0;
   out_5058757651909023675[125] = 0.0;
   out_5058757651909023675[126] = 0.0;
   out_5058757651909023675[127] = 0.0;
   out_5058757651909023675[128] = 0.0;
   out_5058757651909023675[129] = 0.0;
   out_5058757651909023675[130] = 0.0;
   out_5058757651909023675[131] = 0.0;
   out_5058757651909023675[132] = 0.0;
   out_5058757651909023675[133] = 1.0;
   out_5058757651909023675[134] = 0.0;
   out_5058757651909023675[135] = 0.0;
   out_5058757651909023675[136] = 0.0;
   out_5058757651909023675[137] = 0.0;
   out_5058757651909023675[138] = 0.0;
   out_5058757651909023675[139] = 0.0;
   out_5058757651909023675[140] = 0.0;
   out_5058757651909023675[141] = 0.0;
   out_5058757651909023675[142] = 0.0;
   out_5058757651909023675[143] = 0.0;
   out_5058757651909023675[144] = 0.0;
   out_5058757651909023675[145] = 0.0;
   out_5058757651909023675[146] = 0.0;
   out_5058757651909023675[147] = 0.0;
   out_5058757651909023675[148] = 0.0;
   out_5058757651909023675[149] = 0.0;
   out_5058757651909023675[150] = 0.0;
   out_5058757651909023675[151] = 0.0;
   out_5058757651909023675[152] = 1.0;
   out_5058757651909023675[153] = 0.0;
   out_5058757651909023675[154] = 0.0;
   out_5058757651909023675[155] = 0.0;
   out_5058757651909023675[156] = 0.0;
   out_5058757651909023675[157] = 0.0;
   out_5058757651909023675[158] = 0.0;
   out_5058757651909023675[159] = 0.0;
   out_5058757651909023675[160] = 0.0;
   out_5058757651909023675[161] = 0.0;
   out_5058757651909023675[162] = 0.0;
   out_5058757651909023675[163] = 0.0;
   out_5058757651909023675[164] = 0.0;
   out_5058757651909023675[165] = 0.0;
   out_5058757651909023675[166] = 0.0;
   out_5058757651909023675[167] = 0.0;
   out_5058757651909023675[168] = 0.0;
   out_5058757651909023675[169] = 0.0;
   out_5058757651909023675[170] = 0.0;
   out_5058757651909023675[171] = 1.0;
   out_5058757651909023675[172] = 0.0;
   out_5058757651909023675[173] = 0.0;
   out_5058757651909023675[174] = 0.0;
   out_5058757651909023675[175] = 0.0;
   out_5058757651909023675[176] = 0.0;
   out_5058757651909023675[177] = 0.0;
   out_5058757651909023675[178] = 0.0;
   out_5058757651909023675[179] = 0.0;
   out_5058757651909023675[180] = 0.0;
   out_5058757651909023675[181] = 0.0;
   out_5058757651909023675[182] = 0.0;
   out_5058757651909023675[183] = 0.0;
   out_5058757651909023675[184] = 0.0;
   out_5058757651909023675[185] = 0.0;
   out_5058757651909023675[186] = 0.0;
   out_5058757651909023675[187] = 0.0;
   out_5058757651909023675[188] = 0.0;
   out_5058757651909023675[189] = 0.0;
   out_5058757651909023675[190] = 1.0;
   out_5058757651909023675[191] = 0.0;
   out_5058757651909023675[192] = 0.0;
   out_5058757651909023675[193] = 0.0;
   out_5058757651909023675[194] = 0.0;
   out_5058757651909023675[195] = 0.0;
   out_5058757651909023675[196] = 0.0;
   out_5058757651909023675[197] = 0.0;
   out_5058757651909023675[198] = 0.0;
   out_5058757651909023675[199] = 0.0;
   out_5058757651909023675[200] = 0.0;
   out_5058757651909023675[201] = 0.0;
   out_5058757651909023675[202] = 0.0;
   out_5058757651909023675[203] = 0.0;
   out_5058757651909023675[204] = 0.0;
   out_5058757651909023675[205] = 0.0;
   out_5058757651909023675[206] = 0.0;
   out_5058757651909023675[207] = 0.0;
   out_5058757651909023675[208] = 0.0;
   out_5058757651909023675[209] = 1.0;
   out_5058757651909023675[210] = 0.0;
   out_5058757651909023675[211] = 0.0;
   out_5058757651909023675[212] = 0.0;
   out_5058757651909023675[213] = 0.0;
   out_5058757651909023675[214] = 0.0;
   out_5058757651909023675[215] = 0.0;
   out_5058757651909023675[216] = 0.0;
   out_5058757651909023675[217] = 0.0;
   out_5058757651909023675[218] = 0.0;
   out_5058757651909023675[219] = 0.0;
   out_5058757651909023675[220] = 0.0;
   out_5058757651909023675[221] = 0.0;
   out_5058757651909023675[222] = 0.0;
   out_5058757651909023675[223] = 0.0;
   out_5058757651909023675[224] = 0.0;
   out_5058757651909023675[225] = 0.0;
   out_5058757651909023675[226] = 0.0;
   out_5058757651909023675[227] = 0.0;
   out_5058757651909023675[228] = 1.0;
   out_5058757651909023675[229] = 0.0;
   out_5058757651909023675[230] = 0.0;
   out_5058757651909023675[231] = 0.0;
   out_5058757651909023675[232] = 0.0;
   out_5058757651909023675[233] = 0.0;
   out_5058757651909023675[234] = 0.0;
   out_5058757651909023675[235] = 0.0;
   out_5058757651909023675[236] = 0.0;
   out_5058757651909023675[237] = 0.0;
   out_5058757651909023675[238] = 0.0;
   out_5058757651909023675[239] = 0.0;
   out_5058757651909023675[240] = 0.0;
   out_5058757651909023675[241] = 0.0;
   out_5058757651909023675[242] = 0.0;
   out_5058757651909023675[243] = 0.0;
   out_5058757651909023675[244] = 0.0;
   out_5058757651909023675[245] = 0.0;
   out_5058757651909023675[246] = 0.0;
   out_5058757651909023675[247] = 1.0;
   out_5058757651909023675[248] = 0.0;
   out_5058757651909023675[249] = 0.0;
   out_5058757651909023675[250] = 0.0;
   out_5058757651909023675[251] = 0.0;
   out_5058757651909023675[252] = 0.0;
   out_5058757651909023675[253] = 0.0;
   out_5058757651909023675[254] = 0.0;
   out_5058757651909023675[255] = 0.0;
   out_5058757651909023675[256] = 0.0;
   out_5058757651909023675[257] = 0.0;
   out_5058757651909023675[258] = 0.0;
   out_5058757651909023675[259] = 0.0;
   out_5058757651909023675[260] = 0.0;
   out_5058757651909023675[261] = 0.0;
   out_5058757651909023675[262] = 0.0;
   out_5058757651909023675[263] = 0.0;
   out_5058757651909023675[264] = 0.0;
   out_5058757651909023675[265] = 0.0;
   out_5058757651909023675[266] = 1.0;
   out_5058757651909023675[267] = 0.0;
   out_5058757651909023675[268] = 0.0;
   out_5058757651909023675[269] = 0.0;
   out_5058757651909023675[270] = 0.0;
   out_5058757651909023675[271] = 0.0;
   out_5058757651909023675[272] = 0.0;
   out_5058757651909023675[273] = 0.0;
   out_5058757651909023675[274] = 0.0;
   out_5058757651909023675[275] = 0.0;
   out_5058757651909023675[276] = 0.0;
   out_5058757651909023675[277] = 0.0;
   out_5058757651909023675[278] = 0.0;
   out_5058757651909023675[279] = 0.0;
   out_5058757651909023675[280] = 0.0;
   out_5058757651909023675[281] = 0.0;
   out_5058757651909023675[282] = 0.0;
   out_5058757651909023675[283] = 0.0;
   out_5058757651909023675[284] = 0.0;
   out_5058757651909023675[285] = 1.0;
   out_5058757651909023675[286] = 0.0;
   out_5058757651909023675[287] = 0.0;
   out_5058757651909023675[288] = 0.0;
   out_5058757651909023675[289] = 0.0;
   out_5058757651909023675[290] = 0.0;
   out_5058757651909023675[291] = 0.0;
   out_5058757651909023675[292] = 0.0;
   out_5058757651909023675[293] = 0.0;
   out_5058757651909023675[294] = 0.0;
   out_5058757651909023675[295] = 0.0;
   out_5058757651909023675[296] = 0.0;
   out_5058757651909023675[297] = 0.0;
   out_5058757651909023675[298] = 0.0;
   out_5058757651909023675[299] = 0.0;
   out_5058757651909023675[300] = 0.0;
   out_5058757651909023675[301] = 0.0;
   out_5058757651909023675[302] = 0.0;
   out_5058757651909023675[303] = 0.0;
   out_5058757651909023675[304] = 1.0;
   out_5058757651909023675[305] = 0.0;
   out_5058757651909023675[306] = 0.0;
   out_5058757651909023675[307] = 0.0;
   out_5058757651909023675[308] = 0.0;
   out_5058757651909023675[309] = 0.0;
   out_5058757651909023675[310] = 0.0;
   out_5058757651909023675[311] = 0.0;
   out_5058757651909023675[312] = 0.0;
   out_5058757651909023675[313] = 0.0;
   out_5058757651909023675[314] = 0.0;
   out_5058757651909023675[315] = 0.0;
   out_5058757651909023675[316] = 0.0;
   out_5058757651909023675[317] = 0.0;
   out_5058757651909023675[318] = 0.0;
   out_5058757651909023675[319] = 0.0;
   out_5058757651909023675[320] = 0.0;
   out_5058757651909023675[321] = 0.0;
   out_5058757651909023675[322] = 0.0;
   out_5058757651909023675[323] = 1.0;
}
void f_fun(double *state, double dt, double *out_7691273876108319397) {
   out_7691273876108319397[0] = atan2((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), -(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]));
   out_7691273876108319397[1] = asin(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]));
   out_7691273876108319397[2] = atan2(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), -(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]));
   out_7691273876108319397[3] = dt*state[12] + state[3];
   out_7691273876108319397[4] = dt*state[13] + state[4];
   out_7691273876108319397[5] = dt*state[14] + state[5];
   out_7691273876108319397[6] = state[6];
   out_7691273876108319397[7] = state[7];
   out_7691273876108319397[8] = state[8];
   out_7691273876108319397[9] = state[9];
   out_7691273876108319397[10] = state[10];
   out_7691273876108319397[11] = state[11];
   out_7691273876108319397[12] = state[12];
   out_7691273876108319397[13] = state[13];
   out_7691273876108319397[14] = state[14];
   out_7691273876108319397[15] = state[15];
   out_7691273876108319397[16] = state[16];
   out_7691273876108319397[17] = state[17];
}
void F_fun(double *state, double dt, double *out_6123810644866746828) {
   out_6123810644866746828[0] = ((-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*cos(state[0])*cos(state[1]) - sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*cos(state[0])*cos(state[1]) - sin(dt*state[6])*sin(state[0])*cos(dt*state[7])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6123810644866746828[1] = ((-sin(dt*state[6])*sin(dt*state[8]) - sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*cos(state[1]) - (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*sin(state[1]) - sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(state[0]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*sin(state[1]) + (-sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) + sin(dt*state[8])*cos(dt*state[6]))*cos(state[1]) - sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(state[0]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6123810644866746828[2] = 0;
   out_6123810644866746828[3] = 0;
   out_6123810644866746828[4] = 0;
   out_6123810644866746828[5] = 0;
   out_6123810644866746828[6] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(dt*cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) - dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6123810644866746828[7] = (-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[6])*sin(dt*state[7])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[6])*sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) - dt*sin(dt*state[6])*sin(state[1])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + (-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))*(-dt*sin(dt*state[7])*cos(dt*state[6])*cos(state[0])*cos(state[1]) + dt*sin(dt*state[8])*sin(state[0])*cos(dt*state[6])*cos(dt*state[7])*cos(state[1]) - dt*sin(state[1])*cos(dt*state[6])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6123810644866746828[8] = ((dt*sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + dt*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (dt*sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]))*(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2)) + ((dt*sin(dt*state[6])*sin(dt*state[8]) + dt*sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (-dt*sin(dt*state[6])*cos(dt*state[8]) + dt*sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]))*(-(sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) + (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) - sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/(pow(-(sin(dt*state[6])*sin(dt*state[8]) + sin(dt*state[7])*cos(dt*state[6])*cos(dt*state[8]))*sin(state[1]) + (-sin(dt*state[6])*cos(dt*state[8]) + sin(dt*state[7])*sin(dt*state[8])*cos(dt*state[6]))*sin(state[0])*cos(state[1]) + cos(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2) + pow((sin(dt*state[6])*sin(dt*state[7])*sin(dt*state[8]) + cos(dt*state[6])*cos(dt*state[8]))*sin(state[0])*cos(state[1]) - (sin(dt*state[6])*sin(dt*state[7])*cos(dt*state[8]) - sin(dt*state[8])*cos(dt*state[6]))*sin(state[1]) + sin(dt*state[6])*cos(dt*state[7])*cos(state[0])*cos(state[1]), 2));
   out_6123810644866746828[9] = 0;
   out_6123810644866746828[10] = 0;
   out_6123810644866746828[11] = 0;
   out_6123810644866746828[12] = 0;
   out_6123810644866746828[13] = 0;
   out_6123810644866746828[14] = 0;
   out_6123810644866746828[15] = 0;
   out_6123810644866746828[16] = 0;
   out_6123810644866746828[17] = 0;
   out_6123810644866746828[18] = (-sin(dt*state[7])*sin(state[0])*cos(state[1]) - sin(dt*state[8])*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6123810644866746828[19] = (-sin(dt*state[7])*sin(state[1])*cos(state[0]) + sin(dt*state[8])*sin(state[0])*sin(state[1])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6123810644866746828[20] = 0;
   out_6123810644866746828[21] = 0;
   out_6123810644866746828[22] = 0;
   out_6123810644866746828[23] = 0;
   out_6123810644866746828[24] = 0;
   out_6123810644866746828[25] = (dt*sin(dt*state[7])*sin(dt*state[8])*sin(state[0])*cos(state[1]) - dt*sin(dt*state[7])*sin(state[1])*cos(dt*state[8]) + dt*cos(dt*state[7])*cos(state[0])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6123810644866746828[26] = (-dt*sin(dt*state[8])*sin(state[1])*cos(dt*state[7]) - dt*sin(state[0])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/sqrt(1 - pow(sin(dt*state[7])*cos(state[0])*cos(state[1]) - sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1]) + sin(state[1])*cos(dt*state[7])*cos(dt*state[8]), 2));
   out_6123810644866746828[27] = 0;
   out_6123810644866746828[28] = 0;
   out_6123810644866746828[29] = 0;
   out_6123810644866746828[30] = 0;
   out_6123810644866746828[31] = 0;
   out_6123810644866746828[32] = 0;
   out_6123810644866746828[33] = 0;
   out_6123810644866746828[34] = 0;
   out_6123810644866746828[35] = 0;
   out_6123810644866746828[36] = ((sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6123810644866746828[37] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-sin(dt*state[7])*sin(state[2])*cos(state[0])*cos(state[1]) + sin(dt*state[8])*sin(state[0])*sin(state[2])*cos(dt*state[7])*cos(state[1]) - sin(state[1])*sin(state[2])*cos(dt*state[7])*cos(dt*state[8]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(-sin(dt*state[7])*cos(state[0])*cos(state[1])*cos(state[2]) + sin(dt*state[8])*sin(state[0])*cos(dt*state[7])*cos(state[1])*cos(state[2]) - sin(state[1])*cos(dt*state[7])*cos(dt*state[8])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6123810644866746828[38] = ((-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (-sin(state[0])*sin(state[1])*sin(state[2]) - cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6123810644866746828[39] = 0;
   out_6123810644866746828[40] = 0;
   out_6123810644866746828[41] = 0;
   out_6123810644866746828[42] = 0;
   out_6123810644866746828[43] = (-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))*(dt*(sin(state[0])*cos(state[2]) - sin(state[1])*sin(state[2])*cos(state[0]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*sin(state[2])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + ((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))*(dt*(-sin(state[0])*sin(state[2]) - sin(state[1])*cos(state[0])*cos(state[2]))*cos(dt*state[7]) - dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[7])*sin(dt*state[8]) - dt*sin(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6123810644866746828[44] = (dt*(sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*sin(state[2])*cos(dt*state[7])*cos(state[1]))*(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2)) + (dt*(sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*cos(dt*state[7])*cos(dt*state[8]) - dt*sin(dt*state[8])*cos(dt*state[7])*cos(state[1])*cos(state[2]))*((-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) - (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) - sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]))/(pow(-(sin(state[0])*sin(state[2]) + sin(state[1])*cos(state[0])*cos(state[2]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*cos(state[2]) - sin(state[2])*cos(state[0]))*sin(dt*state[8])*cos(dt*state[7]) + cos(dt*state[7])*cos(dt*state[8])*cos(state[1])*cos(state[2]), 2) + pow(-(-sin(state[0])*cos(state[2]) + sin(state[1])*sin(state[2])*cos(state[0]))*sin(dt*state[7]) + (sin(state[0])*sin(state[1])*sin(state[2]) + cos(state[0])*cos(state[2]))*sin(dt*state[8])*cos(dt*state[7]) + sin(state[2])*cos(dt*state[7])*cos(dt*state[8])*cos(state[1]), 2));
   out_6123810644866746828[45] = 0;
   out_6123810644866746828[46] = 0;
   out_6123810644866746828[47] = 0;
   out_6123810644866746828[48] = 0;
   out_6123810644866746828[49] = 0;
   out_6123810644866746828[50] = 0;
   out_6123810644866746828[51] = 0;
   out_6123810644866746828[52] = 0;
   out_6123810644866746828[53] = 0;
   out_6123810644866746828[54] = 0;
   out_6123810644866746828[55] = 0;
   out_6123810644866746828[56] = 0;
   out_6123810644866746828[57] = 1;
   out_6123810644866746828[58] = 0;
   out_6123810644866746828[59] = 0;
   out_6123810644866746828[60] = 0;
   out_6123810644866746828[61] = 0;
   out_6123810644866746828[62] = 0;
   out_6123810644866746828[63] = 0;
   out_6123810644866746828[64] = 0;
   out_6123810644866746828[65] = 0;
   out_6123810644866746828[66] = dt;
   out_6123810644866746828[67] = 0;
   out_6123810644866746828[68] = 0;
   out_6123810644866746828[69] = 0;
   out_6123810644866746828[70] = 0;
   out_6123810644866746828[71] = 0;
   out_6123810644866746828[72] = 0;
   out_6123810644866746828[73] = 0;
   out_6123810644866746828[74] = 0;
   out_6123810644866746828[75] = 0;
   out_6123810644866746828[76] = 1;
   out_6123810644866746828[77] = 0;
   out_6123810644866746828[78] = 0;
   out_6123810644866746828[79] = 0;
   out_6123810644866746828[80] = 0;
   out_6123810644866746828[81] = 0;
   out_6123810644866746828[82] = 0;
   out_6123810644866746828[83] = 0;
   out_6123810644866746828[84] = 0;
   out_6123810644866746828[85] = dt;
   out_6123810644866746828[86] = 0;
   out_6123810644866746828[87] = 0;
   out_6123810644866746828[88] = 0;
   out_6123810644866746828[89] = 0;
   out_6123810644866746828[90] = 0;
   out_6123810644866746828[91] = 0;
   out_6123810644866746828[92] = 0;
   out_6123810644866746828[93] = 0;
   out_6123810644866746828[94] = 0;
   out_6123810644866746828[95] = 1;
   out_6123810644866746828[96] = 0;
   out_6123810644866746828[97] = 0;
   out_6123810644866746828[98] = 0;
   out_6123810644866746828[99] = 0;
   out_6123810644866746828[100] = 0;
   out_6123810644866746828[101] = 0;
   out_6123810644866746828[102] = 0;
   out_6123810644866746828[103] = 0;
   out_6123810644866746828[104] = dt;
   out_6123810644866746828[105] = 0;
   out_6123810644866746828[106] = 0;
   out_6123810644866746828[107] = 0;
   out_6123810644866746828[108] = 0;
   out_6123810644866746828[109] = 0;
   out_6123810644866746828[110] = 0;
   out_6123810644866746828[111] = 0;
   out_6123810644866746828[112] = 0;
   out_6123810644866746828[113] = 0;
   out_6123810644866746828[114] = 1;
   out_6123810644866746828[115] = 0;
   out_6123810644866746828[116] = 0;
   out_6123810644866746828[117] = 0;
   out_6123810644866746828[118] = 0;
   out_6123810644866746828[119] = 0;
   out_6123810644866746828[120] = 0;
   out_6123810644866746828[121] = 0;
   out_6123810644866746828[122] = 0;
   out_6123810644866746828[123] = 0;
   out_6123810644866746828[124] = 0;
   out_6123810644866746828[125] = 0;
   out_6123810644866746828[126] = 0;
   out_6123810644866746828[127] = 0;
   out_6123810644866746828[128] = 0;
   out_6123810644866746828[129] = 0;
   out_6123810644866746828[130] = 0;
   out_6123810644866746828[131] = 0;
   out_6123810644866746828[132] = 0;
   out_6123810644866746828[133] = 1;
   out_6123810644866746828[134] = 0;
   out_6123810644866746828[135] = 0;
   out_6123810644866746828[136] = 0;
   out_6123810644866746828[137] = 0;
   out_6123810644866746828[138] = 0;
   out_6123810644866746828[139] = 0;
   out_6123810644866746828[140] = 0;
   out_6123810644866746828[141] = 0;
   out_6123810644866746828[142] = 0;
   out_6123810644866746828[143] = 0;
   out_6123810644866746828[144] = 0;
   out_6123810644866746828[145] = 0;
   out_6123810644866746828[146] = 0;
   out_6123810644866746828[147] = 0;
   out_6123810644866746828[148] = 0;
   out_6123810644866746828[149] = 0;
   out_6123810644866746828[150] = 0;
   out_6123810644866746828[151] = 0;
   out_6123810644866746828[152] = 1;
   out_6123810644866746828[153] = 0;
   out_6123810644866746828[154] = 0;
   out_6123810644866746828[155] = 0;
   out_6123810644866746828[156] = 0;
   out_6123810644866746828[157] = 0;
   out_6123810644866746828[158] = 0;
   out_6123810644866746828[159] = 0;
   out_6123810644866746828[160] = 0;
   out_6123810644866746828[161] = 0;
   out_6123810644866746828[162] = 0;
   out_6123810644866746828[163] = 0;
   out_6123810644866746828[164] = 0;
   out_6123810644866746828[165] = 0;
   out_6123810644866746828[166] = 0;
   out_6123810644866746828[167] = 0;
   out_6123810644866746828[168] = 0;
   out_6123810644866746828[169] = 0;
   out_6123810644866746828[170] = 0;
   out_6123810644866746828[171] = 1;
   out_6123810644866746828[172] = 0;
   out_6123810644866746828[173] = 0;
   out_6123810644866746828[174] = 0;
   out_6123810644866746828[175] = 0;
   out_6123810644866746828[176] = 0;
   out_6123810644866746828[177] = 0;
   out_6123810644866746828[178] = 0;
   out_6123810644866746828[179] = 0;
   out_6123810644866746828[180] = 0;
   out_6123810644866746828[181] = 0;
   out_6123810644866746828[182] = 0;
   out_6123810644866746828[183] = 0;
   out_6123810644866746828[184] = 0;
   out_6123810644866746828[185] = 0;
   out_6123810644866746828[186] = 0;
   out_6123810644866746828[187] = 0;
   out_6123810644866746828[188] = 0;
   out_6123810644866746828[189] = 0;
   out_6123810644866746828[190] = 1;
   out_6123810644866746828[191] = 0;
   out_6123810644866746828[192] = 0;
   out_6123810644866746828[193] = 0;
   out_6123810644866746828[194] = 0;
   out_6123810644866746828[195] = 0;
   out_6123810644866746828[196] = 0;
   out_6123810644866746828[197] = 0;
   out_6123810644866746828[198] = 0;
   out_6123810644866746828[199] = 0;
   out_6123810644866746828[200] = 0;
   out_6123810644866746828[201] = 0;
   out_6123810644866746828[202] = 0;
   out_6123810644866746828[203] = 0;
   out_6123810644866746828[204] = 0;
   out_6123810644866746828[205] = 0;
   out_6123810644866746828[206] = 0;
   out_6123810644866746828[207] = 0;
   out_6123810644866746828[208] = 0;
   out_6123810644866746828[209] = 1;
   out_6123810644866746828[210] = 0;
   out_6123810644866746828[211] = 0;
   out_6123810644866746828[212] = 0;
   out_6123810644866746828[213] = 0;
   out_6123810644866746828[214] = 0;
   out_6123810644866746828[215] = 0;
   out_6123810644866746828[216] = 0;
   out_6123810644866746828[217] = 0;
   out_6123810644866746828[218] = 0;
   out_6123810644866746828[219] = 0;
   out_6123810644866746828[220] = 0;
   out_6123810644866746828[221] = 0;
   out_6123810644866746828[222] = 0;
   out_6123810644866746828[223] = 0;
   out_6123810644866746828[224] = 0;
   out_6123810644866746828[225] = 0;
   out_6123810644866746828[226] = 0;
   out_6123810644866746828[227] = 0;
   out_6123810644866746828[228] = 1;
   out_6123810644866746828[229] = 0;
   out_6123810644866746828[230] = 0;
   out_6123810644866746828[231] = 0;
   out_6123810644866746828[232] = 0;
   out_6123810644866746828[233] = 0;
   out_6123810644866746828[234] = 0;
   out_6123810644866746828[235] = 0;
   out_6123810644866746828[236] = 0;
   out_6123810644866746828[237] = 0;
   out_6123810644866746828[238] = 0;
   out_6123810644866746828[239] = 0;
   out_6123810644866746828[240] = 0;
   out_6123810644866746828[241] = 0;
   out_6123810644866746828[242] = 0;
   out_6123810644866746828[243] = 0;
   out_6123810644866746828[244] = 0;
   out_6123810644866746828[245] = 0;
   out_6123810644866746828[246] = 0;
   out_6123810644866746828[247] = 1;
   out_6123810644866746828[248] = 0;
   out_6123810644866746828[249] = 0;
   out_6123810644866746828[250] = 0;
   out_6123810644866746828[251] = 0;
   out_6123810644866746828[252] = 0;
   out_6123810644866746828[253] = 0;
   out_6123810644866746828[254] = 0;
   out_6123810644866746828[255] = 0;
   out_6123810644866746828[256] = 0;
   out_6123810644866746828[257] = 0;
   out_6123810644866746828[258] = 0;
   out_6123810644866746828[259] = 0;
   out_6123810644866746828[260] = 0;
   out_6123810644866746828[261] = 0;
   out_6123810644866746828[262] = 0;
   out_6123810644866746828[263] = 0;
   out_6123810644866746828[264] = 0;
   out_6123810644866746828[265] = 0;
   out_6123810644866746828[266] = 1;
   out_6123810644866746828[267] = 0;
   out_6123810644866746828[268] = 0;
   out_6123810644866746828[269] = 0;
   out_6123810644866746828[270] = 0;
   out_6123810644866746828[271] = 0;
   out_6123810644866746828[272] = 0;
   out_6123810644866746828[273] = 0;
   out_6123810644866746828[274] = 0;
   out_6123810644866746828[275] = 0;
   out_6123810644866746828[276] = 0;
   out_6123810644866746828[277] = 0;
   out_6123810644866746828[278] = 0;
   out_6123810644866746828[279] = 0;
   out_6123810644866746828[280] = 0;
   out_6123810644866746828[281] = 0;
   out_6123810644866746828[282] = 0;
   out_6123810644866746828[283] = 0;
   out_6123810644866746828[284] = 0;
   out_6123810644866746828[285] = 1;
   out_6123810644866746828[286] = 0;
   out_6123810644866746828[287] = 0;
   out_6123810644866746828[288] = 0;
   out_6123810644866746828[289] = 0;
   out_6123810644866746828[290] = 0;
   out_6123810644866746828[291] = 0;
   out_6123810644866746828[292] = 0;
   out_6123810644866746828[293] = 0;
   out_6123810644866746828[294] = 0;
   out_6123810644866746828[295] = 0;
   out_6123810644866746828[296] = 0;
   out_6123810644866746828[297] = 0;
   out_6123810644866746828[298] = 0;
   out_6123810644866746828[299] = 0;
   out_6123810644866746828[300] = 0;
   out_6123810644866746828[301] = 0;
   out_6123810644866746828[302] = 0;
   out_6123810644866746828[303] = 0;
   out_6123810644866746828[304] = 1;
   out_6123810644866746828[305] = 0;
   out_6123810644866746828[306] = 0;
   out_6123810644866746828[307] = 0;
   out_6123810644866746828[308] = 0;
   out_6123810644866746828[309] = 0;
   out_6123810644866746828[310] = 0;
   out_6123810644866746828[311] = 0;
   out_6123810644866746828[312] = 0;
   out_6123810644866746828[313] = 0;
   out_6123810644866746828[314] = 0;
   out_6123810644866746828[315] = 0;
   out_6123810644866746828[316] = 0;
   out_6123810644866746828[317] = 0;
   out_6123810644866746828[318] = 0;
   out_6123810644866746828[319] = 0;
   out_6123810644866746828[320] = 0;
   out_6123810644866746828[321] = 0;
   out_6123810644866746828[322] = 0;
   out_6123810644866746828[323] = 1;
}
void h_4(double *state, double *unused, double *out_6926576296604605753) {
   out_6926576296604605753[0] = state[6] + state[9];
   out_6926576296604605753[1] = state[7] + state[10];
   out_6926576296604605753[2] = state[8] + state[11];
}
void H_4(double *state, double *unused, double *out_6256705133791921779) {
   out_6256705133791921779[0] = 0;
   out_6256705133791921779[1] = 0;
   out_6256705133791921779[2] = 0;
   out_6256705133791921779[3] = 0;
   out_6256705133791921779[4] = 0;
   out_6256705133791921779[5] = 0;
   out_6256705133791921779[6] = 1;
   out_6256705133791921779[7] = 0;
   out_6256705133791921779[8] = 0;
   out_6256705133791921779[9] = 1;
   out_6256705133791921779[10] = 0;
   out_6256705133791921779[11] = 0;
   out_6256705133791921779[12] = 0;
   out_6256705133791921779[13] = 0;
   out_6256705133791921779[14] = 0;
   out_6256705133791921779[15] = 0;
   out_6256705133791921779[16] = 0;
   out_6256705133791921779[17] = 0;
   out_6256705133791921779[18] = 0;
   out_6256705133791921779[19] = 0;
   out_6256705133791921779[20] = 0;
   out_6256705133791921779[21] = 0;
   out_6256705133791921779[22] = 0;
   out_6256705133791921779[23] = 0;
   out_6256705133791921779[24] = 0;
   out_6256705133791921779[25] = 1;
   out_6256705133791921779[26] = 0;
   out_6256705133791921779[27] = 0;
   out_6256705133791921779[28] = 1;
   out_6256705133791921779[29] = 0;
   out_6256705133791921779[30] = 0;
   out_6256705133791921779[31] = 0;
   out_6256705133791921779[32] = 0;
   out_6256705133791921779[33] = 0;
   out_6256705133791921779[34] = 0;
   out_6256705133791921779[35] = 0;
   out_6256705133791921779[36] = 0;
   out_6256705133791921779[37] = 0;
   out_6256705133791921779[38] = 0;
   out_6256705133791921779[39] = 0;
   out_6256705133791921779[40] = 0;
   out_6256705133791921779[41] = 0;
   out_6256705133791921779[42] = 0;
   out_6256705133791921779[43] = 0;
   out_6256705133791921779[44] = 1;
   out_6256705133791921779[45] = 0;
   out_6256705133791921779[46] = 0;
   out_6256705133791921779[47] = 1;
   out_6256705133791921779[48] = 0;
   out_6256705133791921779[49] = 0;
   out_6256705133791921779[50] = 0;
   out_6256705133791921779[51] = 0;
   out_6256705133791921779[52] = 0;
   out_6256705133791921779[53] = 0;
}
void h_10(double *state, double *unused, double *out_9066166637456014375) {
   out_9066166637456014375[0] = 9.8100000000000005*sin(state[1]) - state[4]*state[8] + state[5]*state[7] + state[12] + state[15];
   out_9066166637456014375[1] = -9.8100000000000005*sin(state[0])*cos(state[1]) + state[3]*state[8] - state[5]*state[6] + state[13] + state[16];
   out_9066166637456014375[2] = -9.8100000000000005*cos(state[0])*cos(state[1]) - state[3]*state[7] + state[4]*state[6] + state[14] + state[17];
}
void H_10(double *state, double *unused, double *out_8818018586628651595) {
   out_8818018586628651595[0] = 0;
   out_8818018586628651595[1] = 9.8100000000000005*cos(state[1]);
   out_8818018586628651595[2] = 0;
   out_8818018586628651595[3] = 0;
   out_8818018586628651595[4] = -state[8];
   out_8818018586628651595[5] = state[7];
   out_8818018586628651595[6] = 0;
   out_8818018586628651595[7] = state[5];
   out_8818018586628651595[8] = -state[4];
   out_8818018586628651595[9] = 0;
   out_8818018586628651595[10] = 0;
   out_8818018586628651595[11] = 0;
   out_8818018586628651595[12] = 1;
   out_8818018586628651595[13] = 0;
   out_8818018586628651595[14] = 0;
   out_8818018586628651595[15] = 1;
   out_8818018586628651595[16] = 0;
   out_8818018586628651595[17] = 0;
   out_8818018586628651595[18] = -9.8100000000000005*cos(state[0])*cos(state[1]);
   out_8818018586628651595[19] = 9.8100000000000005*sin(state[0])*sin(state[1]);
   out_8818018586628651595[20] = 0;
   out_8818018586628651595[21] = state[8];
   out_8818018586628651595[22] = 0;
   out_8818018586628651595[23] = -state[6];
   out_8818018586628651595[24] = -state[5];
   out_8818018586628651595[25] = 0;
   out_8818018586628651595[26] = state[3];
   out_8818018586628651595[27] = 0;
   out_8818018586628651595[28] = 0;
   out_8818018586628651595[29] = 0;
   out_8818018586628651595[30] = 0;
   out_8818018586628651595[31] = 1;
   out_8818018586628651595[32] = 0;
   out_8818018586628651595[33] = 0;
   out_8818018586628651595[34] = 1;
   out_8818018586628651595[35] = 0;
   out_8818018586628651595[36] = 9.8100000000000005*sin(state[0])*cos(state[1]);
   out_8818018586628651595[37] = 9.8100000000000005*sin(state[1])*cos(state[0]);
   out_8818018586628651595[38] = 0;
   out_8818018586628651595[39] = -state[7];
   out_8818018586628651595[40] = state[6];
   out_8818018586628651595[41] = 0;
   out_8818018586628651595[42] = state[4];
   out_8818018586628651595[43] = -state[3];
   out_8818018586628651595[44] = 0;
   out_8818018586628651595[45] = 0;
   out_8818018586628651595[46] = 0;
   out_8818018586628651595[47] = 0;
   out_8818018586628651595[48] = 0;
   out_8818018586628651595[49] = 0;
   out_8818018586628651595[50] = 1;
   out_8818018586628651595[51] = 0;
   out_8818018586628651595[52] = 0;
   out_8818018586628651595[53] = 1;
}
void h_13(double *state, double *unused, double *out_8808739167586425245) {
   out_8808739167586425245[0] = state[3];
   out_8808739167586425245[1] = state[4];
   out_8808739167586425245[2] = state[5];
}
void H_13(double *state, double *unused, double *out_4579407731600928908) {
   out_4579407731600928908[0] = 0;
   out_4579407731600928908[1] = 0;
   out_4579407731600928908[2] = 0;
   out_4579407731600928908[3] = 1;
   out_4579407731600928908[4] = 0;
   out_4579407731600928908[5] = 0;
   out_4579407731600928908[6] = 0;
   out_4579407731600928908[7] = 0;
   out_4579407731600928908[8] = 0;
   out_4579407731600928908[9] = 0;
   out_4579407731600928908[10] = 0;
   out_4579407731600928908[11] = 0;
   out_4579407731600928908[12] = 0;
   out_4579407731600928908[13] = 0;
   out_4579407731600928908[14] = 0;
   out_4579407731600928908[15] = 0;
   out_4579407731600928908[16] = 0;
   out_4579407731600928908[17] = 0;
   out_4579407731600928908[18] = 0;
   out_4579407731600928908[19] = 0;
   out_4579407731600928908[20] = 0;
   out_4579407731600928908[21] = 0;
   out_4579407731600928908[22] = 1;
   out_4579407731600928908[23] = 0;
   out_4579407731600928908[24] = 0;
   out_4579407731600928908[25] = 0;
   out_4579407731600928908[26] = 0;
   out_4579407731600928908[27] = 0;
   out_4579407731600928908[28] = 0;
   out_4579407731600928908[29] = 0;
   out_4579407731600928908[30] = 0;
   out_4579407731600928908[31] = 0;
   out_4579407731600928908[32] = 0;
   out_4579407731600928908[33] = 0;
   out_4579407731600928908[34] = 0;
   out_4579407731600928908[35] = 0;
   out_4579407731600928908[36] = 0;
   out_4579407731600928908[37] = 0;
   out_4579407731600928908[38] = 0;
   out_4579407731600928908[39] = 0;
   out_4579407731600928908[40] = 0;
   out_4579407731600928908[41] = 1;
   out_4579407731600928908[42] = 0;
   out_4579407731600928908[43] = 0;
   out_4579407731600928908[44] = 0;
   out_4579407731600928908[45] = 0;
   out_4579407731600928908[46] = 0;
   out_4579407731600928908[47] = 0;
   out_4579407731600928908[48] = 0;
   out_4579407731600928908[49] = 0;
   out_4579407731600928908[50] = 0;
   out_4579407731600928908[51] = 0;
   out_4579407731600928908[52] = 0;
   out_4579407731600928908[53] = 0;
}
void h_14(double *state, double *unused, double *out_5822426025914201853) {
   out_5822426025914201853[0] = state[6];
   out_5822426025914201853[1] = state[7];
   out_5822426025914201853[2] = state[8];
}
void H_14(double *state, double *unused, double *out_3173916701496549483) {
   out_3173916701496549483[0] = 0;
   out_3173916701496549483[1] = 0;
   out_3173916701496549483[2] = 0;
   out_3173916701496549483[3] = 0;
   out_3173916701496549483[4] = 0;
   out_3173916701496549483[5] = 0;
   out_3173916701496549483[6] = 1;
   out_3173916701496549483[7] = 0;
   out_3173916701496549483[8] = 0;
   out_3173916701496549483[9] = 0;
   out_3173916701496549483[10] = 0;
   out_3173916701496549483[11] = 0;
   out_3173916701496549483[12] = 0;
   out_3173916701496549483[13] = 0;
   out_3173916701496549483[14] = 0;
   out_3173916701496549483[15] = 0;
   out_3173916701496549483[16] = 0;
   out_3173916701496549483[17] = 0;
   out_3173916701496549483[18] = 0;
   out_3173916701496549483[19] = 0;
   out_3173916701496549483[20] = 0;
   out_3173916701496549483[21] = 0;
   out_3173916701496549483[22] = 0;
   out_3173916701496549483[23] = 0;
   out_3173916701496549483[24] = 0;
   out_3173916701496549483[25] = 1;
   out_3173916701496549483[26] = 0;
   out_3173916701496549483[27] = 0;
   out_3173916701496549483[28] = 0;
   out_3173916701496549483[29] = 0;
   out_3173916701496549483[30] = 0;
   out_3173916701496549483[31] = 0;
   out_3173916701496549483[32] = 0;
   out_3173916701496549483[33] = 0;
   out_3173916701496549483[34] = 0;
   out_3173916701496549483[35] = 0;
   out_3173916701496549483[36] = 0;
   out_3173916701496549483[37] = 0;
   out_3173916701496549483[38] = 0;
   out_3173916701496549483[39] = 0;
   out_3173916701496549483[40] = 0;
   out_3173916701496549483[41] = 0;
   out_3173916701496549483[42] = 0;
   out_3173916701496549483[43] = 0;
   out_3173916701496549483[44] = 1;
   out_3173916701496549483[45] = 0;
   out_3173916701496549483[46] = 0;
   out_3173916701496549483[47] = 0;
   out_3173916701496549483[48] = 0;
   out_3173916701496549483[49] = 0;
   out_3173916701496549483[50] = 0;
   out_3173916701496549483[51] = 0;
   out_3173916701496549483[52] = 0;
   out_3173916701496549483[53] = 0;
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

void pose_update_4(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_4, H_4, NULL, in_z, in_R, in_ea, MAHA_THRESH_4);
}
void pose_update_10(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_10, H_10, NULL, in_z, in_R, in_ea, MAHA_THRESH_10);
}
void pose_update_13(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_13, H_13, NULL, in_z, in_R, in_ea, MAHA_THRESH_13);
}
void pose_update_14(double *in_x, double *in_P, double *in_z, double *in_R, double *in_ea) {
  update<3, 3, 0>(in_x, in_P, h_14, H_14, NULL, in_z, in_R, in_ea, MAHA_THRESH_14);
}
void pose_err_fun(double *nom_x, double *delta_x, double *out_2056840914183716702) {
  err_fun(nom_x, delta_x, out_2056840914183716702);
}
void pose_inv_err_fun(double *nom_x, double *true_x, double *out_4454043914811945605) {
  inv_err_fun(nom_x, true_x, out_4454043914811945605);
}
void pose_H_mod_fun(double *state, double *out_5058757651909023675) {
  H_mod_fun(state, out_5058757651909023675);
}
void pose_f_fun(double *state, double dt, double *out_7691273876108319397) {
  f_fun(state,  dt, out_7691273876108319397);
}
void pose_F_fun(double *state, double dt, double *out_6123810644866746828) {
  F_fun(state,  dt, out_6123810644866746828);
}
void pose_h_4(double *state, double *unused, double *out_6926576296604605753) {
  h_4(state, unused, out_6926576296604605753);
}
void pose_H_4(double *state, double *unused, double *out_6256705133791921779) {
  H_4(state, unused, out_6256705133791921779);
}
void pose_h_10(double *state, double *unused, double *out_9066166637456014375) {
  h_10(state, unused, out_9066166637456014375);
}
void pose_H_10(double *state, double *unused, double *out_8818018586628651595) {
  H_10(state, unused, out_8818018586628651595);
}
void pose_h_13(double *state, double *unused, double *out_8808739167586425245) {
  h_13(state, unused, out_8808739167586425245);
}
void pose_H_13(double *state, double *unused, double *out_4579407731600928908) {
  H_13(state, unused, out_4579407731600928908);
}
void pose_h_14(double *state, double *unused, double *out_5822426025914201853) {
  h_14(state, unused, out_5822426025914201853);
}
void pose_H_14(double *state, double *unused, double *out_3173916701496549483) {
  H_14(state, unused, out_3173916701496549483);
}
void pose_predict(double *in_x, double *in_P, double *in_Q, double dt) {
  predict(in_x, in_P, in_Q, dt);
}
}

const EKF pose = {
  .name = "pose",
  .kinds = { 4, 10, 13, 14 },
  .feature_kinds = {  },
  .f_fun = pose_f_fun,
  .F_fun = pose_F_fun,
  .err_fun = pose_err_fun,
  .inv_err_fun = pose_inv_err_fun,
  .H_mod_fun = pose_H_mod_fun,
  .predict = pose_predict,
  .hs = {
    { 4, pose_h_4 },
    { 10, pose_h_10 },
    { 13, pose_h_13 },
    { 14, pose_h_14 },
  },
  .Hs = {
    { 4, pose_H_4 },
    { 10, pose_H_10 },
    { 13, pose_H_13 },
    { 14, pose_H_14 },
  },
  .updates = {
    { 4, pose_update_4 },
    { 10, pose_update_10 },
    { 13, pose_update_13 },
    { 14, pose_update_14 },
  },
  .Hes = {
  },
  .sets = {
  },
  .extra_routines = {
  },
};

ekf_lib_init(pose)
