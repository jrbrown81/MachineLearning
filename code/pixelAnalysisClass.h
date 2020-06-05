//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun  3 09:49:20 2020 by ROOT version 6.18/04
// from TTree photonList/Photon Energy and Position List
// found on file: x0y0_point.root
//////////////////////////////////////////////////////////

#ifndef pixelAnalysisClass_h
#define pixelAnalysisClass_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class pixelAnalysisClass {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           hits;
   Double_t        Egam;
   Int_t           gammaHits;
   vector<int>     *process;
   vector<double>  *xGam;
   vector<double>  *yGam;
   vector<double>  *zGam;
   vector<int>		 *sipmHits;

   // List of branches
   TBranch        *b_hits;   //!
   TBranch        *b_Egam;   //!
   TBranch        *b_gammaHits;   //!
   TBranch        *b_process;   //!
   TBranch        *b_xGam;   //!
   TBranch        *b_yGam;   //!
   TBranch        *b_zGam;   //!
   TBranch        *b_sipmHits;   //!
   
   TH2F* gammaXY_h;
   
   TH1F* energyDeposit_h;
   TH1F* photonHits_h;
   TH2F* hitsVsEnergy_h;
   
   TH2F* sipmHits_h;
   TH2F* sipmHits_cut_h;

   pixelAnalysisClass(TTree *tree=0);
   virtual ~pixelAnalysisClass();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString filename,Bool_t outputCSV=0);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
	 void InitHistograms();
	 void outputToROOT(TString filename);
//	 void Plot(UInt_t x, UInt_t y, UInt_t z, UInt_t version, Bool_t print, Bool_t output_lightmap);

		TFile* rootOut;
};

#endif

#ifdef pixelAnalysis_cxx
pixelAnalysisClass::pixelAnalysisClass(TTree *tree) : fChain(0)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
//      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("x0y0_point.root");
//      if (!f || !f->IsOpen()) {
//         f = new TFile("x0y0_point.root");
//      }
//      f->GetObject("photonList",tree);
   }
   Init(tree);
}

pixelAnalysisClass::~pixelAnalysisClass()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pixelAnalysisClass::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pixelAnalysisClass::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void pixelAnalysisClass::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   process = 0;
   xGam = 0;
   yGam = 0;
   zGam = 0;
   sipmHits = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("hits", &hits, &b_hits);
   fChain->SetBranchAddress("Egam", &Egam, &b_Egam);
   fChain->SetBranchAddress("gammaHits", &gammaHits, &b_gammaHits);
   fChain->SetBranchAddress("process", &process, &b_process);
   fChain->SetBranchAddress("xGam", &xGam, &b_xGam);
   fChain->SetBranchAddress("yGam", &yGam, &b_yGam);
   fChain->SetBranchAddress("zGam", &zGam, &b_zGam);
	 fChain->SetBranchAddress("sipmHits", &sipmHits, &b_sipmHits);
   Notify();
}

Bool_t pixelAnalysisClass::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pixelAnalysisClass::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pixelAnalysisClass::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pixelAnalysis_cxx
