#define pixelAnalysis_cxx
#include "pixelAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

TString path="./";

void pixelAnalysisOutput(TString filename, Bool_t outputCSV=0) {
		// open file
		// filename = "../rootfiles/" + filename + ".root";
		// TString filename_input = "/scratch/data/rootfiles/" + filename + ".root";
	//  TString filename_input = "/shared/storage/physnp/faoa500/scratch/data/rootfiles/" + filename + ".root";
		TString filename_input = path + filename + ".root";
		TTree* tree;
		TFile* f = new TFile(filename_input);
		f->GetObject("photonList", tree);
		pixelAnalysis* t = new pixelAnalysis(tree);

//		Double_t maxE = 800.;

//		t->SetOutput(filename);
		// t->InitHistograms(200, 1000);
		// t->InitHistograms(200, maxE);
		t->InitHistograms();

//		Double_t correction_main = 1.;
//		Double_t correction_coinc = 1.;

		t->Loop(filename, outputCSV);
//		t->Loop(false, correction_main, correction_coinc, maxE, false, false);
//		t->Plot(0, 0, 0, 0, true, false);
}

//void pixelAnalysis::SetOutput(TString filename) {
//  plot_out_file = new TFile(path + "output/plots_" + filename + ".root", "recreate");
//}

void pixelAnalysis::InitHistograms() {
//void pixelAnalysis::InitHistograms(UInt_t bins, Double_t maxE) {
	
	Int_t nBins_1D = 1000;
	Int_t nBins_2D = 100;
	
	Double_t xyBins = 104;
	Double_t xyMin = -26.0;
	Double_t xyMax = 26.0;
	Double_t maxE = 1;
	Double_t maxHits = 10000;
	
	gammaXY_h = new TH2F("gammaXY_h","Gamma ray hit positions",xyBins,xyMin,xyMax,xyBins,xyMin,xyMax);
	photonXY_h = new TH2F("photonXY_h","Photon hit positions",xyBins,xyMin,xyMax,xyBins,xyMin,xyMax);
	
	energyDeposit_h = new TH1F("energyDeposit_h","Energy deposits",nBins_1D,0,maxE);
	photonHits_h = new TH1F("photonHits_h","Total photons collected",nBins_1D,0,maxHits);
	hitsVsEnergy_h = new TH2F("hitsVsEnergy_h","Photons collected vs. energy deposit",nBins_2D,0,maxE,nBins_2D,0,maxHits);
	
	sipmHits_h = new TH2F("sipmHits_h","SiPM hit pattern",8,0,8,8,0,8);
	sipmHits_cut_h = new TH2F("sipmHits_cut_h","SiPM hit pattern for good hits",8,0,8,8,0,8);
	
}

//void pixelAnalysis::Plot(UInt_t x, UInt_t y, UInt_t z, UInt_t version, Bool_t print, Bool_t output_lightmap) {
//
//}

void pixelAnalysis::Loop(TString filename, Bool_t outputCSV=0)
{
//   In a ROOT session, you can do:
//      root> .L pixelAnalysis.C
//      root> pixelAnalysis t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   
   ofstream csvOut;
   if(outputCSV) csvOut.open(filename+".csv");
   
   Double_t sipmHits[64];

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
      if(jentry%1000==0) cout << "Processing event " << jentry << endl;
      
      for(int i=0;i<64;i++) sipmHits[i]=0; // reset arrays at start of each event.
      
      gammaXY_h->Fill((*xGam)[0],(*yGam)[0]);
      
      energyDeposit_h->Fill(Egam);
      photonHits_h->Fill(hits);
      hitsVsEnergy_h->Fill(Egam,hits);
      
			for(int i=0;i<x->size();i++) {
				photonXY_h->Fill((*x)[i],(*y)[i]);
				sipmHits_h->Fill((*sipmID)[i]/8,(*sipmID)[i]%8,1./hits);
				if(gammaHits==1) {
					sipmHits_cut_h->Fill((*sipmID)[i]/8,(*sipmID)[i]%8,1./hits);
					sipmHits[(*sipmID)[i]]++;
				}
			}
			
			if(outputCSV && gammaHits==1) {
				for(int i=0;i<64;i++) csvOut << sipmHits[i]/hits << ",";
				csvOut << hits << "\n";
			}
      
   }
   csvOut.close();
	 if(outputCSV) {
			cout << "Single hit events written to file: " << filename << ".csv" << endl;
	 }
   
}
