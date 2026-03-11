#include "TFile.h"
#include "TH1F.h"

#include "RooStats/SPlot.h"
#include "RooAbsData.h"
#include "RooAbsPdf.h"
#include "RooRealVar.h"
#include "RooArgList.h"
# include "RooDataSet.h"

void doSPlot(RooDataSet& data,RooAbsPdf& model, RooRealVar& N_s1, RooRealVar& N2, RooRalVar& N_bkg )
{
    RooArgList yields(*N_s1, *N2, *N_bkg)
    RooStats::SPlot splot("sData","sData", *data, model,yields);

    // // Open ROOT file
    // TFile* outFile = TFile::Open("fit_resultsB_plus_sweights.root", "RECREATE");
    // if (!outFile || outFile->IsZombie()) {
    //     std::cerr << "Error: file not found or invalid: " << "fit_resultsB_plus_sweights.root" << std::endl;
    //     return;
    // }

    // // Retrieve objects
    // RooDataSet* data = dynamic_cast<RooDataSet*>(outFile->Get("data"));
    // RooAbsPdf*  model = dynamic_cast<RooAbsPdf*>(outFile->Get("model"));
    // RooRealVar* N_s1 = dynamic_cast<RooRealVar*>(outFile->Get("N_s1"));
    // RooRealVar* N2   = dynamic_cast<RooRealVar*>(outFile->Get("N2"));
    // RooRealVar* N_bkg= dynamic_cast<RooRealVar*>(outFile->Get("N_bkg"));

    // if (!data || !model || !N_s1 || !N2 || !N_bkg) {
    //     std::cerr << "Error: one or more objects missing in file!" << std::endl;
    //     outFile->Close();
    //     return;
    // }

    // // Create RooArgList of yields
    // RooArgList yields(*N_s1, *N2, *N_bkg);

    // // Compute sWeights
    // RooStats::SPlot sData("sData","sData", *data, model, yields);

    // // Create histogram
    // TH1F* hist_signal = new TH1F(hist_name, "Signal-weighted", nbins, xlow, xhigh);

    // RooRealVar* var = dynamic_cast<RooRealVar*>(data->get()->find(varname));
    // if (!var) {
    //     std::cerr << "Error: variable " << varname << " not found in dataset!" << std::endl;
    //     file->Close();
    //     return;
    // }

    // // Fill histogram with signal sWeight
    // for (int i = 0; i < data->numEntries(); ++i) {
    //     const RooArgSet* row = data->get(i);
    //     double weight = row->getRealValue("N_s1_sw");
    //     double value  = row->getRealValue(varname);
    //     hist_signal->Fill(value, weight);
    // }

    // // Write histogram back to file
    // hist_signal->Write("", TObject::kOverwrite);
    // file->Close();
    // std::cout << "SPlot histogram written to " << filename << std::endl;
}