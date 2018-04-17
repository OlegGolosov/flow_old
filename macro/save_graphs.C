#include "graph_config.h"


void Save_QQ ();
void Save_uQ ();
void SaveResolution();
void Save_V1();
void SaveGraphs();
void SaveV1();
void SaveV2();

TMultiGraph* GetV1(const TString corr, const TString res);
TMultiGraph* GetV2(const TString corr, const TString res1, const TString res2, const int iVar);

Qn::DataContainer<Qn::Profile>  GetResolution( const TString top1, const TString top2, const TString bot);

TFile *fIn {nullptr};
TFile *fOut {nullptr};
TFile *fTemp {nullptr};

void save_graphs(TString inputFileName = "~/Desktop/analysis/NA49_flow/corr_1.root",
                   TString outputFileName = "~/Desktop/analysis/NA49_flow/graph_1.root")
{		
//		inputFileName = "~/Desktop/analysis/flow/build/corr.root";
//		outputFileName = "~/Desktop/analysis/flow/build/graph.root";
		
//    gStyle->SetOptStat(0);
		
    fIn = TFile::Open(inputFileName);
    fTemp = new TFile (outputFileName + "_", "recreate");
    fOut = new TFile (outputFileName, "recreate");

    Save_QQ ();
    Save_uQ ();
    SaveResolution ();
    Save_V1();
	
    fTemp->Close();
    fOut->Close();
}

void SaveV1()
{
    std::vector <TMultiGraph*> mgraphs;
    TDirectory *v1_dir = fOut->mkdir( "v1" );
    v1_dir->cd();

    for (int iVar=0; iVar<2; ++iVar)
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<2; ++iXy)
            for (int iRes=0; iRes<6; ++iRes)
            {
                if (iRes == 5 && !issim) continue;

                const TString corr_name = Form("TPC_%s_%s_%s%s", var[iVar].Data(), PsdName[iPsd].Data(), XY[iXy].Data(), XY[iXy].Data() );
                TString res_name = Form("RES_%s_%s_%d", PsdName[iPsd].Data(), XY[iXy].Data(), iRes ) ;
                if (iRes == 5) res_name = Form("%s_PSI_%s%s", PsdName[iPsd].Data(), XY[iXy].Data(), XY[iXy].Data()) ;
                std::cout << corr_name << "  /  " << res_name << std::endl;

                mgraphs.push_back( GetV1( corr_name, res_name ) );
                mgraphs.back()->SetName( Form("v1_TPC_%s_%s_%s_%d", var[iVar].Data(), PsdName[iPsd].Data(), XY[iXy].Data(), iRes)  );
                mgraphs.back()->Write();
            }
}


void SaveV2()
{
    std::vector <TMultiGraph*> mgraphs;

    TDirectory *v2_dir = fOut->mkdir( "v2" );
    v2_dir->cd();

    for (int iVar=0; iVar<2; ++iVar)
    for (int iPsd=0; iPsd<3; ++iPsd)
        for (int iXy=0; iXy<4; ++iXy)
        {
            const TString corr_name = Form("TPC_%s_%s_%s", var[iVar].Data(), psd_psd[iPsd].Data(), v2[iXy][0].Data() );
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

            mgraphs.back()->SetName( Form("v2_TPC_%s_%s_%s", var[iVar].Data(), psd_psd[iPsd].Data(), v2[iXy][0].Data() ) );
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
//    TMultiGraph* ret =  DataToMultiGraph( flow, "Multiplicity"  ) ;

//    flow = flow.Rebin( {"Eveto", eVetoBins3}, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );

    TMultiGraph* ret =  DataToMultiGraph( flow, "Eveto"  ) ;

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

//    flow = flow.Rebin( {axisName[iVar], v2axis[iVar]}, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );

//    TMultiGraph* ret =  DataToMultiGraph( flow, "Centrality"  ) ;
//    TMultiGraph* ret =  DataToMultiGraph( flow, "Multiplicity"  ) ;
    TMultiGraph* ret =  DataToMultiGraph( flow, "Eveto"  ) ;
    return ret;
}


void Save_QQ ()
{
	TString xAxisTitle = "Centrality, %";
	std::string comp [5] = {"_XX", "_YY", "_XY", "_YX", "_QQ"}; 
	std::string comp1 [5] = {"x", "y", "x", "y", "x+y"}; 
	std::string comp2 [5] = {"x", "y", "y", "x", "x+y"}; 
	
	TGraphErrors *corr;
	vector <TGraphErrors*> graphs;
	Qn::DataContainer<Qn::Profile> *profile [5];
	profile [4] = new Qn::DataContainer<Qn::Profile>;
	TDirectory *QQ_dir = fOut->mkdir( "QQ" );
	QQ_dir->cd();

	for (ushort i = 0; i < QQ_names.size (); i++)
	{		
		TMultiGraph mg;
		std::cout << std::endl << QQ_names[i][0];
		for (int j = 0; j < 5; j++) 
		{
			if (j < 4) fIn -> GetObject(QQ_names[i][0] + comp [j].c_str(), profile [j]);
			else if (profile [0] && profile [1]) *profile [4] = *profile [0] + *profile [1];
			if (profile [j]) std::cout << "\t" << comp [j];
			else continue;
			corr = DataToProfileGraph (*profile [j]);
			corr -> SetName (QQ_names[i][0] + comp [j].c_str());
			corr -> SetTitle (Form (QQ_names[i][1], comp1 [j].c_str(), comp2 [j].c_str()));
			corr -> GetXaxis () -> SetTitle (xAxisTitle);
			corr -> SetMarkerStyle (markers [j]);//    fOut->Write();

			corr -> SetMarkerColor (colors [j]);
			corr -> SetMarkerSize (1.5);
			corr -> SetLineColor (colors [j]);
			graphs.push_back ((TGraphErrors*) corr -> Clone ());
			mg.Add (corr);
		}
		mg.Write (QQ_names[i][0]);
	}
	std::cout << std::endl;
	
	for (ushort i = 0; i < graphs.size (); i++)
	{
		graphs [i] -> Write ();
	}
}

void Save_uQ ()
{
	std::string profileVar = "Centrality";
	std::vector <std::string> xAxes = {"pt", "y"};
	std::vector <std::string> xAxesTitles = {"p_{T}", "#it{y}"};
	TString comp [5] = {"_XX", "_YY", "_XY", "_YX", "_QQ"}; 
	TString comp1 [5] = {"x", "y", "x", "y", "x+y"}; 
	TString comp2 [5] = {"x", "y", "y", "x", "x+y"}; 
	std::string objectName;
	TGraphErrors *g;
	TMultiGraph *mg;
	TList *glist;
	std::vector <TGraphErrors*> graphs;
	vector <TString> profileNames;
	vector <Qn::DataContainer<Qn::Profile>*> profiles;
	
	Qn::DataContainer<Qn::Profile> *profile [5];
	profile [4] = new Qn::DataContainer<Qn::Profile>;
	
	TDirectory *uQ_dir = fOut->mkdir( "uQ" );
	uQ_dir->cd();
	for (int axis = 0; axis < xAxes.size (); axis++)
	{
		for (ushort i = 0; i < uQ_names.size (); i++)
		{		
			objectName = Form (uQ_names[i][0], xAxes [axis].c_str());
			std::cout << std::endl << objectName;
			for (int j = 0; j < 5; j++) 
			{
				if (j < 4) fIn -> GetObject(objectName + comp [j], profile [j]);
				else if (profile [0] && profile [1]) *profile [4] = *profile [0] + *profile [1];
				if (profile [j]) std::cout << "\t" << comp [j];
				else continue;
				profiles.push_back (profile [j]);
				profileNames.push_back (objectName + comp [j]);
				*profile [j] = profile [j] -> Rebin( centralityAxis, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );
				mg = DataToMultiGraph (*profile [j], profileVar);
				mg -> SetName (Form (uQ_names[i][0], xAxesTitles [axis].c_str()) + comp [j]);
				mg -> SetTitle (Form (uQ_names[i][1], comp1 [j].Data(), comp2 [j].Data()));
				glist = mg -> GetListOfGraphs ();
				for (int k = 0; k < glist -> GetSize (); k++) 
				{
					g = (TGraphErrors*) glist -> At(k);
					g -> GetXaxis () -> SetTitle (xAxesTitles [axis].c_str());
					g -> SetMarkerStyle (markers [k]);
					g -> SetMarkerColor (colors [k]);
					g -> SetLineColor (colors [k]);
					g -> SetMarkerSize (1.5);
					g -> SetName (objectName + comp [j] + Form ("_%i", k + 1));
					graphs.push_back (g);
				}
				mg -> Write(objectName + comp [j]);
			}
		}
	}
	for (ushort i = 0; i < graphs.size (); i++)
	{
		graphs [i] -> Write ();
	}
	
	fTemp -> cd ();
	for (ushort i = 0; i < profiles.size (); i++)
	{
		profiles [i] -> Write (profileNames [i]);
	}
}

void SaveResolution ()
{
	TString xAxisTitle = "Centrality, %";
	TString comp [3] = {"_XX", "_YY", "_QQ"}; 
	TString comp1 [3] = {"x", "y", "x+y"}; 
	TString comp2 [3] = {"x", "y", "x+y"}; 
	
	TGraphErrors *g;
	vector <TGraphErrors*> graphs;
	Qn::DataContainer<Qn::Profile> *profile [3][3], res;
	vector <Qn::DataContainer<Qn::Profile>> profiles;
	vector <TString> profileNames;
	TString resName;
	TString resTitle;
	
	
	profile [2][0] = new Qn::DataContainer<Qn::Profile>;
	profile [2][1] = new Qn::DataContainer<Qn::Profile>;
	profile [2][2] = new Qn::DataContainer<Qn::Profile>;
	
	TDirectory *res_dir = fOut->mkdir( "resolution" );
	res_dir->cd();

	for (ushort i = 0; i < res_names.size (); i++)
	{		
		TMultiGraph mg;
		std::cout << std::endl << res_names[i][0];
		for (int j = 0; j < 3; j++) 
		{
			if (j < 2) 
			{
				fIn -> GetObject(res_names[i][1] + comp [j], profile [j][0]);
				fIn -> GetObject(res_names[i][2] + comp [j], profile [j][1]);
				fIn -> GetObject(res_names[i][3] + comp [j], profile [j][2]);
			}
			else if (profile [0][0] && profile [0][1] &&  profile [0][2] &&
							 profile [1][0] && profile [1][1] &&  profile [1][2]) 
			{
				*profile [2][0] = *profile [0][0] + *profile [1][0];
				*profile [2][1] = *profile [0][1] + *profile [1][1];
				*profile [2][2] = *profile [0][2] + *profile [1][2];
			}
			if (profile [j][0] && profile [j][1] && profile [j][2]) 
			{
				std::cout << "\t" << comp [j];
				res = Sqrt((*profile [j][0]) * (*profile [j][1]) / (*profile [j][2]));
			}
			else continue;
			
			resName = res_names[i][0] + comp [j];
			resTitle = Form (res_names[i][4], comp1 [j].Data(), comp1 [j].Data());
			
			g = DataToProfileGraph (res);
			g -> SetName (resName);
			g -> SetTitle (resTitle);
			g -> GetXaxis () -> SetTitle (xAxisTitle);
			g -> SetMarkerStyle (markers [j]);
			g -> SetMarkerColor (colors [j]);
			g -> SetMarkerSize (1.5);
			g -> SetLineColor (colors [j]);
			profiles.push_back (res);
			profileNames.push_back (resName);
			graphs.push_back ((TGraphErrors*) g -> Clone ());
			mg.Add (g);
		}
		mg.Write(res_names[i][0]);
	}
	std::cout << std::endl;
	
	for (ushort i = 0; i < graphs.size (); i++)
	{
		graphs [i] -> Write ();
	}
	
	fTemp -> cd ();
	
	for (ushort i = 0; i < profiles.size (); i++)
	{
		profiles [i].Write (profileNames [i]);
	}
}

void Save_V1()
{
	std::string profileVar = "Centrality";
	std::vector <std::string> xAxes = {"pt", "y"};
	std::vector <std::string> xAxesTitles = {"p_{T}", "#it{y}"};
	TString comp [3] = {"_XX", "_YY", "_QQ"}; 
	TString comp1 [3] = {"x", "y", "x+y"}; 
	TString comp2 [3] = {"x", "y", "x+y"}; 
	std::string corrName, resName, flowName;
	TGraphErrors *g;
	TMultiGraph *mg;
	TList *glist;
	std::vector <TGraphErrors*> graphs;
	
	Qn::DataContainer<Qn::Profile> *corr [3], *res [3], flow;
	
	TDirectory *flow_dir = fOut->mkdir( "flow" );
	flow_dir->cd();
		
	for (int axis = 0; axis < xAxes.size (); axis++)
	{
		for (ushort i = 0; i < flow_names.size (); i++)
		{		
			flowName = Form (flow_names[i][0], xAxes [axis].c_str());
			corrName = Form (flow_names[i][1], xAxes [axis].c_str());
			resName = Form (flow_names[i][2], xAxes [axis].c_str());
			std::cout << std::endl << flowName << " = " << corrName << " / " << resName << "\t";
			for (int j = 0; j < 3; j++) 
			{
				fTemp -> GetObject (corrName + comp [j], corr [j]);
				fTemp -> GetObject (resName + comp [j], res [j]);
				if (corr [j] && res [j]) std::cout << "\t" << comp [j];
				else continue;
				flow = *corr [j] / *res [j];
				flow = flow.Rebin( centralityAxis, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );
				mg = DataToMultiGraph (flow, profileVar);
				mg -> SetName (flowName + comp [j]);
				mg -> SetTitle (Form (flow_names[i][3], comp1 [j].Data(), xAxesTitles [axis].c_str()));
				glist = mg -> GetListOfGraphs ();
				for (int k = 0; k < glist -> GetSize (); k++) 
				{
					g = (TGraphErrors*) glist -> At(k);
					g -> GetXaxis () -> SetTitle (xAxesTitles [axis].c_str());
					g -> SetMarkerStyle (markers [k]);
					g -> SetMarkerColor (colors [k]);
					g -> SetLineColor (colors [k]);
					g -> SetMarkerSize (1.5);
					g -> SetName (flowName + comp [j] + Form ("_%i", k + 1));
					graphs.push_back (g);
				}
				mg -> Write(flowName + comp [j]);
			}
		}
	}
}