// ********************************************************************
// Simplified version of OpModelDetectorConstruction,
// for CsI, with unified model and multi-SiPM readout
//
// J. Brown
// 14/12/17
// ********************************************************************
//
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "OpModelDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4LogicalBorderSurface.hh"
#include "G4LogicalSkinSurface.hh"
#include "G4OpticalSurface.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "sipmSD.hh"
#include "crystalSD.hh"
#include "G4VSensitiveDetector.hh"
#include "G4NistManager.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"
#include "G4SubtractionSolid.hh"
#include "G4RotationMatrix.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpModelDetectorConstruction::OpModelDetectorConstruction()
 : G4VUserDetectorConstruction()
{
  fExpHall_x = fExpHall_y = fExpHall_z = 100.0*mm;
	
  fCrystal_x = fCrystal_y  =  50.4*mm;
  fCrystal_z = 50.4*mm;

//  fSiPM_x = fSiPM_y = 6*mm;
  fSiPM_x = fSiPM_y = 50.4*mm;
//  fSiPM_z = 0.21*mm;
  fSiPM_z = 0.07*mm;

 fEpoxy_z = 0.35*mm;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

OpModelDetectorConstruction::~OpModelDetectorConstruction(){;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* OpModelDetectorConstruction::Construct()
{

// Enable volume overlap checking
  G4bool checkOverlaps = true;

// ------------- Materials -------------

//Get the nist manager
  G4NistManager* nist = G4NistManager::Instance();
  nist->SetVerbose(1);

// Define CsI
	G4Material* CsI_mat = nist->FindOrBuildMaterial("G4_CESIUM_IODIDE");

// Air
  G4Material* air = nist->FindOrBuildMaterial("G4_AIR");

// Define Materials for Epoxy Cover of SiPM
	G4Element* H = nist->FindOrBuildElement("H");
	G4Element* C = nist->FindOrBuildElement("C");

	G4double epoxy_density = 1.2*g/cm3;
	G4Material* epoxy = new G4Material("epoxy",epoxy_density, 2);
	epoxy->AddElement(H,2);
	epoxy->AddElement(C,2);

// PTFE
  G4Material* PTFE = nist->FindOrBuildMaterial("G4_TEFLON");
// Silicon
   G4Material* Si = nist->FindOrBuildMaterial("G4_Si");

//******************************************************************
// ------------ Generate & Add Material Properties Table ------------
//*****************************************************************
	
	G4double photonEnergy[] = {
							1.82*eV,1.85*eV,1.90*eV,1.93*eV,1.99*eV,
							2.06*eV,2.13*eV,2.21*eV,2.29*eV,2.38*eV,
							2.43*eV,2.47*eV,2.53*eV,2.58*eV,2.63*eV,
							2.75*eV,2.88*eV,3.09*eV,3.54*eV};
	const G4int nEntries = sizeof(photonEnergy)/sizeof(G4double);

//
// Crystal
//
// Refractive index for CsI
// Taken from  Saint Gobain (Assuming that the dopent is small and neglected if this is treated as CsI:TI RI is 1.79 if treated as CsI RI is 1.95
  G4double refractiveIndexCsI[] = {
							1.79,1.79,1.79,1.79,1.79,
							1.79,1.79,1.79,1.79,1.79,
							1.79,1.79,1.79,1.79,1.79,
							1.79,1.79,1.79,1.79 };
	assert(sizeof(refractiveIndexCsI) == sizeof(photonEnergy));

// CsI absorption lengths taken from https://crystalclear.web.cern.ch/crystalclear/LitraniX/Litrani/litrani/AllModules/FitMacros/AbsorptionLength_CsITl.C.html

  G4double absorption[] = {
							412.7*cm,426.1*cm,422.6*cm,433.8*cm,471.7*cm,
							452.2*cm,449.6*cm,446.2*cm,467.6*cm,447.6*cm,
							443.5*cm,462.1*cm,464.9*cm,468.8*cm,444.5*cm,
							516.9*cm,574.1*cm,751.7*cm,160.9*cm };
	assert(sizeof(absorption) == sizeof(photonEnergy));

// CsI Scintillation
// Taken from Saint Gobain (intensity as a function of wavelength)
  G4double scintilFast[] = {
							0.2,0.3,0.4,0.5,0.6,
							0.7,0.8,0.9,1.0,0.9,
							0.8,0.7,0.6,0.5,0.4,
							0.3,0.2,0.1,0.0	};
	assert(sizeof(scintilFast) == sizeof(photonEnergy));
	
//Create a materials table for crystal properties
  G4MaterialPropertiesTable* CsI_MPT = new G4MaterialPropertiesTable();

  CsI_MPT->AddProperty("RINDEX",photonEnergy,refractiveIndexCsI,nEntries)
        ->SetSpline(true);
//  CsI_MPT->AddProperty("RAYLEIGH",photonEnergy,absorption,nEntries)
//        ->SetSpline(true);
   CsI_MPT->AddProperty("ABSLENGTH",photonEnergy,absorption,nEntries)
         ->SetSpline(true);
  CsI_MPT->AddProperty("FASTCOMPONENT",photonEnergy,scintilFast,nEntries)
        ->SetSpline(true);
//  CsI_MPT->AddProperty("SLOWCOMPONENT",photonEnergy,scintilSlow,nEntries)
//        ->SetSpline(true);
  CsI_MPT->AddConstProperty("SCINTILLATIONYIELD",52000./MeV);
//  CsI_MPT->AddConstProperty("SCINTILLATIONYIELD",50./MeV);
  CsI_MPT->AddConstProperty("RESOLUTIONSCALE",1.0);
  CsI_MPT->AddConstProperty("FASTTIMECONSTANT", 1000.*ns);
//  CsI_MPT->AddConstProperty("SLOWTIMECONSTANT",245.*ns);
//  CsI_MPT->AddConstProperty("YIELDRATIO",1); // Fast component only

  G4cout << "crystal G4MaterialPropertiesTable" << G4endl;
  CsI_MPT->DumpTable();

  CsI_mat->SetMaterialPropertiesTable(CsI_MPT);

  // Set the Birks Constant for the scintillator
	CsI_mat->GetIonisation()->SetBirksConstant(0.0163*mm/MeV);

//
//  ADD Optical properties to materials
//

// Air
// Define Optical Properties of Air
  G4double short_energy[]={2.000*eV,3.000*eV,4.200*eV};
  const G4int short_num = sizeof(short_energy)/sizeof(G4double);

// Set Refractive Index of Air
  G4double air_RIND[]={1.00,1.00,1.00};
  assert(sizeof(air_RIND) == sizeof(short_energy));
	
  G4MaterialPropertiesTable* airMPT = new G4MaterialPropertiesTable();
  airMPT->AddProperty("RINDEX", short_energy, air_RIND ,short_num);

  G4cout << "Air G4MaterialPropertiesTable" << G4endl;
  airMPT->DumpTable();

  air->SetMaterialPropertiesTable(airMPT);

// Epoxy
	G4double epoxy_RIND[]={1.590,1.590,1.590};
	assert(sizeof(epoxy_RIND) == sizeof(short_energy));
	
	G4MaterialPropertiesTable* epoxyMPT = new G4MaterialPropertiesTable();
	epoxyMPT->AddProperty("RINDEX",short_energy,epoxy_RIND,short_num);
	
	G4cout << "Epoxy G4MaterialProprtiesTable" << G4endl;
	epoxyMPT->DumpTable();
	
	epoxy->SetMaterialPropertiesTable(epoxyMPT);

//  PTFE
// Set Refractive Index of PTFE
  G4double PTFE_RIND[]={1.365,1.365,1.365}; // as used in Dietz-Laursonn
  assert(sizeof(PTFE_RIND) == sizeof(short_energy));

  G4MaterialPropertiesTable* PTFE_MPT = new G4MaterialPropertiesTable();
  PTFE_MPT->AddProperty("RINDEX", short_energy, PTFE_RIND ,short_num);

  G4cout << "PTFE G4MaterialPropertiesTable" << G4endl;
  PTFE_MPT->DumpTable();

  PTFE->SetMaterialPropertiesTable(PTFE_MPT);

//***********************************
// ------------- Volumes --------------
//***********************************

// The experimental Hall
//
  G4Box* expHall_box = new G4Box("World",0.5*fExpHall_x,0.5*fExpHall_y,0.5*fExpHall_z);
  G4LogicalVolume* expHall_log
    = new G4LogicalVolume(expHall_box,air,"World",0,0,0);
  G4VPhysicalVolume* expHall_phys
    = new G4PVPlacement(0,G4ThreeVector(),expHall_log,"World",0,false,0);
  expHall_log->SetVisAttributes(G4VisAttributes::Invisible);

  G4double PTFE_thickness=1.6*mm;
  G4double PTFE_xy = fCrystal_x + 2*PTFE_thickness;
  G4double PTFE_z = fCrystal_z + 2*PTFE_thickness;

  G4double PTFE_offset = 0.0;
  G4double crystal_offset = 0.0;
	
//	G4double SiPMOffset = (fSiPM_z+fCrystal_z)*0.5;
	G4double SiPMOffset = (fEpoxy_z+fCrystal_z)*0.5;

////////////////
// PTFE wrapping
  G4Box* PTFE_box = new G4Box("PTFE",PTFE_xy*0.5,PTFE_xy*0.5,PTFE_z*0.5);
  G4LogicalVolume* PTFE_log
		= new G4LogicalVolume(PTFE_box,PTFE,"PTFE_log",0,0,0);
  G4VPhysicalVolume* PTFE_phys =
			new G4PVPlacement(0,G4ThreeVector(0,0,PTFE_offset),PTFE_log,"PTFE",
						expHall_log,false,0,checkOverlaps);

	G4VisAttributes * PTFE_ats = new G4VisAttributes(G4Colour(1.0, 1.0, 1.0) );
	PTFE_log->SetVisAttributes(PTFE_ats);

////////////////
// The crystal volume
  G4Box* crystal_box = new G4Box("crystal",0.5*fCrystal_x,0.5*fCrystal_y,0.5*fCrystal_z);
  G4LogicalVolume* crystal_log
    = new G4LogicalVolume(crystal_box,CsI_mat,"crystal_log",0,0,0);
  G4VPhysicalVolume* crystal_phys
    = new G4PVPlacement(0,G4ThreeVector(0,0,crystal_offset),crystal_log,"crystal",
                        PTFE_log,false,0,checkOverlaps);

	G4VisAttributes * crystal_ats = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0) );
	crystal_log->SetVisAttributes(crystal_ats);

////////////////
// Epoxy Cover to photosensor
//	G4Box* sipm_box = new G4Box("sipm_box",fSiPM_x*0.5,fSiPM_y*0.5,fSiPM_z*0.5);
//	G4LogicalVolume* SiPM_log = new G4LogicalVolume(sipm_box, epoxy , "SiPM_log", 0,0,0);
// SiPM 0 - xy plan back
//	G4VPhysicalVolume* SiPM_phys_0 = new G4PVPlacement(0,	// no rotation
//											G4ThreeVector(0,0,SiPMOffset),	// position
//											SiPM_log,                //its logical volume
//											"SiPM1",              //its name
//											PTFE_log,              //its mother  volume
//											false,                   //no boolean operation
//											0,                       //copy number
//											checkOverlaps);          //overlaps checking

	G4RotationMatrix* rotX90 = new G4RotationMatrix();
	rotX90->rotateX(90.*deg);
	G4RotationMatrix* rotX180 = new G4RotationMatrix();
	rotX180->rotateX(180.*deg);
	G4RotationMatrix* rotX270 = new G4RotationMatrix();
	rotX270->rotateX(270.*deg);
	G4RotationMatrix* rotY90 = new G4RotationMatrix();
	rotY90->rotateY(90.*deg);
	G4RotationMatrix* rotY270 = new G4RotationMatrix();
	rotY270->rotateY(270.*deg);
	
	G4Box* epoxy_box = new G4Box("Epoxy_box",fSiPM_x*0.5,fSiPM_y*0.5,fEpoxy_z*0.5);
	G4LogicalVolume* epoxy_log = new G4LogicalVolume(epoxy_box, epoxy , "epoxy_log", 0,0,0);
	G4Box* sipm_box = new G4Box("sipm_box",fSiPM_x*0.5,fSiPM_y*0.5,fSiPM_z*0.5);
	G4LogicalVolume* SiPM_log = new G4LogicalVolume(sipm_box, Si , "SiPM_log", 0,0,0);

// SiPM 0 - xy plane back
	G4VPhysicalVolume* epoxy_phys_0 = new G4PVPlacement(0,G4ThreeVector(0,0,SiPMOffset),epoxy_log,
											"epoxy0",PTFE_log,false,0,checkOverlaps);
// Share Si physical volume used by all SiPMs
	G4VPhysicalVolume* Si_phys
		= new G4PVPlacement(0,G4ThreeVector(0,0,0.5*(fEpoxy_z-fSiPM_z)),SiPM_log,
		"sipm0",epoxy_log,false,0,checkOverlaps);
// SiPM 1 - xy plane front
	G4VPhysicalVolume* epoxy_phys_1 =
	new G4PVPlacement(rotX180,G4ThreeVector(0,0,-SiPMOffset),epoxy_log,"epoxy1",PTFE_log,false,1,checkOverlaps);
// SiPM 2 - xz plane, positive side
	G4VPhysicalVolume* epoxy_phys_2 =
	new G4PVPlacement(rotX90,G4ThreeVector(0,SiPMOffset,0),epoxy_log,"epoxy2",PTFE_log,false,2,checkOverlaps);
// SiPM 3 - xz plane, negative side
	G4VPhysicalVolume* epoxy_phys_3 =
	new G4PVPlacement(rotX270,G4ThreeVector(0,-SiPMOffset,0),epoxy_log,"epoxy3",PTFE_log,false,3,checkOverlaps);
// SiPM 4 - yz plane, positive side
	G4VPhysicalVolume* epoxy_phys_4 =
	new G4PVPlacement(rotY270,G4ThreeVector(SiPMOffset,0,0),epoxy_log,"epoxy4",PTFE_log,false,4,checkOverlaps);
// SiPM 5 - yz plane, negative side
	G4VPhysicalVolume* epoxy_phys_5 =
	new G4PVPlacement(rotY90,G4ThreeVector(-SiPMOffset,0,0),epoxy_log,"epoxy5",PTFE_log,false,5,checkOverlaps);
	
	G4VisAttributes * epoxy_ats = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0) );
	epoxy_log->SetVisAttributes(epoxy_ats);
	G4VisAttributes * sipm_ats = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0) );
	SiPM_log->SetVisAttributes(sipm_ats);

//**************************************
// ------------- Surfaces --------------
//**************************************

///////////////////////
// Crystal to PTFE

// unified

//	G4double sigma_alpha_1=100*rad;
	G4double sigma_alpha_1=0.6*rad; // From Gostojic "Simulation 2"
//	G4double sigma_alpha_2=10.*rad; // Note that my alpha 1 and 2 are opposite to Gostojic

  G4OpticalSurface* crystalPTFESurface = new G4OpticalSurface("crystalSurface");
	crystalPTFESurface->SetType(dielectric_dielectric);
  crystalPTFESurface->SetModel(unified);
	crystalPTFESurface->SetFinish(groundbackpainted);
	crystalPTFESurface->SetSigmaAlpha(sigma_alpha_1);

  new G4LogicalBorderSurface("crystalSurface",crystal_phys,PTFE_phys,crystalPTFESurface);

  G4double PTFE_reflect[]={0.97,0.97,0.97}; // as used in Gostojic2016
//   G4double PTFE_reflect[]={0.99,0.99,0.99}; // as used in Dietz-Laursonn
//   G4double PTFE_reflect[]={0.0,0.0,0.0}; // as used in Dietz-Laursonn
  assert(sizeof(PTFE_reflect) == sizeof(short_energy));
	
  G4double specularlobe[3]={0.,0.,0.};
	G4double specularspike[3]={0.,0.,0.};
	G4double backscatter[3]={0.,0.0,0.};

  G4MaterialPropertiesTable* crystalPTFE_SMPT = new G4MaterialPropertiesTable();
  crystalPTFE_SMPT->AddProperty("REFLECTIVITY",short_energy,PTFE_reflect,short_num);
  crystalPTFE_SMPT->AddProperty("SPECULARLOBECONSTANT",short_energy,specularlobe,short_num);
  crystalPTFE_SMPT->AddProperty("SPECULARSPIKECONSTANT",short_energy,specularspike,short_num);
  crystalPTFE_SMPT->AddProperty("BACKSCATTERCONSTANT",short_energy,backscatter,short_num);
// use refractive index to simulate a thin layer of air between crystal and wrapping
// This only has an effect if using "backpainted" surfaces!
   crystalPTFE_SMPT->AddProperty("RINDEX",short_energy,air_RIND,short_num);

  crystalPTFESurface->SetMaterialPropertiesTable(crystalPTFE_SMPT);

// glisur // old
//  G4OpticalSurface* crystalPTFESurface = new G4OpticalSurface("crystalSurface");
//  crystalPTFESurface->SetType(dielectric_metal); // use this to ensure get 97% of light reflected from PTFE
//  crystalPTFESurface->SetFinish(ground); // as used in Gostojic2016
//  crystalPTFESurface->SetModel(glisur);
//  crystalPTFESurface->SetPolish(0.75); // 1 is a polished surface, 0 is maximum roughness
//
//  new G4LogicalBorderSurface("crystalSurface",crystal_phys,PTFE_phys,crystalPTFESurface);
//
//  G4double PTFE_reflect[]={0.97,0.97,0.97}; // as used in Gostojic2016
//  assert(sizeof(PTFE_reflect) == sizeof(short_energy));
//
//  G4MaterialPropertiesTable* crystalPTFE_SMPT = new G4MaterialPropertiesTable();
//  crystalPTFE_SMPT->AddProperty("REFLECTIVITY",short_energy,PTFE_reflect,short_num);
//  crystalPTFESurface->SetMaterialPropertiesTable(crystalPTFE_SMPT);
//
////  G4cout << "Crystal_PTFE Surface Material Properties Table" << G4endl;
////  crystalPTFE_SMPT->DumpTable();
//
////////////////////////
// Crystal to SiPM

// SiPM Properties
	G4double Si_reflect[]={0.0,0.0,0.0};
//	G4double SiPM_reflect[]={1.0,1.0,1.0};
	G4double SiPM_reflect[]={0.97,0.97,0.97};
	assert(sizeof(SiPM_reflect) == sizeof(short_energy));
	G4double grease_RIND[]={1.465,1.465,1.465};	// Think this only has an effect for back/frontpainted surfaces
	assert(sizeof(grease_RIND) == sizeof(short_energy));

	G4double SiPM_Energy[]={2.0*eV,2.18*eV,2.38*eV,2.64*eV,2.95*eV,3.35*eV,3.88*eV,4.*eV,4.13*eV,4.27*eV };
	const G4int SiPM_num=sizeof(SiPM_Energy)/sizeof(G4double);
	G4double SiPM_PDE[] = {0.15,0.18,0.25,0.375,0.43,0.33,0.08,0.05,0.05,0.05};
	assert(sizeof(SiPM_PDE) == sizeof(SiPM_Energy));

// unified, crystal to epoxy layer
	G4OpticalSurface* crystalSiPMSurface = new G4OpticalSurface("crystalSiPMSurface",unified,ground,dielectric_dielectric);
//	crystalSiPMSurface->SetSigmaAlpha(sigma_alpha_2); // as used by Gostojic2016
// I think both crystal surfaces should have same level of roughness
	crystalSiPMSurface->SetSigmaAlpha(sigma_alpha_1);
	
	G4MaterialPropertiesTable* crystalSiPM_SMPT = new G4MaterialPropertiesTable();
	crystalSiPM_SMPT->AddProperty("RINDEX",short_energy,grease_RIND,short_num);
	crystalSiPM_SMPT->AddProperty("REFLECTIVITY",short_energy,SiPM_reflect,short_num);
	crystalSiPM_SMPT->AddProperty("SPECULARLOBECONSTANT",short_energy,specularlobe,short_num);
	crystalSiPM_SMPT->AddProperty("SPECULARSPIKECONSTANT",short_energy,specularspike,short_num);
	crystalSiPM_SMPT->AddProperty("BACKSCATTERCONSTANT",short_energy,backscatter,short_num);
//	crystalSiPM_SMPT->AddProperty("EFFICIENCY",SiPM_Energy,SiPM_PDE,SiPM_num); // not used as have efficiency for epoxy-Si boundary
  crystalSiPMSurface->SetMaterialPropertiesTable(crystalSiPM_SMPT);

	new G4LogicalBorderSurface("crystalSiPMSurface",crystal_phys,epoxy_phys_0,crystalSiPMSurface);

// Epoxy to Si
	G4OpticalSurface* epoxySiSurface = new G4OpticalSurface("epoxySiSurface");
	epoxySiSurface->SetType(dielectric_metal);
	epoxySiSurface->SetFinish(polished);
	epoxySiSurface->SetModel(glisur);
	
	G4MaterialPropertiesTable* epoxySi_SMPT = new G4MaterialPropertiesTable();
	epoxySi_SMPT->AddProperty("REFLECTIVITY",short_energy,Si_reflect,short_num);
	epoxySi_SMPT->AddProperty("EFFICIENCY",SiPM_Energy,SiPM_PDE,SiPM_num);
	epoxySiSurface->SetMaterialPropertiesTable(epoxySi_SMPT);

	new G4LogicalBorderSurface("epoxySiSurface",epoxy_phys_0,Si_phys,epoxySiSurface);
	new G4LogicalBorderSurface("epoxySiSurface",epoxy_phys_1,Si_phys,epoxySiSurface);
	new G4LogicalBorderSurface("epoxySiSurface",epoxy_phys_2,Si_phys,epoxySiSurface);
	new G4LogicalBorderSurface("epoxySiSurface",epoxy_phys_3,Si_phys,epoxySiSurface);
	new G4LogicalBorderSurface("epoxySiSurface",epoxy_phys_4,Si_phys,epoxySiSurface);
	new G4LogicalBorderSurface("epoxySiSurface",epoxy_phys_5,Si_phys,epoxySiSurface);

// Epoxy to PTFE
  G4OpticalSurface* epoxyPTFESurface = new G4OpticalSurface("epoxyPTFESurface");
	epoxyPTFESurface->SetType(dielectric_dielectric);
  epoxyPTFESurface->SetModel(unified);
	epoxyPTFESurface->SetFinish(groundbackpainted);
	epoxyPTFESurface->SetSigmaAlpha(sigma_alpha_1);

  G4MaterialPropertiesTable* epoxyPTFE_SMPT = new G4MaterialPropertiesTable();
  epoxyPTFE_SMPT->AddProperty("REFLECTIVITY",short_energy,PTFE_reflect,short_num);
  epoxyPTFE_SMPT->AddProperty("SPECULARLOBECONSTANT",short_energy,specularlobe,short_num);
  epoxyPTFE_SMPT->AddProperty("SPECULARSPIKECONSTANT",short_energy,specularspike,short_num);
  epoxyPTFE_SMPT->AddProperty("BACKSCATTERCONSTANT",short_energy,backscatter,short_num);
// use refractive index to simulate a thin layer of air between crystal and wrapping
// This only has an effect if using "backpainted" surfaces!
	epoxyPTFE_SMPT->AddProperty("RINDEX",short_energy,air_RIND,short_num);

  epoxyPTFESurface->SetMaterialPropertiesTable(epoxyPTFE_SMPT);

  new G4LogicalBorderSurface("epoxyPTFESurface",epoxy_phys_0,PTFE_phys,epoxyPTFESurface);
  new G4LogicalBorderSurface("epoxyPTFESurface",epoxy_phys_1,PTFE_phys,epoxyPTFESurface);
  new G4LogicalBorderSurface("epoxyPTFESurface",epoxy_phys_2,PTFE_phys,epoxyPTFESurface);
  new G4LogicalBorderSurface("epoxyPTFESurface",epoxy_phys_3,PTFE_phys,epoxyPTFESurface);
  new G4LogicalBorderSurface("epoxyPTFESurface",epoxy_phys_4,PTFE_phys,epoxyPTFESurface);
  new G4LogicalBorderSurface("epoxyPTFESurface",epoxy_phys_5,PTFE_phys,epoxyPTFESurface);

//  G4cout << "crystalSiPMSurface G4MaterialPropertiesTable" << G4endl;
//  crystalSiPMSurface->DumpInfo();

// not using a refractive index here (as in Gostojic2016), presumably because coupling
// adhesive is matched to window index so that will be used by default by Geant
//	crystalSiPM_SMPT->AddProperty("RINDEX", crystal_Energy, YG_Rindex, YG_num);

////////////////////////

//always return the physical World
  return expHall_phys;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


void OpModelDetectorConstruction::ConstructSDandField(){

//**********  Define Sensitive Detector **************
//Create Instance for SiPM array
	G4String SDname = "/myDet/SiPM1";
	sipmSD* SiPM_SD = new sipmSD(SDname,"photonHitsCollection");
//Register to SD Manager
	SetSensitiveDetector("SiPM_log",SiPM_SD,true);

//Create Instance for crystal
 	SDname = "/myDet/crystal";
 	crystalSD* crystal_SD = new crystalSD(SDname,"gammaHitsCollection");
	SetSensitiveDetector("crystal_log",crystal_SD,true);

}
