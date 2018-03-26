//NA49
//Centrality: mid-central E= 158 AGeV
// 
//pion v2 versus pT
const float NA49_v2_pi_158_pT_bins[16] = {0.025000, 0.075000, 0.125000, 0.175000, 0.225000, 0.275000, 0.325000, 0.375000, 0.450000, 0.550000, 0.650000, 0.750000, 0.900000, 1.100000, 1.400000, 1.800000};
const float NA49_v2_pi_158_pT_value[16] = {0.001996, 0.005658, 0.009174, 0.014097, 0.017529, 0.022674, 0.024777, 0.029069, 0.036871, 0.045733, 0.055261, 0.060024, 0.076119, 0.098258, 0.108228, 0.116131};
const float NA49_v2_pi_158_pT_error[16] = {0.001970, 0.001216, 0.001060, 0.001048, 0.001087, 0.001151, 0.001232, 0.001327, 0.001081, 0.001332, 0.001646, 0.002079, 0.002163, 0.003319, 0.004408, 0.009742};

//proton v2 versus pT
const float NA49_v2_p_158_pT_bins[10] = {0.100000, 0.300000, 0.500000, 0.700000, 0.900000, 1.100000, 1.300000, 1.500000, 1.700000, 1.900000};
const float NA49_v2_p_158_pT_bins_error[10] = {0., 0., 0., 0., 0., 0., 0., 0., 0., 0.};
const float NA49_v2_p_158_pT_value[10] = {0.021050, 0.022376, 0.016868, 0.016236, 0.039938, 0.056425, 0.087632, 0.098544, 0.127763, 0.130592};
const float NA49_v2_p_158_pT_error[10] =  {0.014947, 0.009315, 0.009128, 0.005324, 0.005943, 0.007557, 0.010846, 0.014054, 0.013090, 0.016607};

//proton v2 versus rapidity
const float NA49_v2_p_158_Y_bins[4] = {0.280000, 0.680000, 1.080000, 1.480000};
const float NA49_v2_p_158_Y_value[4] = {0.032000, 0.035288, 0.028587, 0.030498};
const float NA49_v2_p_158_Y_error[4] = {0.004122, 0.003172, 0.002854, 0.003085};

//Centrality: mid-central E= 40 AGeV
//proton v2 versus pT

const float NA49_v2_p_40_pT_bins[5] = {0.200000, 0.600000, 1.000000, 1.400000, 1.800000};
const float NA49_v2_p_40_pT_bins_error[5] = {0., 0., 0., 0., 0.};
const float NA49_v2_p_40_pT_value[5] = {-0.009078, -0.002772, 0.030819, 0.078349, 0.055943};
const float NA49_v2_p_40_pT_error[5] = {0.014115, 0.005836, 0.006384, 0.010387, 0.019183};

// ************************************
// NA49 40 AGeV standard method data 
// ************************************

// Centrality: min bias
// pion v1 versus rapidity
const float NA49_v1_mbias_pi_40_Y_bins[]  = {0.030000, 0.230000, 0.430000, 0.630000, 0.830000, 1.030000, 1.230000, 1.430000, 1.630000};
const float NA49_v1_mbias_pi_40_Y_value[] = {-0.001814, -0.000882, -0.005226, -0.006014, -0.011072, -0.018949, -0.025561, -0.032546, -0.037069};
const float NA49_v1_mbias_pi_40_Y_error[] =  {0.001582, 0.001582, 0.001645, 0.001796, 0.001940, 0.001997, 0.002079, 0.002244, 0.002539};

// pion v1 versus pt
const float NA49_v1_mbias_pi_40_pT_bins[]= {0.040000, 0.140000, 0.240000, 0.340000, 0.440000, 0.540000, 0.640000, 0.740000, 0.890000, 1.090000, 1.290000, 1.490000, 1.790000};
const float NA49_v1_mbias_pi_40_pT_value[] = {-0.021456, -0.018266, -0.007137, -0.009428, -0.012974, -0.013528, -0.011616, -0.007868, -0.002078, 0.014924, 0.017013, 0.024791, 0.034213};
const float NA49_v1_mbias_pi_40_pT_error[] = {0.001743, 0.001270, 0.001476, 0.001705, 0.001988, 0.002373, 0.002875, 0.003486, 0.003349, 0.005022, 0.007656, 0.011694, 0.014520};

//pion v2 versus rapidity
const float NA49_v2_mbias_pi_40_Y_bins[] = {0.090000, 0.290000, 0.490000, 0.690000, 0.890000, 1.090000, 1.290000, 1.490000, 1.690000};
const float NA49_v2_mbias_pi_40_Y_value[] = {0.018754, 0.019863, 0.017544, 0.012971, 0.019025, 0.021103, 0.035542, 0.026456, 0.011133};
const float NA49_v2_mbias_pi_40_Y_error[] = {0.005720, 0.005752, 0.005918, 0.006015, 0.006483, 0.006979, 0.007702, 0.008770, 0.010347};

//pion v2 versus pt
const float NA49_v2_mbias_pi_40_pT_bins[]= {0.060000, 0.160000, 0.260000, 0.360000, 0.460000, 0.560000, 0.660000, 0.760000, 0.910000, 1.110000, 1.310000, 1.510000, 1.810000};
const float NA49_v2_mbias_pi_40_pT_value[] =  {0.004931, 0.001791, 0.011467, 0.017065, 0.021747, 0.027708, 0.039545, 0.051243, 0.061393, 0.071502, 0.122695, 0.115874, 0.12097};
const float NA49_v2_mbias_pi_40_pT_error[] = {0.007414, 0.004777, 0.005414, 0.005912, 0.006731, 0.007865, 0.009501, 0.011567, 0.011149, 0.016915, 0.026085, 0.039814, 0.053058};


//Centrality: central

//pion v1 versus rapidity
const float NA49_v1_centr_pi_40_Y_bins[] = {0.090000, 0.290000, 0.490000, 0.690000, 0.890000, 1.090000, 1.290000, 1.490000, 1.690000};
const float NA49_v1_centr_pi_40_Y_value[] = {-0.002917, -0.001064, -0.005188, 0.000165, -0.006057, -0.010585, -0.016514, -0.021671, -0.021830};
const float NA49_v1_centr_pi_40_Y_error[] = {0.002751, 0.002762, 0.002888, 0.003165, 0.003426, 0.003532, 0.003687, 0.004000, 0.004559};

//pion v1 versus pt
const float NA49_v1_centr_pi_40_pT_bins[] = {0.060000, 0.160000, 0.260000, 0.360000, 0.460000, 0.560000, 0.660000, 0.760000, 0.910000, 1.110000, 1.310000, 1.510000, 1.810000};
const float NA49_v1_centr_pi_40_pT_value[] = {-0.024160, -0.013253, -0.004783, -0.000505, -0.005080, -0.009384, -0.002377, -0.004053, -0.001248, 0.022148, 0.013643, 0.007168, 0.011767};
const float NA49_v1_centr_pi_40_pT_error[] = {0.003133, 0.002263, 0.002610, 0.002996, 0.003476, 0.004130, 0.004980, 0.006008, 0.005742, 0.008518, 0.012902, 0.019462, 0.022513};

//pion v2 versus rapidity
const float NA49_v2_centr_pi_40_Y_bins[] = {0.090000, 0.290000, 0.490000, 0.690000, 0.890000, 1.090000, 1.290000, 1.490000, 1.690000};
const float NA49_v2_centr_pi_40_Y_value[] = {-0.009240, -0.000071, -0.000733, -0.009338, -0.010038, 0.007246, 0.045612, 0.051558, -0.026392};
const float NA49_v2_centr_pi_40_Y_error[] = {0.016173, 0.016304, 0.016799, 0.017105, 0.018528, 0.020074, 0.022294, 0.025597, 0.030496};

//pion v2 versus pt
const float NA49_v2_centr_pi_40_pT_bins[] = {0.060000, 0.160000, 0.260000, 0.360000, 0.460000, 0.560000, 0.660000, 0.760000, 0.910000, 1.110000, 1.310000, 1.510000, 1.810000};
const float NA49_v2_centr_pi_40_pT_value[] = {0.013361, -0.013973, -0.008927, 0.003440, -0.018276, -0.008425, 0.016685, 0.040448, 0.040749, 0.032528, 0.124015, 0.095045, 0.133742};
const float NA49_v2_centr_pi_40_pT_error[] = {0.021908, 0.013895, 0.015526, 0.016826, 0.019069, 0.022166, 0.026685, 0.032319, 0.030887, 0.046341, 0.070777, 0.107107, 0.112914};


//Centrality: mid-central

//pion v1 versus rapidity
const float NA49_v1_mcentr_pi_40_Y_bins[] = {0.060000, 0.260000, 0.460000, 0.660000, 0.860000, 1.060000, 1.260000, 1.460000, 1.660000};
const float NA49_v1_mcentr_pi_40_Y_value[] = {-0.001103, -0.001252, -0.004370, -0.008522, -0.011762, -0.020268, -0.029440, -0.035648, -0.043193};
const float NA49_v1_mcentr_pi_40_Y_error[] = {0.002042, 0.002036, 0.002102, 0.002293, 0.002483, 0.002568, 0.002685, 0.002905, 0.003290};

//pion v1 versus pt
const float NA49_v1_mcentr_pi_40_pT_bins[] = {0.050000, 0.150000, 0.250000, 0.350000, 0.450000, 0.550000, 0.650000, 0.750000, 0.900000, 1.100000, 1.300000, 1.500000, 1.800000};
const float NA49_v1_mcentr_pi_40_pT_value[] = {-0.020437, -0.020135, -0.007285, -0.013533, -0.015285, -0.012257, -0.017684, -0.011000, 0.002180, 0.005412, 0.025699, 0.044994, 0.062799};
const float NA49_v1_mcentr_pi_40_pT_error[] = {0.002234, 0.001629, 0.001890, 0.002187, 0.002557, 0.003063, 0.003726, 0.004541, 0.004365, 0.006611, 0.010104, 0.015539, 0.018450};

//pion v2 versus rapidity
const float NA49_v2_mcentr_pi_40_Y_bins[] = {0.060000, 0.260000, 0.460000, 0.660000, 0.860000, 1.060000, 1.260000, 1.460000, 1.660000};
const float NA49_v2_mcentr_pi_40_Y_value[] = {0.024770, 0.023833, 0.023160, 0.019666, 0.032268, 0.024772, 0.031206, 0.022143, 0.030117};
const float NA49_v2_mcentr_pi_40_Y_error[] = {0.004201, 0.004208, 0.004344, 0.004440, 0.004779, 0.005149, 0.005708, 0.006510, 0.007703};

//pion v2 versus pt
const float NA49_v2_mcentr_pi_40_pT_bins[] = {0.050000, 0.150000, 0.250000, 0.350000, 0.450000, 0.550000, 0.650000, 0.750000, 0.900000, 1.100000, 1.300000, 1.500000, 1.800000};
const float NA49_v2_mcentr_pi_40_pT_value[] = {-0.003180, 0.010014, 0.016026, 0.024243, 0.032966, 0.041051, 0.049668, 0.053051, 0.065806, 0.093092, 0.117910, 0.113181, 0.130355};
const float NA49_v2_mcentr_pi_40_pT_error[] = {0.005445, 0.003514, 0.003980, 0.004329, 0.004934, 0.005813, 0.007037, 0.008615, 0.008376, 0.012768, 0.019785, 0.030081, 0.040669};


//Centrality: peripheral

//pion v1 versus rapidity
const float NA49_v1_per_pi_40_Y_bins[] = {0.030000, 0.230000, 0.430000, 0.630000, 0.830000, 1.030000, 1.230000, 1.430000, 1.630000};
const float NA49_v1_per_pi_40_Y_value[] = {0.000573, -0.004717, -0.012663, -0.018926, -0.033673, -0.045617, -0.053355, -0.073629, -0.086166};
const float NA49_v1_per_pi_40_Y_error[] = {0.002462, 0.002437, 0.002501, 0.002700, 0.002936, 0.003021, 0.003147, 0.003398, 0.003793};

//pion v1 versus pt
const float NA49_v1_per_pi_40_pT_bins[] = {0.040000, 0.140000, 0.240000, 0.340000, 0.440000, 0.540000, 0.640000, 0.740000, 0.890000, 1.090000, 1.290000, 1.490000, 1.790000};
const float NA49_v1_per_pi_40_pT_value[] = {-0.021820, -0.030928, -0.026938, -0.032392, -0.041378, -0.036585, -0.029139, -0.021672, -0.022864, 0.004461, -0.005396, 0.031558, 0.003868};
const float NA49_v1_per_pi_40_pT_error[] = {0.002614, 0.001889, 0.002207, 0.002577, 0.003042, 0.003682, 0.004526, 0.005563, 0.005500, 0.008517, 0.013315, 0.021167, 0.011700};

//pion v2 versus rapidity
const float NA49_v2_per_pi_40_Y_bins[] = {0.030000, 0.230000, 0.430000, 0.630000, 0.830000, 1.030000, 1.230000, 1.430000, 1.630000};
const float NA49_v2_per_pi_40_Y_value[] = {0.061216, 0.043069, 0.041216, 0.025346, 0.031566, 0.034724, 0.045622, 0.009114, 0.017752};
const float NA49_v2_per_pi_40_Y_error[] = {0.007401, 0.007365, 0.007576, 0.007737, 0.008329, 0.008876, 0.009790, 0.011048, 0.012956};

//pion v2 versus pt
const float NA49_v2_per_pi_40_pT_bins[] = {0.040000, 0.140000, 0.240000, 0.340000, 0.440000, 0.540000, 0.640000, 0.740000, 0.890000, 1.090000, 1.290000, 1.490000, 1.790000};
const float NA49_v2_per_pi_40_pT_value[] = {0.013888, 0.009422, 0.044918, 0.017056, 0.058014, 0.067450, 0.053726, 0.057203, 0.090791, 0.096066, 0.186829, 0.095682, 0.042780};
const float NA49_v2_per_pi_40_pT_error[] = {0.009278, 0.006000, 0.006881, 0.007520, 0.008602, 0.010205, 0.012495, 0.015477, 0.015341, 0.023959, 0.037999, 0.058463, 0.029478};

//pion v1 doubly integrated
const float NA49_v1_per_pi_40__bins[] = {0.114000, 0.238000, 0.405000, 0.582000, 0.715000, 0.862000};
const float NA49_v1_per_pi_40__value[] = {-0.006231, -0.008133, -0.010975, -0.016791, -0.024781, -0.034510};
const float NA49_v1_per_pi_40__error[] = {0.001631, 0.001485, 0.001072, 0.001188, 0.001313, 0.001373};

//pion v2 doubly integrated
const float NA49_v2_per_pi_40__bins[] = {0.248000, 0.415000, 0.592000, 0.725000, 0.872000};
const float NA49_v2_per_pi_40__value[] = {0.002784, 0.023870, 0.027499, 0.035467, 0.038631};
const float NA49_v2_per_pi_40__error[] = {0.006398, 0.002271, 0.002297, 0.003537, 0.004550};


//Centrality: min bias

//proton v1 versus rapidity
const float NA49_v1_mbias_p_40_Y_bins[] = {0.030000, 0.230000, 0.430000, 0.630000, 0.830000, 1.030000, 1.230000, 1.430000, 1.630000};
const float NA49_v1_mbias_p_40_Y_value[] = {0.011493, -0.003981, 0.005275, 0.016351, 0.020721, 0.036335, 0.064065, 0.072681, 0.127169};
const float NA49_v1_mbias_p_40_Y_error[] = {0.006304, 0.005383, 0.004828, 0.004395, 0.004153, 0.004111, 0.004426, 0.005830, 0.006982};

//proton v1 versus pt
const float NA49_v1_mbias_p_40_pT_bins[] = {0.190000, 0.590000, 0.990000, 1.390000, 1.790000};
const float NA49_v1_mbias_p_40_pT_value[] = {0.019550, 0.037704, 0.044694, 0.057269, 0.072862};
const float NA49_v1_mbias_p_40_pT_error[] = {0.006021, 0.002549, 0.003314, 0.005913, 0.011493};

//proton v2 versus rapidity
const float NA49_v2_mbias_p_40_Y_bins[] = {0.090000, 0.290000, 0.490000, 0.690000, 0.890000, 1.090000, 1.290000, 1.490000, 1.690000};
const float NA49_v2_mbias_p_40_Y_value[] = {-0.040500, -0.011498, -0.004003, 0.020053, 0.034678, 0.029657, 0.026706, 0.002980, 0.013873};
const float NA49_v2_mbias_p_40_Y_error[] = {0.012878, 0.013037, 0.013623, 0.013975, 0.014285, 0.014575, 0.015236, 0.017339, 0.018582};

//proton v2 versus pt
const float NA49_v2_mbias_p_40_pT_bins[] = {0.210000, 0.610000, 1.010000, 1.410000, 1.810000};
const float NA49_v2_mbias_p_40_pT_value[] = {0.014621, -0.018605, 0.033131, 0.081133, 0.028649};
const float NA49_v2_mbias_p_40_pT_error[] = {0.019306, 0.007821, 0.008264, 0.013293, 0.024852};


//Centrality: central

//proton v1 versus rapidity
const float NA49_v1_centr_p_40_Y_bins[] = {0.090000, 0.290000, 0.490000, 0.690000, 0.890000, 1.090000, 1.290000, 1.490000, 1.690000};
const float NA49_v1_centr_p_40_Y_value[] = {0.012413, -0.015930, 0.008343, 0.023212, 0.029754, 0.042131, 0.074295, 0.057046, 0.102056};
const float NA49_v1_centr_p_40_Y_error[] = {0.011113, 0.009532, 0.008596, 0.007911, 0.007587, 0.007658, 0.008500, 0.011890, 0.014955};

//proton v1 versus pt
const float NA49_v1_centr_p_40_pT_bins[] = {0.210000, 0.610000, 1.010000, 1.410000, 1.810000};
const float NA49_v1_centr_p_40_pT_value[] = {0.020166, 0.039646, 0.032989, 0.044888, 0.037560};
const float NA49_v1_centr_p_40_pT_error[] = {0.011263, 0.004805, 0.006077, 0.010514, 0.019924};

//proton v2 versus rapidity
const float NA49_v2_centr_p_40_Y_bins[] = {0.090000, 0.290000, 0.490000, 0.690000, 0.890000, 1.090000, 1.290000, 1.490000, 1.690000};
const float NA49_v2_centr_p_40_Y_value[] = {-0.144605, -0.024009, -0.041886, 0.027192, 0.022955, 0.009959, 0.028963, 0.045647, -0.034399};
const float NA49_v2_centr_p_40_Y_error[] = {0.038359, 0.038890, 0.040874, 0.042303, 0.043736, 0.045457, 0.048902, 0.058413, 0.065307};

//proton v2 versus pt
const float NA49_v2_centr_p_40_pT_bins[] = {0.210000, 0.610000, 1.010000, 1.410000, 1.810000};
const float NA49_v2_centr_p_40_pT_value[] = {0.083274, -0.060677, 0.016781, 0.072384, -0.032908};
const float NA49_v2_centr_p_40_pT_error[] = {0.058951, 0.024550, 0.025563, 0.039947, 0.073075};


//Centrality: mid-central

//proton v1 versus rapidity
const float NA49_v1_mcentr_p_40_Y_bins[] = {0.060000, 0.260000, 0.460000, 0.660000, 0.860000, 1.060000, 1.260000, 1.460000, 1.660000};
const float NA49_v1_mcentr_p_40_Y_value[] = {0.009626, 0.006667, 0.002908, 0.011843, 0.021517, 0.033891, 0.065268, 0.087310, 0.149380};
const float NA49_v1_mcentr_p_40_Y_error[] = {0.008276, 0.007043, 0.006319, 0.005730, 0.005387, 0.005304, 0.005635, 0.007097, 0.008346};

//proton v1 versus pt
const float NA49_v1_mcentr_p_40_pT_bins[] = {0.200000, 0.600000, 1.000000, 1.400000, 1.800000};
const float NA49_v1_mcentr_p_40_pT_value[] = {0.015463, 0.038280, 0.058103, 0.071785, 0.105167};
const float NA49_v1_mcentr_p_40_pT_error[] = {0.007601, 0.003261, 0.004325, 0.007780, 0.015245};

//proton v2 versus rapidity
const float NA49_v2_mcentr_p_40_Y_bins[] = {0.060000, 0.260000, 0.460000, 0.660000, 0.860000, 1.060000, 1.260000, 1.460000, 1.660000};
const float NA49_v2_mcentr_p_40_Y_value[] = {0.002357, -0.012401, 0.009431, 0.017015, 0.029420, 0.024909, 0.024376, -0.000210, 0.031832};
const float NA49_v2_mcentr_p_40_Y_error[] = {0.009417, 0.009589, 0.009992, 0.010305, 0.010662, 0.010983, 0.011427, 0.012473, 0.013442};

//proton v2 versus pt
const float NA49_v2_mcentr_p_40_pT_bins[] = {0.200000, 0.600000, 1.000000, 1.400000, 1.800000};
const float NA49_v2_mcentr_p_40_pT_value[] = {-0.009078, -0.002772, 0.030819, 0.078349, 0.055943};
const float NA49_v2_mcentr_p_40_pT_error[] = {0.014115, 0.005836, 0.006384, 0.010387, 0.019183};


//Centrality: peripheral

//proton v1 versus rapidity
const float NA49_v1_per_p_40_Y_bins[] = {0.030000, 0.230000, 0.430000, 0.630000, 0.830000, 1.030000, 1.230000, 1.430000, 1.630000};
const float NA49_v1_per_p_40_Y_value[] = {0.007747, -0.008503, -0.008210, -0.012620, -0.006407, 0.001395, 0.023858, 0.058316, 0.104220};
const float NA49_v1_per_p_40_Y_error[] = {0.010676, 0.008938, 0.007931, 0.007340, 0.006905, 0.006058, 0.006156, 0.007214, 0.008102};

//proton v1 versus pt
const float NA49_v1_per_p_40_pT_bins[] = {0.190000, 0.590000, 0.990000, 1.390000, 1.790000};
const float NA49_v1_per_p_40_pT_value[] = {0.011149, 0.021338, 0.022565, 0.038026, 0.049176};
const float NA49_v1_per_p_40_pT_error[] = {0.008381, 0.003634, 0.005377, 0.010623, 0.021554};

//proton v2 versus rapidity
const float NA49_v2_per_p_40_Y_bins[] = {0.030000, 0.230000, 0.430000, 0.630000, 0.830000, 1.030000, 1.230000, 1.430000, 1.630000};
const float NA49_v2_per_p_40_Y_value[] = {-0.015160, 0.015613, 0.021108, 0.021907, 0.058562, 0.066846, -0.005337, -0.034883, -0.000961};
const float NA49_v2_per_p_40_Y_error[] = {0.017229, 0.017499, 0.018352, 0.021043, 0.021617, 0.018238, 0.018584, 0.019440, 0.020003};

// proton v2 versus pt
const float NA49_v2_per_p_40_pT_bins[] = {0.190000, 0.590000, 0.990000, 1.390000, 1.790000};
const float NA49_v2_per_p_40_pT_value[] = {-0.032652, -0.001256, 0.028596, 0.077278, 0.072583};
const float NA49_v2_per_p_40_pT_error[] = {0.029013, 0.009745, 0.011838, 0.020721, 0.039579};

// proton v1 doubly integrated
const float NA49_v1_per_p_40__bins[] = {0.114000, 0.238000, 0.405000, 0.582000, 0.715000, 0.862000};
const float NA49_v1_per_p_40__value[] = {0.021745, 0.046114, 0.046577, 0.039638, 0.031707, 0.011413};
const float NA49_v1_per_p_40__error[] = {0.004891, 0.004311, 0.002991, 0.003209, 0.003514, 0.003670};

// proton v2 doubly integrated
const float NA49_v2_per_p_40__bins[] = {0.248000, 0.415000, 0.592000, 0.725000, 0.872000};
const float NA49_v2_per_p_40__value[] = {-0.010892, 0.009367, 0.021296, 0.023523, 0.004514};
const float NA49_v2_per_p_40__error[] = {0.015661, 0.005187, 0.005035, 0.007589, 0.010116};