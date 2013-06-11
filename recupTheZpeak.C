

TString outputDir = "fitPlots"; 		//directory that will contain the fit plots
TString thePlotToDraw[1] = {"Tight2012"}; 	// name of the ID in the TnP trees 
TString theName[1] = {"Tight_POG_ID"}; 		// name of the ID that will appear on the plot ...
nbOfIds = 1;					//number of IDs
TString thePath = "/afs/cern.ch/user/h/hbrun/public/testTnPoutput/";// the directory where to find the TnP output 
TString kind;
recupTheZpeak(){
//	TDirectory *theDr = (TDirectory*) myFile->Get("eleIDdir");///denom_pt/fit_eff_plots");
	//theDr->ls();
	int myIndex;	
	
	TSystemDirectory dir(thePath, thePath);
	TSystemFile *file;
	TString fname;
	TIter next(dir.GetListOfFiles());
	while ((file=(TSystemFile*)next())) {
		fname = file->GetName();
		if (fname.BeginsWith("TnP")) {
			if (fname.Contains("data")) kind = "data";
			else kind = "mc";
			bool pass = false;
			for (int p = 0 ; p< nbOfIds ; p++){
				if (fname.Contains(thePlotToDraw[p])) {
					pass = true;				 
					theIndex = p;
					break;
				}
			}
			if (!(pass)) continue;
			TFile *myFile = new TFile(fname);
			TIter nextkey(myFile->GetListOfKeys());
			TKey *key;
			while (key = (TKey*)nextkey()) {
				TString theTypeClasse = key->GetClassName();
				TString theNomClasse = key->GetTitle();
				if ( theTypeClasse == "TDirectoryFile"){
					TDirectory *theDr = (TDirectory*) myFile->Get(theNomClasse);
					TIter nextkey2(theDr->GetListOfKeys());
					TKey *key2;
					while (key2 = (TKey*)nextkey2()) {
						TString theTypeClasse2 = key2->GetClassName();
						TString theNomClasse2 = key2->GetTitle();	
						if ( theTypeClasse == "TDirectoryFile"){
							TDirectory *theDr2 = (TDirectory*) myFile->Get(theNomClasse+"/"+theNomClasse2);
							TIter nextkey3(theDr2->GetListOfKeys());
							TKey *key3;
							while (key3 = (TKey*)nextkey3()) {
								TString theTypeClasse3 = key3->GetClassName();
								TString theNomClasse3 = key3->GetTitle();	
								if (((theNomClasse3.Contains("FromMC"))||(theNomClasse3.Contains("higgsSF")))&&(!(theNomClasse3.Contains("all")))) {
									TCanvas *theCanvas = (TCanvas*) myFile->Get(theNomClasse+"/"+theNomClasse2+"/"+theNomClasse3+"/fit_canvas");
									theCanvas->Print(outputDir+"/"+kind+"_"+theName[theIndex]+"__"+theNomClasse3+".png");
									
								}
							}
						}

					}
			
				}
			}
			delete myFile;
		}
	
	}

}
