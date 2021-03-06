#include "graph_config.h"


void Save_QQ ();
void Save_QQQ ();
void Save_uQ ();
void Save_uQQ ();
void SaveResolution();
void SaveFlow(int harmonic);
void SaveGraphs();
void SaveV1();
void SaveV2();

TMultiGraph* GetV1(const TString corr, const TString res);
TMultiGraph* GetV2(const TString corr, const TString res1, const TString res2, const int iVar);

Qn::DataContainer<Qn::Profile>  GetResolution( const TString top1, const TString top2, const TString bot);

TFile *fIn {nullptr};
TFile *fOut {nullptr};
TFile *fTemp {nullptr};

void save_graphs(TString inputFileName = "~/Desktop/analysis/NA49_flow/lowY_3+3_rings/piminus/corr_2.root",
                   TString outputFileName = "~/Desktop/analysis/NA49_flow/lowY_3+3_rings/piminus/graph_2.root")
{		
		cout << inputFileName << endl;
		cout << outputFileName << endl;
		
    fIn = TFile::Open (inputFileName);
    fTemp = new TFile (outputFileName + "_", "recreate");
    fOut = new TFile (outputFileName, "recreate");

    Save_QQ ();
//    Save_QQQ ();
    Save_uQ ();
//    Save_uQQ ();
    SaveResolution ();
    SaveFlow(1);
//    SaveFlow(2);
	
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
	TString xAxisTitle = "Centrality class";
	TString comp [5] = {"_XX", "_YY", "_QQ", "_XY", "_YX"}; 
	TString comp1 [5] = {"x", "y", "x+y", "x", "y"}; 
	TString comp2 [5] = {"x", "y", "x+y", "y", "x"};  
	
	TGraphErrors *corr;
	vector <TGraphErrors*> graphs;
	Qn::DataContainer<Qn::Profile> *profile [5];
	profile [2] = new Qn::DataContainer<Qn::Profile>;
	TDirectory *QQ_dir = fOut->mkdir( "QQ" );
	QQ_dir->cd();

	for (ushort i = 0; i < QQ_names.size (); i++)
	{		
		TMultiGraph mg;
//		mg.SetTitle (Form (QQ_names[i][1], "", "") + ";" + xAxisTitle);
		mg.SetTitle (";" + xAxisTitle);
		std::cout << std::endl << QQ_names[i][0];
		for (int j = 0; j < 5; j++) 
		{
			if (j != 2) fIn -> GetObject(QQ_names[i][0] + comp [j].Data(), profile [j]);
			else if (profile [0] && profile [1]) *profile [2] = (*profile [0] + *profile [1]) * 2.;
			if (profile [j]) std::cout << "\t" << comp [j];
			else continue;
			corr = DataToProfileGraph (*profile [j]);
			corr -> SetName (QQ_names[i][0] + comp [j].Data());
			corr -> SetTitle (Form (QQ_names[i][1], comp1 [j].Data(), comp2 [j].Data()));
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

void Save_QQQ ()
{
	TString xAxisTitle = "Centrality class";
	std::string comp [5] = {"_X2XX", "_X2YY", "_Y2XY", "_Y2YX", "_QQ"}; 
	std::string comp1 [5] = {"x", "y", "y", "y", "x+y"}; 
	std::string comp2 [5] = {"x", "y", "x", "y", "x+y"}; 
	std::string comp3 [5] = {"x", "y", "y", "x", "x+y"}; 
	
	TGraphErrors *corr;
	vector <TGraphErrors*> graphs;
	Qn::DataContainer<Qn::Profile> *profile [5];
	profile [4] = new Qn::DataContainer<Qn::Profile>;
	TDirectory *QQQ_dir = fOut->mkdir( "QQQ" );
	QQQ_dir->cd();

	for (ushort i = 0; i < QQQ_names.size (); i++)
	{		
		TMultiGraph mg;
//		mg.SetTitle (Form (QQ_names[i][1], "", "") + ";" + xAxisTitle);
		mg.SetTitle (";" + xAxisTitle);
		std::cout << std::endl << QQQ_names[i][0];
		for (int j = 0; j < 4; j++) // check! (4 or 5)
		{
			if (j < 4) fIn -> GetObject(QQQ_names[i][0] + comp [j].c_str(), profile [j]);
			else if (profile [0] && profile [1]) *profile [4] = *profile [0] + *profile [1];
			if (profile [j]) std::cout << "\t" << comp [j];
			else continue;
			corr = DataToProfileGraph (*profile [j]);
			corr -> SetName (QQQ_names[i][0] + comp [j].c_str());
			corr -> SetTitle (Form (QQQ_names[i][1], comp1 [j].c_str(), comp2 [j].c_str(), comp3 [j].c_str()));
			corr -> GetXaxis () -> SetTitle (xAxisTitle);
			corr -> SetMarkerStyle (markers [j]);//    fOut->Write();

			corr -> SetMarkerColor (colors [j]);
			corr -> SetMarkerSize (1.5);
			corr -> SetLineColor (colors [j]);
			graphs.push_back ((TGraphErrors*) corr -> Clone ());
			mg.Add (corr);
		}
		mg.Write (QQQ_names[i][0]);
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
	TString comp [5] = {"_XX", "_YY", "_QQ", "_XY", "_YX"}; 
	TString comp1 [5] = {"x", "y", "x+y", "x", "y"}; 
	TString comp2 [5] = {"x", "y", "x+y", "y", "x"}; 
	TString centralities [3] = {"central", "midcentral", "peripheral"}; 
	std::string objectName;
//	TGraphErrors *g;
//	TMultiGraph *mg;
	TList *glist;
	std::vector <TGraphErrors*> graphs;
	vector <TString> profileNames;
	vector <Qn::DataContainer<Qn::Profile>*> profiles;
	TGraphErrors *g, *gc;
	TMultiGraph *mg, *mg2 [3][3], *mg3 [3][10];
	
	Qn::DataContainer<Qn::Profile> *profile [5];
	
	TDirectory *uQ_dir = fOut->mkdir( "uQ" );
	uQ_dir->cd();
	for (int axis = 0; axis < xAxes.size (); axis++)
	{
		for (ushort i = 0; i < uQ_names.size (); i++)
		{		
			profile [2] = new Qn::DataContainer<Qn::Profile>;
			objectName = Form (uQ_names[i][0], xAxes [axis].c_str());
			std::cout << std::endl << objectName;
			for (int j = 0; j < 5; j++) 
			{
				if (j != 2) fIn -> GetObject(objectName + comp [j], profile [j]);
				else if (profile [0] && profile [1]) *profile [2] = (*profile [0] + *profile [1]) * 2.;
				if (profile [j]) std::cout << "\t" << comp [j];
				else continue;
				*profile [j] = profile [j] -> Rebin( centralityAxis, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );
				profiles.push_back (profile [j]);
				profileNames.push_back (objectName + comp [j]);
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

void Save_uQQ ()
{
	std::string profileVar = "Centrality";
	std::vector <std::string> xAxes = {"pt", "y"};
	std::vector <std::string> xAxesTitles = {"p_{T}", "#it{y}"};
	TString comp [5] = {"_X2XX", "_X2YY", "_Y2XY", "_Y2YX", "_QQ"}; 
	TString comp1 [5] = {"x", "y", "x", "y", "x+y"}; 
	TString comp2 [5] = {"x", "y", "y", "x", "x+y"}; 
	TString comp3 [5] = {"x", "y", "y", "x", "x+y"}; 
	std::string objectName;
	TGraphErrors *g;
	TMultiGraph *mg;
	TList *glist;
	std::vector <TGraphErrors*> graphs;
	vector <TString> profileNames;
	vector <Qn::DataContainer<Qn::Profile>*> profiles;
	
	Qn::DataContainer<Qn::Profile> *profile [5];
	
	TDirectory *uQQ_dir = fOut->mkdir( "uQQ" );
	uQQ_dir->cd();
	for (int axis = 0; axis < xAxes.size (); axis++)
	{
		for (ushort i = 0; i < uQQ_names.size (); i++)
		{		
			profile [4] = new Qn::DataContainer<Qn::Profile>;
			objectName = Form (uQQ_names[i][0], xAxes [axis].c_str());
			std::cout << std::endl << objectName;
			for (int j = 0; j < 4; j++) // check: 4 or 5
			{
				if (j < 4) fIn -> GetObject(objectName + comp [j], profile [j]);
				else if (profile [0] && profile [1]) *profile [4] = *profile [0] + *profile [1];
				if (profile [j]) std::cout << "\t" << comp [j];
				else continue;
				profiles.push_back (profile [j]);
				profileNames.push_back (objectName + comp [j]);
				*profile [j] = profile [j] -> Rebin( centralityAxis, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );
				mg = DataToMultiGraph (*profile [j], profileVar);
				mg -> SetName (Form (uQQ_names[i][0], xAxesTitles [axis].c_str()) + comp [j]);
				mg -> SetTitle (Form (uQQ_names[i][1], comp1 [j].Data(), comp2 [j].Data(), comp3 [j].Data()));
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
	TString xAxisTitle = "Centrality class";
	TString comp [3] = {"XX", "YY", "QQ"}; 
	TString comp1 [3] = {"x", "y", "x+y"}; 
	TString comp2 [3] = {"x", "y", "x+y"}; 
	
	TGraphErrors *g;
	vector <TGraphErrors*> graphs;
	Qn::DataContainer<Qn::Profile> *profile [3][3], res;
	vector <Qn::DataContainer<Qn::Profile>> profiles;
	vector <TString> profileNames;
	TString resName;
	TString resTitle;
	
	profile [2][0] = new Qn::DataContainer<Qn::Profile>; // [comp][ab-ac-bc]
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
				fIn -> GetObject(res_names[i][1]+ comp [j], profile [j][0]);
				fIn -> GetObject(res_names[i][2]+ comp [j], profile [j][1]);
				fIn -> GetObject(res_names[i][3]+ comp [j], profile [j][2]);
			}
			else if (profile [0][0] && profile [0][1] &&  profile [0][2] &&
							 profile [1][0] && profile [1][1] &&  profile [1][2]) 
			{
				*profile [2][0] = (*profile [0][0] + *profile [1][0]) * 2.;
				*profile [2][1] = (*profile [0][1] + *profile [1][1]) * 2.;
				*profile [2][2] = (*profile [0][2] + *profile [1][2]) * 2.;
			}
			if (profile [j][0] && profile [j][1] && profile [j][2]) 
			{
				std::cout << "\t" << comp [j];
				res = Sqrt((*profile [j][0]) * (*profile [j][1]) / (*profile [j][2]));
			}
			else continue;
			
			resName = res_names[i][0]+ comp [j];
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
		mg.SetTitle(Form (res_names [i][4] + ";%s;R_{1}", "", xAxisTitle.Data()));
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


void SaveFlow (int harmonic)
{
	std::string profileVar = "Centrality";
	std::vector <std::string> xAxes = {"pt", "y"};
	std::vector <std::string> xAxesTitles = {"p_{T} [GeV/c]", "#it{y}"};
	TString folderNames [2] = {"V1", "V2"};
	TString comp [3] = {"_XX", "_YY", "_QQ"}; 
	TString comp1 [3] = {"x", "y", "x+y"}; 
	TString centralities [3] = {"central", "midcentral", "peripheral"};
	
	const int (*pubB)[3];
	const float *(*pubX)[3];
	const float *(*pubY)[3];
	const float *(*pubE)[3];
	
	// pions
	pubB = nBins_pi;
	pubX = NA49_pi_v1_bins;
	pubY = NA49_pi_v1_value;
	pubE = NA49_pi_v1_error;
	// pions
		
	// protons
//	pubB = nBins_p;
//	pubX = NA49_p_v1_bins;
//	pubY = NA49_p_v1_value;
//	pubE = NA49_p_v1_error;
	// protons
	
	TGraphErrors* pub [3];
	
	std::vector <std::vector<TString>> flow_names;
	if (harmonic == 1) flow_names = V1_names; 
	if (harmonic == 2) flow_names = V2_names; 
	std::string corrName, resName, flowName;
	TGraphErrors *g, *gc;
	TMultiGraph *mg, *mg2 [3][3], *mg3 [3][10];
	TList *glist;
	std::vector <TGraphErrors*> graphs;
	Qn::DataContainer<Qn::Profile> *corr [3], *res [3], flow [3];
	
	TDirectory *flow_dir = fOut->mkdir( folderNames [harmonic - 1] );
	flow_dir->cd();
	TDirectory *cent_dir [3];
	for (int cent = 0; cent < 3; cent++)
		cent_dir [cent] = flow_dir -> mkdir (centralities [cent]);
		
	for (int axis = 0; axis < xAxes.size (); axis++)
	{
		for (int cent = 0; cent < 3; cent++) {
			pub [cent] = new TGraphErrors (pubB [axis][cent], pubX [axis][cent], pubY [axis][cent], 0, pubE [axis][cent]);
			pub [cent] -> SetTitle ("v_{1,x+y}{#psi_{p}^{PP}}");
			pub [cent] -> SetName (Form("v1_%s_pub_%s", xAxes [axis].c_str(), centralities [cent].Data()));
			pub [cent] -> SetLineColor (kBlack);
			pub [cent] -> SetMarkerColor (kBlack);
			pub [cent] -> SetMarkerStyle (28);
			pub [cent] -> SetMarkerSize (1.5);
			graphs.push_back(pub [cent]);
			
			for (int j = 0; j < 3; j++) {
				mg2 [cent][j] = new TMultiGraph ();
				mg2 [cent][j] -> SetTitle (Form ("V_{%d}^{%s} (%s) (%s);%s;V_{1}^{%s}", harmonic, comp1 [j].Data(), xAxes [axis].c_str(), centralities [cent].Data(), xAxesTitles [axis].c_str(), comp1 [j].Data()));
			}
			for (int name = 0; name < flow_names.size (); name++) 
			{
				mg3 [cent][name] = new TMultiGraph ();
			}
		}
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
//				if (j == 2) flow [j] = *corr [j] / (*res [j]); // like I like)
				if (j == 2) flow [j] = ((*corr [0] / (*res [0])) + (*corr [1] / (*res [1]))) * sqrt (2.); // alice-like 1 - average before centrality rebin
//				flow [j] = (*corr [j]) * sqrt (2.) / (*res [j]); // alice-like 2
				else flow [j] = (*corr [j]) * sqrt (2.) / (*res [j]); // everything besides alice-like 2
				flow [j] = flow [j].Rebin( centralityAxis, [](Qn::Profile &a, Qn::Profile &b) { return  a+b; } );
//				if (j == 2) flow [j] = (flow [0] + flow [1]); // alice-like 2 - average after centrality rebin
				mg = DataToMultiGraph (flow [j], profileVar);
				mg -> SetName (flowName + comp [j]);
				mg -> SetTitle (Form (flow_names[i][3], comp1 [j].Data()));
				glist = mg -> GetListOfGraphs ();
				for (int cent = 0; cent < glist -> GetSize (); cent++) 
				{		
					g = (TGraphErrors*) glist -> At(cent);
					g -> SetTitle (Form (flow_names[i][3], comp1 [j].Data()));
					g -> GetXaxis () -> SetTitle (xAxesTitles [axis].c_str());
					g -> SetMarkerSize (1.5);
					g -> SetMarkerStyle (markers [i]);
					g -> SetMarkerColor (colors [i]);
					g -> SetLineColor (colors [i]);
					g -> SetName (flowName + "_" + comp1 [j] + "_" + centralities [cent]);
					graphs.push_back (g);
					if (i == 0) mg2 [cent][j] -> Add (pub [cent]);
					mg2 [cent][j] -> Add (g);
					gc = (TGraphErrors*) g -> Clone ();
					gc -> SetMarkerStyle (markers [j]);
					gc -> SetMarkerColor (colors [j]);
					gc -> SetLineColor (colors [j]);
					if (j == 0) mg3 [cent][i] -> Add (pub [cent]);
					mg3 [cent][i] -> Add (gc);
					mg3 [cent][i] -> SetTitle (Form (flow_names[i][3] + " (%s);%s;V_{1}", "", centralities [cent].Data(), xAxesTitles [axis].c_str()));
				}
//				g = new TGraphErrors (NA49_pi_v1_bins[][].size(), NA49_pi_v1_bins[][], NA49_pi_v1_value[][], NA49_pi_v1_error[][]);
//				mg -> Write(flowName + comp [j]);
			}
		}
		
		for (int cent = 0; cent < 3; cent++) 
		{
			cent_dir [cent] -> cd ();
			for (int j = 0; j < 3; j++) 
			{
				mg2 [cent][j] -> Write (Form ("V_1_%s_%s", comp1 [j].Data(), xAxes [axis].c_str()));
			}
			for (int name = 0; name < flow_names.size (); name++) 
			{
				mg3 [cent][name] -> Write (Form (flow_names[name][0], xAxes [axis].c_str()));
			}
		}
	}
	
	std::cout << std::endl;
	
	flow_dir -> cd ();
	for (ushort i = 0; i < graphs.size (); i++)
	{
		graphs [i] -> Write ();
	}
}