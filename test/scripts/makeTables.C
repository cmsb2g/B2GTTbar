{

TFile *f = new TFile("../templates_RSGluon.root", "READ");

f->cd();

double data[6][2];
double ttbar[6][2];
double qcd[6][2];

double ZpW[6][4][2];
double ZpN[6][4][2];
double RSG[6][4][2];

double ttbar_JES[6][2];
double ttbar_btag[6][2];
double ttbar_Q2[6][2];
double ttbar_PDF[6][2];
double ttbar_toppt[6][2];
double qcd_modMass[6][2];
double qcd_closure[6][2];

double ZpW_JES[6][4][2];
double ZpN_JES[6][4][2];
double RSG_JES[6][4][2];
double ZpW_btag[6][4][2];
double ZpN_btag[6][4][2];
double RSG_btag[6][4][2];
double ZpW_PDF[6][4][2];
double ZpN_PDF[6][4][2];
double RSG_PDF[6][4][2];
double ZpW_JER[6][4][2];
double ZpN_JER[6][4][2];
double RSG_JER[6][4][2];


qcd_modMass[0][0] = ( btag0__qcd__modMass__plus->Integral() - btag0__qcd->Integral() ) / btag0__qcd->Integral();
qcd_modMass[1][0] = ( btag1__qcd__modMass__plus->Integral() - btag1__qcd->Integral() ) / btag1__qcd->Integral();
qcd_modMass[2][0] = ( btag2__qcd__modMass__plus->Integral() - btag2__qcd->Integral() ) / btag2__qcd->Integral();
qcd_modMass[3][0] = ( btag3__qcd__modMass__plus->Integral() - btag3__qcd->Integral() ) / btag3__qcd->Integral();
qcd_modMass[4][0] = ( btag4__qcd__modMass__plus->Integral() - btag4__qcd->Integral() ) / btag4__qcd->Integral();
qcd_modMass[5][0] = ( btag5__qcd__modMass__plus->Integral() - btag5__qcd->Integral() ) / btag5__qcd->Integral();
qcd_modMass[0][1] = ( btag0__qcd__modMass__minus->Integral() - btag0__qcd->Integral() ) / btag0__qcd->Integral();
qcd_modMass[1][1] = ( btag1__qcd__modMass__minus->Integral() - btag1__qcd->Integral() ) / btag1__qcd->Integral();
qcd_modMass[2][1] = ( btag2__qcd__modMass__minus->Integral() - btag2__qcd->Integral() ) / btag2__qcd->Integral();
qcd_modMass[3][1] = ( btag3__qcd__modMass__minus->Integral() - btag3__qcd->Integral() ) / btag3__qcd->Integral();
qcd_modMass[4][1] = ( btag4__qcd__modMass__minus->Integral() - btag4__qcd->Integral() ) / btag4__qcd->Integral();
qcd_modMass[5][1] = ( btag5__qcd__modMass__minus->Integral() - btag5__qcd->Integral() ) / btag5__qcd->Integral();

qcd_closure[0][0] = ( btag0__qcd__closure__plus->Integral() - btag0__qcd->Integral() ) / btag0__qcd->Integral();
qcd_closure[1][0] = ( btag1__qcd__closure__plus->Integral() - btag1__qcd->Integral() ) / btag1__qcd->Integral();
qcd_closure[2][0] = ( btag2__qcd__closure__plus->Integral() - btag2__qcd->Integral() ) / btag2__qcd->Integral();
qcd_closure[3][0] = ( btag3__qcd__closure__plus->Integral() - btag3__qcd->Integral() ) / btag3__qcd->Integral();
qcd_closure[4][0] = ( btag4__qcd__closure__plus->Integral() - btag4__qcd->Integral() ) / btag4__qcd->Integral();
qcd_closure[5][0] = ( btag5__qcd__closure__plus->Integral() - btag5__qcd->Integral() ) / btag5__qcd->Integral();
qcd_closure[0][1] = ( btag0__qcd__closure__minus->Integral() - btag0__qcd->Integral() ) / btag0__qcd->Integral();
qcd_closure[1][1] = ( btag1__qcd__closure__minus->Integral() - btag1__qcd->Integral() ) / btag1__qcd->Integral();
qcd_closure[2][1] = ( btag2__qcd__closure__minus->Integral() - btag2__qcd->Integral() ) / btag2__qcd->Integral();
qcd_closure[3][1] = ( btag3__qcd__closure__minus->Integral() - btag3__qcd->Integral() ) / btag3__qcd->Integral();
qcd_closure[4][1] = ( btag4__qcd__closure__minus->Integral() - btag4__qcd->Integral() ) / btag4__qcd->Integral();
qcd_closure[5][1] = ( btag5__qcd__closure__minus->Integral() - btag5__qcd->Integral() ) / btag5__qcd->Integral();


ttbar[0][0] = btag0__ttbar->Integral();
ttbar[1][0] = btag1__ttbar->Integral();
ttbar[2][0] = btag2__ttbar->Integral();
ttbar[3][0] = btag3__ttbar->Integral();
ttbar[4][0] = btag4__ttbar->Integral();
ttbar[5][0] = btag5__ttbar->Integral();
ttbar[0][1] = sqrt(btag0__ttbar->GetEntries()) / btag0__ttbar->GetEntries();
ttbar[1][1] = sqrt(btag1__ttbar->GetEntries()) / btag1__ttbar->GetEntries();
ttbar[2][1] = sqrt(btag2__ttbar->GetEntries()) / btag2__ttbar->GetEntries();
ttbar[3][1] = sqrt(btag3__ttbar->GetEntries()) / btag3__ttbar->GetEntries();
ttbar[4][1] = sqrt(btag4__ttbar->GetEntries()) / btag4__ttbar->GetEntries();
ttbar[5][1] = sqrt(btag5__ttbar->GetEntries()) / btag5__ttbar->GetEntries();



ttbar_JES[0][0] = (btag0__ttbar__jec__plus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
ttbar_JES[1][0] = (btag1__ttbar__jec__plus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
ttbar_JES[2][0] = (btag2__ttbar__jec__plus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
ttbar_JES[3][0] = (btag3__ttbar__jec__plus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
ttbar_JES[4][0] = (btag4__ttbar__jec__plus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
ttbar_JES[5][0] = (btag5__ttbar__jec__plus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();
ttbar_JES[0][1] = (btag0__ttbar__jec__minus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
ttbar_JES[1][1] = (btag1__ttbar__jec__minus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
ttbar_JES[2][1] = (btag2__ttbar__jec__minus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
ttbar_JES[3][1] = (btag3__ttbar__jec__minus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
ttbar_JES[4][1] = (btag4__ttbar__jec__minus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
ttbar_JES[5][1] = (btag5__ttbar__jec__minus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();



ttbar_PDF[0][0] = (btag0__ttbar__pdf__plus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
ttbar_PDF[1][0] = (btag1__ttbar__pdf__plus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
ttbar_PDF[2][0] = (btag2__ttbar__pdf__plus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
ttbar_PDF[3][0] = (btag3__ttbar__pdf__plus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
ttbar_PDF[4][0] = (btag4__ttbar__pdf__plus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
ttbar_PDF[5][0] = (btag5__ttbar__pdf__plus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();
ttbar_PDF[0][1] = (btag0__ttbar__pdf__minus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
ttbar_PDF[1][1] = (btag1__ttbar__pdf__minus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
ttbar_PDF[2][1] = (btag2__ttbar__pdf__minus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
ttbar_PDF[3][1] = (btag3__ttbar__pdf__minus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
ttbar_PDF[4][1] = (btag4__ttbar__pdf__minus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
ttbar_PDF[5][1] = (btag5__ttbar__pdf__minus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();



//ttbar_toppt[0][0] = (btag0__ttbar__toppt__plus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
//ttbar_toppt[1][0] = (btag1__ttbar__toppt__plus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
//ttbar_toppt[2][0] = (btag2__ttbar__toppt__plus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
//ttbar_toppt[3][0] = (btag3__ttbar__toppt__plus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
//ttbar_toppt[4][0] = (btag4__ttbar__toppt__plus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
//ttbar_toppt[5][0] = (btag5__ttbar__toppt__plus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();
//ttbar_toppt[0][1] = (btag0__ttbar__toppt__minus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
//ttbar_toppt[1][1] = (btag1__ttbar__toppt__minus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
//ttbar_toppt[2][1] = (btag2__ttbar__toppt__minus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
//ttbar_toppt[3][1] = (btag3__ttbar__toppt__minus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
//ttbar_toppt[4][1] = (btag4__ttbar__toppt__minus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
//ttbar_toppt[5][1] = (btag5__ttbar__toppt__minus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();



ttbar_Q2[0][0] = (btag0__ttbar__q2__plus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
ttbar_Q2[1][0] = (btag1__ttbar__q2__plus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
ttbar_Q2[2][0] = (btag2__ttbar__q2__plus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
ttbar_Q2[3][0] = (btag3__ttbar__q2__plus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
ttbar_Q2[4][0] = (btag4__ttbar__q2__plus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
ttbar_Q2[5][0] = (btag5__ttbar__q2__plus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();
ttbar_Q2[0][1] = (btag0__ttbar__q2__minus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
ttbar_Q2[1][1] = (btag1__ttbar__q2__minus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
ttbar_Q2[2][1] = (btag2__ttbar__q2__minus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
ttbar_Q2[3][1] = (btag3__ttbar__q2__minus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
ttbar_Q2[4][1] = (btag4__ttbar__q2__minus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
ttbar_Q2[5][1] = (btag5__ttbar__q2__minus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();


qcd[0][0] = btag0__qcd->Integral();
qcd[1][0] = btag1__qcd->Integral();
qcd[2][0] = btag2__qcd->Integral();
qcd[3][0] = btag3__qcd->Integral();
qcd[4][0] = btag4__qcd->Integral();
qcd[5][0] = btag5__qcd->Integral();
qcd[0][1] = sqrt(btag0__qcd->GetEntries()) / btag0__qcd->GetEntries();
qcd[1][1] = sqrt(btag1__qcd->GetEntries()) / btag1__qcd->GetEntries();
qcd[2][1] = sqrt(btag2__qcd->GetEntries()) / btag2__qcd->GetEntries();
qcd[3][1] = sqrt(btag3__qcd->GetEntries()) / btag3__qcd->GetEntries();
qcd[4][1] = sqrt(btag4__qcd->GetEntries()) / btag4__qcd->GetEntries();
qcd[5][1] = sqrt(btag5__qcd->GetEntries()) / btag5__qcd->GetEntries();



ZpN[0][0][0] = btag0__Zprime1000->Integral();
ZpN[1][0][0] = btag1__Zprime1000->Integral();
ZpN[2][0][0] = btag2__Zprime1000->Integral();
ZpN[3][0][0] = btag3__Zprime1000->Integral();
ZpN[4][0][0] = btag4__Zprime1000->Integral();
ZpN[5][0][0] = btag5__Zprime1000->Integral();
ZpN[0][0][1] = sqrt(btag0__Zprime1000->GetEntries()) / btag0__Zprime1000->GetEntries();
ZpN[1][0][1] = sqrt(btag1__Zprime1000->GetEntries()) / btag1__Zprime1000->GetEntries();
ZpN[2][0][1] = sqrt(btag2__Zprime1000->GetEntries()) / btag2__Zprime1000->GetEntries();
ZpN[3][0][1] = sqrt(btag3__Zprime1000->GetEntries()) / btag3__Zprime1000->GetEntries();
ZpN[4][0][1] = sqrt(btag4__Zprime1000->GetEntries()) / btag4__Zprime1000->GetEntries();
ZpN[5][0][1] = sqrt(btag5__Zprime1000->GetEntries()) / btag5__Zprime1000->GetEntries();

ZpN[0][1][0] = btag0__Zprime1500->Integral();
ZpN[1][1][0] = btag1__Zprime1500->Integral();
ZpN[2][1][0] = btag2__Zprime1500->Integral();
ZpN[3][1][0] = btag3__Zprime1500->Integral();
ZpN[4][1][0] = btag4__Zprime1500->Integral();
ZpN[5][1][0] = btag5__Zprime1500->Integral();
ZpN[0][1][1] = sqrt(btag0__Zprime1500->GetEntries()) / btag0__Zprime1500->GetEntries();
ZpN[1][1][1] = sqrt(btag1__Zprime1500->GetEntries()) / btag1__Zprime1500->GetEntries();
ZpN[2][1][1] = sqrt(btag2__Zprime1500->GetEntries()) / btag2__Zprime1500->GetEntries();
ZpN[3][1][1] = sqrt(btag3__Zprime1500->GetEntries()) / btag3__Zprime1500->GetEntries();
ZpN[4][1][1] = sqrt(btag4__Zprime1500->GetEntries()) / btag4__Zprime1500->GetEntries();
ZpN[5][1][1] = sqrt(btag5__Zprime1500->GetEntries()) / btag5__Zprime1500->GetEntries();

ZpN[0][2][0] = btag0__Zprime2000->Integral();
ZpN[1][2][0] = btag1__Zprime2000->Integral();
ZpN[2][2][0] = btag2__Zprime2000->Integral();
ZpN[3][2][0] = btag3__Zprime2000->Integral();
ZpN[4][2][0] = btag4__Zprime2000->Integral();
ZpN[5][2][0] = btag5__Zprime2000->Integral();
ZpN[0][2][1] = sqrt(btag0__Zprime2000->GetEntries()) / btag0__Zprime2000->GetEntries();
ZpN[1][2][1] = sqrt(btag1__Zprime2000->GetEntries()) / btag1__Zprime2000->GetEntries();
ZpN[2][2][1] = sqrt(btag2__Zprime2000->GetEntries()) / btag2__Zprime2000->GetEntries();
ZpN[3][2][1] = sqrt(btag3__Zprime2000->GetEntries()) / btag3__Zprime2000->GetEntries();
ZpN[4][2][1] = sqrt(btag4__Zprime2000->GetEntries()) / btag4__Zprime2000->GetEntries();
ZpN[5][2][1] = sqrt(btag5__Zprime2000->GetEntries()) / btag5__Zprime2000->GetEntries();

ZpN[0][3][0] = btag0__Zprime3000->Integral();
ZpN[1][3][0] = btag1__Zprime3000->Integral();
ZpN[2][3][0] = btag2__Zprime3000->Integral();
ZpN[3][3][0] = btag3__Zprime3000->Integral();
ZpN[4][3][0] = btag4__Zprime3000->Integral();
ZpN[5][3][0] = btag5__Zprime3000->Integral();
ZpN[0][3][1] = sqrt(btag0__Zprime3000->GetEntries()) / btag0__Zprime3000->GetEntries();
ZpN[1][3][1] = sqrt(btag1__Zprime3000->GetEntries()) / btag1__Zprime3000->GetEntries();
ZpN[2][3][1] = sqrt(btag2__Zprime3000->GetEntries()) / btag2__Zprime3000->GetEntries();
ZpN[3][3][1] = sqrt(btag3__Zprime3000->GetEntries()) / btag3__Zprime3000->GetEntries();
ZpN[4][3][1] = sqrt(btag4__Zprime3000->GetEntries()) / btag4__Zprime3000->GetEntries();
ZpN[5][3][1] = sqrt(btag5__Zprime3000->GetEntries()) / btag5__Zprime3000->GetEntries();


ZpN_JES[0][0][0] = (btag0__Zprime1000__jec__plus->Integral() - btag0__Zprime1000->Integral()) / btag0__Zprime1000->Integral();
ZpN_JES[1][0][0] = (btag1__Zprime1000__jec__plus->Integral() - btag1__Zprime1000->Integral()) / btag1__Zprime1000->Integral();
ZpN_JES[2][0][0] = (btag2__Zprime1000__jec__plus->Integral() - btag2__Zprime1000->Integral()) / btag2__Zprime1000->Integral();
ZpN_JES[3][0][0] = (btag3__Zprime1000__jec__plus->Integral() - btag3__Zprime1000->Integral()) / btag3__Zprime1000->Integral();
ZpN_JES[4][0][0] = (btag4__Zprime1000__jec__plus->Integral() - btag4__Zprime1000->Integral()) / btag4__Zprime1000->Integral();
ZpN_JES[5][0][0] = (btag5__Zprime1000__jec__plus->Integral() - btag5__Zprime1000->Integral()) / btag5__Zprime1000->Integral();
ZpN_JES[0][0][1] = (btag0__Zprime1000__jec__minus->Integral() - btag0__Zprime1000->Integral()) / btag0__Zprime1000->Integral();
ZpN_JES[1][0][1] = (btag1__Zprime1000__jec__minus->Integral() - btag1__Zprime1000->Integral()) / btag1__Zprime1000->Integral();
ZpN_JES[2][0][1] = (btag2__Zprime1000__jec__minus->Integral() - btag2__Zprime1000->Integral()) / btag2__Zprime1000->Integral();
ZpN_JES[3][0][1] = (btag3__Zprime1000__jec__minus->Integral() - btag3__Zprime1000->Integral()) / btag3__Zprime1000->Integral();
ZpN_JES[4][0][1] = (btag4__Zprime1000__jec__minus->Integral() - btag4__Zprime1000->Integral()) / btag4__Zprime1000->Integral();
ZpN_JES[5][0][1] = (btag5__Zprime1000__jec__minus->Integral() - btag5__Zprime1000->Integral()) / btag5__Zprime1000->Integral();

ZpN_JES[0][1][0] = (btag0__Zprime1500__jec__plus->Integral() - btag0__Zprime1500->Integral()) / btag0__Zprime1500->Integral();
ZpN_JES[1][1][0] = (btag1__Zprime1500__jec__plus->Integral() - btag1__Zprime1500->Integral()) / btag1__Zprime1500->Integral();
ZpN_JES[2][1][0] = (btag2__Zprime1500__jec__plus->Integral() - btag2__Zprime1500->Integral()) / btag2__Zprime1500->Integral();
ZpN_JES[3][1][0] = (btag3__Zprime1500__jec__plus->Integral() - btag3__Zprime1500->Integral()) / btag3__Zprime1500->Integral();
ZpN_JES[4][1][0] = (btag4__Zprime1500__jec__plus->Integral() - btag4__Zprime1500->Integral()) / btag4__Zprime1500->Integral();
ZpN_JES[5][1][0] = (btag5__Zprime1500__jec__plus->Integral() - btag5__Zprime1500->Integral()) / btag5__Zprime1500->Integral();
ZpN_JES[0][1][1] = (btag0__Zprime1500__jec__minus->Integral() - btag0__Zprime1500->Integral()) / btag0__Zprime1500->Integral();
ZpN_JES[1][1][1] = (btag1__Zprime1500__jec__minus->Integral() - btag1__Zprime1500->Integral()) / btag1__Zprime1500->Integral();
ZpN_JES[2][1][1] = (btag2__Zprime1500__jec__minus->Integral() - btag2__Zprime1500->Integral()) / btag2__Zprime1500->Integral();
ZpN_JES[3][1][1] = (btag3__Zprime1500__jec__minus->Integral() - btag3__Zprime1500->Integral()) / btag3__Zprime1500->Integral();
ZpN_JES[4][1][1] = (btag4__Zprime1500__jec__minus->Integral() - btag4__Zprime1500->Integral()) / btag4__Zprime1500->Integral();
ZpN_JES[5][1][1] = (btag5__Zprime1500__jec__minus->Integral() - btag5__Zprime1500->Integral()) / btag5__Zprime1500->Integral();

ZpN_JES[0][2][0] = (btag0__Zprime2000__jec__plus->Integral() - btag0__Zprime2000->Integral()) / btag0__Zprime2000->Integral();
ZpN_JES[1][2][0] = (btag1__Zprime2000__jec__plus->Integral() - btag1__Zprime2000->Integral()) / btag1__Zprime2000->Integral();
ZpN_JES[2][2][0] = (btag2__Zprime2000__jec__plus->Integral() - btag2__Zprime2000->Integral()) / btag2__Zprime2000->Integral();
ZpN_JES[3][2][0] = (btag3__Zprime2000__jec__plus->Integral() - btag3__Zprime2000->Integral()) / btag3__Zprime2000->Integral();
ZpN_JES[4][2][0] = (btag4__Zprime2000__jec__plus->Integral() - btag4__Zprime2000->Integral()) / btag4__Zprime2000->Integral();
ZpN_JES[5][2][0] = (btag5__Zprime2000__jec__plus->Integral() - btag5__Zprime2000->Integral()) / btag5__Zprime2000->Integral();
ZpN_JES[0][2][1] = (btag0__Zprime2000__jec__minus->Integral() - btag0__Zprime2000->Integral()) / btag0__Zprime2000->Integral();
ZpN_JES[1][2][1] = (btag1__Zprime2000__jec__minus->Integral() - btag1__Zprime2000->Integral()) / btag1__Zprime2000->Integral();
ZpN_JES[2][2][1] = (btag2__Zprime2000__jec__minus->Integral() - btag2__Zprime2000->Integral()) / btag2__Zprime2000->Integral();
ZpN_JES[3][2][1] = (btag3__Zprime2000__jec__minus->Integral() - btag3__Zprime2000->Integral()) / btag3__Zprime2000->Integral();
ZpN_JES[4][2][1] = (btag4__Zprime2000__jec__minus->Integral() - btag4__Zprime2000->Integral()) / btag4__Zprime2000->Integral();
ZpN_JES[5][2][1] = (btag5__Zprime2000__jec__minus->Integral() - btag5__Zprime2000->Integral()) / btag5__Zprime2000->Integral();

ZpN_JES[0][3][0] = (btag0__Zprime3000__jec__plus->Integral() - btag0__Zprime3000->Integral()) / btag0__Zprime3000->Integral();
ZpN_JES[1][3][0] = (btag1__Zprime3000__jec__plus->Integral() - btag1__Zprime3000->Integral()) / btag1__Zprime3000->Integral();
ZpN_JES[2][3][0] = (btag2__Zprime3000__jec__plus->Integral() - btag2__Zprime3000->Integral()) / btag2__Zprime3000->Integral();
ZpN_JES[3][3][0] = (btag3__Zprime3000__jec__plus->Integral() - btag3__Zprime3000->Integral()) / btag3__Zprime3000->Integral();
ZpN_JES[4][3][0] = (btag4__Zprime3000__jec__plus->Integral() - btag4__Zprime3000->Integral()) / btag4__Zprime3000->Integral();
ZpN_JES[5][3][0] = (btag5__Zprime3000__jec__plus->Integral() - btag5__Zprime3000->Integral()) / btag5__Zprime3000->Integral();
ZpN_JES[0][3][1] = (btag0__Zprime3000__jec__minus->Integral() - btag0__Zprime3000->Integral()) / btag0__Zprime3000->Integral();
ZpN_JES[1][3][1] = (btag1__Zprime3000__jec__minus->Integral() - btag1__Zprime3000->Integral()) / btag1__Zprime3000->Integral();
ZpN_JES[2][3][1] = (btag2__Zprime3000__jec__minus->Integral() - btag2__Zprime3000->Integral()) / btag2__Zprime3000->Integral();
ZpN_JES[3][3][1] = (btag3__Zprime3000__jec__minus->Integral() - btag3__Zprime3000->Integral()) / btag3__Zprime3000->Integral();
ZpN_JES[4][3][1] = (btag4__Zprime3000__jec__minus->Integral() - btag4__Zprime3000->Integral()) / btag4__Zprime3000->Integral();
ZpN_JES[5][3][1] = (btag5__Zprime3000__jec__minus->Integral() - btag5__Zprime3000->Integral()) / btag5__Zprime3000->Integral();


ZpN_PDF[0][0][0] = (btag0__Zprime1000__pdf__plus->Integral() - btag0__Zprime1000->Integral()) / btag0__Zprime1000->Integral();
ZpN_PDF[1][0][0] = (btag1__Zprime1000__pdf__plus->Integral() - btag1__Zprime1000->Integral()) / btag1__Zprime1000->Integral();
ZpN_PDF[2][0][0] = (btag2__Zprime1000__pdf__plus->Integral() - btag2__Zprime1000->Integral()) / btag2__Zprime1000->Integral();
ZpN_PDF[3][0][0] = (btag3__Zprime1000__pdf__plus->Integral() - btag3__Zprime1000->Integral()) / btag3__Zprime1000->Integral();
ZpN_PDF[4][0][0] = (btag4__Zprime1000__pdf__plus->Integral() - btag4__Zprime1000->Integral()) / btag4__Zprime1000->Integral();
ZpN_PDF[5][0][0] = (btag5__Zprime1000__pdf__plus->Integral() - btag5__Zprime1000->Integral()) / btag5__Zprime1000->Integral();
ZpN_PDF[0][0][1] = (btag0__Zprime1000__pdf__minus->Integral() - btag0__Zprime1000->Integral()) / btag0__Zprime1000->Integral();
ZpN_PDF[1][0][1] = (btag1__Zprime1000__pdf__minus->Integral() - btag1__Zprime1000->Integral()) / btag1__Zprime1000->Integral();
ZpN_PDF[2][0][1] = (btag2__Zprime1000__pdf__minus->Integral() - btag2__Zprime1000->Integral()) / btag2__Zprime1000->Integral();
ZpN_PDF[3][0][1] = (btag3__Zprime1000__pdf__minus->Integral() - btag3__Zprime1000->Integral()) / btag3__Zprime1000->Integral();
ZpN_PDF[4][0][1] = (btag4__Zprime1000__pdf__minus->Integral() - btag4__Zprime1000->Integral()) / btag4__Zprime1000->Integral();
ZpN_PDF[5][0][1] = (btag5__Zprime1000__pdf__minus->Integral() - btag5__Zprime1000->Integral()) / btag5__Zprime1000->Integral();

ZpN_PDF[0][1][0] = (btag0__Zprime1500__pdf__plus->Integral() - btag0__Zprime1500->Integral()) / btag0__Zprime1500->Integral();
ZpN_PDF[1][1][0] = (btag1__Zprime1500__pdf__plus->Integral() - btag1__Zprime1500->Integral()) / btag1__Zprime1500->Integral();
ZpN_PDF[2][1][0] = (btag2__Zprime1500__pdf__plus->Integral() - btag2__Zprime1500->Integral()) / btag2__Zprime1500->Integral();
ZpN_PDF[3][1][0] = (btag3__Zprime1500__pdf__plus->Integral() - btag3__Zprime1500->Integral()) / btag3__Zprime1500->Integral();
ZpN_PDF[4][1][0] = (btag4__Zprime1500__pdf__plus->Integral() - btag4__Zprime1500->Integral()) / btag4__Zprime1500->Integral();
ZpN_PDF[5][1][0] = (btag5__Zprime1500__pdf__plus->Integral() - btag5__Zprime1500->Integral()) / btag5__Zprime1500->Integral();
ZpN_PDF[0][1][1] = (btag0__Zprime1500__pdf__minus->Integral() - btag0__Zprime1500->Integral()) / btag0__Zprime1500->Integral();
ZpN_PDF[1][1][1] = (btag1__Zprime1500__pdf__minus->Integral() - btag1__Zprime1500->Integral()) / btag1__Zprime1500->Integral();
ZpN_PDF[2][1][1] = (btag2__Zprime1500__pdf__minus->Integral() - btag2__Zprime1500->Integral()) / btag2__Zprime1500->Integral();
ZpN_PDF[3][1][1] = (btag3__Zprime1500__pdf__minus->Integral() - btag3__Zprime1500->Integral()) / btag3__Zprime1500->Integral();
ZpN_PDF[4][1][1] = (btag4__Zprime1500__pdf__minus->Integral() - btag4__Zprime1500->Integral()) / btag4__Zprime1500->Integral();
ZpN_PDF[5][1][1] = (btag5__Zprime1500__pdf__minus->Integral() - btag5__Zprime1500->Integral()) / btag5__Zprime1500->Integral();

ZpN_PDF[0][2][0] = (btag0__Zprime2000__pdf__plus->Integral() - btag0__Zprime2000->Integral()) / btag0__Zprime2000->Integral();
ZpN_PDF[1][2][0] = (btag1__Zprime2000__pdf__plus->Integral() - btag1__Zprime2000->Integral()) / btag1__Zprime2000->Integral();
ZpN_PDF[2][2][0] = (btag2__Zprime2000__pdf__plus->Integral() - btag2__Zprime2000->Integral()) / btag2__Zprime2000->Integral();
ZpN_PDF[3][2][0] = (btag3__Zprime2000__pdf__plus->Integral() - btag3__Zprime2000->Integral()) / btag3__Zprime2000->Integral();
ZpN_PDF[4][2][0] = (btag4__Zprime2000__pdf__plus->Integral() - btag4__Zprime2000->Integral()) / btag4__Zprime2000->Integral();
ZpN_PDF[5][2][0] = (btag5__Zprime2000__pdf__plus->Integral() - btag5__Zprime2000->Integral()) / btag5__Zprime2000->Integral();
ZpN_PDF[0][2][1] = (btag0__Zprime2000__pdf__minus->Integral() - btag0__Zprime2000->Integral()) / btag0__Zprime2000->Integral();
ZpN_PDF[1][2][1] = (btag1__Zprime2000__pdf__minus->Integral() - btag1__Zprime2000->Integral()) / btag1__Zprime2000->Integral();
ZpN_PDF[2][2][1] = (btag2__Zprime2000__pdf__minus->Integral() - btag2__Zprime2000->Integral()) / btag2__Zprime2000->Integral();
ZpN_PDF[3][2][1] = (btag3__Zprime2000__pdf__minus->Integral() - btag3__Zprime2000->Integral()) / btag3__Zprime2000->Integral();
ZpN_PDF[4][2][1] = (btag4__Zprime2000__pdf__minus->Integral() - btag4__Zprime2000->Integral()) / btag4__Zprime2000->Integral();
ZpN_PDF[5][2][1] = (btag5__Zprime2000__pdf__minus->Integral() - btag5__Zprime2000->Integral()) / btag5__Zprime2000->Integral();

ZpN_PDF[0][3][0] = (btag0__Zprime3000__pdf__plus->Integral() - btag0__Zprime3000->Integral()) / btag0__Zprime3000->Integral();
ZpN_PDF[1][3][0] = (btag1__Zprime3000__pdf__plus->Integral() - btag1__Zprime3000->Integral()) / btag1__Zprime3000->Integral();
ZpN_PDF[2][3][0] = (btag2__Zprime3000__pdf__plus->Integral() - btag2__Zprime3000->Integral()) / btag2__Zprime3000->Integral();
ZpN_PDF[3][3][0] = (btag3__Zprime3000__pdf__plus->Integral() - btag3__Zprime3000->Integral()) / btag3__Zprime3000->Integral();
ZpN_PDF[4][3][0] = (btag4__Zprime3000__pdf__plus->Integral() - btag4__Zprime3000->Integral()) / btag4__Zprime3000->Integral();
ZpN_PDF[5][3][0] = (btag5__Zprime3000__pdf__plus->Integral() - btag5__Zprime3000->Integral()) / btag5__Zprime3000->Integral();
ZpN_PDF[0][3][1] = (btag0__Zprime3000__pdf__minus->Integral() - btag0__Zprime3000->Integral()) / btag0__Zprime3000->Integral();
ZpN_PDF[1][3][1] = (btag1__Zprime3000__pdf__minus->Integral() - btag1__Zprime3000->Integral()) / btag1__Zprime3000->Integral();
ZpN_PDF[2][3][1] = (btag2__Zprime3000__pdf__minus->Integral() - btag2__Zprime3000->Integral()) / btag2__Zprime3000->Integral();
ZpN_PDF[3][3][1] = (btag3__Zprime3000__pdf__minus->Integral() - btag3__Zprime3000->Integral()) / btag3__Zprime3000->Integral();
ZpN_PDF[4][3][1] = (btag4__Zprime3000__pdf__minus->Integral() - btag4__Zprime3000->Integral()) / btag4__Zprime3000->Integral();
ZpN_PDF[5][3][1] = (btag5__Zprime3000__pdf__minus->Integral() - btag5__Zprime3000->Integral()) / btag5__Zprime3000->Integral();






ZpN_btag[0][0][0] = (btag0__Zprime1000__btag__plus->Integral() - btag0__Zprime1000->Integral()) / btag0__Zprime1000->Integral();
ZpN_btag[1][0][0] = (btag1__Zprime1000__btag__plus->Integral() - btag1__Zprime1000->Integral()) / btag1__Zprime1000->Integral();
ZpN_btag[2][0][0] = (btag2__Zprime1000__btag__plus->Integral() - btag2__Zprime1000->Integral()) / btag2__Zprime1000->Integral();
ZpN_btag[3][0][0] = (btag3__Zprime1000__btag__plus->Integral() - btag3__Zprime1000->Integral()) / btag3__Zprime1000->Integral();
ZpN_btag[4][0][0] = (btag4__Zprime1000__btag__plus->Integral() - btag4__Zprime1000->Integral()) / btag4__Zprime1000->Integral();
ZpN_btag[5][0][0] = (btag5__Zprime1000__btag__plus->Integral() - btag5__Zprime1000->Integral()) / btag5__Zprime1000->Integral();
ZpN_btag[0][0][1] = (btag0__Zprime1000__btag__minus->Integral() - btag0__Zprime1000->Integral()) / btag0__Zprime1000->Integral();
ZpN_btag[1][0][1] = (btag1__Zprime1000__btag__minus->Integral() - btag1__Zprime1000->Integral()) / btag1__Zprime1000->Integral();
ZpN_btag[2][0][1] = (btag2__Zprime1000__btag__minus->Integral() - btag2__Zprime1000->Integral()) / btag2__Zprime1000->Integral();
ZpN_btag[3][0][1] = (btag3__Zprime1000__btag__minus->Integral() - btag3__Zprime1000->Integral()) / btag3__Zprime1000->Integral();
ZpN_btag[4][0][1] = (btag4__Zprime1000__btag__minus->Integral() - btag4__Zprime1000->Integral()) / btag4__Zprime1000->Integral();
ZpN_btag[5][0][1] = (btag5__Zprime1000__btag__minus->Integral() - btag5__Zprime1000->Integral()) / btag5__Zprime1000->Integral();

ZpN_btag[0][1][0] = (btag0__Zprime1500__btag__plus->Integral() - btag0__Zprime1500->Integral()) / btag0__Zprime1500->Integral();
ZpN_btag[1][1][0] = (btag1__Zprime1500__btag__plus->Integral() - btag1__Zprime1500->Integral()) / btag1__Zprime1500->Integral();
ZpN_btag[2][1][0] = (btag2__Zprime1500__btag__plus->Integral() - btag2__Zprime1500->Integral()) / btag2__Zprime1500->Integral();
ZpN_btag[3][1][0] = (btag3__Zprime1500__btag__plus->Integral() - btag3__Zprime1500->Integral()) / btag3__Zprime1500->Integral();
ZpN_btag[4][1][0] = (btag4__Zprime1500__btag__plus->Integral() - btag4__Zprime1500->Integral()) / btag4__Zprime1500->Integral();
ZpN_btag[5][1][0] = (btag5__Zprime1500__btag__plus->Integral() - btag5__Zprime1500->Integral()) / btag5__Zprime1500->Integral();
ZpN_btag[0][1][1] = (btag0__Zprime1500__btag__minus->Integral() - btag0__Zprime1500->Integral()) / btag0__Zprime1500->Integral();
ZpN_btag[1][1][1] = (btag1__Zprime1500__btag__minus->Integral() - btag1__Zprime1500->Integral()) / btag1__Zprime1500->Integral();
ZpN_btag[2][1][1] = (btag2__Zprime1500__btag__minus->Integral() - btag2__Zprime1500->Integral()) / btag2__Zprime1500->Integral();
ZpN_btag[3][1][1] = (btag3__Zprime1500__btag__minus->Integral() - btag3__Zprime1500->Integral()) / btag3__Zprime1500->Integral();
ZpN_btag[4][1][1] = (btag4__Zprime1500__btag__minus->Integral() - btag4__Zprime1500->Integral()) / btag4__Zprime1500->Integral();
ZpN_btag[5][1][1] = (btag5__Zprime1500__btag__minus->Integral() - btag5__Zprime1500->Integral()) / btag5__Zprime1500->Integral();

ZpN_btag[0][2][0] = (btag0__Zprime2000__btag__plus->Integral() - btag0__Zprime2000->Integral()) / btag0__Zprime2000->Integral();
ZpN_btag[1][2][0] = (btag1__Zprime2000__btag__plus->Integral() - btag1__Zprime2000->Integral()) / btag1__Zprime2000->Integral();
ZpN_btag[2][2][0] = (btag2__Zprime2000__btag__plus->Integral() - btag2__Zprime2000->Integral()) / btag2__Zprime2000->Integral();
ZpN_btag[3][2][0] = (btag3__Zprime2000__btag__plus->Integral() - btag3__Zprime2000->Integral()) / btag3__Zprime2000->Integral();
ZpN_btag[4][2][0] = (btag4__Zprime2000__btag__plus->Integral() - btag4__Zprime2000->Integral()) / btag4__Zprime2000->Integral();
ZpN_btag[5][2][0] = (btag5__Zprime2000__btag__plus->Integral() - btag5__Zprime2000->Integral()) / btag5__Zprime2000->Integral();
ZpN_btag[0][2][1] = (btag0__Zprime2000__btag__minus->Integral() - btag0__Zprime2000->Integral()) / btag0__Zprime2000->Integral();
ZpN_btag[1][2][1] = (btag1__Zprime2000__btag__minus->Integral() - btag1__Zprime2000->Integral()) / btag1__Zprime2000->Integral();
ZpN_btag[2][2][1] = (btag2__Zprime2000__btag__minus->Integral() - btag2__Zprime2000->Integral()) / btag2__Zprime2000->Integral();
ZpN_btag[3][2][1] = (btag3__Zprime2000__btag__minus->Integral() - btag3__Zprime2000->Integral()) / btag3__Zprime2000->Integral();
ZpN_btag[4][2][1] = (btag4__Zprime2000__btag__minus->Integral() - btag4__Zprime2000->Integral()) / btag4__Zprime2000->Integral();
ZpN_btag[5][2][1] = (btag5__Zprime2000__btag__minus->Integral() - btag5__Zprime2000->Integral()) / btag5__Zprime2000->Integral();

ZpN_btag[0][3][0] = (btag0__Zprime3000__btag__plus->Integral() - btag0__Zprime3000->Integral()) / btag0__Zprime3000->Integral();
ZpN_btag[1][3][0] = (btag1__Zprime3000__btag__plus->Integral() - btag1__Zprime3000->Integral()) / btag1__Zprime3000->Integral();
ZpN_btag[2][3][0] = (btag2__Zprime3000__btag__plus->Integral() - btag2__Zprime3000->Integral()) / btag2__Zprime3000->Integral();
ZpN_btag[3][3][0] = (btag3__Zprime3000__btag__plus->Integral() - btag3__Zprime3000->Integral()) / btag3__Zprime3000->Integral();
ZpN_btag[4][3][0] = (btag4__Zprime3000__btag__plus->Integral() - btag4__Zprime3000->Integral()) / btag4__Zprime3000->Integral();
ZpN_btag[5][3][0] = (btag5__Zprime3000__btag__plus->Integral() - btag5__Zprime3000->Integral()) / btag5__Zprime3000->Integral();
ZpN_btag[0][3][1] = (btag0__Zprime3000__btag__minus->Integral() - btag0__Zprime3000->Integral()) / btag0__Zprime3000->Integral();
ZpN_btag[1][3][1] = (btag1__Zprime3000__btag__minus->Integral() - btag1__Zprime3000->Integral()) / btag1__Zprime3000->Integral();
ZpN_btag[2][3][1] = (btag2__Zprime3000__btag__minus->Integral() - btag2__Zprime3000->Integral()) / btag2__Zprime3000->Integral();
ZpN_btag[3][3][1] = (btag3__Zprime3000__btag__minus->Integral() - btag3__Zprime3000->Integral()) / btag3__Zprime3000->Integral();
ZpN_btag[4][3][1] = (btag4__Zprime3000__btag__minus->Integral() - btag4__Zprime3000->Integral()) / btag4__Zprime3000->Integral();
ZpN_btag[5][3][1] = (btag5__Zprime3000__btag__minus->Integral() - btag5__Zprime3000->Integral()) / btag5__Zprime3000->Integral();

ttbar_btag[0][0] = (btag0__ttbar__btag__plus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
ttbar_btag[1][0] =  (btag1__ttbar__btag__plus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
ttbar_btag[2][0] = (btag2__ttbar__btag__plus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
ttbar_btag[3][0] = (btag3__ttbar__btag__plus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
ttbar_btag[4][0] = (btag4__ttbar__btag__plus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
ttbar_btag[5][0] = (btag5__ttbar__btag__plus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();
ttbar_btag[0][1] = (btag0__ttbar__btag__minus->Integral() - btag0__ttbar->Integral()) / btag0__ttbar->Integral();
ttbar_btag[1][1] = (btag1__ttbar__btag__minus->Integral() - btag1__ttbar->Integral()) / btag1__ttbar->Integral();
ttbar_btag[2][1] = (btag2__ttbar__btag__minus->Integral() - btag2__ttbar->Integral()) / btag2__ttbar->Integral();
ttbar_btag[3][1] = (btag3__ttbar__btag__minus->Integral() - btag3__ttbar->Integral()) / btag3__ttbar->Integral();
ttbar_btag[4][1] = (btag4__ttbar__btag__minus->Integral() - btag4__ttbar->Integral()) / btag4__ttbar->Integral();
ttbar_btag[5][1] = (btag5__ttbar__btag__minus->Integral() - btag5__ttbar->Integral()) / btag5__ttbar->Integral();




ZpN_JER[0][0][0] = (btag0__Zprime1000__jer__plus->Integral() - btag0__Zprime1000->Integral()) / btag0__Zprime1000->Integral();
ZpN_JER[1][0][0] = (btag1__Zprime1000__jer__plus->Integral() - btag1__Zprime1000->Integral()) / btag1__Zprime1000->Integral();
ZpN_JER[2][0][0] = (btag2__Zprime1000__jer__plus->Integral() - btag2__Zprime1000->Integral()) / btag2__Zprime1000->Integral();
ZpN_JER[3][0][0] = (btag3__Zprime1000__jer__plus->Integral() - btag3__Zprime1000->Integral()) / btag3__Zprime1000->Integral();
ZpN_JER[4][0][0] = (btag4__Zprime1000__jer__plus->Integral() - btag4__Zprime1000->Integral()) / btag4__Zprime1000->Integral();
ZpN_JER[5][0][0] = (btag5__Zprime1000__jer__plus->Integral() - btag5__Zprime1000->Integral()) / btag5__Zprime1000->Integral();
ZpN_JER[0][0][1] = (btag0__Zprime1000__jer__minus->Integral() - btag0__Zprime1000->Integral()) / btag0__Zprime1000->Integral();
ZpN_JER[1][0][1] = (btag1__Zprime1000__jer__minus->Integral() - btag1__Zprime1000->Integral()) / btag1__Zprime1000->Integral();
ZpN_JER[2][0][1] = (btag2__Zprime1000__jer__minus->Integral() - btag2__Zprime1000->Integral()) / btag2__Zprime1000->Integral();
ZpN_JER[3][0][1] = (btag3__Zprime1000__jer__minus->Integral() - btag3__Zprime1000->Integral()) / btag3__Zprime1000->Integral();
ZpN_JER[4][0][1] = (btag4__Zprime1000__jer__minus->Integral() - btag4__Zprime1000->Integral()) / btag4__Zprime1000->Integral();
ZpN_JER[5][0][1] = (btag5__Zprime1000__jer__minus->Integral() - btag5__Zprime1000->Integral()) / btag5__Zprime1000->Integral();

ZpN_JER[0][1][0] = (btag0__Zprime1500__jer__plus->Integral() - btag0__Zprime1500->Integral()) / btag0__Zprime1500->Integral();
ZpN_JER[1][1][0] = (btag1__Zprime1500__jer__plus->Integral() - btag1__Zprime1500->Integral()) / btag1__Zprime1500->Integral();
ZpN_JER[2][1][0] = (btag2__Zprime1500__jer__plus->Integral() - btag2__Zprime1500->Integral()) / btag2__Zprime1500->Integral();
ZpN_JER[3][1][0] = (btag3__Zprime1500__jer__plus->Integral() - btag3__Zprime1500->Integral()) / btag3__Zprime1500->Integral();
ZpN_JER[4][1][0] = (btag4__Zprime1500__jer__plus->Integral() - btag4__Zprime1500->Integral()) / btag4__Zprime1500->Integral();
ZpN_JER[5][1][0] = (btag5__Zprime1500__jer__plus->Integral() - btag5__Zprime1500->Integral()) / btag5__Zprime1500->Integral();
ZpN_JER[0][1][1] = (btag0__Zprime1500__jer__minus->Integral() - btag0__Zprime1500->Integral()) / btag0__Zprime1500->Integral();
ZpN_JER[1][1][1] = (btag1__Zprime1500__jer__minus->Integral() - btag1__Zprime1500->Integral()) / btag1__Zprime1500->Integral();
ZpN_JER[2][1][1] = (btag2__Zprime1500__jer__minus->Integral() - btag2__Zprime1500->Integral()) / btag2__Zprime1500->Integral();
ZpN_JER[3][1][1] = (btag3__Zprime1500__jer__minus->Integral() - btag3__Zprime1500->Integral()) / btag3__Zprime1500->Integral();
ZpN_JER[4][1][1] = (btag4__Zprime1500__jer__minus->Integral() - btag4__Zprime1500->Integral()) / btag4__Zprime1500->Integral();
ZpN_JER[5][1][1] = (btag5__Zprime1500__jer__minus->Integral() - btag5__Zprime1500->Integral()) / btag5__Zprime1500->Integral();

ZpN_JER[0][2][0] = (btag0__Zprime2000__jer__plus->Integral() - btag0__Zprime2000->Integral()) / btag0__Zprime2000->Integral();
ZpN_JER[1][2][0] = (btag1__Zprime2000__jer__plus->Integral() - btag1__Zprime2000->Integral()) / btag1__Zprime2000->Integral();
ZpN_JER[2][2][0] = (btag2__Zprime2000__jer__plus->Integral() - btag2__Zprime2000->Integral()) / btag2__Zprime2000->Integral();
ZpN_JER[3][2][0] = (btag3__Zprime2000__jer__plus->Integral() - btag3__Zprime2000->Integral()) / btag3__Zprime2000->Integral();
ZpN_JER[4][2][0] = (btag4__Zprime2000__jer__plus->Integral() - btag4__Zprime2000->Integral()) / btag4__Zprime2000->Integral();
ZpN_JER[5][2][0] = (btag5__Zprime2000__jer__plus->Integral() - btag5__Zprime2000->Integral()) / btag5__Zprime2000->Integral();
ZpN_JER[0][2][1] = (btag0__Zprime2000__jer__minus->Integral() - btag0__Zprime2000->Integral()) / btag0__Zprime2000->Integral();
ZpN_JER[1][2][1] = (btag1__Zprime2000__jer__minus->Integral() - btag1__Zprime2000->Integral()) / btag1__Zprime2000->Integral();
ZpN_JER[2][2][1] = (btag2__Zprime2000__jer__minus->Integral() - btag2__Zprime2000->Integral()) / btag2__Zprime2000->Integral();
ZpN_JER[3][2][1] = (btag3__Zprime2000__jer__minus->Integral() - btag3__Zprime2000->Integral()) / btag3__Zprime2000->Integral();
ZpN_JER[4][2][1] = (btag4__Zprime2000__jer__minus->Integral() - btag4__Zprime2000->Integral()) / btag4__Zprime2000->Integral();
ZpN_JER[5][2][1] = (btag5__Zprime2000__jer__minus->Integral() - btag5__Zprime2000->Integral()) / btag5__Zprime2000->Integral();

ZpN_JER[0][3][0] = (btag0__Zprime3000__jer__plus->Integral() - btag0__Zprime3000->Integral()) / btag0__Zprime3000->Integral();
ZpN_JER[1][3][0] = (btag1__Zprime3000__jer__plus->Integral() - btag1__Zprime3000->Integral()) / btag1__Zprime3000->Integral();
ZpN_JER[2][3][0] = (btag2__Zprime3000__jer__plus->Integral() - btag2__Zprime3000->Integral()) / btag2__Zprime3000->Integral();
ZpN_JER[3][3][0] = (btag3__Zprime3000__jer__plus->Integral() - btag3__Zprime3000->Integral()) / btag3__Zprime3000->Integral();
ZpN_JER[4][3][0] = (btag4__Zprime3000__jer__plus->Integral() - btag4__Zprime3000->Integral()) / btag4__Zprime3000->Integral();
ZpN_JER[5][3][0] = (btag5__Zprime3000__jer__plus->Integral() - btag5__Zprime3000->Integral()) / btag5__Zprime3000->Integral();
ZpN_JER[0][3][1] = (btag0__Zprime3000__jer__minus->Integral() - btag0__Zprime3000->Integral()) / btag0__Zprime3000->Integral();
ZpN_JER[1][3][1] = (btag1__Zprime3000__jer__minus->Integral() - btag1__Zprime3000->Integral()) / btag1__Zprime3000->Integral();
ZpN_JER[2][3][1] = (btag2__Zprime3000__jer__minus->Integral() - btag2__Zprime3000->Integral()) / btag2__Zprime3000->Integral();
ZpN_JER[3][3][1] = (btag3__Zprime3000__jer__minus->Integral() - btag3__Zprime3000->Integral()) / btag3__Zprime3000->Integral();
ZpN_JER[4][3][1] = (btag4__Zprime3000__jer__minus->Integral() - btag4__Zprime3000->Integral()) / btag4__Zprime3000->Integral();
ZpN_JER[5][3][1] = (btag5__Zprime3000__jer__minus->Integral() - btag5__Zprime3000->Integral()) / btag5__Zprime3000->Integral();


/*

ZpW[0][0][0] = btag0__ZprimeWide1000->Integral();
ZpW[1][0][0] = btag1__ZprimeWide1000->Integral();
ZpW[2][0][0] = btag2__ZprimeWide1000->Integral();
ZpW[3][0][0] = btag3__ZprimeWide1000->Integral();
ZpW[4][0][0] = btag4__ZprimeWide1000->Integral();
ZpW[5][0][0] = btag5__ZprimeWide1000->Integral();
ZpW[0][0][1] = sqrt(btag0__ZprimeWide1000->GetEntries()) / btag0__ZprimeWide1000->GetEntries();
ZpW[1][0][1] = sqrt(btag1__ZprimeWide1000->GetEntries()) / btag1__ZprimeWide1000->GetEntries();
ZpW[2][0][1] = sqrt(btag2__ZprimeWide1000->GetEntries()) / btag2__ZprimeWide1000->GetEntries();
ZpW[3][0][1] = sqrt(btag3__ZprimeWide1000->GetEntries()) / btag3__ZprimeWide1000->GetEntries();
ZpW[4][0][1] = sqrt(btag4__ZprimeWide1000->GetEntries()) / btag4__ZprimeWide1000->GetEntries();
ZpW[5][0][1] = sqrt(btag5__ZprimeWide1000->GetEntries()) / btag5__ZprimeWide1000->GetEntries();

ZpW[0][1][0] = btag0__ZprimeWide1500->Integral();
ZpW[1][1][0] = btag1__ZprimeWide1500->Integral();
ZpW[2][1][0] = btag2__ZprimeWide1500->Integral();
ZpW[3][1][0] = btag3__ZprimeWide1500->Integral();
ZpW[4][1][0] = btag4__ZprimeWide1500->Integral();
ZpW[5][1][0] = btag5__ZprimeWide1500->Integral();
ZpW[0][1][1] = sqrt(btag0__ZprimeWide1500->GetEntries()) / btag0__ZprimeWide1500->GetEntries();
ZpW[1][1][1] = sqrt(btag1__ZprimeWide1500->GetEntries()) / btag1__ZprimeWide1500->GetEntries();
ZpW[2][1][1] = sqrt(btag2__ZprimeWide1500->GetEntries()) / btag2__ZprimeWide1500->GetEntries();
ZpW[3][1][1] = sqrt(btag3__ZprimeWide1500->GetEntries()) / btag3__ZprimeWide1500->GetEntries();
ZpW[4][1][1] = sqrt(btag4__ZprimeWide1500->GetEntries()) / btag4__ZprimeWide1500->GetEntries();
ZpW[5][1][1] = sqrt(btag5__ZprimeWide1500->GetEntries()) / btag5__ZprimeWide1500->GetEntries();

ZpW[0][2][0] = btag0__ZprimeWide2000->Integral();
ZpW[1][2][0] = btag1__ZprimeWide2000->Integral();
ZpW[2][2][0] = btag2__ZprimeWide2000->Integral();
ZpW[3][2][0] = btag3__ZprimeWide2000->Integral();
ZpW[4][2][0] = btag4__ZprimeWide2000->Integral();
ZpW[5][2][0] = btag5__ZprimeWide2000->Integral();
ZpW[0][2][1] = sqrt(btag0__ZprimeWide2000->GetEntries()) / btag0__ZprimeWide2000->GetEntries();
ZpW[1][2][1] = sqrt(btag1__ZprimeWide2000->GetEntries()) / btag1__ZprimeWide2000->GetEntries();
ZpW[2][2][1] = sqrt(btag2__ZprimeWide2000->GetEntries()) / btag2__ZprimeWide2000->GetEntries();
ZpW[3][2][1] = sqrt(btag3__ZprimeWide2000->GetEntries()) / btag3__ZprimeWide2000->GetEntries();
ZpW[4][2][1] = sqrt(btag4__ZprimeWide2000->GetEntries()) / btag4__ZprimeWide2000->GetEntries();
ZpW[5][2][1] = sqrt(btag5__ZprimeWide2000->GetEntries()) / btag5__ZprimeWide2000->GetEntries();

ZpW[0][3][0] = btag0__ZprimeWide3000->Integral();
ZpW[1][3][0] = btag1__ZprimeWide3000->Integral();
ZpW[2][3][0] = btag2__ZprimeWide3000->Integral();
ZpW[3][3][0] = btag3__ZprimeWide3000->Integral();
ZpW[4][3][0] = btag4__ZprimeWide3000->Integral();
ZpW[5][3][0] = btag5__ZprimeWide3000->Integral();
ZpW[0][3][1] = sqrt(btag0__ZprimeWide3000->GetEntries()) / btag0__ZprimeWide3000->GetEntries();
ZpW[1][3][1] = sqrt(btag1__ZprimeWide3000->GetEntries()) / btag1__ZprimeWide3000->GetEntries();
ZpW[2][3][1] = sqrt(btag2__ZprimeWide3000->GetEntries()) / btag2__ZprimeWide3000->GetEntries();
ZpW[3][3][1] = sqrt(btag3__ZprimeWide3000->GetEntries()) / btag3__ZprimeWide3000->GetEntries();
ZpW[4][3][1] = sqrt(btag4__ZprimeWide3000->GetEntries()) / btag4__ZprimeWide3000->GetEntries();
ZpW[5][3][1] = sqrt(btag5__ZprimeWide3000->GetEntries()) / btag5__ZprimeWide3000->GetEntries();

ZpW_JES[0][0][0] = (btag0__ZprimeWide1000__jec__plus->Integral() - btag0__ZprimeWide1000->Integral()) / btag0__ZprimeWide1000->Integral();
ZpW_JES[1][0][0] = (btag1__ZprimeWide1000__jec__plus->Integral() - btag1__ZprimeWide1000->Integral()) / btag1__ZprimeWide1000->Integral();
ZpW_JES[2][0][0] = (btag2__ZprimeWide1000__jec__plus->Integral() - btag2__ZprimeWide1000->Integral()) / btag2__ZprimeWide1000->Integral();
ZpW_JES[3][0][0] = (btag3__ZprimeWide1000__jec__plus->Integral() - btag3__ZprimeWide1000->Integral()) / btag3__ZprimeWide1000->Integral();
ZpW_JES[4][0][0] = (btag4__ZprimeWide1000__jec__plus->Integral() - btag4__ZprimeWide1000->Integral()) / btag4__ZprimeWide1000->Integral();
ZpW_JES[5][0][0] = (btag5__ZprimeWide1000__jec__plus->Integral() - btag5__ZprimeWide1000->Integral()) / btag5__ZprimeWide1000->Integral();
ZpW_JES[0][0][1] = (btag0__ZprimeWide1000__jec__minus->Integral() - btag0__ZprimeWide1000->Integral()) / btag0__ZprimeWide1000->Integral();
ZpW_JES[1][0][1] = (btag1__ZprimeWide1000__jec__minus->Integral() - btag1__ZprimeWide1000->Integral()) / btag1__ZprimeWide1000->Integral();
ZpW_JES[2][0][1] = (btag2__ZprimeWide1000__jec__minus->Integral() - btag2__ZprimeWide1000->Integral()) / btag2__ZprimeWide1000->Integral();
ZpW_JES[3][0][1] = (btag3__ZprimeWide1000__jec__minus->Integral() - btag3__ZprimeWide1000->Integral()) / btag3__ZprimeWide1000->Integral();
ZpW_JES[4][0][1] = (btag4__ZprimeWide1000__jec__minus->Integral() - btag4__ZprimeWide1000->Integral()) / btag4__ZprimeWide1000->Integral();
ZpW_JES[5][0][1] = (btag5__ZprimeWide1000__jec__minus->Integral() - btag5__ZprimeWide1000->Integral()) / btag5__ZprimeWide1000->Integral();

ZpW_JES[0][1][0] = (btag0__ZprimeWide1500__jec__plus->Integral() - btag0__ZprimeWide1500->Integral()) / btag0__ZprimeWide1500->Integral();
ZpW_JES[1][1][0] = (btag1__ZprimeWide1500__jec__plus->Integral() - btag1__ZprimeWide1500->Integral()) / btag1__ZprimeWide1500->Integral();
ZpW_JES[2][1][0] = (btag2__ZprimeWide1500__jec__plus->Integral() - btag2__ZprimeWide1500->Integral()) / btag2__ZprimeWide1500->Integral();
ZpW_JES[3][1][0] = (btag3__ZprimeWide1500__jec__plus->Integral() - btag3__ZprimeWide1500->Integral()) / btag3__ZprimeWide1500->Integral();
ZpW_JES[4][1][0] = (btag4__ZprimeWide1500__jec__plus->Integral() - btag4__ZprimeWide1500->Integral()) / btag4__ZprimeWide1500->Integral();
ZpW_JES[5][1][0] = (btag5__ZprimeWide1500__jec__plus->Integral() - btag5__ZprimeWide1500->Integral()) / btag5__ZprimeWide1500->Integral();
ZpW_JES[0][1][1] = (btag0__ZprimeWide1500__jec__minus->Integral() - btag0__ZprimeWide1500->Integral()) / btag0__ZprimeWide1500->Integral();
ZpW_JES[1][1][1] = (btag1__ZprimeWide1500__jec__minus->Integral() - btag1__ZprimeWide1500->Integral()) / btag1__ZprimeWide1500->Integral();
ZpW_JES[2][1][1] = (btag2__ZprimeWide1500__jec__minus->Integral() - btag2__ZprimeWide1500->Integral()) / btag2__ZprimeWide1500->Integral();
ZpW_JES[3][1][1] = (btag3__ZprimeWide1500__jec__minus->Integral() - btag3__ZprimeWide1500->Integral()) / btag3__ZprimeWide1500->Integral();
ZpW_JES[4][1][1] = (btag4__ZprimeWide1500__jec__minus->Integral() - btag4__ZprimeWide1500->Integral()) / btag4__ZprimeWide1500->Integral();
ZpW_JES[5][1][1] = (btag5__ZprimeWide1500__jec__minus->Integral() - btag5__ZprimeWide1500->Integral()) / btag5__ZprimeWide1500->Integral();

ZpW_JES[0][2][0] = (btag0__ZprimeWide2000__jec__plus->Integral() - btag0__ZprimeWide2000->Integral()) / btag0__ZprimeWide2000->Integral();
ZpW_JES[1][2][0] = (btag1__ZprimeWide2000__jec__plus->Integral() - btag1__ZprimeWide2000->Integral()) / btag1__ZprimeWide2000->Integral();
ZpW_JES[2][2][0] = (btag2__ZprimeWide2000__jec__plus->Integral() - btag2__ZprimeWide2000->Integral()) / btag2__ZprimeWide2000->Integral();
ZpW_JES[3][2][0] = (btag3__ZprimeWide2000__jec__plus->Integral() - btag3__ZprimeWide2000->Integral()) / btag3__ZprimeWide2000->Integral();
ZpW_JES[4][2][0] = (btag4__ZprimeWide2000__jec__plus->Integral() - btag4__ZprimeWide2000->Integral()) / btag4__ZprimeWide2000->Integral();
ZpW_JES[5][2][0] = (btag5__ZprimeWide2000__jec__plus->Integral() - btag5__ZprimeWide2000->Integral()) / btag5__ZprimeWide2000->Integral();
ZpW_JES[0][2][1] = (btag0__ZprimeWide2000__jec__minus->Integral() - btag0__ZprimeWide2000->Integral()) / btag0__ZprimeWide2000->Integral();
ZpW_JES[1][2][1] = (btag1__ZprimeWide2000__jec__minus->Integral() - btag1__ZprimeWide2000->Integral()) / btag1__ZprimeWide2000->Integral();
ZpW_JES[2][2][1] = (btag2__ZprimeWide2000__jec__minus->Integral() - btag2__ZprimeWide2000->Integral()) / btag2__ZprimeWide2000->Integral();
ZpW_JES[3][2][1] = (btag3__ZprimeWide2000__jec__minus->Integral() - btag3__ZprimeWide2000->Integral()) / btag3__ZprimeWide2000->Integral();
ZpW_JES[4][2][1] = (btag4__ZprimeWide2000__jec__minus->Integral() - btag4__ZprimeWide2000->Integral()) / btag4__ZprimeWide2000->Integral();
ZpW_JES[5][2][1] = (btag5__ZprimeWide2000__jec__minus->Integral() - btag5__ZprimeWide2000->Integral()) / btag5__ZprimeWide2000->Integral();

ZpW_JES[0][3][0] = (btag0__ZprimeWide3000__jec__plus->Integral() - btag0__ZprimeWide3000->Integral()) / btag0__ZprimeWide3000->Integral();
ZpW_JES[1][3][0] = (btag1__ZprimeWide3000__jec__plus->Integral() - btag1__ZprimeWide3000->Integral()) / btag1__ZprimeWide3000->Integral();
ZpW_JES[2][3][0] = (btag2__ZprimeWide3000__jec__plus->Integral() - btag2__ZprimeWide3000->Integral()) / btag2__ZprimeWide3000->Integral();
ZpW_JES[3][3][0] = (btag3__ZprimeWide3000__jec__plus->Integral() - btag3__ZprimeWide3000->Integral()) / btag3__ZprimeWide3000->Integral();
ZpW_JES[4][3][0] = (btag4__ZprimeWide3000__jec__plus->Integral() - btag4__ZprimeWide3000->Integral()) / btag4__ZprimeWide3000->Integral();
ZpW_JES[5][3][0] = (btag5__ZprimeWide3000__jec__plus->Integral() - btag5__ZprimeWide3000->Integral()) / btag5__ZprimeWide3000->Integral();
ZpW_JES[0][3][1] = (btag0__ZprimeWide3000__jec__minus->Integral() - btag0__ZprimeWide3000->Integral()) / btag0__ZprimeWide3000->Integral();
ZpW_JES[1][3][1] = (btag1__ZprimeWide3000__jec__minus->Integral() - btag1__ZprimeWide3000->Integral()) / btag1__ZprimeWide3000->Integral();
ZpW_JES[2][3][1] = (btag2__ZprimeWide3000__jec__minus->Integral() - btag2__ZprimeWide3000->Integral()) / btag2__ZprimeWide3000->Integral();
ZpW_JES[3][3][1] = (btag3__ZprimeWide3000__jec__minus->Integral() - btag3__ZprimeWide3000->Integral()) / btag3__ZprimeWide3000->Integral();
ZpW_JES[4][3][1] = (btag4__ZprimeWide3000__jec__minus->Integral() - btag4__ZprimeWide3000->Integral()) / btag4__ZprimeWide3000->Integral();
ZpW_JES[5][3][1] = (btag5__ZprimeWide3000__jec__minus->Integral() - btag5__ZprimeWide3000->Integral()) / btag5__ZprimeWide3000->Integral();

ZpW_PDF[0][0][0] = (btag0__ZprimeWide1000__pdf__plus->Integral() - btag0__ZprimeWide1000->Integral()) / btag0__ZprimeWide1000->Integral();
ZpW_PDF[1][0][0] = (btag1__ZprimeWide1000__pdf__plus->Integral() - btag1__ZprimeWide1000->Integral()) / btag1__ZprimeWide1000->Integral();
ZpW_PDF[2][0][0] = (btag2__ZprimeWide1000__pdf__plus->Integral() - btag2__ZprimeWide1000->Integral()) / btag2__ZprimeWide1000->Integral();
ZpW_PDF[3][0][0] = (btag3__ZprimeWide1000__pdf__plus->Integral() - btag3__ZprimeWide1000->Integral()) / btag3__ZprimeWide1000->Integral();
ZpW_PDF[4][0][0] = (btag4__ZprimeWide1000__pdf__plus->Integral() - btag4__ZprimeWide1000->Integral()) / btag4__ZprimeWide1000->Integral();
ZpW_PDF[5][0][0] = (btag5__ZprimeWide1000__pdf__plus->Integral() - btag5__ZprimeWide1000->Integral()) / btag5__ZprimeWide1000->Integral();
ZpW_PDF[0][0][1] = (btag0__ZprimeWide1000__pdf__minus->Integral() - btag0__ZprimeWide1000->Integral()) / btag0__ZprimeWide1000->Integral();
ZpW_PDF[1][0][1] = (btag1__ZprimeWide1000__pdf__minus->Integral() - btag1__ZprimeWide1000->Integral()) / btag1__ZprimeWide1000->Integral();
ZpW_PDF[2][0][1] = (btag2__ZprimeWide1000__pdf__minus->Integral() - btag2__ZprimeWide1000->Integral()) / btag2__ZprimeWide1000->Integral();
ZpW_PDF[3][0][1] = (btag3__ZprimeWide1000__pdf__minus->Integral() - btag3__ZprimeWide1000->Integral()) / btag3__ZprimeWide1000->Integral();
ZpW_PDF[4][0][1] = (btag4__ZprimeWide1000__pdf__minus->Integral() - btag4__ZprimeWide1000->Integral()) / btag4__ZprimeWide1000->Integral();
ZpW_PDF[5][0][1] = (btag5__ZprimeWide1000__pdf__minus->Integral() - btag5__ZprimeWide1000->Integral()) / btag5__ZprimeWide1000->Integral();

ZpW_PDF[0][1][0] = (btag0__ZprimeWide1500__pdf__plus->Integral() - btag0__ZprimeWide1500->Integral()) / btag0__ZprimeWide1500->Integral();
ZpW_PDF[1][1][0] = (btag1__ZprimeWide1500__pdf__plus->Integral() - btag1__ZprimeWide1500->Integral()) / btag1__ZprimeWide1500->Integral();
ZpW_PDF[2][1][0] = (btag2__ZprimeWide1500__pdf__plus->Integral() - btag2__ZprimeWide1500->Integral()) / btag2__ZprimeWide1500->Integral();
ZpW_PDF[3][1][0] = (btag3__ZprimeWide1500__pdf__plus->Integral() - btag3__ZprimeWide1500->Integral()) / btag3__ZprimeWide1500->Integral();
ZpW_PDF[4][1][0] = (btag4__ZprimeWide1500__pdf__plus->Integral() - btag4__ZprimeWide1500->Integral()) / btag4__ZprimeWide1500->Integral();
ZpW_PDF[5][1][0] = (btag5__ZprimeWide1500__pdf__plus->Integral() - btag5__ZprimeWide1500->Integral()) / btag5__ZprimeWide1500->Integral();
ZpW_PDF[0][1][1] = (btag0__ZprimeWide1500__pdf__minus->Integral() - btag0__ZprimeWide1500->Integral()) / btag0__ZprimeWide1500->Integral();
ZpW_PDF[1][1][1] = (btag1__ZprimeWide1500__pdf__minus->Integral() - btag1__ZprimeWide1500->Integral()) / btag1__ZprimeWide1500->Integral();
ZpW_PDF[2][1][1] = (btag2__ZprimeWide1500__pdf__minus->Integral() - btag2__ZprimeWide1500->Integral()) / btag2__ZprimeWide1500->Integral();
ZpW_PDF[3][1][1] = (btag3__ZprimeWide1500__pdf__minus->Integral() - btag3__ZprimeWide1500->Integral()) / btag3__ZprimeWide1500->Integral();
ZpW_PDF[4][1][1] = (btag4__ZprimeWide1500__pdf__minus->Integral() - btag4__ZprimeWide1500->Integral()) / btag4__ZprimeWide1500->Integral();
ZpW_PDF[5][1][1] = (btag5__ZprimeWide1500__pdf__minus->Integral() - btag5__ZprimeWide1500->Integral()) / btag5__ZprimeWide1500->Integral();

ZpW_PDF[0][2][0] = (btag0__ZprimeWide2000__pdf__plus->Integral() - btag0__ZprimeWide2000->Integral()) / btag0__ZprimeWide2000->Integral();
ZpW_PDF[1][2][0] = (btag1__ZprimeWide2000__pdf__plus->Integral() - btag1__ZprimeWide2000->Integral()) / btag1__ZprimeWide2000->Integral();
ZpW_PDF[2][2][0] = (btag2__ZprimeWide2000__pdf__plus->Integral() - btag2__ZprimeWide2000->Integral()) / btag2__ZprimeWide2000->Integral();
ZpW_PDF[3][2][0] = (btag3__ZprimeWide2000__pdf__plus->Integral() - btag3__ZprimeWide2000->Integral()) / btag3__ZprimeWide2000->Integral();
ZpW_PDF[4][2][0] = (btag4__ZprimeWide2000__pdf__plus->Integral() - btag4__ZprimeWide2000->Integral()) / btag4__ZprimeWide2000->Integral();
ZpW_PDF[5][2][0] = (btag5__ZprimeWide2000__pdf__plus->Integral() - btag5__ZprimeWide2000->Integral()) / btag5__ZprimeWide2000->Integral();
ZpW_PDF[0][2][1] = (btag0__ZprimeWide2000__pdf__minus->Integral() - btag0__ZprimeWide2000->Integral()) / btag0__ZprimeWide2000->Integral();
ZpW_PDF[1][2][1] = (btag1__ZprimeWide2000__pdf__minus->Integral() - btag1__ZprimeWide2000->Integral()) / btag1__ZprimeWide2000->Integral();
ZpW_PDF[2][2][1] = (btag2__ZprimeWide2000__pdf__minus->Integral() - btag2__ZprimeWide2000->Integral()) / btag2__ZprimeWide2000->Integral();
ZpW_PDF[3][2][1] = (btag3__ZprimeWide2000__pdf__minus->Integral() - btag3__ZprimeWide2000->Integral()) / btag3__ZprimeWide2000->Integral();
ZpW_PDF[4][2][1] = (btag4__ZprimeWide2000__pdf__minus->Integral() - btag4__ZprimeWide2000->Integral()) / btag4__ZprimeWide2000->Integral();
ZpW_PDF[5][2][1] = (btag5__ZprimeWide2000__pdf__minus->Integral() - btag5__ZprimeWide2000->Integral()) / btag5__ZprimeWide2000->Integral();

ZpW_PDF[0][3][0] = (btag0__ZprimeWide3000__pdf__plus->Integral() - btag0__ZprimeWide3000->Integral()) / btag0__ZprimeWide3000->Integral();
ZpW_PDF[1][3][0] = (btag1__ZprimeWide3000__pdf__plus->Integral() - btag1__ZprimeWide3000->Integral()) / btag1__ZprimeWide3000->Integral();
ZpW_PDF[2][3][0] = (btag2__ZprimeWide3000__pdf__plus->Integral() - btag2__ZprimeWide3000->Integral()) / btag2__ZprimeWide3000->Integral();
ZpW_PDF[3][3][0] = (btag3__ZprimeWide3000__pdf__plus->Integral() - btag3__ZprimeWide3000->Integral()) / btag3__ZprimeWide3000->Integral();
ZpW_PDF[4][3][0] = (btag4__ZprimeWide3000__pdf__plus->Integral() - btag4__ZprimeWide3000->Integral()) / btag4__ZprimeWide3000->Integral();
ZpW_PDF[5][3][0] = (btag5__ZprimeWide3000__pdf__plus->Integral() - btag5__ZprimeWide3000->Integral()) / btag5__ZprimeWide3000->Integral();
ZpW_PDF[0][3][1] = (btag0__ZprimeWide3000__pdf__minus->Integral() - btag0__ZprimeWide3000->Integral()) / btag0__ZprimeWide3000->Integral();
ZpW_PDF[1][3][1] = (btag1__ZprimeWide3000__pdf__minus->Integral() - btag1__ZprimeWide3000->Integral()) / btag1__ZprimeWide3000->Integral();
ZpW_PDF[2][3][1] = (btag2__ZprimeWide3000__pdf__minus->Integral() - btag2__ZprimeWide3000->Integral()) / btag2__ZprimeWide3000->Integral();
ZpW_PDF[3][3][1] = (btag3__ZprimeWide3000__pdf__minus->Integral() - btag3__ZprimeWide3000->Integral()) / btag3__ZprimeWide3000->Integral();
ZpW_PDF[4][3][1] = (btag4__ZprimeWide3000__pdf__minus->Integral() - btag4__ZprimeWide3000->Integral()) / btag4__ZprimeWide3000->Integral();
ZpW_PDF[5][3][1] = (btag5__ZprimeWide3000__pdf__minus->Integral() - btag5__ZprimeWide3000->Integral()) / btag5__ZprimeWide3000->Integral();






ZpW_btag[0][0][0] = (btag0__ZprimeWide1000__subjbtag__plus->Integral() - btag0__ZprimeWide1000->Integral()) / btag0__ZprimeWide1000->Integral();
ZpW_btag[1][0][0] = (btag1__ZprimeWide1000__subjbtag__plus->Integral() - btag1__ZprimeWide1000->Integral()) / btag1__ZprimeWide1000->Integral();
ZpW_btag[2][0][0] = (btag2__ZprimeWide1000__subjbtag__plus->Integral() - btag2__ZprimeWide1000->Integral()) / btag2__ZprimeWide1000->Integral();
ZpW_btag[3][0][0] = (btag3__ZprimeWide1000__subjbtag__plus->Integral() - btag3__ZprimeWide1000->Integral()) / btag3__ZprimeWide1000->Integral();
ZpW_btag[4][0][0] = (btag4__ZprimeWide1000__subjbtag__plus->Integral() - btag4__ZprimeWide1000->Integral()) / btag4__ZprimeWide1000->Integral();
ZpW_btag[5][0][0] = (btag5__ZprimeWide1000__subjbtag__plus->Integral() - btag5__ZprimeWide1000->Integral()) / btag5__ZprimeWide1000->Integral();
ZpW_btag[0][0][1] = (btag0__ZprimeWide1000__subjbtag__minus->Integral() - btag0__ZprimeWide1000->Integral()) / btag0__ZprimeWide1000->Integral();
ZpW_btag[1][0][1] = (btag1__ZprimeWide1000__subjbtag__minus->Integral() - btag1__ZprimeWide1000->Integral()) / btag1__ZprimeWide1000->Integral();
ZpW_btag[2][0][1] = (btag2__ZprimeWide1000__subjbtag__minus->Integral() - btag2__ZprimeWide1000->Integral()) / btag2__ZprimeWide1000->Integral();
ZpW_btag[3][0][1] = (btag3__ZprimeWide1000__subjbtag__minus->Integral() - btag3__ZprimeWide1000->Integral()) / btag3__ZprimeWide1000->Integral();
ZpW_btag[4][0][1] = (btag4__ZprimeWide1000__subjbtag__minus->Integral() - btag4__ZprimeWide1000->Integral()) / btag4__ZprimeWide1000->Integral();
ZpW_btag[5][0][1] = (btag5__ZprimeWide1000__subjbtag__minus->Integral() - btag5__ZprimeWide1000->Integral()) / btag5__ZprimeWide1000->Integral();

ZpW_btag[0][1][0] = (btag0__ZprimeWide1500__subjbtag__plus->Integral() - btag0__ZprimeWide1500->Integral()) / btag0__ZprimeWide1500->Integral();
ZpW_btag[1][1][0] = (btag1__ZprimeWide1500__subjbtag__plus->Integral() - btag1__ZprimeWide1500->Integral()) / btag1__ZprimeWide1500->Integral();
ZpW_btag[2][1][0] = (btag2__ZprimeWide1500__subjbtag__plus->Integral() - btag2__ZprimeWide1500->Integral()) / btag2__ZprimeWide1500->Integral();
ZpW_btag[3][1][0] = (btag3__ZprimeWide1500__subjbtag__plus->Integral() - btag3__ZprimeWide1500->Integral()) / btag3__ZprimeWide1500->Integral();
ZpW_btag[4][1][0] = (btag4__ZprimeWide1500__subjbtag__plus->Integral() - btag4__ZprimeWide1500->Integral()) / btag4__ZprimeWide1500->Integral();
ZpW_btag[5][1][0] = (btag5__ZprimeWide1500__subjbtag__plus->Integral() - btag5__ZprimeWide1500->Integral()) / btag5__ZprimeWide1500->Integral();
ZpW_btag[0][1][1] = (btag0__ZprimeWide1500__subjbtag__minus->Integral() - btag0__ZprimeWide1500->Integral()) / btag0__ZprimeWide1500->Integral();
ZpW_btag[1][1][1] = (btag1__ZprimeWide1500__subjbtag__minus->Integral() - btag1__ZprimeWide1500->Integral()) / btag1__ZprimeWide1500->Integral();
ZpW_btag[2][1][1] = (btag2__ZprimeWide1500__subjbtag__minus->Integral() - btag2__ZprimeWide1500->Integral()) / btag2__ZprimeWide1500->Integral();
ZpW_btag[3][1][1] = (btag3__ZprimeWide1500__subjbtag__minus->Integral() - btag3__ZprimeWide1500->Integral()) / btag3__ZprimeWide1500->Integral();
ZpW_btag[4][1][1] = (btag4__ZprimeWide1500__subjbtag__minus->Integral() - btag4__ZprimeWide1500->Integral()) / btag4__ZprimeWide1500->Integral();
ZpW_btag[5][1][1] = (btag5__ZprimeWide1500__subjbtag__minus->Integral() - btag5__ZprimeWide1500->Integral()) / btag5__ZprimeWide1500->Integral();

ZpW_btag[0][2][0] = (btag0__ZprimeWide2000__subjbtag__plus->Integral() - btag0__ZprimeWide2000->Integral()) / btag0__ZprimeWide2000->Integral();
ZpW_btag[1][2][0] = (btag1__ZprimeWide2000__subjbtag__plus->Integral() - btag1__ZprimeWide2000->Integral()) / btag1__ZprimeWide2000->Integral();
ZpW_btag[2][2][0] = (btag2__ZprimeWide2000__subjbtag__plus->Integral() - btag2__ZprimeWide2000->Integral()) / btag2__ZprimeWide2000->Integral();
ZpW_btag[3][2][0] = (btag3__ZprimeWide2000__subjbtag__plus->Integral() - btag3__ZprimeWide2000->Integral()) / btag3__ZprimeWide2000->Integral();
ZpW_btag[4][2][0] = (btag4__ZprimeWide2000__subjbtag__plus->Integral() - btag4__ZprimeWide2000->Integral()) / btag4__ZprimeWide2000->Integral();
ZpW_btag[5][2][0] = (btag5__ZprimeWide2000__subjbtag__plus->Integral() - btag5__ZprimeWide2000->Integral()) / btag5__ZprimeWide2000->Integral();
ZpW_btag[0][2][1] = (btag0__ZprimeWide2000__subjbtag__minus->Integral() - btag0__ZprimeWide2000->Integral()) / btag0__ZprimeWide2000->Integral();
ZpW_btag[1][2][1] = (btag1__ZprimeWide2000__subjbtag__minus->Integral() - btag1__ZprimeWide2000->Integral()) / btag1__ZprimeWide2000->Integral();
ZpW_btag[2][2][1] = (btag2__ZprimeWide2000__subjbtag__minus->Integral() - btag2__ZprimeWide2000->Integral()) / btag2__ZprimeWide2000->Integral();
ZpW_btag[3][2][1] = (btag3__ZprimeWide2000__subjbtag__minus->Integral() - btag3__ZprimeWide2000->Integral()) / btag3__ZprimeWide2000->Integral();
ZpW_btag[4][2][1] = (btag4__ZprimeWide2000__subjbtag__minus->Integral() - btag4__ZprimeWide2000->Integral()) / btag4__ZprimeWide2000->Integral();
ZpW_btag[5][2][1] = (btag5__ZprimeWide2000__subjbtag__minus->Integral() - btag5__ZprimeWide2000->Integral()) / btag5__ZprimeWide2000->Integral();

ZpW_btag[0][3][0] = (btag0__ZprimeWide3000__subjbtag__plus->Integral() - btag0__ZprimeWide3000->Integral()) / btag0__ZprimeWide3000->Integral();
ZpW_btag[1][3][0] = (btag1__ZprimeWide3000__subjbtag__plus->Integral() - btag1__ZprimeWide3000->Integral()) / btag1__ZprimeWide3000->Integral();
ZpW_btag[2][3][0] = (btag2__ZprimeWide3000__subjbtag__plus->Integral() - btag2__ZprimeWide3000->Integral()) / btag2__ZprimeWide3000->Integral();
ZpW_btag[3][3][0] = (btag3__ZprimeWide3000__subjbtag__plus->Integral() - btag3__ZprimeWide3000->Integral()) / btag3__ZprimeWide3000->Integral();
ZpW_btag[4][3][0] = (btag4__ZprimeWide3000__subjbtag__plus->Integral() - btag4__ZprimeWide3000->Integral()) / btag4__ZprimeWide3000->Integral();
ZpW_btag[5][3][0] = (btag5__ZprimeWide3000__subjbtag__plus->Integral() - btag5__ZprimeWide3000->Integral()) / btag5__ZprimeWide3000->Integral();
ZpW_btag[0][3][1] = (btag0__ZprimeWide3000__subjbtag__minus->Integral() - btag0__ZprimeWide3000->Integral()) / btag0__ZprimeWide3000->Integral();
ZpW_btag[1][3][1] = (btag1__ZprimeWide3000__subjbtag__minus->Integral() - btag1__ZprimeWide3000->Integral()) / btag1__ZprimeWide3000->Integral();
ZpW_btag[2][3][1] = (btag2__ZprimeWide3000__subjbtag__minus->Integral() - btag2__ZprimeWide3000->Integral()) / btag2__ZprimeWide3000->Integral();
ZpW_btag[3][3][1] = (btag3__ZprimeWide3000__subjbtag__minus->Integral() - btag3__ZprimeWide3000->Integral()) / btag3__ZprimeWide3000->Integral();
ZpW_btag[4][3][1] = (btag4__ZprimeWide3000__subjbtag__minus->Integral() - btag4__ZprimeWide3000->Integral()) / btag4__ZprimeWide3000->Integral();
ZpW_btag[5][3][1] = (btag5__ZprimeWide3000__subjbtag__minus->Integral() - btag5__ZprimeWide3000->Integral()) / btag5__ZprimeWide3000->Integral();











ZpW_JER[0][0][0] = (btag0__ZprimeWide1000__jer__plus->Integral() - btag0__ZprimeWide1000->Integral()) / btag0__ZprimeWide1000->Integral();
ZpW_JER[1][0][0] = (btag1__ZprimeWide1000__jer__plus->Integral() - btag1__ZprimeWide1000->Integral()) / btag1__ZprimeWide1000->Integral();
ZpW_JER[2][0][0] = (btag2__ZprimeWide1000__jer__plus->Integral() - btag2__ZprimeWide1000->Integral()) / btag2__ZprimeWide1000->Integral();
ZpW_JER[3][0][0] = (btag3__ZprimeWide1000__jer__plus->Integral() - btag3__ZprimeWide1000->Integral()) / btag3__ZprimeWide1000->Integral();
ZpW_JER[4][0][0] = (btag4__ZprimeWide1000__jer__plus->Integral() - btag4__ZprimeWide1000->Integral()) / btag4__ZprimeWide1000->Integral();
ZpW_JER[5][0][0] = (btag5__ZprimeWide1000__jer__plus->Integral() - btag5__ZprimeWide1000->Integral()) / btag5__ZprimeWide1000->Integral();
ZpW_JER[0][0][1] = (btag0__ZprimeWide1000__jer__minus->Integral() - btag0__ZprimeWide1000->Integral()) / btag0__ZprimeWide1000->Integral();
ZpW_JER[1][0][1] = (btag1__ZprimeWide1000__jer__minus->Integral() - btag1__ZprimeWide1000->Integral()) / btag1__ZprimeWide1000->Integral();
ZpW_JER[2][0][1] = (btag2__ZprimeWide1000__jer__minus->Integral() - btag2__ZprimeWide1000->Integral()) / btag2__ZprimeWide1000->Integral();
ZpW_JER[3][0][1] = (btag3__ZprimeWide1000__jer__minus->Integral() - btag3__ZprimeWide1000->Integral()) / btag3__ZprimeWide1000->Integral();
ZpW_JER[4][0][1] = (btag4__ZprimeWide1000__jer__minus->Integral() - btag4__ZprimeWide1000->Integral()) / btag4__ZprimeWide1000->Integral();
ZpW_JER[5][0][1] = (btag5__ZprimeWide1000__jer__minus->Integral() - btag5__ZprimeWide1000->Integral()) / btag5__ZprimeWide1000->Integral();

ZpW_JER[0][1][0] = (btag0__ZprimeWide1500__jer__plus->Integral() - btag0__ZprimeWide1500->Integral()) / btag0__ZprimeWide1500->Integral();
ZpW_JER[1][1][0] = (btag1__ZprimeWide1500__jer__plus->Integral() - btag1__ZprimeWide1500->Integral()) / btag1__ZprimeWide1500->Integral();
ZpW_JER[2][1][0] = (btag2__ZprimeWide1500__jer__plus->Integral() - btag2__ZprimeWide1500->Integral()) / btag2__ZprimeWide1500->Integral();
ZpW_JER[3][1][0] = (btag3__ZprimeWide1500__jer__plus->Integral() - btag3__ZprimeWide1500->Integral()) / btag3__ZprimeWide1500->Integral();
ZpW_JER[4][1][0] = (btag4__ZprimeWide1500__jer__plus->Integral() - btag4__ZprimeWide1500->Integral()) / btag4__ZprimeWide1500->Integral();
ZpW_JER[5][1][0] = (btag5__ZprimeWide1500__jer__plus->Integral() - btag5__ZprimeWide1500->Integral()) / btag5__ZprimeWide1500->Integral();
ZpW_JER[0][1][1] = (btag0__ZprimeWide1500__jer__minus->Integral() - btag0__ZprimeWide1500->Integral()) / btag0__ZprimeWide1500->Integral();
ZpW_JER[1][1][1] = (btag1__ZprimeWide1500__jer__minus->Integral() - btag1__ZprimeWide1500->Integral()) / btag1__ZprimeWide1500->Integral();
ZpW_JER[2][1][1] = (btag2__ZprimeWide1500__jer__minus->Integral() - btag2__ZprimeWide1500->Integral()) / btag2__ZprimeWide1500->Integral();
ZpW_JER[3][1][1] = (btag3__ZprimeWide1500__jer__minus->Integral() - btag3__ZprimeWide1500->Integral()) / btag3__ZprimeWide1500->Integral();
ZpW_JER[4][1][1] = (btag4__ZprimeWide1500__jer__minus->Integral() - btag4__ZprimeWide1500->Integral()) / btag4__ZprimeWide1500->Integral();
ZpW_JER[5][1][1] = (btag5__ZprimeWide1500__jer__minus->Integral() - btag5__ZprimeWide1500->Integral()) / btag5__ZprimeWide1500->Integral();

ZpW_JER[0][2][0] = (btag0__ZprimeWide2000__jer__plus->Integral() - btag0__ZprimeWide2000->Integral()) / btag0__ZprimeWide2000->Integral();
ZpW_JER[1][2][0] = (btag1__ZprimeWide2000__jer__plus->Integral() - btag1__ZprimeWide2000->Integral()) / btag1__ZprimeWide2000->Integral();
ZpW_JER[2][2][0] = (btag2__ZprimeWide2000__jer__plus->Integral() - btag2__ZprimeWide2000->Integral()) / btag2__ZprimeWide2000->Integral();
ZpW_JER[3][2][0] = (btag3__ZprimeWide2000__jer__plus->Integral() - btag3__ZprimeWide2000->Integral()) / btag3__ZprimeWide2000->Integral();
ZpW_JER[4][2][0] = (btag4__ZprimeWide2000__jer__plus->Integral() - btag4__ZprimeWide2000->Integral()) / btag4__ZprimeWide2000->Integral();
ZpW_JER[5][2][0] = (btag5__ZprimeWide2000__jer__plus->Integral() - btag5__ZprimeWide2000->Integral()) / btag5__ZprimeWide2000->Integral();
ZpW_JER[0][2][1] = (btag0__ZprimeWide2000__jer__minus->Integral() - btag0__ZprimeWide2000->Integral()) / btag0__ZprimeWide2000->Integral();
ZpW_JER[1][2][1] = (btag1__ZprimeWide2000__jer__minus->Integral() - btag1__ZprimeWide2000->Integral()) / btag1__ZprimeWide2000->Integral();
ZpW_JER[2][2][1] = (btag2__ZprimeWide2000__jer__minus->Integral() - btag2__ZprimeWide2000->Integral()) / btag2__ZprimeWide2000->Integral();
ZpW_JER[3][2][1] = (btag3__ZprimeWide2000__jer__minus->Integral() - btag3__ZprimeWide2000->Integral()) / btag3__ZprimeWide2000->Integral();
ZpW_JER[4][2][1] = (btag4__ZprimeWide2000__jer__minus->Integral() - btag4__ZprimeWide2000->Integral()) / btag4__ZprimeWide2000->Integral();
ZpW_JER[5][2][1] = (btag5__ZprimeWide2000__jer__minus->Integral() - btag5__ZprimeWide2000->Integral()) / btag5__ZprimeWide2000->Integral();

ZpW_JER[0][3][0] = (btag0__ZprimeWide3000__jer__plus->Integral() - btag0__ZprimeWide3000->Integral()) / btag0__ZprimeWide3000->Integral();
ZpW_JER[1][3][0] = (btag1__ZprimeWide3000__jer__plus->Integral() - btag1__ZprimeWide3000->Integral()) / btag1__ZprimeWide3000->Integral();
ZpW_JER[2][3][0] = (btag2__ZprimeWide3000__jer__plus->Integral() - btag2__ZprimeWide3000->Integral()) / btag2__ZprimeWide3000->Integral();
ZpW_JER[3][3][0] = (btag3__ZprimeWide3000__jer__plus->Integral() - btag3__ZprimeWide3000->Integral()) / btag3__ZprimeWide3000->Integral();
ZpW_JER[4][3][0] = (btag4__ZprimeWide3000__jer__plus->Integral() - btag4__ZprimeWide3000->Integral()) / btag4__ZprimeWide3000->Integral();
ZpW_JER[5][3][0] = (btag5__ZprimeWide3000__jer__plus->Integral() - btag5__ZprimeWide3000->Integral()) / btag5__ZprimeWide3000->Integral();
ZpW_JER[0][3][1] = (btag0__ZprimeWide3000__jer__minus->Integral() - btag0__ZprimeWide3000->Integral()) / btag0__ZprimeWide3000->Integral();
ZpW_JER[1][3][1] = (btag1__ZprimeWide3000__jer__minus->Integral() - btag1__ZprimeWide3000->Integral()) / btag1__ZprimeWide3000->Integral();
ZpW_JER[2][3][1] = (btag2__ZprimeWide3000__jer__minus->Integral() - btag2__ZprimeWide3000->Integral()) / btag2__ZprimeWide3000->Integral();
ZpW_JER[3][3][1] = (btag3__ZprimeWide3000__jer__minus->Integral() - btag3__ZprimeWide3000->Integral()) / btag3__ZprimeWide3000->Integral();
ZpW_JER[4][3][1] = (btag4__ZprimeWide3000__jer__minus->Integral() - btag4__ZprimeWide3000->Integral()) / btag4__ZprimeWide3000->Integral();
ZpW_JER[5][3][1] = (btag5__ZprimeWide3000__jer__minus->Integral() - btag5__ZprimeWide3000->Integral()) / btag5__ZprimeWide3000->Integral();




RSG[0][0][0] = btag0__RSgluon1000->Integral();
RSG[1][0][0] = btag1__RSgluon1000->Integral();
RSG[2][0][0] = btag2__RSgluon1000->Integral();
RSG[3][0][0] = btag3__RSgluon1000->Integral();
RSG[4][0][0] = btag4__RSgluon1000->Integral();
RSG[5][0][0] = btag5__RSgluon1000->Integral();
RSG[0][0][1] = sqrt(btag0__RSgluon1000->GetEntries()) / btag0__RSgluon1000->GetEntries();
RSG[1][0][1] = sqrt(btag1__RSgluon1000->GetEntries()) / btag1__RSgluon1000->GetEntries();
RSG[2][0][1] = sqrt(btag2__RSgluon1000->GetEntries()) / btag2__RSgluon1000->GetEntries();
RSG[3][0][1] = sqrt(btag3__RSgluon1000->GetEntries()) / btag3__RSgluon1000->GetEntries();
RSG[4][0][1] = sqrt(btag4__RSgluon1000->GetEntries()) / btag4__RSgluon1000->GetEntries();
RSG[5][0][1] = sqrt(btag5__RSgluon1000->GetEntries()) / btag5__RSgluon1000->GetEntries();

RSG[0][1][0] = btag0__RSgluon1500->Integral();
RSG[1][1][0] = btag1__RSgluon1500->Integral();
RSG[2][1][0] = btag2__RSgluon1500->Integral();
RSG[3][1][0] = btag3__RSgluon1500->Integral();
RSG[4][1][0] = btag4__RSgluon1500->Integral();
RSG[5][1][0] = btag5__RSgluon1500->Integral();
RSG[0][1][1] = sqrt(btag0__RSgluon1500->GetEntries()) / btag0__RSgluon1500->GetEntries();
RSG[1][1][1] = sqrt(btag1__RSgluon1500->GetEntries()) / btag1__RSgluon1500->GetEntries();
RSG[2][1][1] = sqrt(btag2__RSgluon1500->GetEntries()) / btag2__RSgluon1500->GetEntries();
RSG[3][1][1] = sqrt(btag3__RSgluon1500->GetEntries()) / btag3__RSgluon1500->GetEntries();
RSG[4][1][1] = sqrt(btag4__RSgluon1500->GetEntries()) / btag4__RSgluon1500->GetEntries();
RSG[5][1][1] = sqrt(btag5__RSgluon1500->GetEntries()) / btag5__RSgluon1500->GetEntries();

RSG[0][2][0] = btag0__RSgluon2000->Integral();
RSG[1][2][0] = btag1__RSgluon2000->Integral();
RSG[2][2][0] = btag2__RSgluon2000->Integral();
RSG[3][2][0] = btag3__RSgluon2000->Integral();
RSG[4][2][0] = btag4__RSgluon2000->Integral();
RSG[5][2][0] = btag5__RSgluon2000->Integral();
RSG[0][2][1] = sqrt(btag0__RSgluon2000->GetEntries()) / btag0__RSgluon2000->GetEntries();
RSG[1][2][1] = sqrt(btag1__RSgluon2000->GetEntries()) / btag1__RSgluon2000->GetEntries();
RSG[2][2][1] = sqrt(btag2__RSgluon2000->GetEntries()) / btag2__RSgluon2000->GetEntries();
RSG[3][2][1] = sqrt(btag3__RSgluon2000->GetEntries()) / btag3__RSgluon2000->GetEntries();
RSG[4][2][1] = sqrt(btag4__RSgluon2000->GetEntries()) / btag4__RSgluon2000->GetEntries();
RSG[5][2][1] = sqrt(btag5__RSgluon2000->GetEntries()) / btag5__RSgluon2000->GetEntries();

RSG[0][3][0] = btag0__RSgluon3000->Integral();
RSG[1][3][0] = btag1__RSgluon3000->Integral();
RSG[2][3][0] = btag2__RSgluon3000->Integral();
RSG[3][3][0] = btag3__RSgluon3000->Integral();
RSG[4][3][0] = btag4__RSgluon3000->Integral();
RSG[5][3][0] = btag5__RSgluon3000->Integral();
RSG[0][3][1] = sqrt(btag0__RSgluon3000->GetEntries()) / btag0__RSgluon3000->GetEntries();
RSG[1][3][1] = sqrt(btag1__RSgluon3000->GetEntries()) / btag1__RSgluon3000->GetEntries();
RSG[2][3][1] = sqrt(btag2__RSgluon3000->GetEntries()) / btag2__RSgluon3000->GetEntries();
RSG[3][3][1] = sqrt(btag3__RSgluon3000->GetEntries()) / btag3__RSgluon3000->GetEntries();
RSG[4][3][1] = sqrt(btag4__RSgluon3000->GetEntries()) / btag4__RSgluon3000->GetEntries();
RSG[5][3][1] = sqrt(btag5__RSgluon3000->GetEntries()) / btag5__RSgluon3000->GetEntries();

RSG_JES[0][0][0] = (btag0__RSgluon1000__jec__plus->Integral() - btag0__RSgluon1000->Integral()) / btag0__RSgluon1000->Integral();
RSG_JES[1][0][0] = (btag1__RSgluon1000__jec__plus->Integral() - btag1__RSgluon1000->Integral()) / btag1__RSgluon1000->Integral();
RSG_JES[2][0][0] = (btag2__RSgluon1000__jec__plus->Integral() - btag2__RSgluon1000->Integral()) / btag2__RSgluon1000->Integral();
RSG_JES[3][0][0] = (btag3__RSgluon1000__jec__plus->Integral() - btag3__RSgluon1000->Integral()) / btag3__RSgluon1000->Integral();
RSG_JES[4][0][0] = (btag4__RSgluon1000__jec__plus->Integral() - btag4__RSgluon1000->Integral()) / btag4__RSgluon1000->Integral();
RSG_JES[5][0][0] = (btag5__RSgluon1000__jec__plus->Integral() - btag5__RSgluon1000->Integral()) / btag5__RSgluon1000->Integral();
RSG_JES[0][0][1] = (btag0__RSgluon1000__jec__minus->Integral() - btag0__RSgluon1000->Integral()) / btag0__RSgluon1000->Integral();
RSG_JES[1][0][1] = (btag1__RSgluon1000__jec__minus->Integral() - btag1__RSgluon1000->Integral()) / btag1__RSgluon1000->Integral();
RSG_JES[2][0][1] = (btag2__RSgluon1000__jec__minus->Integral() - btag2__RSgluon1000->Integral()) / btag2__RSgluon1000->Integral();
RSG_JES[3][0][1] = (btag3__RSgluon1000__jec__minus->Integral() - btag3__RSgluon1000->Integral()) / btag3__RSgluon1000->Integral();
RSG_JES[4][0][1] = (btag4__RSgluon1000__jec__minus->Integral() - btag4__RSgluon1000->Integral()) / btag4__RSgluon1000->Integral();
RSG_JES[5][0][1] = (btag5__RSgluon1000__jec__minus->Integral() - btag5__RSgluon1000->Integral()) / btag5__RSgluon1000->Integral();

RSG_JES[0][1][0] = (btag0__RSgluon1500__jec__plus->Integral() - btag0__RSgluon1500->Integral()) / btag0__RSgluon1500->Integral();
RSG_JES[1][1][0] = (btag1__RSgluon1500__jec__plus->Integral() - btag1__RSgluon1500->Integral()) / btag1__RSgluon1500->Integral();
RSG_JES[2][1][0] = (btag2__RSgluon1500__jec__plus->Integral() - btag2__RSgluon1500->Integral()) / btag2__RSgluon1500->Integral();
RSG_JES[3][1][0] = (btag3__RSgluon1500__jec__plus->Integral() - btag3__RSgluon1500->Integral()) / btag3__RSgluon1500->Integral();
RSG_JES[4][1][0] = (btag4__RSgluon1500__jec__plus->Integral() - btag4__RSgluon1500->Integral()) / btag4__RSgluon1500->Integral();
RSG_JES[5][1][0] = (btag5__RSgluon1500__jec__plus->Integral() - btag5__RSgluon1500->Integral()) / btag5__RSgluon1500->Integral();
RSG_JES[0][1][1] = (btag0__RSgluon1500__jec__minus->Integral() - btag0__RSgluon1500->Integral()) / btag0__RSgluon1500->Integral();
RSG_JES[1][1][1] = (btag1__RSgluon1500__jec__minus->Integral() - btag1__RSgluon1500->Integral()) / btag1__RSgluon1500->Integral();
RSG_JES[2][1][1] = (btag2__RSgluon1500__jec__minus->Integral() - btag2__RSgluon1500->Integral()) / btag2__RSgluon1500->Integral();
RSG_JES[3][1][1] = (btag3__RSgluon1500__jec__minus->Integral() - btag3__RSgluon1500->Integral()) / btag3__RSgluon1500->Integral();
RSG_JES[4][1][1] = (btag4__RSgluon1500__jec__minus->Integral() - btag4__RSgluon1500->Integral()) / btag4__RSgluon1500->Integral();
RSG_JES[5][1][1] = (btag5__RSgluon1500__jec__minus->Integral() - btag5__RSgluon1500->Integral()) / btag5__RSgluon1500->Integral();

RSG_JES[0][2][0] = (btag0__RSgluon2000__jec__plus->Integral() - btag0__RSgluon2000->Integral()) / btag0__RSgluon2000->Integral();
RSG_JES[1][2][0] = (btag1__RSgluon2000__jec__plus->Integral() - btag1__RSgluon2000->Integral()) / btag1__RSgluon2000->Integral();
RSG_JES[2][2][0] = (btag2__RSgluon2000__jec__plus->Integral() - btag2__RSgluon2000->Integral()) / btag2__RSgluon2000->Integral();
RSG_JES[3][2][0] = (btag3__RSgluon2000__jec__plus->Integral() - btag3__RSgluon2000->Integral()) / btag3__RSgluon2000->Integral();
RSG_JES[4][2][0] = (btag4__RSgluon2000__jec__plus->Integral() - btag4__RSgluon2000->Integral()) / btag4__RSgluon2000->Integral();
RSG_JES[5][2][0] = (btag5__RSgluon2000__jec__plus->Integral() - btag5__RSgluon2000->Integral()) / btag5__RSgluon2000->Integral();
RSG_JES[0][2][1] = (btag0__RSgluon2000__jec__minus->Integral() - btag0__RSgluon2000->Integral()) / btag0__RSgluon2000->Integral();
RSG_JES[1][2][1] = (btag1__RSgluon2000__jec__minus->Integral() - btag1__RSgluon2000->Integral()) / btag1__RSgluon2000->Integral();
RSG_JES[2][2][1] = (btag2__RSgluon2000__jec__minus->Integral() - btag2__RSgluon2000->Integral()) / btag2__RSgluon2000->Integral();
RSG_JES[3][2][1] = (btag3__RSgluon2000__jec__minus->Integral() - btag3__RSgluon2000->Integral()) / btag3__RSgluon2000->Integral();
RSG_JES[4][2][1] = (btag4__RSgluon2000__jec__minus->Integral() - btag4__RSgluon2000->Integral()) / btag4__RSgluon2000->Integral();
RSG_JES[5][2][1] = (btag5__RSgluon2000__jec__minus->Integral() - btag5__RSgluon2000->Integral()) / btag5__RSgluon2000->Integral();

RSG_JES[0][3][0] = (btag0__RSgluon3000__jec__plus->Integral() - btag0__RSgluon3000->Integral()) / btag0__RSgluon3000->Integral();
RSG_JES[1][3][0] = (btag1__RSgluon3000__jec__plus->Integral() - btag1__RSgluon3000->Integral()) / btag1__RSgluon3000->Integral();
RSG_JES[2][3][0] = (btag2__RSgluon3000__jec__plus->Integral() - btag2__RSgluon3000->Integral()) / btag2__RSgluon3000->Integral();
RSG_JES[3][3][0] = (btag3__RSgluon3000__jec__plus->Integral() - btag3__RSgluon3000->Integral()) / btag3__RSgluon3000->Integral();
RSG_JES[4][3][0] = (btag4__RSgluon3000__jec__plus->Integral() - btag4__RSgluon3000->Integral()) / btag4__RSgluon3000->Integral();
RSG_JES[5][3][0] = (btag5__RSgluon3000__jec__plus->Integral() - btag5__RSgluon3000->Integral()) / btag5__RSgluon3000->Integral();
RSG_JES[0][3][1] = (btag0__RSgluon3000__jec__minus->Integral() - btag0__RSgluon3000->Integral()) / btag0__RSgluon3000->Integral();
RSG_JES[1][3][1] = (btag1__RSgluon3000__jec__minus->Integral() - btag1__RSgluon3000->Integral()) / btag1__RSgluon3000->Integral();
RSG_JES[2][3][1] = (btag2__RSgluon3000__jec__minus->Integral() - btag2__RSgluon3000->Integral()) / btag2__RSgluon3000->Integral();
RSG_JES[3][3][1] = (btag3__RSgluon3000__jec__minus->Integral() - btag3__RSgluon3000->Integral()) / btag3__RSgluon3000->Integral();
RSG_JES[4][3][1] = (btag4__RSgluon3000__jec__minus->Integral() - btag4__RSgluon3000->Integral()) / btag4__RSgluon3000->Integral();
RSG_JES[5][3][1] = (btag5__RSgluon3000__jec__minus->Integral() - btag5__RSgluon3000->Integral()) / btag5__RSgluon3000->Integral();


RSG_PDF[0][0][0] = (btag0__RSgluon1000__pdf__plus->Integral() - btag0__RSgluon1000->Integral()) / btag0__RSgluon1000->Integral();
RSG_PDF[1][0][0] = (btag1__RSgluon1000__pdf__plus->Integral() - btag1__RSgluon1000->Integral()) / btag1__RSgluon1000->Integral();
RSG_PDF[2][0][0] = (btag2__RSgluon1000__pdf__plus->Integral() - btag2__RSgluon1000->Integral()) / btag2__RSgluon1000->Integral();
RSG_PDF[3][0][0] = (btag3__RSgluon1000__pdf__plus->Integral() - btag3__RSgluon1000->Integral()) / btag3__RSgluon1000->Integral();
RSG_PDF[4][0][0] = (btag4__RSgluon1000__pdf__plus->Integral() - btag4__RSgluon1000->Integral()) / btag4__RSgluon1000->Integral();
RSG_PDF[5][0][0] = (btag5__RSgluon1000__pdf__plus->Integral() - btag5__RSgluon1000->Integral()) / btag5__RSgluon1000->Integral();
RSG_PDF[0][0][1] = (btag0__RSgluon1000__pdf__minus->Integral() - btag0__RSgluon1000->Integral()) / btag0__RSgluon1000->Integral();
RSG_PDF[1][0][1] = (btag1__RSgluon1000__pdf__minus->Integral() - btag1__RSgluon1000->Integral()) / btag1__RSgluon1000->Integral();
RSG_PDF[2][0][1] = (btag2__RSgluon1000__pdf__minus->Integral() - btag2__RSgluon1000->Integral()) / btag2__RSgluon1000->Integral();
RSG_PDF[3][0][1] = (btag3__RSgluon1000__pdf__minus->Integral() - btag3__RSgluon1000->Integral()) / btag3__RSgluon1000->Integral();
RSG_PDF[4][0][1] = (btag4__RSgluon1000__pdf__minus->Integral() - btag4__RSgluon1000->Integral()) / btag4__RSgluon1000->Integral();
RSG_PDF[5][0][1] = (btag5__RSgluon1000__pdf__minus->Integral() - btag5__RSgluon1000->Integral()) / btag5__RSgluon1000->Integral();

RSG_PDF[0][1][0] = (btag0__RSgluon1500__pdf__plus->Integral() - btag0__RSgluon1500->Integral()) / btag0__RSgluon1500->Integral();
RSG_PDF[1][1][0] = (btag1__RSgluon1500__pdf__plus->Integral() - btag1__RSgluon1500->Integral()) / btag1__RSgluon1500->Integral();
RSG_PDF[2][1][0] = (btag2__RSgluon1500__pdf__plus->Integral() - btag2__RSgluon1500->Integral()) / btag2__RSgluon1500->Integral();
RSG_PDF[3][1][0] = (btag3__RSgluon1500__pdf__plus->Integral() - btag3__RSgluon1500->Integral()) / btag3__RSgluon1500->Integral();
RSG_PDF[4][1][0] = (btag4__RSgluon1500__pdf__plus->Integral() - btag4__RSgluon1500->Integral()) / btag4__RSgluon1500->Integral();
RSG_PDF[5][1][0] = (btag5__RSgluon1500__pdf__plus->Integral() - btag5__RSgluon1500->Integral()) / btag5__RSgluon1500->Integral();
RSG_PDF[0][1][1] = (btag0__RSgluon1500__pdf__minus->Integral() - btag0__RSgluon1500->Integral()) / btag0__RSgluon1500->Integral();
RSG_PDF[1][1][1] = (btag1__RSgluon1500__pdf__minus->Integral() - btag1__RSgluon1500->Integral()) / btag1__RSgluon1500->Integral();
RSG_PDF[2][1][1] = (btag2__RSgluon1500__pdf__minus->Integral() - btag2__RSgluon1500->Integral()) / btag2__RSgluon1500->Integral();
RSG_PDF[3][1][1] = (btag3__RSgluon1500__pdf__minus->Integral() - btag3__RSgluon1500->Integral()) / btag3__RSgluon1500->Integral();
RSG_PDF[4][1][1] = (btag4__RSgluon1500__pdf__minus->Integral() - btag4__RSgluon1500->Integral()) / btag4__RSgluon1500->Integral();
RSG_PDF[5][1][1] = (btag5__RSgluon1500__pdf__minus->Integral() - btag5__RSgluon1500->Integral()) / btag5__RSgluon1500->Integral();

RSG_PDF[0][2][0] = (btag0__RSgluon2000__pdf__plus->Integral() - btag0__RSgluon2000->Integral()) / btag0__RSgluon2000->Integral();
RSG_PDF[1][2][0] = (btag1__RSgluon2000__pdf__plus->Integral() - btag1__RSgluon2000->Integral()) / btag1__RSgluon2000->Integral();
RSG_PDF[2][2][0] = (btag2__RSgluon2000__pdf__plus->Integral() - btag2__RSgluon2000->Integral()) / btag2__RSgluon2000->Integral();
RSG_PDF[3][2][0] = (btag3__RSgluon2000__pdf__plus->Integral() - btag3__RSgluon2000->Integral()) / btag3__RSgluon2000->Integral();
RSG_PDF[4][2][0] = (btag4__RSgluon2000__pdf__plus->Integral() - btag4__RSgluon2000->Integral()) / btag4__RSgluon2000->Integral();
RSG_PDF[5][2][0] = (btag5__RSgluon2000__pdf__plus->Integral() - btag5__RSgluon2000->Integral()) / btag5__RSgluon2000->Integral();
RSG_PDF[0][2][1] = (btag0__RSgluon2000__pdf__minus->Integral() - btag0__RSgluon2000->Integral()) / btag0__RSgluon2000->Integral();
RSG_PDF[1][2][1] = (btag1__RSgluon2000__pdf__minus->Integral() - btag1__RSgluon2000->Integral()) / btag1__RSgluon2000->Integral();
RSG_PDF[2][2][1] = (btag2__RSgluon2000__pdf__minus->Integral() - btag2__RSgluon2000->Integral()) / btag2__RSgluon2000->Integral();
RSG_PDF[3][2][1] = (btag3__RSgluon2000__pdf__minus->Integral() - btag3__RSgluon2000->Integral()) / btag3__RSgluon2000->Integral();
RSG_PDF[4][2][1] = (btag4__RSgluon2000__pdf__minus->Integral() - btag4__RSgluon2000->Integral()) / btag4__RSgluon2000->Integral();
RSG_PDF[5][2][1] = (btag5__RSgluon2000__pdf__minus->Integral() - btag5__RSgluon2000->Integral()) / btag5__RSgluon2000->Integral();

RSG_PDF[0][3][0] = (btag0__RSgluon3000__pdf__plus->Integral() - btag0__RSgluon3000->Integral()) / btag0__RSgluon3000->Integral();
RSG_PDF[1][3][0] = (btag1__RSgluon3000__pdf__plus->Integral() - btag1__RSgluon3000->Integral()) / btag1__RSgluon3000->Integral();
RSG_PDF[2][3][0] = (btag2__RSgluon3000__pdf__plus->Integral() - btag2__RSgluon3000->Integral()) / btag2__RSgluon3000->Integral();
RSG_PDF[3][3][0] = (btag3__RSgluon3000__pdf__plus->Integral() - btag3__RSgluon3000->Integral()) / btag3__RSgluon3000->Integral();
RSG_PDF[4][3][0] = (btag4__RSgluon3000__pdf__plus->Integral() - btag4__RSgluon3000->Integral()) / btag4__RSgluon3000->Integral();
RSG_PDF[5][3][0] = (btag5__RSgluon3000__pdf__plus->Integral() - btag5__RSgluon3000->Integral()) / btag5__RSgluon3000->Integral();
RSG_PDF[0][3][1] = (btag0__RSgluon3000__pdf__minus->Integral() - btag0__RSgluon3000->Integral()) / btag0__RSgluon3000->Integral();
RSG_PDF[1][3][1] = (btag1__RSgluon3000__pdf__minus->Integral() - btag1__RSgluon3000->Integral()) / btag1__RSgluon3000->Integral();
RSG_PDF[2][3][1] = (btag2__RSgluon3000__pdf__minus->Integral() - btag2__RSgluon3000->Integral()) / btag2__RSgluon3000->Integral();
RSG_PDF[3][3][1] = (btag3__RSgluon3000__pdf__minus->Integral() - btag3__RSgluon3000->Integral()) / btag3__RSgluon3000->Integral();
RSG_PDF[4][3][1] = (btag4__RSgluon3000__pdf__minus->Integral() - btag4__RSgluon3000->Integral()) / btag4__RSgluon3000->Integral();
RSG_PDF[5][3][1] = (btag5__RSgluon3000__pdf__minus->Integral() - btag5__RSgluon3000->Integral()) / btag5__RSgluon3000->Integral();





RSG_btag[0][0][0] = (btag0__RSgluon1000__subjbtag__plus->Integral() - btag0__RSgluon1000->Integral()) / btag0__RSgluon1000->Integral();
RSG_btag[1][0][0] = (btag1__RSgluon1000__subjbtag__plus->Integral() - btag1__RSgluon1000->Integral()) / btag1__RSgluon1000->Integral();
RSG_btag[2][0][0] = (btag2__RSgluon1000__subjbtag__plus->Integral() - btag2__RSgluon1000->Integral()) / btag2__RSgluon1000->Integral();
RSG_btag[3][0][0] = (btag3__RSgluon1000__subjbtag__plus->Integral() - btag3__RSgluon1000->Integral()) / btag3__RSgluon1000->Integral();
RSG_btag[4][0][0] = (btag4__RSgluon1000__subjbtag__plus->Integral() - btag4__RSgluon1000->Integral()) / btag4__RSgluon1000->Integral();
RSG_btag[5][0][0] = (btag5__RSgluon1000__subjbtag__plus->Integral() - btag5__RSgluon1000->Integral()) / btag5__RSgluon1000->Integral();
RSG_btag[0][0][1] = (btag0__RSgluon1000__subjbtag__minus->Integral() - btag0__RSgluon1000->Integral()) / btag0__RSgluon1000->Integral();
RSG_btag[1][0][1] = (btag1__RSgluon1000__subjbtag__minus->Integral() - btag1__RSgluon1000->Integral()) / btag1__RSgluon1000->Integral();
RSG_btag[2][0][1] = (btag2__RSgluon1000__subjbtag__minus->Integral() - btag2__RSgluon1000->Integral()) / btag2__RSgluon1000->Integral();
RSG_btag[3][0][1] = (btag3__RSgluon1000__subjbtag__minus->Integral() - btag3__RSgluon1000->Integral()) / btag3__RSgluon1000->Integral();
RSG_btag[4][0][1] = (btag4__RSgluon1000__subjbtag__minus->Integral() - btag4__RSgluon1000->Integral()) / btag4__RSgluon1000->Integral();
RSG_btag[5][0][1] = (btag5__RSgluon1000__subjbtag__minus->Integral() - btag5__RSgluon1000->Integral()) / btag5__RSgluon1000->Integral();

RSG_btag[0][1][0] = (btag0__RSgluon1500__subjbtag__plus->Integral() - btag0__RSgluon1500->Integral()) / btag0__RSgluon1500->Integral();
RSG_btag[1][1][0] = (btag1__RSgluon1500__subjbtag__plus->Integral() - btag1__RSgluon1500->Integral()) / btag1__RSgluon1500->Integral();
RSG_btag[2][1][0] = (btag2__RSgluon1500__subjbtag__plus->Integral() - btag2__RSgluon1500->Integral()) / btag2__RSgluon1500->Integral();
RSG_btag[3][1][0] = (btag3__RSgluon1500__subjbtag__plus->Integral() - btag3__RSgluon1500->Integral()) / btag3__RSgluon1500->Integral();
RSG_btag[4][1][0] = (btag4__RSgluon1500__subjbtag__plus->Integral() - btag4__RSgluon1500->Integral()) / btag4__RSgluon1500->Integral();
RSG_btag[5][1][0] = (btag5__RSgluon1500__subjbtag__plus->Integral() - btag5__RSgluon1500->Integral()) / btag5__RSgluon1500->Integral();
RSG_btag[0][1][1] = (btag0__RSgluon1500__subjbtag__minus->Integral() - btag0__RSgluon1500->Integral()) / btag0__RSgluon1500->Integral();
RSG_btag[1][1][1] = (btag1__RSgluon1500__subjbtag__minus->Integral() - btag1__RSgluon1500->Integral()) / btag1__RSgluon1500->Integral();
RSG_btag[2][1][1] = (btag2__RSgluon1500__subjbtag__minus->Integral() - btag2__RSgluon1500->Integral()) / btag2__RSgluon1500->Integral();
RSG_btag[3][1][1] = (btag3__RSgluon1500__subjbtag__minus->Integral() - btag3__RSgluon1500->Integral()) / btag3__RSgluon1500->Integral();
RSG_btag[4][1][1] = (btag4__RSgluon1500__subjbtag__minus->Integral() - btag4__RSgluon1500->Integral()) / btag4__RSgluon1500->Integral();
RSG_btag[5][1][1] = (btag5__RSgluon1500__subjbtag__minus->Integral() - btag5__RSgluon1500->Integral()) / btag5__RSgluon1500->Integral();

RSG_btag[0][2][0] = (btag0__RSgluon2000__subjbtag__plus->Integral() - btag0__RSgluon2000->Integral()) / btag0__RSgluon2000->Integral();
RSG_btag[1][2][0] = (btag1__RSgluon2000__subjbtag__plus->Integral() - btag1__RSgluon2000->Integral()) / btag1__RSgluon2000->Integral();
RSG_btag[2][2][0] = (btag2__RSgluon2000__subjbtag__plus->Integral() - btag2__RSgluon2000->Integral()) / btag2__RSgluon2000->Integral();
RSG_btag[3][2][0] = (btag3__RSgluon2000__subjbtag__plus->Integral() - btag3__RSgluon2000->Integral()) / btag3__RSgluon2000->Integral();
RSG_btag[4][2][0] = (btag4__RSgluon2000__subjbtag__plus->Integral() - btag4__RSgluon2000->Integral()) / btag4__RSgluon2000->Integral();
RSG_btag[5][2][0] = (btag5__RSgluon2000__subjbtag__plus->Integral() - btag5__RSgluon2000->Integral()) / btag5__RSgluon2000->Integral();
RSG_btag[0][2][1] = (btag0__RSgluon2000__subjbtag__minus->Integral() - btag0__RSgluon2000->Integral()) / btag0__RSgluon2000->Integral();
RSG_btag[1][2][1] = (btag1__RSgluon2000__subjbtag__minus->Integral() - btag1__RSgluon2000->Integral()) / btag1__RSgluon2000->Integral();
RSG_btag[2][2][1] = (btag2__RSgluon2000__subjbtag__minus->Integral() - btag2__RSgluon2000->Integral()) / btag2__RSgluon2000->Integral();
RSG_btag[3][2][1] = (btag3__RSgluon2000__subjbtag__minus->Integral() - btag3__RSgluon2000->Integral()) / btag3__RSgluon2000->Integral();
RSG_btag[4][2][1] = (btag4__RSgluon2000__subjbtag__minus->Integral() - btag4__RSgluon2000->Integral()) / btag4__RSgluon2000->Integral();
RSG_btag[5][2][1] = (btag5__RSgluon2000__subjbtag__minus->Integral() - btag5__RSgluon2000->Integral()) / btag5__RSgluon2000->Integral();

RSG_btag[0][3][0] = (btag0__RSgluon3000__subjbtag__plus->Integral() - btag0__RSgluon3000->Integral()) / btag0__RSgluon3000->Integral();
RSG_btag[1][3][0] = (btag1__RSgluon3000__subjbtag__plus->Integral() - btag1__RSgluon3000->Integral()) / btag1__RSgluon3000->Integral();
RSG_btag[2][3][0] = (btag2__RSgluon3000__subjbtag__plus->Integral() - btag2__RSgluon3000->Integral()) / btag2__RSgluon3000->Integral();
RSG_btag[3][3][0] = (btag3__RSgluon3000__subjbtag__plus->Integral() - btag3__RSgluon3000->Integral()) / btag3__RSgluon3000->Integral();
RSG_btag[4][3][0] = (btag4__RSgluon3000__subjbtag__plus->Integral() - btag4__RSgluon3000->Integral()) / btag4__RSgluon3000->Integral();
RSG_btag[5][3][0] = (btag5__RSgluon3000__subjbtag__plus->Integral() - btag5__RSgluon3000->Integral()) / btag5__RSgluon3000->Integral();
RSG_btag[0][3][1] = (btag0__RSgluon3000__subjbtag__minus->Integral() - btag0__RSgluon3000->Integral()) / btag0__RSgluon3000->Integral();
RSG_btag[1][3][1] = (btag1__RSgluon3000__subjbtag__minus->Integral() - btag1__RSgluon3000->Integral()) / btag1__RSgluon3000->Integral();
RSG_btag[2][3][1] = (btag2__RSgluon3000__subjbtag__minus->Integral() - btag2__RSgluon3000->Integral()) / btag2__RSgluon3000->Integral();
RSG_btag[3][3][1] = (btag3__RSgluon3000__subjbtag__minus->Integral() - btag3__RSgluon3000->Integral()) / btag3__RSgluon3000->Integral();
RSG_btag[4][3][1] = (btag4__RSgluon3000__subjbtag__minus->Integral() - btag4__RSgluon3000->Integral()) / btag4__RSgluon3000->Integral();
RSG_btag[5][3][1] = (btag5__RSgluon3000__subjbtag__minus->Integral() - btag5__RSgluon3000->Integral()) / btag5__RSgluon3000->Integral();




RSG_JER[0][0][0] = (btag0__RSgluon1000__jer__plus->Integral() - btag0__RSgluon1000->Integral()) / btag0__RSgluon1000->Integral();
RSG_JER[1][0][0] = (btag1__RSgluon1000__jer__plus->Integral() - btag1__RSgluon1000->Integral()) / btag1__RSgluon1000->Integral();
RSG_JER[2][0][0] = (btag2__RSgluon1000__jer__plus->Integral() - btag2__RSgluon1000->Integral()) / btag2__RSgluon1000->Integral();
RSG_JER[3][0][0] = (btag3__RSgluon1000__jer__plus->Integral() - btag3__RSgluon1000->Integral()) / btag3__RSgluon1000->Integral();
RSG_JER[4][0][0] = (btag4__RSgluon1000__jer__plus->Integral() - btag4__RSgluon1000->Integral()) / btag4__RSgluon1000->Integral();
RSG_JER[5][0][0] = (btag5__RSgluon1000__jer__plus->Integral() - btag5__RSgluon1000->Integral()) / btag5__RSgluon1000->Integral();
RSG_JER[0][0][1] = (btag0__RSgluon1000__jer__minus->Integral() - btag0__RSgluon1000->Integral()) / btag0__RSgluon1000->Integral();
RSG_JER[1][0][1] = (btag1__RSgluon1000__jer__minus->Integral() - btag1__RSgluon1000->Integral()) / btag1__RSgluon1000->Integral();
RSG_JER[2][0][1] = (btag2__RSgluon1000__jer__minus->Integral() - btag2__RSgluon1000->Integral()) / btag2__RSgluon1000->Integral();
RSG_JER[3][0][1] = (btag3__RSgluon1000__jer__minus->Integral() - btag3__RSgluon1000->Integral()) / btag3__RSgluon1000->Integral();
RSG_JER[4][0][1] = (btag4__RSgluon1000__jer__minus->Integral() - btag4__RSgluon1000->Integral()) / btag4__RSgluon1000->Integral();
RSG_JER[5][0][1] = (btag5__RSgluon1000__jer__minus->Integral() - btag5__RSgluon1000->Integral()) / btag5__RSgluon1000->Integral();

RSG_JER[0][1][0] = (btag0__RSgluon1500__jer__plus->Integral() - btag0__RSgluon1500->Integral()) / btag0__RSgluon1500->Integral();
RSG_JER[1][1][0] = (btag1__RSgluon1500__jer__plus->Integral() - btag1__RSgluon1500->Integral()) / btag1__RSgluon1500->Integral();
RSG_JER[2][1][0] = (btag2__RSgluon1500__jer__plus->Integral() - btag2__RSgluon1500->Integral()) / btag2__RSgluon1500->Integral();
RSG_JER[3][1][0] = (btag3__RSgluon1500__jer__plus->Integral() - btag3__RSgluon1500->Integral()) / btag3__RSgluon1500->Integral();
RSG_JER[4][1][0] = (btag4__RSgluon1500__jer__plus->Integral() - btag4__RSgluon1500->Integral()) / btag4__RSgluon1500->Integral();
RSG_JER[5][1][0] = (btag5__RSgluon1500__jer__plus->Integral() - btag5__RSgluon1500->Integral()) / btag5__RSgluon1500->Integral();
RSG_JER[0][1][1] = (btag0__RSgluon1500__jer__minus->Integral() - btag0__RSgluon1500->Integral()) / btag0__RSgluon1500->Integral();
RSG_JER[1][1][1] = (btag1__RSgluon1500__jer__minus->Integral() - btag1__RSgluon1500->Integral()) / btag1__RSgluon1500->Integral();
RSG_JER[2][1][1] = (btag2__RSgluon1500__jer__minus->Integral() - btag2__RSgluon1500->Integral()) / btag2__RSgluon1500->Integral();
RSG_JER[3][1][1] = (btag3__RSgluon1500__jer__minus->Integral() - btag3__RSgluon1500->Integral()) / btag3__RSgluon1500->Integral();
RSG_JER[4][1][1] = (btag4__RSgluon1500__jer__minus->Integral() - btag4__RSgluon1500->Integral()) / btag4__RSgluon1500->Integral();
RSG_JER[5][1][1] = (btag5__RSgluon1500__jer__minus->Integral() - btag5__RSgluon1500->Integral()) / btag5__RSgluon1500->Integral();

RSG_JER[0][2][0] = (btag0__RSgluon2000__jer__plus->Integral() - btag0__RSgluon2000->Integral()) / btag0__RSgluon2000->Integral();
RSG_JER[1][2][0] = (btag1__RSgluon2000__jer__plus->Integral() - btag1__RSgluon2000->Integral()) / btag1__RSgluon2000->Integral();
RSG_JER[2][2][0] = (btag2__RSgluon2000__jer__plus->Integral() - btag2__RSgluon2000->Integral()) / btag2__RSgluon2000->Integral();
RSG_JER[3][2][0] = (btag3__RSgluon2000__jer__plus->Integral() - btag3__RSgluon2000->Integral()) / btag3__RSgluon2000->Integral();
RSG_JER[4][2][0] = (btag4__RSgluon2000__jer__plus->Integral() - btag4__RSgluon2000->Integral()) / btag4__RSgluon2000->Integral();
RSG_JER[5][2][0] = (btag5__RSgluon2000__jer__plus->Integral() - btag5__RSgluon2000->Integral()) / btag5__RSgluon2000->Integral();
RSG_JER[0][2][1] = (btag0__RSgluon2000__jer__minus->Integral() - btag0__RSgluon2000->Integral()) / btag0__RSgluon2000->Integral();
RSG_JER[1][2][1] = (btag1__RSgluon2000__jer__minus->Integral() - btag1__RSgluon2000->Integral()) / btag1__RSgluon2000->Integral();
RSG_JER[2][2][1] = (btag2__RSgluon2000__jer__minus->Integral() - btag2__RSgluon2000->Integral()) / btag2__RSgluon2000->Integral();
RSG_JER[3][2][1] = (btag3__RSgluon2000__jer__minus->Integral() - btag3__RSgluon2000->Integral()) / btag3__RSgluon2000->Integral();
RSG_JER[4][2][1] = (btag4__RSgluon2000__jer__minus->Integral() - btag4__RSgluon2000->Integral()) / btag4__RSgluon2000->Integral();
RSG_JER[5][2][1] = (btag5__RSgluon2000__jer__minus->Integral() - btag5__RSgluon2000->Integral()) / btag5__RSgluon2000->Integral();

RSG_JER[0][3][0] = (btag0__RSgluon3000__jer__plus->Integral() - btag0__RSgluon3000->Integral()) / btag0__RSgluon3000->Integral();
RSG_JER[1][3][0] = (btag1__RSgluon3000__jer__plus->Integral() - btag1__RSgluon3000->Integral()) / btag1__RSgluon3000->Integral();
RSG_JER[2][3][0] = (btag2__RSgluon3000__jer__plus->Integral() - btag2__RSgluon3000->Integral()) / btag2__RSgluon3000->Integral();
RSG_JER[3][3][0] = (btag3__RSgluon3000__jer__plus->Integral() - btag3__RSgluon3000->Integral()) / btag3__RSgluon3000->Integral();
RSG_JER[4][3][0] = (btag4__RSgluon3000__jer__plus->Integral() - btag4__RSgluon3000->Integral()) / btag4__RSgluon3000->Integral();
RSG_JER[5][3][0] = (btag5__RSgluon3000__jer__plus->Integral() - btag5__RSgluon3000->Integral()) / btag5__RSgluon3000->Integral();
RSG_JER[0][3][1] = (btag0__RSgluon3000__jer__minus->Integral() - btag0__RSgluon3000->Integral()) / btag0__RSgluon3000->Integral();
RSG_JER[1][3][1] = (btag1__RSgluon3000__jer__minus->Integral() - btag1__RSgluon3000->Integral()) / btag1__RSgluon3000->Integral();
RSG_JER[2][3][1] = (btag2__RSgluon3000__jer__minus->Integral() - btag2__RSgluon3000->Integral()) / btag2__RSgluon3000->Integral();
RSG_JER[3][3][1] = (btag3__RSgluon3000__jer__minus->Integral() - btag3__RSgluon3000->Integral()) / btag3__RSgluon3000->Integral();
RSG_JER[4][3][1] = (btag4__RSgluon3000__jer__minus->Integral() - btag4__RSgluon3000->Integral()) / btag4__RSgluon3000->Integral();
RSG_JER[5][3][1] = (btag5__RSgluon3000__jer__minus->Integral() - btag5__RSgluon3000->Integral()) / btag5__RSgluon3000->Integral();

*/



for (int cat = 0; cat < 6; cat++){

	cout.precision(1);

	cout << "Category " << cat << endl << endl << endl << endl;
	cout << std::fixed << "Statistics &  " <<    100*ttbar[cat][1] << "  &  " <<
				       100*qcd[cat][1] << " & " << 
				       100*ZpN[cat][0][1] << " & " << 
				       100*ZpN[cat][1][1] << " & " << 
				       100*ZpN[cat][2][1] << " & " << 
				       100*ZpN[cat][3][1] << " & " << 
				        " \\\\ [0.5ex]" << endl; 

	cout << std::fixed << "Jet Energy Scale & " <<
							"$^{" << 100*ttbar_JES[cat][0] << "}_{" << 100*(ttbar_JES[cat][1]) <<  "}$ & " <<
							" & " <<
							"$^{" << 100*ZpN_JES[cat][0][0] << "}_{" << 100*(ZpN_JES[cat][0][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_JES[cat][1][0] << "}_{" << 100*(ZpN_JES[cat][1][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_JES[cat][2][0] << "}_{" << 100*(ZpN_JES[cat][2][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_JES[cat][3][0] << "}_{" << 100*(ZpN_JES[cat][3][1]) <<  "}$  " <<
							  "\\\\ [0.5ex]" << endl;
 

	cout << std::fixed << "Jet Energy Resolution & " <<
							" & " <<
							" & " <<
							"$^{" << 100*ZpN_JER[cat][0][0] << "}_{" << 100*(ZpN_JER[cat][0][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_JER[cat][1][0] << "}_{" << 100*(ZpN_JER[cat][1][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_JER[cat][2][0] << "}_{" << 100*(ZpN_JER[cat][2][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_JER[cat][3][0] << "}_{" << 100*(ZpN_JER[cat][3][1]) <<  "}$  " <<
							  "\\\\ [0.5ex]" << endl;
 
	cout << std::fixed << "b-tag Scale Factor & " << 
							"$^{" << 100*ttbar_btag[cat][0] << "}_{" << 100*(ttbar_btag[cat][1]) <<  "}$ & " <<
							" & " <<
							"$^{" << 100*ZpN_btag[cat][0][0] << "}_{" << 100*(ZpN_btag[cat][0][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_btag[cat][1][0] << "}_{" << 100*(ZpN_btag[cat][1][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_btag[cat][2][0] << "}_{" << 100*(ZpN_btag[cat][2][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_btag[cat][3][0] << "}_{" << 100*(ZpN_btag[cat][3][1]) <<  "}$  " <<
							  " \\\\ [0.5ex]" << endl;
 

	cout << std::fixed << "top-tag Scale Factor  & " << " 20.2 & & 20.2 & 20.2 & 20.2 & 20.2  \\\\ [0.5ex]" << endl;

//	cout << std::fixed << "QCD Mistag Matrix & & " << 100*qcd_mis[cat][1] << " & & & & & & & & & & & & \\\\ [0.5ex]" << endl;

	cout << std::fixed << "\\ttbar Cross Section & " << " 15 & & & & & \\\\ [0.5ex]" << endl;
	
	cout << std::fixed << "\\ttbar $Q^2$ Scale & " << "$^{" << 100*ttbar_Q2[cat][0] << "}_{" << 100*ttbar_Q2[cat][1] << "}$  & & & & & & & & & & & & & \\\\ [0.5ex]" << endl;

	cout << std::fixed << "Luminosity & " << " 2.7 & & 2.7 & 2.7 & 2.7 & 2.7  \\\\ [0.5ex]" << endl;

//	cout << std::fixed << "Trigger Efficiency & " << " 2 & & 2 & 2 & 2 & 2 & 2 & 2 & 2 & 2 & 2 & 2 & 2 & 2 \\\\ [0.5ex]" << endl;

	
	cout << std::fixed << "Parton Distribution Functions & " <<
							"$^{" << 100*ttbar_PDF[cat][0] << "}_{" << 100*(ttbar_PDF[cat][1]) <<  "}$ & " <<
							" & " <<
							"$^{" << 100*ZpN_PDF[cat][0][0] << "}_{" << 100*(ZpN_PDF[cat][0][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_PDF[cat][1][0] << "}_{" << 100*(ZpN_PDF[cat][1][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_PDF[cat][2][0] << "}_{" << 100*(ZpN_PDF[cat][2][1]) <<  "}$ & " <<
							"$^{" << 100*ZpN_PDF[cat][3][0] << "}_{" << 100*(ZpN_PDF[cat][3][1]) <<  "}$  " <<
							  " \\\\ [0.5ex]" << endl;

	cout << std::fixed << " Modified Mass & " << "  & " << "$^{" << 100*qcd_modMass[cat][0] << "}_{" << 100*qcd_modMass[cat][1] <<  "}$ &  &  &  &   \\\\ [0.5ex]" << endl; 

	cout << std::fixed << " Closure Test & " << "  & " << "$^{" << 100*qcd_closure[cat][0] << "}_{" << 100*qcd_closure[cat][1] <<  "}$ &  &  &  &   \\\\ [0.5ex]" << endl; 

	//cout << std::fixed << "\\ttbar $p_T$ Reweighting & " << "$^{" << 100*ttbar_toppt[cat][0] << "}_{" << 100*ttbar_toppt[cat][1] << "}$  & & & & & & & & & & & & & \\\\ [0.5ex]" << endl;

	cout << endl << endl << endl << endl << endl << endl << endl;



}









}




