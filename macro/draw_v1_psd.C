#include "names.h"

TFile *fIn {nullptr};
TFile *fOut {nullptr};

TCanvas* c[2][ncentr];
TLegend *leg[2][ncentr];

TGraphErrors* v1_psd[2][3][2][ncentr];
TGraphErrors* v1_psi[2][2][ncentr];
TGraphErrors* v1_mc_psi[2][2][ncentr];

void flow_psi();
void flow_mc_psi();
void flow_psd();

void draw_v1_psd(TString inputFileName = "../NA49_flow/corr_1.root")
{
    gStyle->SetOptStat(0);
    fIn = TFile::Open(inputFileName);

    TString drawopt = "Psame";

    flow_psd();
    if (issim)
    {
        flow_psi();
        flow_mc_psi();
    }
    for (int iVar=0; iVar<2; ++iVar)
    for (int iXy=0; iXy<2; ++iXy)
    for (uint iCentr=0; iCentr<ncentr; ++iCentr)
    {

        TString name = Form("v1_STS_%s_%s", var[iVar].Data(), XY[iXy].Data());
        c[iXy][iCentr] = new TCanvas(Form("c_%i_%i_%i", iVar, iXy, iCentr), "",1200, 1000);
        leg[iXy][iCentr] = new TLegend(0.1, 0.1, 0.3, 0.3);

        plot_axis( x_range[iVar][0], x_range[iVar][1], y_range[iVar][0], y_range[iVar][1], Form("%s_centr%d", name.Data(), iCentr), var[iVar], "v_{1}");

        for (int iPsd=0; iPsd<3; ++iPsd)
        {
            if (issim)
            {
                v1_psi[iVar][iXy][iCentr]->SetLineWidth(2);
                v1_psi[iVar][iXy][iCentr]->SetLineColor(kGreen);
                v1_psi[iVar][iXy][iCentr]->Draw("Lsame");

                v1_mc_psi[iVar][iXy][iCentr]->SetLineWidth(2);
                v1_mc_psi[iVar][iXy][iCentr]->SetLineColor(kPink-3);
                v1_mc_psi[iVar][iXy][iCentr]->Draw("Lsame");

                leg[iXy][iCentr]->AddEntry(v1_mc_psi[iVar][iXy][iCentr], "MC #Psi", "l");
                leg[iXy][iCentr]->AddEntry(v1_psi[iVar][iXy][iCentr], "STS #Psi", "l");
            }

            v1_psd[iVar][iPsd][iXy][iCentr] -> SetMarkerSize(1.6);
            v1_psd[iVar][iPsd][iXy][iCentr] -> SetMarkerStyle(markers[iPsd]);
            v1_psd[iVar][iPsd][iXy][iCentr] -> SetMarkerColor(colors[iPsd]);
            v1_psd[iVar][iPsd][iXy][iCentr] -> SetLineColor(colors[iPsd]);

            v1_psd[iVar][iPsd][iXy][iCentr]->Draw(drawopt);

            TString legEntryName = Form("PSD%d",  iPsd+1);
            leg[iXy][iCentr]->AddEntry(v1_psd[iVar][iPsd][iXy][iCentr], legEntryName, "pl");

        }

        plot_star_pion_v1(iVar, iCentr, *leg[iXy][iCentr]);
        plot_na49_pion_v1(iVar, iCentr, *leg[iXy][iCentr]);

        leg[iXy][iCentr]->Draw("same");
        c[iXy][iCentr]->SaveAs( Form ("../NA49_flow/out_na61/centr_%d_%s.png", iCentr, name.Data()) );
        c[iXy][iCentr]->Close ();
    }
}
void flow_psd()
{
    for (int iVar=0; iVar<2; ++iVar)
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<2; ++iXy)
        {
            TString name = Form("v1/v1_STS_%s_%s_%s_0", var[iVar].Data(), PsdName[iPsd].Data(), XY[iXy].Data()) ;
            std::cout << name << std::endl;

            TMultiGraph *mgr;
            fIn->GetObject(name, mgr);
            TList *list = mgr->GetListOfGraphs();
            for (uint iCentr=0; iCentr<ncentr; ++iCentr)
            {
                v1_psd[iVar][iPsd][iXy][iCentr] = (TGraphErrors*) list->At(iCentr);
//                     v1_psd->Draw(drawopt);
            }
        }
 }

void flow_psi()
{
    for (int iVar=0; iVar<2; ++iVar)
    for (int iXy=0; iXy<2; ++iXy)
    {
        TString name = Form("multi_graphs/STS_%s_PSI_%s%s", var[iVar].Data(), XY[iXy].Data(), XY[iXy].Data()) ;
        TMultiGraph *mgr;
        fIn->GetObject(name, mgr);
        TList *list = mgr->GetListOfGraphs();
        for (uint iCentr=0; iCentr<ncentr; ++iCentr)
            v1_psi[iVar][iXy][iCentr] = (TGraphErrors*) list->At(iCentr);
    }
}

void flow_mc_psi()
{
    for (int iVar=0; iVar<2; ++iVar)
    for (int iXy=0; iXy<2; ++iXy)
    {
        TString name = Form("multi_graphs/MC_%s_PSI_%s%s", var[iVar].Data(), XY[iXy].Data(), XY[iXy].Data()) ;
        TMultiGraph *mgr;
        fIn->GetObject(name, mgr);
        TList *list = mgr->GetListOfGraphs();
        for (uint iCentr=0; iCentr<ncentr; ++iCentr)
            v1_mc_psi[iVar][iXy][iCentr] = (TGraphErrors*) list->At(iCentr);
    }
}
