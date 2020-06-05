#define pixelAnalysis_cxx
#include "pixelAnalysisClass.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

TString path="/home/userfs/j/jb536/physnp/simulations/geant4/optical/myOpModel/CsI/50x50x12.5mm/results/";

void pixelAnalysis(TString filename, Bool_t outputCSV=0, Bool_t outputROOT=0) {

		TString filename_input = path + filename + ".root";
		TTree* tree;
		TFile* f = new TFile(filename_input);
		f->GetObject("photonList", tree);
		pixelAnalysisClass* t = new pixelAnalysisClass(tree);

		t->InitHistograms();
		t->Loop(filename, outputCSV);
		if(outputROOT) t->outputToROOT(filename);
		f->cd();
}

void pixelAnalysisClass::InitHistograms() {
	
	Int_t nBins_1D = 1000;
	Int_t nBins_2D = 100;
	
	Double_t xyBins = 104;
	Double_t xyMin = -26.0;
	Double_t xyMax = 26.0;
	Double_t maxE = 1;
	Double_t maxHits = 10000;
	
	gammaXY_h = new TH2F("gammaXY_h","Gamma ray hit positions",xyBins,xyMin,xyMax,xyBins,xyMin,xyMax);
	
	energyDeposit_h = new TH1F("energyDeposit_h","Energy deposits",nBins_1D,0,maxE);
	photonHits_h = new TH1F("photonHits_h","Total photons collected",nBins_1D,0,maxHits);
	hitsVsEnergy_h = new TH2F("hitsVsEnergy_h","Photons collected vs. energy deposit",nBins_2D,0,maxE,nBins_2D,0,maxHits);
	
	sipmHits_h = new TH2F("sipmHits_h","SiPM hit pattern",8,0,8,8,0,8);
	sipmHits_cut_h = new TH2F("sipmHits_cut_h","SiPM hit pattern for good hits",8,0,8,8,0,8);
	
}

void pixelAnalysisClass::outputToROOT(TString filename)
{
	cout << "Writing plots to rootfile: " << filename + "_plots.root" << endl;
	
	rootOut = new TFile(path + filename + "_plots.root","recreate");

	gammaXY_h->Write();
	energyDeposit_h->Write();
	photonHits_h->Write();
	hitsVsEnergy_h->Write();
	sipmHits_h->Write();
	sipmHits_cut_h->Write();
	
	rootOut->Close();

}

//void pixelAnalysisClass::Plot(UInt_t x, UInt_t y, UInt_t z, UInt_t version, Bool_t print, Bool_t output_lightmap) {
//
//}

void pixelAnalysisClass::Loop(TString filename, Bool_t outputCSV=0)
{

   if (fChain == 0) return;
   
   ofstream csvOut;
   if(outputCSV) csvOut.open(filename+".csv");
   
   Long64_t nentries = fChain->GetEntriesFast();
   
   Int_t x=0;
   Int_t y=0;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(jentry%1000==0) cout << "Processing event " << jentry << endl;
            
      gammaXY_h->Fill((*xGam)[0],(*yGam)[0]);
      
      energyDeposit_h->Fill(Egam);
      photonHits_h->Fill(hits);
      hitsVsEnergy_h->Fill(Egam,hits);
      
      for(int i=0;i<64;i++) {
				x = i%8;
				y = i/8;
				sipmHits_h->Fill(x,y,(*sipmHits)[i]);
				if(gammaHits==1) sipmHits_cut_h->Fill(x,y,(*sipmHits)[i]);
      }
      
			if(outputCSV && gammaHits==1) {
				for(int i=0;i<64;i++) csvOut << (double)(*sipmHits)[i]/hits << ",";
				csvOut << hits << "\n";
			}
      
   }
   csvOut.close();
	 if(outputCSV) {
			cout << "Single hit events written to file: " << filename << ".csv" << endl;
	 }
   
}
