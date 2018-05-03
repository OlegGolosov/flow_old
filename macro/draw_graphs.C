vector <TString> subevents = {"TPC_pt", "TPC_y"};
//vector <TString> qa = {"h2ypt_", "h2phipt_", "h2phiy_"};
vector <TString> qa = {};
vector <TString> QQ = {"PSD1_PSD2_SP", "PSD1_PSD3_SP", "PSD2_PSD3_SP",};
vector <TString> res = {"R1_PSD1_3S_EP_", "R1_PSD2_3S_EP_"};
vector <TString> resComp = {"x-direction", "y-direction", "full"};
vector <TString> flowComp = {"x", "y", "x+y"};
//float resLim [4] = {0, 6, 0., .11};
float resLim [4] = {0, 6, 0., 0.8};
float QQLim [4] = {0, 6, -0.0003, 0.0045};
//vector <TString> v1 = {"V_1_x_%s", "V_1_y_%s", "V_1_x+y_%s", "V1_%s_3S_PSD1", "V1_%s_3S_PSD2"};
//vector <TString> v1 = {"V1_%s_3S_PSD1", "V1_%s_3S_PSD2"};
vector <TString> v1 = {"V1_%s_3S_PSD1"};
vector <TString> v1_all = {"V1_%s_3S_PSD1_x_%s", "V1_%s_3S_PSD1_y_%s", "V1_%s_3S_PSD1_x+y_%s",
													 "V1_%s_3S_PSD2_x_%s", "V1_%s_3S_PSD2_y_%s", "V1_%s_3S_PSD2_x+y_%s"};
TString v1_pub = "v1_%s_pub_%s";

TString particle = "#pi-";
TString particle = "p";
float v1Lim [2][4] = {{0., 1.8, -0.06, 0.1},
											{0., 1.4, -0.1, 0.01}}; // pions
//float v1Lim [2][4] = {{0., 2., -0.06, 0.2},
//											{0., 2., -0.02, 0.2}}; // protons
float legPos [2][4] = {{0.12, 0.54, 0.45, 0.89},
											{0.12, 0.12, 0.52, 0.52}};
//int imin = 0; // show published
int imin = 1; // do not show published
TString centralities [3] = {"central", "midcentral", "peripheral"};
TString centRange [3] = {"0-12.5%", "12.5-33.5%", "33.5-100%"};
TString xAxes [2] = {"pt", "y"};
TString xAxesTitles [2] = {"p_{T} [GeV/c]", "#it{y}"};
TString integration [2] = {"0 < #it{y} < 1.4", "0 < p_{T} <2.0 GeV/c"};
TString steps [2] = {"rec", "twr"};
TString stepNames [2] = {"recentring", "twist and rescale"};
TString expName = "Pb-Pb @ 40A GeV";
const int colors[6] = {kBlue, kRed, kGreen+4, kMagenta, kBlack, kOrange};
const int markers[6] = { 20, 21, 22, 26, 27, 1};

											

void draw_graphs (TString inFolder = "/home/ogolosov/Desktop/analysis/NA49_flow/lowY_eff/piminus/centr+mb/")
{
	TString outFolder = inFolder;
//	TString outFolder = inFolder + "/pdf";
//	gSystem -> Exec ("mkdir -p " + outFolder);
	TString objectName, xaxis, yaxis, printPath;
	TGraphErrors *g [5], *g_pub [3];
	TMultiGraph *mg, *mg_all, *mg_all_pub;
	TH2F *h2;
	TFile *fIn;
	gStyle -> SetLegendBorderSize (0);
	gStyle -> SetLegendTextSize (0.035);
	TCanvas *c = new TCanvas ("c","c", 800, 600);
	TLegend *l;
	TList *glist;
	int counter = 0;
	TText *text = new TText();
	text-> SetNDC();
	text -> SetTextSize(0.035);
//	text -> SetTextFont(42);
//		text -> SetTextAlign(22);
	text -> DrawText(0.6, 0.8, expName);
	gPad->Print(outFolder + "/output.pdf(","pdf");

	TH1F *hAxis = new TH1F("axis","",100,-3.,3.);
	hAxis->SetStats (0);
	hAxis->GetYaxis()->SetTitle("v_{1}");
	hAxis->SetLineColor (kBlack);
	hAxis->GetXaxis()->SetTitleSize(0.05);
	hAxis->GetYaxis()->SetTitleSize(0.05);
	hAxis->GetXaxis()->SetTitleOffset(0.9);
	hAxis->GetYaxis()->SetTitleOffset(0.9);
	
	fIn = new TFile (inFolder + "/qa.root", "read");
	for (int sub = 0; sub < subevents.size (); sub++)
	{ 
		for (int iqa = 0; iqa < qa.size (); iqa++) 
		{
			h2 = (TH2F*) fIn -> Get (subevents [sub] + "/" + qa [iqa] + subevents [sub]);
			h2 -> Draw ("colz");
			gPad -> SetLogz ();
//			gPad -> SaveAs (outFolder + "/" + qa [iqa] + subevents [sub] + ".png");
//			gPad -> SaveAs (outFolder + "/" + qa [iqa] + subevents [sub] + ".C");
			
			gPad->Print(outFolder + "/output.pdf","pdf");
//			gPad -> SaveAs (outFolder + Form ("/%i.pdf", counter++));
		}
	}
	
	for (int step = 1; step < 2; step++) {
		fIn = new TFile (inFolder + Form ("/graph_%d.root", step + 1), "read"); 
		if (step == 1)
		{
			for (int i = 0; i < QQ.size (); i++) 
			{
				mg = (TMultiGraph*) fIn -> Get ("QQ/" + QQ [i]);
				mg -> Draw ("AP");
				mg -> GetXaxis () -> SetRangeUser (QQLim[0], QQLim[1]);
				mg -> GetYaxis () -> SetRangeUser (QQLim[2], QQLim[3]);
				l = new TLegend (0.66, 0.62, 0.88, 0.87);
				glist = mg -> GetListOfGraphs ();
				for (int i = 0; i < glist -> GetSize (); i++) 
				{		
					g [i] = (TGraphErrors*) glist -> At(i);
//					g [i] -> SetName (res [ires] + Form("%d", i));
//					g [i] -> SetMarkerSize (1.5);
//					g [i] -> SetMarkerStyle (markers [i]);
//					g [i] -> SetMarkerColor (colors [i]);
//					g [i] -> SetLineColor (colors [i]);
					l -> AddEntry (g [i] -> GetName (), g [i] -> GetTitle (), "p");
				}
				l -> Draw ();
				text -> DrawText(0.15, 0.85, expName);
				text -> DrawText(0.15, 0.8, "NA49 performance");
				text -> DrawText(0.15, 0.75, "Centrality: EVETO");
				gPad->Print(outFolder + "/output.pdf","pdf");
//				gPad -> SaveAs (outFolder + "/" + QQ [ires] + ".png");
//				gPad -> SaveAs (outFolder + "/" + QQ [ires] + ".C");
				gPad -> SaveAs (outFolder + Form ("/c%i.C", counter++));
			}
			for (int ires = 0; ires < res.size (); ires++) 
			{
				mg = (TMultiGraph*) fIn -> Get ("resolution/" + res [ires]);
				mg -> Draw ("AP");
				mg -> GetXaxis () -> SetRangeUser (resLim[0], resLim[1]);
				mg -> GetYaxis () -> SetRangeUser (resLim[2], resLim[3]);
				l = new TLegend (0.4, 0.15, 0.8, 0.35);
				l -> SetHeader ("3-sub: VCAL[RCAL1, RCAL2]");
				glist = mg -> GetListOfGraphs ();
				for (int i = 0; i < glist -> GetSize (); i++) 
				{		
					g [i] = (TGraphErrors*) glist -> At(i);
					l -> AddEntry (g [i] -> GetName (), Form ("R_{1,%s}", resComp [i].Data()), "p");
				}
				l -> Draw ();
				text -> DrawText(0.6, 0.85, expName);
				text -> DrawText(0.6, 0.8, "NA49 performance");
				text -> DrawText(0.6, 0.75, "Centrality: EVETO");
				gPad->Print(outFolder + "/output.pdf","pdf");
//				gPad -> SaveAs (outFolder + "/" + res [ires] + ".png");
//				gPad -> SaveAs (outFolder + "/" + res [ires] + ".C");
				gPad -> SaveAs (outFolder + Form ("/c%i.C", counter++));
			}
		}
	

		for (int axis = 0; axis < 2; axis++)
		{	
			for (int iname = 0; iname < v1.size (); iname++) 
			{
				for (int cent = 0; cent < 3; cent++) 
				{
					hAxis->SetTitle(Form ("%s, %s", centralities [cent].Data(), stepNames [step].Data()));
					hAxis->GetXaxis()->SetTitle(xAxesTitles [axis]);
					hAxis->GetXaxis() -> SetRangeUser (v1Lim[axis][0], v1Lim[axis][1]);
					hAxis->GetYaxis() -> SetRangeUser (v1Lim[axis][2], v1Lim[axis][3]);
					hAxis->Draw();
					objectName = Form ("V1/%s/" + v1 [iname], centralities [cent].Data(), xAxes [axis].Data());
					cout << objectName << endl;
					mg = (TMultiGraph*) fIn -> Get (objectName);
//					mg -> SetTitle (Form ("%s, %s", centralities [cent].Data(), stepNames [step].Data()));
					l = new TLegend (legPos[axis][0], legPos[axis][1], legPos[axis][2], legPos[axis][3]);   
					l -> SetHeader(centRange [cent] + ", " + particle + ", " + integration [axis], "C");
					l -> AddEntry ("", "v_{1}{#psi^{p}_{SP}}; Q_{VCAL}{SP}", "");
//					mg -> Draw ("AP");
					glist = mg -> GetListOfGraphs ();
					for (int i = imin; i < glist -> GetSize (); i++) 
					{		
						g [i] = (TGraphErrors*) glist -> At(i);
						g [i] -> Draw ("p");
						l -> AddEntry (g [i] -> GetName (), Form ("v_{1,%s}", flowComp [i - 1].Data()), "p");
//						l -> AddEntry (g [i] -> GetName (), Form ("%s", g [i] -> GetTitle ()), "p");
//						l -> AddEntry (g [i] -> GetName (), Form ("R_{1,%s}", resComp [i].Data()), "p");
					}
					l -> Draw();				
					text -> DrawText(0.65, 0.85, "NA49 preliminary");
					text -> DrawText(0.65, 0.8, expName);
					text -> DrawText(0.65, 0.75, "Centrality: EVETO");
					gPad -> Print(outFolder + "/output.pdf","pdf");	

//					gPad -> SaveAs (outFolder + "/" + Form (v1 [iname], xAxes [axis].Data()) + "_" + steps [step] + ".png");
//					gPad -> SaveAs (outFolder + "/" + Form (v1 [iname], xAxes [axis].Data()) + "_" + steps [step] + ".C");
					gPad -> SaveAs (outFolder + Form ("/c%i.C", counter++));

				}
			}
			
			for (int iname = 0; iname < v1_all.size (); iname++) 
			{	
				hAxis->SetTitle(Form ("%s", stepNames [step].Data()));
				hAxis->GetXaxis()->SetTitle(xAxesTitles [axis]);
				hAxis->GetXaxis() -> SetRangeUser (v1Lim[axis][0], v1Lim[axis][1]);
				hAxis->GetYaxis() -> SetRangeUser (v1Lim[axis][2], v1Lim[axis][3]);
				hAxis->Draw();
				l = new TLegend (legPos[axis][0], legPos[axis][1], legPos[axis][2], legPos[axis][3]);
				l -> SetHeader(integration [axis], "C");
				l->SetNColumns(2);
				l -> AddEntry ("", "v_{1}{#psi^{p}_{SP}}; Q_{VCAL}^{3-sub}", "");
				l -> AddEntry ("", "v_{1}{#psi^{p}_{PP}}; Q_{TPC}^{RNDM-sub}", "");
				for (int cent = 0; cent < 3; cent++) 
				{
					objectName = Form ("V1/" + v1_pub, xAxes [axis].Data(), centralities [cent].Data());
					cout << objectName << endl;
					g_pub [cent] = (TGraphErrors*) fIn -> Get (objectName);
					g_pub [cent] -> SetFillColorAlpha(colors [cent] - 7, 0.35);   
					g_pub [cent] -> SetFillStyle(3244);
					g_pub [cent] -> Draw ("3");
					l -> AddEntry (g_pub [cent] -> GetName (), Form ("%s", centRange [cent].Data()), "f");
//					l -> AddEntry (g_pub [cent] -> GetName (), Form ("%s, %s", g_pub [cent] -> GetTitle (), centRange [cent].Data()), "f");


					objectName = Form ("V1/" + v1_all [iname], xAxes [axis].Data(), centralities [cent].Data());
					cout << objectName << endl;
					g [cent] = (TGraphErrors*) fIn -> Get (objectName);
					g [cent] -> SetLineColor (colors [cent]);   
					g [cent] -> SetMarkerColor (colors [cent]);   
					g [cent] -> SetMarkerStyle(markers [cent]);
					g [cent] -> Draw ("P");
					l -> AddEntry (g [cent] -> GetName (), Form ("%s", centRange [cent].Data()), "p");
				}
				
				for (int cent = 0; cent < 3; cent++)
				{
//					l -> AddEntry (g [cent] -> GetName (), Form ("%s, %s", g [cent] -> GetTitle (), centRange [cent].Data()), "p");
				}
								
				text -> DrawText(0.65, 0.85, "NA49 preliminary");
				text -> DrawText(0.65, 0.8, expName);
				text -> DrawText(0.65, 0.75, "Centrality: EVETO");
				l -> Draw ();
//				gPad -> BuildLegend (legPos[axis][0], legPos[axis][1], legPos[axis][2], legPos[axis][3]);
				
//					gPad -> SaveAs (outFolder + "/" + Form (v1_all [iname], xAxes [axis].Data(), "all") + "_" + steps [step] + ".png");
				if (step == 1 && iname < 3) gPad -> SaveAs (outFolder + "/" + Form (v1_all [iname], xAxes [axis].Data(), "all") + "_" + steps [step] + ".C");
					gPad -> SaveAs (outFolder + Form ("/c%i.C", counter++));

				gPad -> Print(outFolder + "/output.pdf","pdf");
			}
			
//			for (int iname = 0; iname < v1_all.size (); iname++) 
//			{	
//				hAxis->SetTitle(Form ("%s", stepNames [step].Data()));
//				hAxis->GetXaxis()->SetTitle(xAxesTitles [axis]);
//				hAxis->GetXaxis() -> SetRangeUser (v1Lim[axis][0], v1Lim[axis][1]);
//				hAxis->GetYaxis() -> SetRangeUser (v1Lim[axis][2], v1Lim[axis][3]);
//				hAxis->Draw();
//				l = new TLegend (legPos[axis][0], legPos[axis][1], legPos[axis][2], legPos[axis][3]);
//				l -> SetHeader(integration [axis], "C");
//				l->SetNColumns(2);
//				l -> AddEntry ("", "v_{1}{#psi^{p}_{SP}}; Q_{VCAL}^{3-sub}", "");
//				l -> AddEntry ("", "v_{1}{#psi^{p}_{PP}}; Q_{TPC}^{RNDM-sub}", "");
//				for (int cent = 0; cent < 3; cent++) 
//				{
//					objectName = Form ("V1/" + v1_pub, xAxes [axis].Data(), centralities [cent].Data());
//					cout << objectName << endl;
//					g_pub [cent] = (TGraphErrors*) fIn -> Get (objectName);
//					g_pub [cent] -> SetFillColorAlpha(colors [cent] - 7, 0.35);   
//					g_pub [cent] -> SetFillStyle(3244);
//					g_pub [cent] -> Draw ("3");
//					l -> AddEntry (g_pub [cent] -> GetName (), Form ("%s", centRange [cent].Data()), "f");
////					l -> AddEntry (g_pub [cent] -> GetName (), Form ("%s, %s", g_pub [cent] -> GetTitle (), centRange [cent].Data()), "f");
//
//
//					objectName = Form ("V1/" + v1_all [iname], xAxes [axis].Data(), centralities [cent].Data());
//					cout << objectName << endl;
//					g [cent] = (TGraphErrors*) fIn -> Get (objectName);
//					g [cent] -> SetLineColor (colors [cent]);   
//					g [cent] -> SetMarkerColor (colors [cent]);   
//					g [cent] -> SetMarkerStyle(markers [cent]);
//					g [cent] -> Draw ("P");
//					l -> AddEntry (g [cent] -> GetName (), Form ("%s", centRange [cent].Data()), "p");
//				}
//				
//				for (int cent = 0; cent < 3; cent++)
//				{
////					l -> AddEntry (g [cent] -> GetName (), Form ("%s, %s", g [cent] -> GetTitle (), centRange [cent].Data()), "p");
//				}
//								
//				text -> DrawText(0.65, 0.85, "NA49 preliminary");
//				text -> DrawText(0.65, 0.8, expName);
//				text -> DrawText(0.65, 0.75, "Centrality: EVETO");
//				l -> Draw ();
////				gPad -> BuildLegend (legPos[axis][0], legPos[axis][1], legPos[axis][2], legPos[axis][3]);
//				
////					gPad -> SaveAs (outFolder + "/" + Form (v1_all [iname], xAxes [axis].Data(), "all") + "_" + steps [step] + ".png");
//				if (step == 1 && iname < 3) gPad -> SaveAs (outFolder + "/" + Form (v1_all [iname], xAxes [axis].Data(), "all") + "_" + steps [step] + ".C");
////					gPad -> SaveAs (outFolder + Form ("/%i.pdf", counter++));
//
//				gPad -> Print(outFolder + "/output.pdf","pdf");
//			}
		}
	}
	c -> Clear();
	text -> DrawText(0.6, 0.8, "The end!");
	gPad -> Print(outFolder + "/output.pdf)","pdf");
}