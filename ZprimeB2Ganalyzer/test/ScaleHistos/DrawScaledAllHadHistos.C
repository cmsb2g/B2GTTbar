{
  //cutflow
  //draw("cutflow","Cutflow","cutflow > -1","cutflow",10,0,10, 0.241, 0.868,0);



  //Jet pt spectra - pt > 400 GeV, abs(eta) < 2.4
  /*draw("topTagJet0_pt","Leading Jet p_{T} [GeV]","cutflow==1","leadingJetPt",200,0,2000, 0.141, 0.868,0);
  draw("topTagJet1_pt","Subleading Jet p_{T} [GeV]","cutflow==2","subLeadingJetPt",200,0,2000, 0.141, 0.868,0);

  //Jet pt spectra - pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV
  draw("topTagJet0_pt","Leading Jet p_{T} [GeV]","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210","leadingJetPt_softDropMass110to210",200,0,2000, 0.141, 0.868, 1);
  draw("topTagJet1_pt","Subleading Jet p_{T} [GeV]","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210","subLeadingJetPt_softDropMass110to210",200,0,2000, 0.141, 0.868, 1);

  //Jet pt spectra - pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, tau3/tau2 < 0.5
  draw("topTagJet0_pt","Leading Jet p_{T} [GeV]","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210 && topTagJet0_nSubjettiness < 0.5","leadingJetPt_softDropMass110to210_nSubjettiness0p5",200,0,2000, 0.141, 0.868, 3);
  draw("topTagJet1_pt","Subleading Jet p_{T} [GeV]","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210 && topTagJet1_nSubjettiness < 0.5","subLeadingJetPt_softDropMass110to210_nSubjettiness0p5",200,0,2000, 0.141, 0.868, 3);

  //Jet pt spectra - pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, tau3/tau2 < 0.61
  draw("topTagJet0_pt","Leading Jet p_{T} [GeV]","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210 && topTagJet0_nSubjettiness < 0.61","leadingJetPt_softDropMass110to210_nSubjettiness0p61",200,0,2000, 0.141, 0.868, 5);
  draw("topTagJet1_pt","Subleading Jet p_{T} [GeV]","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210 && topTagJet1_nSubjettiness < 0.61","subLeadingJetPt_softDropMass110to210_nSubjettiness0p61",200,0,2000, 0.141, 0.868, 5);
  
  //Jet pt spectra - pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, tau3/tau2 < 0.61, CMS subjet b-tag > 0.762
  draw("topTagJet0_pt","Leading Jet p_{T} [GeV]","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210 && topTagJet0_nSubjettiness < 0.61 && topTagJet0_maxSoftDropSubjetbtag > 0.762","leadingJetPt_softDropMass110to210_nSubjettiness0p61_btag0p762",200,0,2000, 0.141, 0.868, 13);
  draw("topTagJet1_pt","Subleading Jet p_{T} [GeV]","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210 && topTagJet1_nSubjettiness < 0.61 && topTagJet1_maxSoftDropSubjetbtag > 0.762","subLeadingJetPt_softDropMass110to210_nSubjettiness0p61_btag0p762",200,0,2000, 0.141, 0.868, 13);
  */

  
  //Jet eta spectra - pt > 400 GeV, abs(eta) < 2.4
  /*draw("topTagJet0_eta","Leading Jet #eta","cutflow==1","leadingJetEta",50,-2.5,2.5, 0.141, 0.868,0);
  draw("topTagJet1_eta","Subleading Jet #eta","cutflow==2","subLeadingJetEta",50,-2.5,2.5, 0.141, 0.868,0);
  


  //Jet tau32 spectra - pt > 400 GeV, abs(eta) < 2.4
  draw("topTagJet0_nSubjettiness","Leading Jet #tau_{3}/#tau_{2}","cutflow==1","leadingJetNsubjettiness",100,0,1, 0.141, 0.868, 0);
  draw("topTagJet1_nSubjettiness","Subleading Jet #tau_{3}/#tau_{2}","cutflow==2","subLeadingJetNsubjettiness",100,0,1, 0.141, 0.868, 0);
 
  //Jet tau32 spectra - pt > 400 GeV, 110 GeV < Soft Drop Mass < 210 GeV, abs(eta) < 2.4
  draw("topTagJet0_nSubjettiness","Leading Jet #tau_{3}/#tau_{2}","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210","leadingJetNsubjettiness_softDropMass110to210",100,0,1, 0.141, 0.868, 1);
  draw("topTagJet1_nSubjettiness","Subleading Jet #tau_{3}/#tau_{2}","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210","subLeadingJetNsubjettiness_softDropMass110to210",100,0,1, 0.141, 0.868, 1);

  //Jet tau32 spectra - pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, CMS subjet b-tag > 0.762
  draw("topTagJet0_nSubjettiness","Leading Jet #tau_{3}/#tau_{2}","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210 && topTagJet0_maxSubjetbtag > 0.762","leadingJetNsubjettiness_softDropMass110to210_btag0p762",100,0,1, 0.141, 0.868, 9);
  draw("topTagJet1_nSubjettiness","Subleading Jet #tau_{3}/#tau_{2}","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210 && topTagJet1_maxSubjetbtag > 0.762","subLeadingJetNsubjettiness_softDropMass110to210_btag0p762",100,0,1, 0.141, 0.868, 9);
  


  //Jet subjet b-tag spectra - pt > 400 GeV, abs(eta) < 2.4
  draw("topTagJet0_maxSubjetbtag","Leading Jet CMSTT subjet b-tag score","cutflow==1","leadingJetCMSTTsubjetbtag",100,0,1, 0.141, 0.868, 0);
  draw("topTagJet1_maxSubjetbtag","Subleading Jet CMSTT subjet b-tag score","cutflow==2","subLeadingJetCMSTTsubjetbtag",100,0,1, 0.141, 0.868, 0);
 
  //Jet subjet b-tag spectra - pt > 400 GeV, 110 GeV < Soft Drop Mass < 210 GeV, abs(eta) < 2.4
  draw("topTagJet0_maxSubjetbtag","Leading Jet CMSTT subjet b-tag score","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210","leadingJetCMSTTsubjetbtag_softDropMass110to210",100,0,1, 0.141, 0.868, 1);
  draw("topTagJet1_maxSubjetbtag","Subleading Jet CMSTT subjet b-tag score","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210","subLeadingJetCMSTTsubjetbtag_softDropMass110to210",100,0,1, 0.141, 0.868, 1);

  //Jet subjet b-tag spectra - pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, tau3/tau2 < 0.5
  draw("topTagJet0_maxSubjetbtag","Leading Jet CMSTT subjet b-tag score","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210 && topTagJet0_nSubjettiness < 0.5","leadingJetCMSTTsubjetbtag_softDropMass110to210_nSubjettiness0p5",100,0,1, 0.141, 0.868, 3);
  draw("topTagJet1_maxSubjetbtag","Subleading Jet CMSTT subjet b-tag score","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210 && topTagJet1_nSubjettiness < 0.5","subLeadingJetCMSTTsubjetbtag_softDropMass110to210_nSubjettiness0p5",100,0,1, 0.141, 0.868, 3);

  //Jet subjet b-tag spectra - pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, tau3/tau2 < 0.61
  draw("topTagJet0_maxSubjetbtag","Leading Jet CMSTT subjet b-tag score","cutflow==1 && topTagJet0_softDropMass > 110 && topTagJet0_softDropMass < 210 && topTagJet0_nSubjettiness < 0.61","leadingJetCMSTTsubjetbtag_softDropMass110to210_nSubjettiness0p61",100,0,1, 0.141, 0.868, 5);
  draw("topTagJet1_maxSubjetbtag","Subleading Jet CMSTT subjet b-tag score","cutflow==2 && topTagJet1_softDropMass > 110 && topTagJet1_softDropMass < 210 && topTagJet1_nSubjettiness < 0.61","subLeadingJetCMSTTsubjetbtag_softDropMass110to210_nSubjettiness0p61",100,0,1, 0.141, 0.868, 5);

 
  
  //Jet Soft Drop Mass spectra - pt > 400 GeV, abs(eta) < 2.4
  draw("topTagJet0_softDropMass","Leading Jet Soft Drop Mass [GeV]","cutflow==1","leadingJetSoftDropMass",30,0,300, 0.141, 0.868, 0);
  draw("topTagJet1_softDropMass","Subleading Jet Soft Drop Mass [GeV]","cutflow==2","subLeadingJetSoftDropMass",30,0,300, 0.141, 0.868, 0);

  //Jet Soft Drop Mass spectra - pt > 400 GeV, abs(eta) < 2.4, tau3/tau2 < 0.5
  draw("topTagJet0_softDropMass","Leading Jet Soft Drop Mass [GeV]","cutflow==1 && topTagJet0_nSubjettiness < 0.5","leadingJetSoftDropMass_nSubjettiness0p5",30,0,300, 0.141, 0.868, 2);
  draw("topTagJet1_softDropMass","Subleading Jet Soft Drop Mass [GeV]","cutflow==2 && topTagJet1_nSubjettiness < 0.5","subLeadingJetSoftDropMass_nSubjettiness0p5",30,0,300, 0.141, 0.868, 2);

  //Jet Soft Drop Mass spectra - pt > 400 GeV, abs(eta) < 2.4, tau3/tau2 < 0.61
  draw("topTagJet0_softDropMass","Leading Jet Soft Drop Mass [GeV]","cutflow==1 && topTagJet0_nSubjettiness < 0.61","leadingJetSoftDropMass_nSubjettiness0p61",30,0,300, 0.141, 0.868, 4);
  draw("topTagJet1_softDropMass","Subleading Jet Soft Drop Mass [GeV]","cutflow==2 && topTagJet1_nSubjettiness < 0.61","subLeadingJetSoftDropMass_nSubjettiness0p61",30,0,300, 0.141, 0.868, 4);

  //Jet Soft Drop Mass spectra - pt > 400 GeV, abs(eta) < 2.4, tau3/tau2 < 0.61, CMS subjet b-tag > 0.762
  draw("topTagJet0_softDropMass","Leading Jet Soft Drop Mass [GeV]","cutflow==1 && topTagJet0_nSubjettiness < 0.61 && topTagJet0_maxSoftDropSubjetbtag > 0.762 && topTagJet0_maxSoftDropSubjetbtag <= 1.0","leadingJetSoftDropMass_nSubjettiness0p61_softDropBtag0p762",30,0,300, 0.141, 0.868, 12);
  draw("topTagJet1_softDropMass","Subleading Jet Soft Drop Mass [GeV]","cutflow==2 && topTagJet1_nSubjettiness < 0.61 && topTagJet1_maxSoftDropSubjetbtag > 0.762 && topTagJet1_maxSoftDropSubjetbtag <= 1.0","subLeadingJetSoftDropMass_nSubjettiness0p61_softDropBtag0p762",30,0,300, 0.141, 0.868, 12);*/
  
  

  //Z' Soft Drop Mass - both jets: pt > 400 GeV, abs(eta) < 2.4
  draw("softDrop_Z_mass","Soft Drop t#bar{t} Mass [GeV]","cutflow==2","ZprimeSoftDropMass_noMassWindow",60,0,3000, 0.141, 0.868);

  //Z' Soft Drop Mass - both jets: pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV
  /*draw("softDrop_Z_mass","Soft Drop t#bar{t} Mass [GeV]","cutflow==4","ZprimeSoftDropMass",60,0,3000, 0.141, 0.868, 1);

  //Z' Soft Drop Mass - both jets: pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, tau3/tau2 < 0.61
  draw("softDrop_Z_mass","Soft Drop t#bar{t} Mass [GeV]","cutflow==5","ZprimeSoftDropMass_nSubjettiness0p61",60,0,3000, 0.141, 0.868, 5);

  //Z' Soft Drop Mass - both jets: pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, tau3/tau2 < 0.61; 1 b-tag > 0.762
  draw("softDrop_Z_mass","Soft Drop t#bar{t} Mass [GeV]","cutflow==6","ZprimeSoftDropMass_nSubjettiness0p61_1btag0p762",60,0,3000, 0.141, 0.868, 21);

  //Z' Soft Drop Mass - both jets: pt > 400 GeV, abs(eta) < 2.4, 110 GeV < Soft Drop Mass < 210 GeV, tau3/tau2 < 0.61; 2 b-tags > 0.762
  draw("softDrop_Z_mass","Soft Drop t#bar{t} Mass [GeV]","cutflow==7 && topTagJet0_maxSoftDropSubjetbtag <= 1.0 && topTagJet1_maxSoftDropSubjetbtag <= 1.0","ZprimeSoftDropMass_nSubjettiness0p61_2btag0p762",60,0,3000, 0.141, 0.868, 37);*/
  
}
