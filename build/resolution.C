{
	TCanvas* resolution_c=new TCanvas("resolution_c","resolution_c");
	resolution_c->Divide(2,2);
	
	resolution_c->cd(1);
	xGam_vs_dNdx_0_h->Draw("");
	TF1* lin1=new TF1("lin1","pol1",-5,5);
	lin1->FixParameter(0,0);
	xGam_vs_dNdx_0_h->Fit("lin1","R");
	double m1=lin1->GetParameter(1);
	
	resolution_c->cd(2);
	xGam_vs_dNdx_0_h->ProjectionX("dNdx_0_px",50,51);
//	xGam_vs_dNdx_0_h->ProjectionX("dNdx_0_px",70,71);
	TF1* myGaus1=new TF1("myGaus1","gaus",-5,5);
	dNdx_0_px->Fit("myGaus1","","",-1.5,1.5);
//	dNdx_0_px->Fit("myGaus1","","",0,10);
	double width1=2.355*myGaus1->GetParameter(2);
	
	double res1=width1*m1;
	
	resolution_c->cd(3);
	xGam_vs_x8_fit_max_h->Draw("");
	TF1* lin2=new TF1("lin2","pol1",-5,5);
	lin2->FixParameter(0,0);
	xGam_vs_x8_fit_max_h->Fit("lin2","R");
	double m2=lin2->GetParameter(1);
	
	resolution_c->cd(4);
	xGam_vs_x8_fit_max_h->ProjectionX("fit_max_px",50,51);
//	xGam_vs_x8_fit_max_h->ProjectionX("fit_max_px",70,71);
	TF1* myGaus2=new TF1("myGaus2","gaus",-5,5);
	fit_max_px->Fit("myGaus2","","",-1.5,1.5);
//	fit_max_px->Fit("myGaus2","","",0,10);
	double width2=2.355*myGaus2->GetParameter(2);
	
	double res2=width2*m2;

	cout << endl << "Position resolution from dN/dx=0 method = " << res1 << " mm" << endl ;
	cout << "Position resolution from fit max. method = " << res2 << " mm" << endl << endl ;
}
