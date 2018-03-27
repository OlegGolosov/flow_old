#include "names.h"

void SaveResolution();
void SaveGraphs();
void SaveV1();
void SaveV2();

TMultiGraph* GetV1(const TString corr, const TString res);
TMultiGraph* GetV2(const TString corr, const TString res1, const TString res2, const int iVar);

Qn::DataContainer<Qn::Profile>  GetResolution( const TString top1, const TString top2, const TString bot);

TFile *fIn {nullptr};
TFile *fOut {nullptr};
TDirectory *savdir;

void save_profiles(TString inputFileName = "~/Desktop/Analysis/NA49_flow/corr_step_1.root",
                   TString outputFileName = "~/Desktop/Analysis/NA49_flow/graph_step_1.root")
{
    gStyle->SetOptStat(0);
    fIn = TFile::Open(inputFileName);
    fOut = TFile::Open(outputFileName, "recreate");
    savdir = gDirectory;

    SaveResolution();
    SaveGraphs();

    fOut->Write();

    SaveV1();
    SaveV2();

    fOut->Close();
}

void SaveV1()
{
    std::vector <TMultiGraph*> mgraphs;
    TDirectory *v1_dir = savdir->mkdir( "v1" );
    v1_dir->cd();

    for (int iVar=0; iVar<2; ++iVar)
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<2; ++iXy)
            for (int iRes=0; iRes<6; ++iRes)
            {
                if (iRes == 5 && !issim) continue;

                const TString corr_name = Form("STS_%s_%s_%s%s", var[iVar].Data(), PsdName[iPsd].Data(), XY[iXy].Data(), XY[iXy].Data() );
                TString res_name = Form("RES_%s_%s_%d", PsdName[iPsd].Data(), XY[iXy].Data(), iRes ) ;
                if (iRes == 5) res_name = Form("%s_PSI_%s%s", PsdName[iPsd].Data(), XY[iXy].Data(), XY[iXy].Data()) ;
                std::cout << corr_name << "  /  " << res_name << std::endl;

                mgraphs.push_back( GetV1( corr_name, res_name ) );
                mgraphs.back()->SetName( Form("v1_STS_%s_%s_%s_%d", var[iVar].Data(), PsdName[iPsd].Data(), XY[iXy].Data(), iRes)  );
                mgraphs.back()->Write();
            }
}


void SaveV2()
{
    std::vector <TMultiGraph*> mgraphs;

    TDirectory *v2_dir = savdir->mkdir( "v2" );
    v2_dir->cd();

    for (int iVar=0; iVar<2; ++iVar)
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<4; ++iXy)
        {
            const TString corr_name = Form("STS_%s_%s_%s", var[iVar].Data(), psd_psd[iPsd].Data(), v2[iXy][0].Data() );
            TString res_name1 = "";
            TString res_name2 = "";

            if (iXy<2)
               res_name1 = Form("%s_%s", psd_psd[iPsd].Data(), v2[iXy][1].Data() ) ;
            else
            {
                res_name1 = Form("RES_PSD%d_%s_0", iPsd/2+1, v2[iXy][1].Data() ) ;
                res_name2 = Form("RES_PSD%d_%s_0", (iPsd+1)/2+2, v2[iXy][2].Data() ) ;
            }

            std::cout << corr_name << "  /  " << res_name1 << " " << res_name2  << std::endl;

            mgraphs.push_back( GetV2( corr_name, res_name1, res_name2, iVar ) );

            mgraphs.back()->SetName( Form("v2_STS_%s_%s_%s", var[iVar].Data(), psd_psd[iPsd].Data(), v2[iXy][0].Data() ) );
            mgraphs.back()->Write();
        }
}




TMultiGraph* GetV1(const TString corr, const TString res)
{
    Qn::DataContainer<Qn::Profile> *pcorr;
    Qn::DataContainer<Qn::Profile> *pres;

    fIn->GetObject(corr, pcorr);
    fOut->GetObject( "resolution/correlation/" + res, pres);

    Qn::DataContainer<Qn::Profile> flow = *pcorr / *pres;

//     flow = flow.Rebin( {"Centrality", centrality_bins }, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );

//    TMultiGraph* ret =  DataToMultiGraph( flow, "Centrality"  ) ;
    TMultiGraph* ret =  DataToMultiGraph( flow, "Multiplicity"  ) ;
    return ret;
}

TMultiGraph* GetV2(const TString corr, const TString res1, const TString res2, const int iVar)
{
    Qn::DataContainer<Qn::Profile> *pcorr;
    Qn::DataContainer<Qn::Profile> *pres1;
    Qn::DataContainer<Qn::Profile> *pres2;

    Qn::DataContainer<Qn::Profile> flow;

    float scale = 8.0;

    fIn->GetObject(corr, pcorr);
    if (res2=="")
    {
        fIn->GetObject(res1, pres1);
        flow = (*pcorr * scale ) / (*pres1) ;
    }
    else
    {
        fOut->GetObject("resolution/correlation/" + res1, pres1);
        fOut->GetObject("resolution/correlation/" + res2, pres2);
        flow =/* 4. **/ (*pcorr * scale) / ( (*pres1) * (*pres2) );
    }

//     flow = flow.Rebin( {"Centrality", centrality_bins }, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );
//     for (auto i : flow.GetAxes())
//         std::cout << i.Name() << std::endl;

    flow = flow.Rebin( {axisName[iVar], v2axis[iVar]}, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );

//    TMultiGraph* ret =  DataToMultiGraph( flow, "Centrality"  ) ;
    TMultiGraph* ret =  DataToMultiGraph( flow, "Multiplicity"  ) ;
    return ret;
}


void SaveGraphs()
{
    std::vector <TGraphErrors*> graphs;
    std::vector <TMultiGraph*> mgraphs;

    fOut->cd();
    TDirectory *graphs_dir = savdir->mkdir( "graphs" );
    graphs_dir->cd();

//     save TGraphErrors (config in names.h)
    for (auto iprofile : profiles)
    {
        Qn::DataContainer<Qn::Profile> *profile;
        fIn->GetObject(iprofile, profile);
        graphs.push_back ( DataToProfileGraph(*profile) );

        graphs.back()->SetName(iprofile);
        graphs.back()->Write();
    }

    TDirectory *mgraphs_dir = savdir->mkdir( "multi_graphs" );
    mgraphs_dir->cd();

//     save TMultiGraph (config in names.h)
    for (auto iprofile : multiprof)
    {
        Qn::DataContainer<Qn::Profile> *profile;
        fIn->GetObject(iprofile, profile);
//         *profile = profile->Rebin( {"Centrality", centrality_bins }, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );

//        mgraphs.push_back ( DataToMultiGraph(*profile, "Centrality") );
        mgraphs.push_back ( DataToMultiGraph(*profile, "Multiplicity") );

        mgraphs.back()->SetName(iprofile);
        mgraphs.back()->Write();
    }

}

void SaveResolution()
{
    TGraphErrors* res[nres];

    fOut->cd();
    TDirectory *res_dir = savdir->mkdir( "resolution" );
    res_dir->cd();

    TDirectory *cor_dir = res_dir->mkdir( "correlation" );
    cor_dir->cd();

    for (ushort ires = 0; ires<nres; ++ires)
    {
        std::cout << sres[ires][0] << "  " << sres[ires][1] << "  " << sres[ires][2] << std::endl;

        Qn::DataContainer<Qn::Profile> pres = GetResolution(sres[ires][0], sres[ires][1], sres[ires][2]);
        pres.Write( sres[ires][3]);
        res[ires] = DataToProfileGraph( pres );
        res[ires] -> SetName(sres[ires][3]);
    }

    if (issim)
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<2; ++iXy)
        {
            const TString res_name = Form("%s_PSI_%s%s", PsdName[iPsd].Data(), XY[iXy].Data(), XY[iXy].Data()) ;
            Qn::DataContainer<Qn::Profile> *pres;
            fIn->GetObject(res_name, pres);
            pres->Write( res_name );
        }

    res_dir->cd();
    for (ushort ires = 0; ires<nres; ++ires)
        res[ires]->Write();

}

Qn::DataContainer<Qn::Profile> GetResolution(const TString top1, const TString top2, const TString bot)
{
    Qn::DataContainer<Qn::Profile> *ptop1;
    Qn::DataContainer<Qn::Profile> *ptop2;
    Qn::DataContainer<Qn::Profile> *pbot;

    fIn->GetObject(top1, ptop1);
    fIn->GetObject(top2, ptop2);
    fIn->GetObject(bot , pbot);

    Qn::DataContainer<Qn::Profile> ret = Sqrt( (*ptop1) * (*ptop2) / (*pbot) ) ;
    return ret;
}

