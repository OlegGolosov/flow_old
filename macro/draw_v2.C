#include "names.h"

TFile *fIn {nullptr};
TFile *fOut {nullptr};

TCanvas* c[2][ncentr];
TLegend *leg[2][ncentr];

TGraphErrors* v2_psd[2][3][4][ncentr];

void flow_psd();

void draw_v2(TString inputFileName = "../NA49_flow/graph_2.root")
{
    gStyle->SetOptStat(0);
    fIn = TFile::Open(inputFileName);

    TString drawopt = "Psame";

    flow_psd();

    for (int iVar=0; iVar<2; ++iVar)
    for (int iXy=0; iXy<4; ++iXy)
    for (uint iCentr=0; iCentr<ncentr; ++iCentr)
    {

        TString name = Form("v2_TPC_%s_%s", var[iVar].Data(), v2[iXy][0].Data());
        c[iXy][iCentr] = new TCanvas(Form("c_%i_%i_%i", iVar, iXy, iCentr), "",1200, 1000);
        leg[iXy][iCentr] = new TLegend(0.1, 0.1, 0.3, 0.3);

        plot_axis( x_range[iVar][0], x_range[iVar][1], y_range_v2[iVar][0], y_range_v2[iVar][1], Form("%s_centr%d", name.Data(), iCentr), var[iVar], "v_{2}");

        for (int iPsd=0; iPsd<3; ++iPsd)
        {
            v2_psd[iVar][iPsd][iXy][iCentr] -> SetMarkerSize(1.6);
            v2_psd[iVar][iPsd][iXy][iCentr] -> SetMarkerStyle(markers[iPsd]);
            v2_psd[iVar][iPsd][iXy][iCentr] -> SetMarkerColor(colors[iPsd]);
            v2_psd[iVar][iPsd][iXy][iCentr] -> SetLineColor(colors[iPsd]);

            v2_psd[iVar][iPsd][iXy][iCentr]->Draw(drawopt);

            TString legEntryName = Form("%s_%s",  psd_psd[iPsd].Data(), v2[iXy][0].Data());
            leg[iXy][iCentr]->AddEntry(v2_psd[iVar][iPsd][iXy][iCentr], legEntryName, "pl");

        }

//         plot_star_pion_v2(iVar, iCentr, *leg[iXy][iCentr]);
        plot_na49_pion_v2(iVar, iCentr, *leg[iXy][iCentr]);

        leg[iXy][iCentr]->Draw("same");
        c[iXy][iCentr]->SaveAs( Form ("../NA49_flow/v2_centr_%d_%s.png", iCentr, name.Data()) );
        c[iXy][iCentr]->Close ();
    }
}
void flow_psd()
{
    for (int iVar=0; iVar<2; ++iVar)
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<4; ++iXy)
        {
            TString name = Form("v2/v2_TPC_%s_%s_%s", var[iVar].Data(), psd_psd[iPsd].Data(), v2[iXy][0].Data()  ) ;
            std::cout << name << std::endl;

            TMultiGraph *mgr;
            fIn->GetObject(name, mgr);
            TList *list = mgr->GetListOfGraphs();
            for (uint iCentr=0; iCentr<ncentr; ++iCentr)
            {
                v2_psd[iVar][iPsd][iXy][iCentr] = (TGraphErrors*) list->At(iCentr);
//                     v2_psd->Draw(drawopt);
            }
        }
 }
