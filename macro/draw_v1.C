#include "names.h"

TFile *fIn {nullptr};
TFile *fOut {nullptr};

TCanvas* c[3][2][ncentr];
TLegend *leg[3][2][ncentr];

TGraphErrors* v1_psd[2][3][2][6][ncentr];
TGraphErrors* v1_psi[2][2][ncentr];
TGraphErrors* v1_mc_psi[2][2][ncentr];

void flow_psi();
void flow_mc_psi();
void flow_psd();

void draw_v1(TString inputFileName = "../NA49_flow/graph_2.root")
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
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<2; ++iXy)
            for (uint iCentr=0; iCentr<ncentr; ++iCentr)
            {
                TString name = Form("v1_TPC_%s_%s_%s", var[iVar].Data(), PsdName[iPsd].Data(), XY[iXy].Data());
                c[iPsd][iXy][iCentr] = new TCanvas(Form("c_%i_%i_%i_%i", iVar, iPsd, iXy, iCentr), "",1200, 1000);
                leg[iPsd][iXy][iCentr] = new TLegend(0.5, 0.65, 0.99, 0.9);

                plot_axis( x_range[iVar][0], x_range[iVar][1], y_range[iVar][0], y_range[iVar][1], Form("%s_centr%d", name.Data(), iCentr), var[iVar], "v_{1}");

                if (issim)
                {
                    v1_psi[iVar][iXy][iCentr]->SetLineWidth(2);
                    v1_psi[iVar][iXy][iCentr]->SetLineColor(kGreen);
                    v1_psi[iVar][iXy][iCentr]->Draw("Lsame");

                    v1_mc_psi[iVar][iXy][iCentr]->SetLineWidth(2);
                    v1_mc_psi[iVar][iXy][iCentr]->SetLineColor(kPink-3);
                    v1_mc_psi[iVar][iXy][iCentr]->Draw("Lsame");

                    leg[iPsd][iXy][iCentr]->AddEntry(v1_mc_psi[iVar][iXy][iCentr], "MC #Psi", "l");
                    leg[iPsd][iXy][iCentr]->AddEntry(v1_psi[iVar][iXy][iCentr], "TPC #Psi", "l");
                }
                for (int iRes=0; iRes<6; ++iRes)
                {
                    if (iRes==5 && !issim) continue;

                    v1_psd[iVar][iPsd][iXy][iRes][iCentr] -> SetMarkerSize(1.6);
                    v1_psd[iVar][iPsd][iXy][iRes][iCentr] -> SetMarkerStyle(markers[iRes]);
                    v1_psd[iVar][iPsd][iXy][iRes][iCentr] -> SetMarkerColor(colors[iRes]);
                    v1_psd[iVar][iPsd][iXy][iRes][iCentr] -> SetLineColor(colors[iRes]);
                    if (iRes==5)
                    {
                        v1_psd[iVar][iPsd][iXy][iRes][iCentr]->SetLineWidth(2);
                        v1_psd[iVar][iPsd][iXy][iRes][iCentr]->Draw("Lsame");
                    }
                    else
                        v1_psd[iVar][iPsd][iXy][iRes][iCentr]->Draw(drawopt);

                    TString legEntryName = iRes==5 ? "TPC PSD (#Psi resolution)" : sres[5*(iPsd + iXy*3)+iRes][4];
                    leg[iPsd][iXy][iCentr]->AddEntry(v1_psd[iVar][iPsd][iXy][iRes][iCentr], legEntryName, "pl");
                }
                leg[iPsd][iXy][iCentr]->Draw("same");
                c[iPsd][iXy][iCentr]->SaveAs( Form ("../NA49_flow/centr_%d_%s.png", iCentr, name.Data()) );
                c[iPsd][iXy][iCentr]->Close ();
            }

    }
void flow_psd()
{
    for (int iVar=0; iVar<2; ++iVar)
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<2; ++iXy)
            for (int iRes=0; iRes<6; ++iRes)
            {
                if (iRes==5 && !issim) continue;
                TString name = Form("v1/v1_TPC_%s_%s_%s_%d", var[iVar].Data(), PsdName[iPsd].Data(), XY[iXy].Data(), iRes) ;
                std::cout << name << std::endl;

                TMultiGraph *mgr;
                fIn->GetObject(name, mgr);
                TList *list = mgr->GetListOfGraphs();
                for (uint iCentr=0; iCentr<ncentr; ++iCentr)
                {
                    v1_psd[iVar][iPsd][iXy][iRes][iCentr] = (TGraphErrors*) list->At(iCentr);
//                     v1_psd->Draw(drawopt);
                }
            }
 }

void flow_psi()
{
    for (int iVar=0; iVar<2; ++iVar)
    for (int iXy=0; iXy<2; ++iXy)
    {
        TString name = Form("multi_graphs/TPC_%s_PSI_%s%s", var[iVar].Data(), XY[iXy].Data(), XY[iXy].Data()) ;
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
