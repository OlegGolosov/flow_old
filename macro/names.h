#include "exp_data/exp_data_NA49.h"
#include "exp_data/exp_data_STAR.h"

const int nres = 30;
const TString PsdName[] = { "PSD1", "PSD2", "PSD3" };
const TString XY[] = {"X", "Y"};

const int colors[] = {/*kOrange,*/ kBlue, kRed, kGreen+2, kMagenta, kBlack};
const int markers[] = { 20, 21, 22, 26, 27, 1};

const std::vector <float> centrality_bins = {0,15,35,60,100};
const int ncentr = 4;

const TString psd_psd[] = {"PSD1_PSD2", "PSD1_PSD3", "PSD2_PSD3"};
const TString var[] = {"pT", "eta"};
const float x_range[2][2] = { {0.,3}, {-0.6,2.4} };
const float y_range[2][2] = { {-0.06,0.06}, {-0.15,0.05} };
const float y_range_v2[2][2] = { {-0.2,0.2}, {-0.2,0.2} };

const bool issim=false;

const std::vector <float> v2axis[2] = { { 0., .2, .4, .6, 1., 1.4, 2.2, 3.0 }, {-0.6, 0., 0.6, 1.2, 1.8, 2.4} } ;
const std::string axisName[2] = { "0Pt", "0Rapidity" } ;

const TString v2[4][3] = 
{
    {"X2XX", "XX", ""  },
    {"X2YY", "YY", ""  },
    {"Y2XY", "X", "Y" },
    {"Y2YX", "Y", "X" }
};

const TString sres[][5] = 
{
    { "PSD1_PSD2_XX", "PSD1_PSD3_XX", "PSD2_PSD3_XX", "RES_PSD1_X_0", "<Q^{PSD1}_{x}  Q^{PSD2}_{x}> <Q^{PSD1}_{x}  Q^{PSD3}_{x}> / <Q^{PSD2}_{x}  Q^{PSD3}_{x}>"},  //PSD1 X
    { "STS_R2_PSD1_PSD2_X2XX", "PSD1_PSD3_XX", "STS_R2_PSD2_PSD3_X2XX", "RES_PSD1_X_1", "<Q^{PSD1}_{x}  Q^{PSD3}_{x}> <Q^{STS}_{2,x} Q^{PSD1}_{x}  Q^{PSD2}_{x}> / < Q^{STS}_{2,x} Q^{PSD2}_{x}  Q^{PSD3}_{x}>" }, //PSD1 X
    { "STS_R2_PSD1_PSD3_X2XX", "PSD1_PSD2_XX", "STS_R2_PSD2_PSD3_X2XX", "RES_PSD1_X_2", "<Q^{PSD1}_{x}  Q^{PSD2}_{x}> <Q^{STS}_{2,x} Q^{PSD1}_{x}  Q^{PSD3}_{x}> / < Q^{STS}_{2,x} Q^{PSD2}_{x}  Q^{PSD3}_{x}>" }, //PSD1 X
    { "STS_R2_PSD1_PSD2_Y2XY", "PSD1_PSD3_XX", "STS_R2_PSD2_PSD3_Y2YX", "RES_PSD1_X_3", "<Q^{PSD1}_{x}  Q^{PSD3}_{x}> <Q^{STS}_{2,y} Q^{PSD1}_{x}  Q^{PSD2}_{y}> / < Q^{STS}_{2,y} Q^{PSD2}_{y}  Q^{PSD3}_{x}>"  }, //PSD1 X
    { "STS_R2_PSD1_PSD3_Y2XY", "PSD1_PSD2_XX", "STS_R2_PSD2_PSD3_Y2XY", "RES_PSD1_X_4", "<Q^{PSD1}_{x}  Q^{PSD2}_{x}> <Q^{STS}_{2,y} Q^{PSD1}_{x}  Q^{PSD3}_{y}> / < Q^{STS}_{2,y} Q^{PSD3}_{y}  Q^{PSD2}_{x}>"  }, //PSD1 X

    { "PSD1_PSD2_YY", "PSD1_PSD3_YY", "PSD2_PSD3_YY", "RES_PSD1_Y_0", "<Q^{PSD1}_{y}  Q^{PSD2}_{y}> <Q^{PSD1}_{y}  Q^{PSD3}_{y}> / <Q^{PSD2}_{y}  Q^{PSD3}_{y}>"},  //PSD1 Y
    { "STS_R2_PSD1_PSD2_X2YY", "PSD1_PSD3_YY", "STS_R2_PSD2_PSD3_X2YY", "RES_PSD1_Y_1", "<Q^{PSD1}_{y}  Q^{PSD3}_{y}> <Q^{STS}_{2,x} Q^{PSD1}_{y}  Q^{PSD2}_{y}> / < Q^{STS}_{2,x} Q^{PSD2}_{y}  Q^{PSD3}_{y}>" }, //PSD1 Y
    { "STS_R2_PSD1_PSD3_X2YY", "PSD1_PSD2_YY", "STS_R2_PSD2_PSD3_X2YY", "RES_PSD1_Y_2", "<Q^{PSD1}_{y}  Q^{PSD2}_{y}> <Q^{STS}_{2,x} Q^{PSD1}_{y}  Q^{PSD3}_{y}> / < Q^{STS}_{2,x} Q^{PSD2}_{y}  Q^{PSD3}_{y}>" }, //PSD1 Y
    { "STS_R2_PSD1_PSD2_Y2YX", "PSD1_PSD3_YY", "STS_R2_PSD2_PSD3_Y2XY", "RES_PSD1_Y_3", "<Q^{PSD1}_{y}  Q^{PSD3}_{y}> <Q^{STS}_{2,y} Q^{PSD1}_{y}  Q^{PSD2}_{x}> / < Q^{STS}_{2,y} Q^{PSD2}_{x}  Q^{PSD3}_{y}>"}, //PSD1 Y
    { "STS_R2_PSD1_PSD3_Y2YX", "PSD1_PSD2_YY", "STS_R2_PSD2_PSD3_Y2YX", "RES_PSD1_Y_4", "<Q^{PSD1}_{y}  Q^{PSD2}_{y}> <Q^{STS}_{2,y} Q^{PSD1}_{y}  Q^{PSD3}_{x}> / < Q^{STS}_{2,y} Q^{PSD3}_{x}  Q^{PSD2}_{y}>"}, //PSD1 Y

    { "PSD1_PSD2_XX", "PSD2_PSD3_XX", "PSD1_PSD3_XX", "RES_PSD2_X_0", "<Q^{PSD1}_{x}  Q^{PSD2}_{x}> <Q^{PSD2}_{x}  Q^{PSD3}_{x}> / <Q^{PSD1}_{x}  Q^{PSD3}_{x}>"},  //PSD2 X
    { "STS_R2_PSD1_PSD2_X2XX", "PSD2_PSD3_XX", "STS_R2_PSD1_PSD3_X2XX", "RES_PSD2_X_1", "<Q^{PSD2}_{x}  Q^{PSD3}_{x}> <Q^{STS}_{2,x} Q^{PSD1}_{x}  Q^{PSD2}_{x}> / < Q^{STS}_{2,x} Q^{PSD1}_{x}  Q^{PSD3}_{x}>" }, //PSD2 X
    { "STS_R2_PSD2_PSD3_X2XX", "PSD1_PSD2_XX", "STS_R2_PSD1_PSD3_X2XX", "RES_PSD2_X_2", "<Q^{PSD2}_{x}  Q^{PSD1}_{x}> <Q^{STS}_{2,x} Q^{PSD3}_{x}  Q^{PSD2}_{x}> / < Q^{STS}_{2,x} Q^{PSD1}_{x}  Q^{PSD3}_{x}>" }, //PSD2 X
    { "STS_R2_PSD1_PSD2_Y2YX", "PSD2_PSD3_XX", "STS_R2_PSD1_PSD3_Y2YX", "RES_PSD2_X_3", "<Q^{PSD2}_{x}  Q^{PSD3}_{x}> <Q^{STS}_{2,y} Q^{PSD1}_{y}  Q^{PSD2}_{x}> / < Q^{STS}_{2,y} Q^{PSD1}_{y}  Q^{PSD3}_{x}>"  }, //PSD2 X
    { "STS_R2_PSD2_PSD3_Y2XY", "PSD1_PSD2_XX", "STS_R2_PSD1_PSD3_Y2XY", "RES_PSD2_X_4", "<Q^{PSD2}_{x}  Q^{PSD1}_{x}> <Q^{STS}_{2,y} Q^{PSD3}_{y}  Q^{PSD2}_{x}> / < Q^{STS}_{2,y} Q^{PSD1}_{x}  Q^{PSD3}_{y}>"  }, //PSD2 X

    { "PSD1_PSD2_YY", "PSD2_PSD3_YY", "PSD1_PSD3_YY", "RES_PSD2_Y_0", "<Q^{PSD1}_{y}  Q^{PSD2}_{y}> <Q^{PSD2}_{y}  Q^{PSD3}_{y}> / <Q^{PSD1}_{y}  Q^{PSD3}_{y}>"},  //PSD2 Y
    { "STS_R2_PSD1_PSD2_X2YY", "PSD2_PSD3_YY", "STS_R2_PSD1_PSD3_X2YY", "RES_PSD2_Y_1", "<Q^{PSD2}_{y}  Q^{PSD3}_{y}> <Q^{STS}_{2,x} Q^{PSD1}_{y}  Q^{PSD2}_{y}> / < Q^{STS}_{2,x} Q^{PSD1}_{y}  Q^{PSD3}_{y}>" }, //PSD2 Y
    { "STS_R2_PSD2_PSD3_X2YY", "PSD1_PSD2_YY", "STS_R2_PSD1_PSD3_X2YY", "RES_PSD2_Y_2", "<Q^{PSD2}_{y}  Q^{PSD1}_{y}> <Q^{STS}_{2,x} Q^{PSD3}_{y}  Q^{PSD2}_{y}> / < Q^{STS}_{2,x} Q^{PSD1}_{y}  Q^{PSD3}_{y}>" }, //PSD2 Y
    { "STS_R2_PSD1_PSD2_Y2XY", "PSD2_PSD3_YY", "STS_R2_PSD1_PSD3_Y2YX", "RES_PSD2_Y_3", "<Q^{PSD2}_{y}  Q^{PSD3}_{y}> <Q^{STS}_{2,y} Q^{PSD1}_{x}  Q^{PSD2}_{y}> / < Q^{STS}_{2,y} Q^{PSD1}_{x}  Q^{PSD3}_{y}>"}, //PSD2 Y
    { "STS_R2_PSD2_PSD3_Y2YX", "PSD1_PSD2_YY", "STS_R2_PSD1_PSD3_Y2YX", "RES_PSD2_Y_4", "<Q^{PSD2}_{y}  Q^{PSD1}_{y}> <Q^{STS}_{2,y} Q^{PSD3}_{x}  Q^{PSD2}_{y}> / < Q^{STS}_{2,y} Q^{PSD3}_{x}  Q^{PSD1}_{y}>"}, //PSD2 Y

    { "PSD1_PSD3_XX", "PSD2_PSD3_XX", "PSD1_PSD2_XX", "RES_PSD3_X_0", "<Q^{PSD1}_{x}  Q^{PSD3}_{x}> <Q^{PSD2}_{x}  Q^{PSD3}_{x}> / <Q^{PSD1}_{x}  Q^{PSD2}_{x}>"},  //PSD3 X
    { "STS_R2_PSD1_PSD3_Y2YX", "PSD2_PSD3_XX", "STS_R2_PSD1_PSD2_Y2YX", "RES_PSD3_X_1", "<Q^{PSD2}_{x}  Q^{PSD3}_{x}> <Q^{STS}_{2,y} Q^{PSD1}_{y}  Q^{PSD3}_{x}> / < Q^{STS}_{2,y} Q^{PSD1}_{y}  Q^{PSD2}_{x}>"  }, //PSD3 X
    { "STS_R2_PSD2_PSD3_Y2YX", "PSD1_PSD3_XX", "STS_R2_PSD1_PSD2_Y2XY", "RES_PSD3_X_2", "<Q^{PSD1}_{x}  Q^{PSD3}_{x}> <Q^{STS}_{2,y} Q^{PSD2}_{y}  Q^{PSD3}_{x}> / < Q^{STS}_{2,y} Q^{PSD2}_{y}  Q^{PSD1}_{x}>"  }, //PSD3 X
    { "STS_R2_PSD1_PSD3_X2XX", "PSD2_PSD3_XX", "STS_R2_PSD1_PSD2_X2XX", "RES_PSD3_X_3", "<Q^{PSD2}_{x}  Q^{PSD3}_{x}> <Q^{STS}_{2,x} Q^{PSD1}_{x}  Q^{PSD3}_{x}> / < Q^{STS}_{2,x} Q^{PSD1}_{x}  Q^{PSD2}_{x}>" }, //PSD3 X
    { "STS_R2_PSD2_PSD3_X2XX", "PSD1_PSD3_XX", "STS_R2_PSD1_PSD2_X2XX", "RES_PSD3_X_4", "<Q^{PSD1}_{x}  Q^{PSD3}_{x}> <Q^{STS}_{2,x} Q^{PSD2}_{x}  Q^{PSD3}_{x}> / < Q^{STS}_{2,x} Q^{PSD1}_{x}  Q^{PSD2}_{x}>" }, //PSD3 X

    { "PSD1_PSD3_YY", "PSD2_PSD3_YY", "PSD1_PSD2_YY", "RES_PSD3_Y_0", "<Q^{PSD1}_{y}  Q^{PSD3}_{y}> <Q^{PSD2}_{y}  Q^{PSD3}_{y}> / <Q^{PSD1}_{y}  Q^{PSD2}_{y}>"},  //PSD3 Y
    { "STS_R2_PSD1_PSD3_X2YY", "PSD2_PSD3_YY", "STS_R2_PSD1_PSD2_X2YY", "RES_PSD3_Y_1", "<Q^{PSD2}_{y}  Q^{PSD3}_{y}> <Q^{STS}_{2,x} Q^{PSD1}_{y}  Q^{PSD3}_{y}> / < Q^{STS}_{2,x} Q^{PSD1}_{y}  Q^{PSD2}_{y}>" }, //PSD3 Y
    { "STS_R2_PSD2_PSD3_X2YY", "PSD1_PSD3_YY", "STS_R2_PSD1_PSD2_X2YY", "RES_PSD3_Y_2", "<Q^{PSD1}_{y}  Q^{PSD3}_{y}> <Q^{STS}_{2,x} Q^{PSD2}_{y}  Q^{PSD3}_{y}> / < Q^{STS}_{2,x} Q^{PSD1}_{y}  Q^{PSD2}_{y}>" }, //PSD3 Y
    { "STS_R2_PSD1_PSD3_Y2XY", "PSD2_PSD3_YY", "STS_R2_PSD1_PSD2_Y2XY", "RES_PSD3_Y_3", "<Q^{PSD2}_{y}  Q^{PSD3}_{y}> <Q^{STS}_{2,y} Q^{PSD1}_{x}  Q^{PSD3}_{y}> / < Q^{STS}_{2,y} Q^{PSD1}_{x}  Q^{PSD2}_{y}>"},  //PSD3 Y
    { "STS_R2_PSD2_PSD3_Y2XY", "PSD1_PSD3_YY", "STS_R2_PSD1_PSD2_Y2YX", "RES_PSD3_Y_4", "<Q^{PSD1}_{y}  Q^{PSD3}_{y}> <Q^{STS}_{2,y} Q^{PSD2}_{x}  Q^{PSD3}_{y}> / < Q^{STS}_{2,y} Q^{PSD2}_{x}  Q^{PSD1}_{y}>"}  //PSD3 Y

    
};


const std::vector <TString> profiles = 
{
//   "PSD1_PSI_XX",	
//   "PSD1_PSI_YY",	
//   "PSD2_PSI_XX",	
//   "PSD2_PSI_YY",	
//   "PSD3_PSI_XX",	
//   "PSD3_PSI_YY",
//   "PSD1_PSI_XY",	
//   "PSD1_PSI_YX",	
//   "PSD2_PSI_XY",	
//   "PSD2_PSI_YX",	
//   "PSD3_PSI_XY",	
//   "PSD3_PSI_YX",
//   "STS_R1_PSI_XX",	
//   "STS_R1_PSI_YY",
//   "STS_R1_PSI_XY",	
//   "STS_R1_PSI_YX",
//   "STS_R2_PSI_XX",	
//   "STS_R2_PSI_YY",
//   "STS_R2_PSI_XY",	
//   "STS_R2_PSI_YX",  
  
  "PSD1_PSD2_XX",	
  "PSD1_PSD2_YY",	
  "PSD1_PSD2_XY",	
  "PSD1_PSD2_YX",	
  "PSD1_PSD3_XX",	
  "PSD1_PSD3_YY",	
  "PSD1_PSD3_XY",	
  "PSD1_PSD3_YX",	
  "PSD2_PSD3_XX",	
  "PSD2_PSD3_YY",	
  "PSD2_PSD3_XY",	
  "PSD2_PSD3_YX"
};

const std::vector <TString> multiprof = 
{
//   "MC_eta_PSI_XX",	
//   "MC_eta_PSI_YY",	
//   "MC_eta_PSI_XY",	
//   "MC_eta_PSI_YX",
//   "MC_pT_PSI_XX",	
//   "MC_pT_PSI_YY",	
//   "MC_pT_PSI_XY",	
//   "MC_pT_PSI_YX",
//   "STS_pT_PSI_XX",	
//   "STS_pT_PSI_YY",	
//   "STS_pT_PSI_XY",	
//   "STS_pT_PSI_YX"	
//   "STS_eta_PSI_XX",	
//   "STS_eta_PSI_YY",	
//   "STS_eta_PSI_XY",	
//   "STS_eta_PSI_YX",	

  "STS_pT_PSD1_XX",	
  "STS_pT_PSD1_YY",	
  "STS_pT_PSD1_XY",	
  "STS_pT_PSD1_YX",	
  "STS_pT_PSD2_XX",	
  "STS_pT_PSD2_YY",	
  "STS_pT_PSD2_XY",	
  "STS_pT_PSD2_YX",	    
  "STS_pT_PSD3_XX",	
  "STS_pT_PSD3_YY",	
  "STS_pT_PSD3_XY",	
  "STS_pT_PSD3_YX",
  "STS_eta_PSD1_XX",	
  "STS_eta_PSD1_YY",	
  "STS_eta_PSD1_XY",	
  "STS_eta_PSD1_YX",	
  "STS_eta_PSD2_XX",	
  "STS_eta_PSD2_YY",	
  "STS_eta_PSD2_XY",	
  "STS_eta_PSD2_YX",	
  "STS_eta_PSD3_XX",	
  "STS_eta_PSD3_YY",	
  "STS_eta_PSD3_XY",	
  "STS_eta_PSD3_YX",  
"STS_pT_PSD1_PSD2_X2XX",
"STS_pT_PSD1_PSD2_X2YY",
"STS_pT_PSD1_PSD3_X2XX",
"STS_pT_PSD1_PSD3_X2YY",
"STS_pT_PSD2_PSD3_X2XX",
"STS_pT_PSD2_PSD3_X2YY",
"STS_eta_PSD1_PSD2_X2XX",
"STS_eta_PSD1_PSD2_X2YY",
"STS_eta_PSD1_PSD3_X2XX",
"STS_eta_PSD1_PSD3_X2YY",
"STS_eta_PSD2_PSD3_X2XX",
"STS_eta_PSD2_PSD3_X2YY"
  
};


void plot_axis(const float xmin, const float xmax, const float ymin, const float ymax, 
               const TString title="", const TString xtitle="", const TString ytitle="")
{
    TH1F *h = new TH1F("h" + title, "", 1, xmin, xmax);
    h->SetTitle(title);

    h->GetYaxis()->SetTitle(ytitle);
    h->GetXaxis()->SetTitle(xtitle);

    h->GetYaxis()->SetRangeUser(ymin, ymax);
    h->GetXaxis()->SetRangeUser(xmin, xmax);
    h->Draw("");
}

// // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // //  Experimental data 
// // // // // // // // // // // // // // // // // // // // // // // // // 
// // // // // // // // // // // // // // // // // // // // // // // // // 

const float *NA49_pi_v1_bins[2][3] = {
    { NA49_v1_centr_pi_40_pT_bins, NA49_v1_mcentr_pi_40_pT_bins, NA49_v1_per_pi_40_pT_bins },
    { NA49_v1_centr_pi_40_Y_bins, NA49_v1_mcentr_pi_40_Y_bins, NA49_v1_per_pi_40_Y_bins}     };

const float *NA49_pi_v1_value[2][3] = {
    { NA49_v1_centr_pi_40_pT_value, NA49_v1_mcentr_pi_40_pT_value, NA49_v1_per_pi_40_pT_value } ,
    { NA49_v1_centr_pi_40_Y_value, NA49_v1_mcentr_pi_40_Y_value, NA49_v1_per_pi_40_Y_value}   };

const float *NA49_pi_v1_error[2][3] = {
    { NA49_v1_centr_pi_40_pT_error, NA49_v1_mcentr_pi_40_pT_error, NA49_v1_per_pi_40_pT_error } ,
    { NA49_v1_centr_pi_40_Y_error, NA49_v1_mcentr_pi_40_Y_error, NA49_v1_per_pi_40_Y_error}  };

const float *NA49_p_v1_bins[2][3] = {
    { NA49_v1_centr_p_40_pT_bins, NA49_v1_mcentr_p_40_pT_bins, NA49_v1_per_p_40_pT_bins },
    { NA49_v1_centr_p_40_Y_bins, NA49_v1_mcentr_p_40_Y_bins, NA49_v1_per_p_40_Y_bins}     };

const float *NA49_p_v1_value[2][3] = {
    { NA49_v1_centr_p_40_pT_value, NA49_v1_mcentr_p_40_pT_value, NA49_v1_per_p_40_pT_value } ,
    { NA49_v1_centr_p_40_Y_value, NA49_v1_mcentr_p_40_Y_value, NA49_v1_per_p_40_Y_value}   };

const float *NA49_p_v1_error[2][3] = {
    { NA49_v1_centr_p_40_pT_error, NA49_v1_mcentr_p_40_pT_error, NA49_v1_per_p_40_pT_error } ,
    { NA49_v1_centr_p_40_Y_error, NA49_v1_mcentr_p_40_Y_error, NA49_v1_per_p_40_Y_error}  };    

    
const float *NA49_pi_v2_bins[2][3] = {
    { NA49_v2_centr_pi_40_pT_bins, NA49_v2_mcentr_pi_40_pT_bins, NA49_v2_per_pi_40_pT_bins },
    { NA49_v2_centr_pi_40_Y_bins, NA49_v2_mcentr_pi_40_Y_bins, NA49_v2_per_pi_40_Y_bins}     };

const float *NA49_pi_v2_value[2][3] = {
    { NA49_v2_centr_pi_40_pT_value, NA49_v2_mcentr_pi_40_pT_value, NA49_v2_per_pi_40_pT_value } ,
    { NA49_v2_centr_pi_40_Y_value, NA49_v2_mcentr_pi_40_Y_value, NA49_v2_per_pi_40_Y_value}   };

const float *NA49_pi_v2_error[2][3] = {
    { NA49_v2_centr_pi_40_pT_error, NA49_v2_mcentr_pi_40_pT_error, NA49_v2_per_pi_40_pT_error } ,
    { NA49_v2_centr_pi_40_Y_error, NA49_v2_mcentr_pi_40_Y_error, NA49_v2_per_pi_40_Y_error}  };

const float *NA49_p_v2_bins[2][3] = {
    { NA49_v2_centr_p_40_pT_bins, NA49_v2_mcentr_p_40_pT_bins, NA49_v2_per_p_40_pT_bins },
    { NA49_v2_centr_p_40_Y_bins, NA49_v2_mcentr_p_40_Y_bins, NA49_v2_per_p_40_Y_bins}     };

const float *NA49_p_v2_value[2][3] = {
    { NA49_v2_centr_p_40_pT_value, NA49_v2_mcentr_p_40_pT_value, NA49_v2_per_p_40_pT_value } ,
    { NA49_v2_centr_p_40_Y_value, NA49_v2_mcentr_p_40_Y_value, NA49_v2_per_p_40_Y_value}   };

const float *NA49_p_v2_error[2][3] = {
    { NA49_v2_centr_p_40_pT_error, NA49_v2_mcentr_p_40_pT_error, NA49_v2_per_p_40_pT_error } ,
    { NA49_v2_centr_p_40_Y_error, NA49_v2_mcentr_p_40_Y_error, NA49_v2_per_p_40_Y_error}  };    
    
const int nBins[2] = {13,9};    


void plot_star_pion_v1(Int_t iVar, Int_t iCentr, TLegend &legend)
{
    if (iVar == 0) return; //pT
    TGraphErrors *STAR_v1  = new TGraphErrors(10, STAR_v1_pi_Y_bin, STAR_v1_c10_40_pi_7_7_Y_values, 0, STAR_v1_c10_40_pi_7_7_Y_error);

    STAR_v1 -> SetLineWidth(0);

    STAR_v1->SetFillStyle(3014);
    STAR_v1->SetFillColorAlpha(kMagenta-3, 0.5);
    
    legend.AddEntry(STAR_v1,"STAR","f");    
   
    STAR_v1 -> Draw("PLsameE3");
}


void plot_na49_pion_v1(Int_t iVar, Int_t iCentr, TLegend &legend)
{

    TGraphErrors *NA49_v1  = new TGraphErrors(nBins[iVar], NA49_pi_v1_bins[iVar][iCentr], NA49_pi_v1_value[iVar][iCentr], 0, NA49_pi_v1_error[iVar][iCentr]);
    NA49_v1 -> SetLineWidth(0);

    NA49_v1->SetFillStyle(3014);
    NA49_v1->SetFillColor(kGreen-2);
    
    legend.AddEntry(NA49_v1,"NA49","f");    
   
    NA49_v1 -> Draw("samePLE3");
    
}

void plot_na49_pion_v2(Int_t iVar, Int_t iCentr, TLegend &legend)
{

    TGraphErrors *NA49_v2  = new TGraphErrors(nBins[iVar], NA49_pi_v2_bins[iVar][iCentr], NA49_pi_v2_value[iVar][iCentr], 0, NA49_pi_v2_error[iVar][iCentr]);
    NA49_v2 -> SetLineWidth(0);

    NA49_v2->SetFillStyle(3014);
    NA49_v2->SetFillColor(kGreen-2);
    
    legend.AddEntry(NA49_v2,"NA49","f");    
   
    NA49_v2 -> Draw("samePLE3");
    
}
