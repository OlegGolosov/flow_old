#include "../cuts/isGoodEvent.h"
#include "../cuts/isGoodTrack.h"

#include <iostream>
#include <vector>
#include <random>
#include <array>
#include <string>

#include "TTree.h"
#include "TFile.h"
#include "TString.h"
#include "TH1.h"

#include "DataTreeEvent.h"

#include "CentralityManager.h"
#include "DataTreeEvent.h"

void centrality(const TH1F& hm);


int main(int argc, char **argv)
{

  const std::string filename = argv[1];
  const std::string treename = "DataTree";
  const std::string setup = "na61";


  std::unique_ptr<TChain> chain(new TChain(treename.data()));
  std::ifstream in;
  in.open(filename);
  std::string line;
  std::cout << "Adding files to chain:" << std::endl;
  while ((in >> line).good()) {
    if (!line.empty()) {
      chain->AddFile(line.data());
      std::cout << line << std::endl;
    }
  }

  DataTreeEvent *event = new DataTreeEvent();
  chain->SetBranchAddress("DTEvent", &event);

  std::cout << "Number of entries = " << chain->GetEntries() << std::endl;

  TH1F hm("hm", "hm", 700, 0, 700 );

  DataTreeTrack *track = new DataTreeTrack;

  for (int i=0; i<chain->GetEntries(); ++i)
  {
      if ( (i+1) % 1000 == 0 ) std::cout << i+1 << "/" << chain->GetEntries() << std::endl;
      int m {0};
      chain->GetEntry(i);

      if ( !Cuts::isGoodEvent(*event) ) continue;

      const long ntracks = setup == "na61" ? event->GetNVertexTracks() : event->GetNTracks();

      for (int iTrack = 0; iTrack<ntracks; ++iTrack )
      {
          track = setup == "na61" ? event->GetVertexTrack(iTrack) : event->GetTrack(iTrack);

//           std::cout << iTrack << std::endl;

          if ( setup == "cbm"  ) if ( Cuts::isGoodTrackCbm( *track ) )  m++;
          if ( setup == "na61" || setup == "na49" ) if ( Cuts::isGoodTrack( *track ) ) m++;
      }
      hm.Fill(m);
  }

  hm.SaveAs("hm.root");
  centrality(hm);
}


void centrality(const TH1F& hm)
{
    CentralityEventContainer *fContainer = new CentralityEventContainer;
    TFile *ContFile = new TFile ("test_cont.root", "recreate");
    TTree *ContTree = new TTree ( "container", "container" );
    ContTree->Branch("CentralityEventContainer", "CentralityEventContainer", &fContainer);
    ContTree->SetDirectory(0);

    CentralityDetectorEvent TrakingDet ;
    fContainer->AddDetector(TrakingDet);

    for (Int_t iBin = 0; iBin<hm.GetNbinsX(); ++iBin )
    {
        Float_t Mult = iBin; ///*hm.GetXaxis()->GetXmin() +*/ ( hm.GetXaxis()->GetXmax() /*- hm.GetXaxis()->GetXmin()*/ ) * (Float_t)iBin / hm.GetNbinsX() ;
//         std::cout << Mult << std::endl;

        for (Int_t j = 0; j<hm.GetBinContent(iBin+1); ++j )
        {
            std::vector <Float_t> tracks (1, Mult /*+ r->Uniform( -0.1, 0.1 )*/);
            fContainer->AddDetectorEvent (0, tracks);
            ContTree->Fill();
        }
    }

//     cout << "Writing centrility container..." << endl;
    ContTree->Write();
    ContFile->Close();

    TString OutDir = "./";

    CentralityManager *manager = new CentralityManager;
    manager->SetDirectory(OutDir);

    manager->AddDetector( "Tracking detector" );

    manager->SetContainerFileName ( "test_cont.root" );
    manager->IsSimData ( false );
    //    manager->SetNormalization (1485808);                                 // set full integral (calculated with Glauber model, for mc simulation we don't neeed it?)
    manager->Det1IsInt(true);                                            // if multiplicity used as det1 - true; if as det2 - manager->Det2IsInt(true);
    manager->Do1DAnalisys(true);                                      // 1D slicing
    manager->SetDetectorsForCentralityAnalisys ("Tracking detector");    // for 2D slicing give 2 arguments for function (for example sts_det, psd1_det)
    manager->SetCentralityMax(100);                                      // set maximum value for centrality, more peripheral events will not be analysed
    manager->SetDirectionCentralEvents(1);                               // if impact parameter and detector signal is correlated = 0 (forfard energy), if anticorelated (tracks) = 1
    manager->SetSliceStep (5);                                           // slice step (width) in percents

    manager->RunSliceFinder();
    manager->WriteCentralityFile();
//     manager->QA();


}






