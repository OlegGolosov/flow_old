vector <TString> subevents = {"TPC_pt", "TPC_y"};
vector <TString> qa = {"h2ypt_", "h2phipt_", "h2phiy_"};
vector <TString> res = {"R1_PSD1_3S_SP_", "R1_PSD2_3S_SP_"};
float resLim [4] = {0, 6, 0., .11};
vector <TString> v1 = {"V_1_x_%s", "V_1_y_%s", "V_1_x+y_%s", "V1_%s_3S_PSD1", "V1_%s_3S_PSD2"};
//float v1Lim [2][4] = {{0., 2., -0.06, 0.1},
//											{0., 2., -0.1, 0.03}}; // pions
float v1Lim [2][4] = {{0., 2., -0.06, 0.2},
											{0., 2., -0.02, 0.2}}; // protons
float legPos [2][4] = {{0.2, 0.7, 0.5, 0.9},
											{0.2, 0.7, 0.5, 0.9}};

TString centralities [3] = {"central", "midcentral", "peripheral"};
TString xAxes [2] = {"pt", "y"};
TString steps [2] = {"rec", "twr"};
TString stepNames [2] = {"recentring", "twist and rescale"};

											

void draw_graphs (TString inFolder = "/home/ogolosov/Desktop/analysis/NA49_flow/default_new_y/pimin")
{
	TString outFolder = inFolder;
//	TString outFolder = inFolder + "/pdf";
//	gSystem -> Exec ("mkdir -p " + outFolder);
	TString objectName, xaxis, yaxis;
	TMultiGraph *mg;
	TH2F *h2;
	TFile *fIn; 
	TCanvas *c = new TCanvas ("c","c", 800, 600);
	int counter = 0;
	
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
			
			if (sub == 0 && iqa == 0) gPad->Print(outFolder + "/output.pdf(","pdf");
			else gPad->Print(outFolder + "/output.pdf","pdf");
//			gPad -> SaveAs (outFolder + Form ("/%i.pdf", counter++));
		}
	}
	
	for (int step = 0; step < 2; step++) {
		fIn = new TFile (inFolder + Form ("/graph_%d.root", step + 1), "read"); 
		if (step == 0)
		{
			for (int ires = 0; ires < res.size (); ires++) 
			{
				mg = (TMultiGraph*) fIn -> Get ("resolution/" + res [ires]);
				mg -> Draw ("AP");
				mg -> GetXaxis () -> SetRangeUser (resLim[0], resLim[1]);
				mg -> GetYaxis () -> SetRangeUser (resLim[2], resLim[3]);
				gPad -> BuildLegend (0.2, 0.5, 0.6, 0.7);
//				gPad -> SaveAs (outFolder + "/" + res [ires] + ".png");
//				gPad -> SaveAs (outFolder + "/" + res [ires] + ".C");
//				gPad -> SaveAs (outFolder + Form ("/%i.pdf", counter++));
				gPad->Print(outFolder + "/output.pdf","pdf");
			}
		}	
	
		for (int cent = 0; cent < 3; cent++) 
		{
			for (int axis = 0; axis < 2; axis++)
			{	
				for (int iname = 0; iname < v1.size (); iname++) 
				{
					objectName = Form ("V1/%s/" + v1 [iname], centralities [cent].Data(), xAxes [axis].Data());
					cout << objectName << endl;
					mg = (TMultiGraph*) fIn -> Get (objectName);
					mg -> Draw ("AP");
					xaxis = mg -> GetXaxis () -> GetTitle ();
					yaxis = mg -> GetYaxis () -> GetTitle ();
					mg = (TMultiGraph*) fIn -> Get (objectName);
					mg -> SetTitle (Form ("%s, %s", centralities [cent].Data(), stepNames [step].Data()));
					mg -> Draw ("AP");
					mg -> SetTitle (Form ("%s, %s", centralities [cent].Data(), stepNames [step].Data()));
					mg -> GetXaxis () -> SetRangeUser (v1Lim[axis][0], v1Lim[axis][1]);
					mg -> GetYaxis () -> SetRangeUser (v1Lim[axis][2], v1Lim[axis][3]);
//					mg -> GetYaxis () -> SetTitleOffset (0.95);
					mg -> GetXaxis () -> SetTitle (xaxis);
					mg -> GetYaxis () -> SetTitle (yaxis);
					gPad -> BuildLegend (legPos[axis][0], legPos[axis][1], legPos[axis][2], legPos[axis][3]);
					
//					gPad -> SaveAs (outFolder + "/" + Form (v1 [iname], xAxes [axis].Data()) + "_" + steps [step] + ".png");
//					gPad -> SaveAs (outFolder + "/" + Form (v1 [iname], xAxes [axis].Data()) + "_" + steps [step] + ".C");
//					gPad -> SaveAs (outFolder + Form ("/%i.pdf", counter++));

					if (step == 1 && 
							cent == 2 && 
							axis == 1 && 
							iname == v1.size () - 1) 
								gPad -> Print(outFolder + "/output.pdf)","pdf");
					else gPad -> Print(outFolder + "/output.pdf","pdf");
				}
			}
		}
	}
}