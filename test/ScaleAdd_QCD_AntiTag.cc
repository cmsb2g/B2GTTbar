// ScaleAdd.cc
// Scale the QCD hists appropriately for each pT and Add them together
// [] .L ScaleAdd.cc+
// [] run()

#include "TROOT.h"
#include "TStyle.h"
#include "TLatex.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TH1.h"
#include "THStack.h"
#include "TH2.h"
#include "TF1.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include <TStyle.h>

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <cmath>

using namespace std;

const int nPt = 4;
TString pT_range[nPt] = {//"100to200", "200to300", "300to500", "500to700",
                         "700to1000", "1000to1500", "1500to2000", "2000toInf"};

const int nHist = 32;

void run(){

    vector<string> hists_names;
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapIn_inclusive"                  );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapIn_0btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapIn_1btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapIn_2btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive"                   );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_0btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_1btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapHi_2btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive"                   );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_0btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_1btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetPt_dRapLo_2btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_inclusive"         );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_0btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_1btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_2btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive"          );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive"          );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag"              );
    
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_inclusive"                  );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_0btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_1btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapIn_2btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_inclusive"                   );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_0btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_1btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapHi_2btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_inclusive"                   );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_0btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_1btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetP_dRapLo_2btag"                       );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive"         );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive"          );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive"          );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag"              );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag"              );

    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapIn_inclusive"                 );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapIn_0btag"                     );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapIn_1btag"                     );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapIn_2btag"                     );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapHi_inclusive"                  );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapHi_0btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapHi_1btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapHi_2btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapLo_inclusive"                  );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapLo_0btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapLo_1btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_Probe_jetRap_dRapLo_2btag"                      );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_inclusive"        );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_0btag"            );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_1btag"            );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_2btag"            );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_inclusive"         );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_0btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_1btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_2btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_inclusive"         );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_0btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_1btag"             );
    hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_2btag"             );

    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapIn_inclusive"                );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapIn_0btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapIn_1btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapIn_2btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive"                 );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapHi_0btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapHi_1btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapHi_2btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive"                 );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapLo_0btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapLo_1btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetPt_dRapLo_2btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_inclusive"       );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_0btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_1btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_2btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive"        );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive"        );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag"            );

    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapIn_inclusive"                );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapIn_0btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapIn_1btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapIn_2btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapHi_inclusive"                 );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapHi_0btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapHi_1btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapHi_2btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapLo_inclusive"                 );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapLo_0btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapLo_1btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetP_dRapLo_2btag"                     );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive"       );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive"        );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive"        );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag"            );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag"            );

    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapIn_inclusive"               );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapIn_0btag"                   );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapIn_1btag"                   );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapIn_2btag"                   );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapHi_inclusive"                );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapHi_0btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapHi_1btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapHi_2btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapLo_inclusive"                );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapLo_0btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapLo_1btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_Probe_jetRap_dRapLo_2btag"                    );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_inclusive"      );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_0btag"          );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_1btag"          );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_2btag"          );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_inclusive"       );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_0btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_1btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_2btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_inclusive"       );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_0btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_1btag"           );
    hists_names.push_back("h_AntiTagMinMass_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_2btag"           );

    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapIn_inclusive"                     );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapIn_0btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapIn_1btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapIn_2btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapHi_inclusive"                      );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapHi_0btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapHi_1btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapHi_2btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapLo_inclusive"                      );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapLo_0btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapLo_1btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetPt_dRapLo_2btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_inclusive"            );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_0btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_1btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapIn_2btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_inclusive"             );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_0btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_1btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapHi_2btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_inclusive"             );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_0btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_1btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetPt_dRapLo_2btag"                 );

    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapIn_inclusive"                     );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapIn_0btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapIn_1btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapIn_2btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapHi_inclusive"                      );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapHi_0btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapHi_1btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapHi_2btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapLo_inclusive"                      );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapLo_0btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapLo_1btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetP_dRapLo_2btag"                          );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_inclusive"            );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_0btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_1btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapIn_2btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_inclusive"             );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_0btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_1btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapHi_2btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_inclusive"             );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_0btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_1btag"                 );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetP_dRapLo_2btag"                 );

    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapIn_inclusive"                    );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapIn_0btag"                        );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapIn_1btag"                        );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapIn_2btag"                        );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapHi_inclusive"                     );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapHi_0btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapHi_1btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapHi_2btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapLo_inclusive"                     );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapLo_0btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapLo_1btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_Probe_jetRap_dRapLo_2btag"                         );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_inclusive"           );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_0btag"               );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_1btag"               );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapIn_2btag"               );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_inclusive"            );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_0btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_1btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapHi_2btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_inclusive"            );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_0btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_1btag"                );
    hists_names.push_back("h_NoAntiTag_ReqTopMassSD_TagMassSDTau32_jetRap_dRapLo_2btag"                );

    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapIn_inclusive"                     );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapIn_0btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapIn_1btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapIn_2btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapHi_inclusive"                      );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapHi_0btag"                          );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapHi_1btag"                          );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapHi_2btag"                          );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapLo_inclusive"                      );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapLo_0btag"                          );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapLo_1btag"                          );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetPt_dRapLo_2btag"                          );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapIn_inclusive"            );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapIn_0btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapIn_1btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapIn_2btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapHi_inclusive"             );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapHi_0btag"                 );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapHi_1btag"                 );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapHi_2btag"                 );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapLo_inclusive"             );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapLo_0btag"                 );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapLo_1btag"                 );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetPt_dRapLo_2btag"                 );
    
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapIn_inclusive"                    );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapIn_0btag"                        );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapIn_1btag"                        );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapIn_2btag"                        );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapHi_inclusive"                     );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapHi_0btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapHi_1btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapHi_2btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapLo_inclusive"                     );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapLo_0btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapLo_1btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetP_dRapLo_2btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapIn_inclusive"           );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapIn_0btag"               );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapIn_1btag"               );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapIn_2btag"               );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapHi_inclusive"            );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapHi_0btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapHi_1btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapHi_2btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapLo_inclusive"            );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapLo_0btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapLo_1btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetP_dRapLo_2btag"                );

    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapIn_inclusive"                    );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapIn_0btag"                        );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapIn_1btag"                        );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapIn_2btag"                        );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapHi_inclusive"                     );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapHi_0btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapHi_1btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapHi_2btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapLo_inclusive"                     );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapLo_0btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapLo_1btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_Probe_jetRap_dRapLo_2btag"                         );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapIn_inclusive"           );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapIn_0btag"               );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapIn_1btag"               );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapIn_2btag"               );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapHi_inclusive"            );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapHi_0btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapHi_1btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapHi_2btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapLo_inclusive"            );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapLo_0btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapLo_1btag"                );
    hists_names.push_back("h_AntiTagTau32_NoMassReq_TagMassSDTau32_jetRap_dRapLo_2btag"                );

    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapIn_inclusive"                     );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapIn_0btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapIn_1btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapIn_2btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapHi_inclusive"                      );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapHi_0btag"                          );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapHi_1btag"                          );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapHi_2btag"                          );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapLo_inclusive"                      );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapLo_0btag"                          );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapLo_1btag"                          );
    hists_names.push_back("h_TagOdd_Probe_jetPt_dRapLo_2btag"                          );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapIn_inclusive"            );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapIn_0btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapIn_1btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapIn_2btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapHi_inclusive"             );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapHi_0btag"                 );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapHi_1btag"                 );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapHi_2btag"                 );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapLo_inclusive"             );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapLo_0btag"                 );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapLo_1btag"                 );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetPt_dRapLo_2btag"                 );

    hists_names.push_back("h_TagOdd_Probe_jetP_dRapIn_inclusive"                    );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapIn_0btag"                        );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapIn_1btag"                        );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapIn_2btag"                        );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapHi_inclusive"                     );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapHi_0btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapHi_1btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapHi_2btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapLo_inclusive"                     );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapLo_0btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapLo_1btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetP_dRapLo_2btag"                         );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapIn_inclusive"           );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapIn_0btag"               );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapIn_1btag"               );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapIn_2btag"               );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapHi_inclusive"            );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapHi_0btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapHi_1btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapHi_2btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapLo_inclusive"            );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapLo_0btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapLo_1btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetP_dRapLo_2btag"                );
    
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapIn_inclusive"                    );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapIn_0btag"                        );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapIn_1btag"                        );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapIn_2btag"                        );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapHi_inclusive"                     );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapHi_0btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapHi_1btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapHi_2btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapLo_inclusive"                     );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapLo_0btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapLo_1btag"                         );
    hists_names.push_back("h_TagOdd_Probe_jetRap_dRapLo_2btag"                         );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapIn_inclusive"           );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapIn_0btag"               );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapIn_1btag"               );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapIn_2btag"               );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapHi_inclusive"            );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapHi_0btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapHi_1btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapHi_2btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapLo_inclusive"            );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapLo_0btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapLo_1btag"                );
    hists_names.push_back("h_TagOdd_TagMassSDTau32_jetRap_dRapLo_2btag"                );
    
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapIn_inclusive"                     );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapIn_0btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapIn_1btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapIn_2btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapHi_inclusive"                      );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapHi_0btag"                          );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapHi_1btag"                          );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapHi_2btag"                          );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapLo_inclusive"                      );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapLo_0btag"                          );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapLo_1btag"                          );
    hists_names.push_back("h_TagEven_Probe_jetPt_dRapLo_2btag"                          );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapIn_inclusive"            );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapIn_0btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapIn_1btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapIn_2btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapHi_inclusive"             );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapHi_0btag"                 );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapHi_1btag"                 );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapHi_2btag"                 );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapLo_inclusive"             );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapLo_0btag"                 );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapLo_1btag"                 );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetPt_dRapLo_2btag"                 );

    hists_names.push_back("h_TagEven_Probe_jetP_dRapIn_inclusive"                    );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapIn_0btag"                        );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapIn_1btag"                        );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapIn_2btag"                        );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapHi_inclusive"                     );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapHi_0btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapHi_1btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapHi_2btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapLo_inclusive"                     );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapLo_0btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapLo_1btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetP_dRapLo_2btag"                         );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapIn_inclusive"           );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapIn_0btag"               );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapIn_1btag"               );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapIn_2btag"               );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapHi_inclusive"            );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapHi_0btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapHi_1btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapHi_2btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapLo_inclusive"            );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapLo_0btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapLo_1btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetP_dRapLo_2btag"                );

    hists_names.push_back("h_TagEven_Probe_jetRap_dRapIn_inclusive"                    );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapIn_0btag"                        );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapIn_1btag"                        );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapIn_2btag"                        );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapHi_inclusive"                     );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapHi_0btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapHi_1btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapHi_2btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapLo_inclusive"                     );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapLo_0btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapLo_1btag"                         );
    hists_names.push_back("h_TagEven_Probe_jetRap_dRapLo_2btag"                         );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapIn_inclusive"           );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapIn_0btag"               );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapIn_1btag"               );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapIn_2btag"               );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapHi_inclusive"            );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapHi_0btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapHi_1btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapHi_2btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapLo_inclusive"            );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapLo_0btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapLo_1btag"                );
    hists_names.push_back("h_TagEven_TagMassSDTau32_jetRap_dRapLo_2btag"                );




    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapIn_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapIn_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapIn_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapIn_2btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapHi_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapHi_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapHi_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapHi_2btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapLo_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapLo_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapLo_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetPt_dRapLo_2btag"                     );    
    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapIn_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapIn_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapIn_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapIn_2btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapHi_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapHi_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapHi_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapHi_2btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapLo_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapLo_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapLo_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetP_dRapLo_2btag"                     );    
    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapIn_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapIn_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapIn_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapIn_2btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapHi_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapHi_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapHi_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapHi_2btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapLo_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapLo_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapLo_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagMassSD_jetRap_dRapLo_2btag"                     );    
    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapIn_inclusive"                 ); 
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapIn_0btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapIn_1btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapIn_2btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapHi_inclusive"                 ); 
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapHi_0btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapHi_1btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapHi_2btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapLo_inclusive"                 ); 
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapLo_0btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapLo_1btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetPt_dRapLo_2btag"                     );     
    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapIn_inclusive"                 ); 
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapIn_0btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapIn_1btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapIn_2btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapHi_inclusive"                 ); 
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapHi_0btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapHi_1btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapHi_2btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapLo_inclusive"                 ); 
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapLo_0btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapLo_1btag"                     );     
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetP_dRapLo_2btag"                     );     
    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapIn_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapIn_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapIn_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapIn_2btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapHi_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapHi_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapHi_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapHi_2btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapLo_inclusive"                 );
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapLo_0btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapLo_1btag"                     );    
    // hists_names.push_back("h_AntiTagTau32_ReqTopMassSD_TagTau32_jetRap_dRapLo_2btag"                     );    

    

    

    

    int nHist= hists_names.size();
    cout<<"nHist "<<nHist<<endl;




    TFile * OutFile = new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outAntiTag_QCD_HT700toInf_B2Gv8p4_reader603e_notrig_20160706_nom_scaled.root" , "RECREATE");

    const double lumi = 2530 ; // pb-1
    double mcscales[nPt] = {
        //xs / nevents * lumi
        //27850000. / 81637494. * lumi,
        //1717000. / 18713060. * lumi,
        //351300. / 19826197. * lumi,
        //31630. / 19664159. * lumi,
        6802. / 15356448. * lumi,
        1206 / 4884057. * lumi,
        120.4 / 3863167. * lumi,
        25.25 / 1912529. * lumi
    };

    // Get the 10 QCD files
    TFile* fQCD[nPt];
    TH1D* Check;
    for (int iPt=0; iPt<nPt; iPt++) {
            cout<<"outAntiTag_QCD_HT"+pT_range[iPt]+"_B2Gv8p4_reader603e_20160706.root"<<endl;
            fQCD[iPt]=new TFile("/uscms/home/camclean/nobackup/CMSSW_7_4_1/src/B2GTTbar/test/runs/run20160706/outAntiTag_QCD_HT"+pT_range[iPt]+"_B2Gv8p4_reader603e_20160706.root","READ");
            }

    for (int iPt=0; iPt<nPt; iPt++) {
      cout<<"iPT = "<<iPt<<endl;
        for (int iHist = 0; iHist<nHist; iHist++){
            cout<<" "<<hists_names[iHist]<<endl;
            Check = (TH1D*) fQCD[iPt]->Get(hists_names[iHist].c_str())->Clone();
            cout<<" "<<hists_names[iHist]<<" : after reading the file ="<< Check->GetSum()<<endl;   
        }     
    }
    // Check = (TH1D*) fQCD[3]->Get(hists_names[71])->Clone();
    // cout<<"DEBUG: after reading the file ="<< Check->GetSum()<<endl;

    // Get the relevant histograms
    //vector<TH1D*> h_100to200; vector<TH1D*> h_200to300; vector<TH1D*> h_300to500; vector<TH1D*> h_500to700; 
    vector<TH1D*> h_700to1000; vector<TH1D*> h_1000to1500; vector<TH1D*> h_1500to2000; vector<TH1D*> h_2000toInf; 
    for (unsigned int iHist=0; iHist<hists_names.size(); iHist++) {
      cout<<"debug1"<<endl;
        // h_100to200.push_back( (TH1D*) fQCD[0]->Get(hists_names[iHist])->Clone() );
        // h_100to200[iHist] -> Sumw2();
        // h_200to300.push_back( (TH1D*) fQCD[1]->Get(hists_names[iHist])->Clone() );
        // h_200to300[iHist] -> Sumw2();
        // h_300to500.push_back( (TH1D*) fQCD[2]->Get(hists_names[iHist])->Clone() );
        // h_300to500[iHist] -> Sumw2();
        // h_500to700.push_back( (TH1D*) fQCD[3]->Get(hists_names[iHist])->Clone() );
        // h_500to700[iHist] -> Sumw2();
        h_700to1000.push_back( (TH1D*) fQCD[0]->Get(hists_names[iHist].c_str())->Clone() );
        h_700to1000[iHist] -> Sumw2();
        h_1000to1500.push_back( (TH1D*) fQCD[1]->Get(hists_names[iHist].c_str())->Clone() );
        h_1000to1500[iHist] -> Sumw2();
        h_1500to2000.push_back( (TH1D*) fQCD[2]->Get(hists_names[iHist].c_str())->Clone() );
        h_1500to2000[iHist] -> Sumw2();
        h_2000toInf.push_back( (TH1D*) fQCD[3]->Get(hists_names[iHist].c_str())->Clone() );
        h_2000toInf[iHist] -> Sumw2();
    }
    

    // Scale the relevant hists
    for (int iHist=0; iHist<nHist; iHist++) {
      cout<<"debug2"<<endl;
        // h_100to200[iHist]->Scale(mcscales[0]);
        // h_200to300[iHist]->Scale(mcscales[1]);
        // h_300to500[iHist]->Scale(mcscales[2]);
        // h_500to700[iHist]->Scale(mcscales[3]);
        h_700to1000[iHist]->Scale(mcscales[0]);
        h_1000to1500[iHist]->Scale(mcscales[1]);
        h_1500to2000[iHist]->Scale(mcscales[2]);
        h_2000toInf[iHist]->Scale(mcscales[3]);
    }


    // Add all tag hists and all probe hists
    vector<TH1D*> h_100toInf;
    for (int iHist=0; iHist<nHist; iHist++) {
        //h_100toInf.push_back( (TH1D*)h_100to200[iHist]->Clone());
      h_100toInf.push_back( (TH1D*)h_700to1000[iHist]->Clone());
    }
    
    for (int iHist=0; iHist<nHist; iHist++) {
        // h_100toInf[iHist] ->Add( (TH1D*)h_200to300[iHist], 1);
        // h_100toInf[iHist] ->Add( (TH1D*)h_300to500[iHist], 1);
        // h_100toInf[iHist] ->Add( (TH1D*)h_500to700[iHist], 1);
        //h_100toInf[iHist] ->Add( (TH1D*)h_700to1000[iHist], 1);
        h_100toInf[iHist] ->Add( (TH1D*)h_1000to1500[iHist], 1);
        h_100toInf[iHist] ->Add( (TH1D*)h_1500to2000[iHist], 1);
        h_100toInf[iHist] ->Add( (TH1D*)h_2000toInf[iHist], 1);
    }
    

    // //-------------------------------------------------------------

    // // Get the 10 QCD files
    //     TH2D* Check_2D;

    // for (int iPt=0; iPt<nPt; iPt++) {
    //   cout<<"iPT = "<<iPt<<endl;
    //     for (int iHist = 0; iHist<hists_names_2D.size(); iHist++){
    //         Check_2D = (TH2D*) fQCD[iPt]->Get(hists_names_2D[iHist].c_str())->Clone();
    //         cout<<" "<<hists_names[iHist]<<" : after reading the file ="<< Check_2D->GetSum()<<endl;   
    //     }     
    // }
    // vector<TH2D*> h_700to1000_2D; vector<TH2D*> h_1000to1500_2D; vector<TH2D*> h_1500to2000_2D; vector<TH2D*> h_2000toInf_2D; 
    // for (unsigned int iHist=0; iHist<hists_names_2D.size(); iHist++) {
    //     h_700to1000_2D.push_back( (TH2D*) fQCD[0]->Get(hists_names_2D[iHist].c_str())->Clone() );
    //     h_700to1000_2D[iHist] -> Sumw2();
    //     h_1000to1500_2D.push_back( (TH2D*) fQCD[1]->Get(hists_names_2D[iHist].c_str())->Clone() );
    //     h_1000to1500_2D[iHist] -> Sumw2();
    //     h_1500to2000_2D.push_back( (TH2D*) fQCD[2]->Get(hists_names_2D[iHist].c_str())->Clone() );
    //     h_1500to2000_2D[iHist] -> Sumw2();
    //     h_2000toInf_2D.push_back( (TH2D*) fQCD[3]->Get(hists_names_2D[iHist].c_str())->Clone() );
    //     h_2000toInf_2D[iHist] -> Sumw2();
    // }
    

    // // Scale the relevant hists
    // for (int iHist=0; iHist<hists_names_2D.size(); iHist++) {
    //     h_700to1000_2D[iHist]->Scale(mcscales[0]);
    //     h_1000to1500_2D[iHist]->Scale(mcscales[1]);
    //     h_1500to2000_2D[iHist]->Scale(mcscales[2]);
    //     h_2000toInf_2D[iHist]->Scale(mcscales[3]);
    // }


    // // Add all tag hists and all probe hists
    // vector<TH2D*> h_100toInf_2D;
    // for (int iHist=0; iHist<nHist; iHist++) {
    //   h_100toInf_2D.push_back( (TH2D*)h_700to1000_2D[iHist]->Clone());
    // }
    
    // for (int iHist=0; iHist<nHist; iHist++) {
    //     h_100toInf_2D[iHist] ->Add( (TH2D*)h_1000to1500_2D[iHist], 1);
    //     h_100toInf_2D[iHist] ->Add( (TH2D*)h_1500to2000_2D[iHist], 1);
    //     h_100toInf_2D[iHist] ->Add( (TH2D*)h_2000toInf_2D[iHist], 1);
    // }
    
    //-------------------------------------------------------------



    // Write the final tag and probe hists in a root file
    OutFile->cd();
    for (int iHist=0; iHist<nHist; iHist++) {
        h_100toInf[iHist]->SetName(hists_names[iHist].c_str());
        h_100toInf[iHist]->Write();
    }
    // for (int iHist=0; iHist<hists_names_2D.size(); iHist++) {
    //     h_100toInf_2D[iHist]->SetName(hists_names_2D[iHist].c_str());
    //     h_100toInf_2D[iHist]->Write();
    // }
        
    OutFile->Close();
}







