#include "names.h"


// void plot_axis(float xmin, float xmax, float ymin, float ymax,
//                TString title="", TString xtitle="", TString ytitle="");

TFile *fIn {nullptr};
TFile *fOut {nullptr};

std::vector <TGraphErrors*> graphs;


void draw_profiles (TString inputFileName = "../NA49_flow/graph_2.root")
{
    gStyle->SetOptStat(0);
    fIn = TFile::Open(inputFileName);

    TString drawopt = "Psame";
    int i=0;

    TGraphErrors* res[6][4];
    TCanvas* c[6];
    TLegend *leg[6];

    for (int iprofile=0; iprofile<6; ++iprofile)
    {
        c[iprofile] = new TCanvas(Form("c%i", iprofile), "",1200, 1000);
        plot_axis(0,100,-0.05, 0.3, sres[iprofile*5][3], "Centrality, %", "R_{1}^{PSD}");
        leg[iprofile] = new TLegend(0.5, 0.6, 0.99, 0.9);


        for (int i=0; i<5; ++i)
        {
            TString name = "resolution/" + sres[iprofile*5+i][3];
            fIn->GetObject(name, res[iprofile][i]);

            res[iprofile][i]->SetName(name);
            res[iprofile][i]->SetMarkerSize(1.6);
            res[iprofile][i]->SetMarkerStyle(markers[i]);
            res[iprofile][i]->SetMarkerColor(colors[i]);
            res[iprofile][i]->SetLineColor(colors[i]);
//            if (i==0)
//            {
//                res[iprofile][i]->SetLineWidth(4);
//                res[iprofile][i]->Draw("Lsame");
//            }
//            else
                res[iprofile][i]->Draw(drawopt);

            TString legEntryName = sres[iprofile*5+i][4];
            leg[iprofile]->AddEntry(res[iprofile][i], legEntryName, "pl");

        }
        leg[iprofile]->Draw("same");
        c[iprofile] -> SaveAs("../NA49_flow/" + sres[iprofile*5][3]+ ".png");
    }
}



