//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Jun  3 09:49:20 2020 by ROOT version 6.18/04
// from TTree photonList/Photon Energy and Position List
// found on file: x0y0_point.root
//////////////////////////////////////////////////////////

#ifndef pixelAnalysis_h
#define pixelAnalysis_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "vector"

class pixelAnalysis {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           hits;
//   vector<double>  *x;
//   vector<double>  *y;
//   vector<double>  *z;
//   vector<double>  *t;
//   vector<double>  *E;
//   vector<int>     *sipmID;
   Double_t        Egam;
   Int_t           gammaHits;
   vector<int>     *process;
   vector<double>  *xGam;
   vector<double>  *yGam;
   vector<double>  *zGam;
   vector<int>		 *sipmHits;
//   Int_t           sipm0;
//   Int_t           sipm1;
//   Int_t           sipm2;
//   Int_t           sipm3;
//   Int_t           sipm4;
//   Int_t           sipm5;
//   Int_t           sipm6;
//   Int_t           sipm7;
//   Int_t           sipm8;
//   Int_t           sipm9;
//   Int_t           sipm10;
//   Int_t           sipm11;
//   Int_t           sipm12;
//   Int_t           sipm13;
//   Int_t           sipm14;
//   Int_t           sipm15;
//   Int_t           sipm16;
//   Int_t           sipm17;
//   Int_t           sipm18;
//   Int_t           sipm19;
//   Int_t           sipm20;
//   Int_t           sipm21;
//   Int_t           sipm22;
//   Int_t           sipm23;
//   Int_t           sipm24;
//   Int_t           sipm25;
//   Int_t           sipm26;
//   Int_t           sipm27;
//   Int_t           sipm28;
//   Int_t           sipm29;
//   Int_t           sipm30;
//   Int_t           sipm31;
//   Int_t           sipm32;
//   Int_t           sipm33;
//   Int_t           sipm34;
//   Int_t           sipm35;
//   Int_t           sipm36;
//   Int_t           sipm37;
//   Int_t           sipm38;
//   Int_t           sipm39;
//   Int_t           sipm40;
//   Int_t           sipm41;
//   Int_t           sipm42;
//   Int_t           sipm43;
//   Int_t           sipm44;
//   Int_t           sipm45;
//   Int_t           sipm46;
//   Int_t           sipm47;
//   Int_t           sipm48;
//   Int_t           sipm49;
//   Int_t           sipm50;
//   Int_t           sipm51;
//   Int_t           sipm52;
//   Int_t           sipm53;
//   Int_t           sipm54;
//   Int_t           sipm55;
//   Int_t           sipm56;
//   Int_t           sipm57;
//   Int_t           sipm58;
//   Int_t           sipm59;
//   Int_t           sipm60;
//   Int_t           sipm61;
//   Int_t           sipm62;
//   Int_t           sipm63;

   // List of branches
   TBranch        *b_hits;   //!
//   TBranch        *b_x;   //!
//   TBranch        *b_y;   //!
//   TBranch        *b_z;   //!
//   TBranch        *b_t;   //!
//   TBranch        *b_E;   //!
//   TBranch        *b_sipmID;   //!
   TBranch        *b_Egam;   //!
   TBranch        *b_gammaHits;   //!
   TBranch        *b_process;   //!
   TBranch        *b_xGam;   //!
   TBranch        *b_yGam;   //!
   TBranch        *b_zGam;   //!
   TBranch        *b_sipmHits;   //!
//   TBranch        *b_sipm0;   //!
//   TBranch        *b_sipm1;   //!
//   TBranch        *b_sipm2;   //!
//   TBranch        *b_sipm3;   //!
//   TBranch        *b_sipm4;   //!
//   TBranch        *b_sipm5;   //!
//   TBranch        *b_sipm6;   //!
//   TBranch        *b_sipm7;   //!
//   TBranch        *b_sipm8;   //!
//   TBranch        *b_sipm9;   //!
//   TBranch        *b_sipm10;   //!
//   TBranch        *b_sipm11;   //!
//   TBranch        *b_sipm12;   //!
//   TBranch        *b_sipm13;   //!
//   TBranch        *b_sipm14;   //!
//   TBranch        *b_sipm15;   //!
//   TBranch        *b_sipm16;   //!
//   TBranch        *b_sipm17;   //!
//   TBranch        *b_sipm18;   //!
//   TBranch        *b_sipm19;   //!
//   TBranch        *b_sipm20;   //!
//   TBranch        *b_sipm21;   //!
//   TBranch        *b_sipm22;   //!
//   TBranch        *b_sipm23;   //!
//   TBranch        *b_sipm24;   //!
//   TBranch        *b_sipm25;   //!
//   TBranch        *b_sipm26;   //!
//   TBranch        *b_sipm27;   //!
//   TBranch        *b_sipm28;   //!
//   TBranch        *b_sipm29;   //!
//   TBranch        *b_sipm30;   //!
//   TBranch        *b_sipm31;   //!
//   TBranch        *b_sipm32;   //!
//   TBranch        *b_sipm33;   //!
//   TBranch        *b_sipm34;   //!
//   TBranch        *b_sipm35;   //!
//   TBranch        *b_sipm36;   //!
//   TBranch        *b_sipm37;   //!
//   TBranch        *b_sipm38;   //!
//   TBranch        *b_sipm39;   //!
//   TBranch        *b_sipm40;   //!
//   TBranch        *b_sipm41;   //!
//   TBranch        *b_sipm42;   //!
//   TBranch        *b_sipm43;   //!
//   TBranch        *b_sipm44;   //!
//   TBranch        *b_sipm45;   //!
//   TBranch        *b_sipm46;   //!
//   TBranch        *b_sipm47;   //!
//   TBranch        *b_sipm48;   //!
//   TBranch        *b_sipm49;   //!
//   TBranch        *b_sipm50;   //!
//   TBranch        *b_sipm51;   //!
//   TBranch        *b_sipm52;   //!
//   TBranch        *b_sipm53;   //!
//   TBranch        *b_sipm54;   //!
//   TBranch        *b_sipm55;   //!
//   TBranch        *b_sipm56;   //!
//   TBranch        *b_sipm57;   //!
//   TBranch        *b_sipm58;   //!
//   TBranch        *b_sipm59;   //!
//   TBranch        *b_sipm60;   //!
//   TBranch        *b_sipm61;   //!
//   TBranch        *b_sipm62;   //!
//   TBranch        *b_sipm63;   //!
   
   TH2F* gammaXY_h;
//   TH2F* photonXY_h;
   
   TH1F* energyDeposit_h;
   TH1F* photonHits_h;
   TH2F* hitsVsEnergy_h;
   
   TH2F* sipmHits_h;
   TH2F* sipmHits_cut_h;

   pixelAnalysis(TTree *tree=0);
   virtual ~pixelAnalysis();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(TString filename,Bool_t outputCSV=0);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
	 void InitHistograms();
//	 void Plot(UInt_t x, UInt_t y, UInt_t z, UInt_t version, Bool_t print, Bool_t output_lightmap);
};

#endif

#ifdef pixelAnalysis_cxx
pixelAnalysis::pixelAnalysis(TTree *tree) : fChain(0)
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

pixelAnalysis::~pixelAnalysis()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pixelAnalysis::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t pixelAnalysis::LoadTree(Long64_t entry)
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

void pixelAnalysis::Init(TTree *tree)
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

Bool_t pixelAnalysis::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pixelAnalysis::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pixelAnalysis::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef pixelAnalysis_cxx
