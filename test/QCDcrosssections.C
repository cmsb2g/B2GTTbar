#include <iostream>
#include "QCDcrosssections.h"

namespace QCD_xs_HTbinned {

  enum  { 
    pt100to200,
    pt200to300,
    pt300to500,
    pt500to700,
    pt700to1000,
    pt1000to1500,
    pt1500to2000,
    pt2000toInf
  };
};

namespace QCD_xs_PTbinned {
  enum  {
    pt300to470,
    pt470to600,
    pt600to800,
    pt800to1000,
    pt1000to1400,
    pt1400to1800,
    pt1800to2400,
    pt2400to3200,
    pt3200toInf
  };
};

using namespace QCD_xs_PTbinned;

string labels_xs_pt[20];
double xs_pt[20];//cross section in pb
double Nevents_pt[20];//cross section in pb

void QCDcrossections(){
  labels_xs_pt[QCD_xs_PTbinned::pt300to470] = "300to470";
  labels_xs_pt[QCD_xs_PTbinned::pt470to600] = "470to600";
  labels_xs_pt[QCD_xs_PTbinned::pt600to800] = "600to800";
  labels_xs_pt[QCD_xs_PTbinned::pt800to1000] = "800to1000";
  labels_xs_pt[QCD_xs_PTbinned::pt1000to1400] = "1000to1400";
  labels_xs_pt[QCD_xs_PTbinned::pt1400to1800] = "1400to1800";
  labels_xs_pt[QCD_xs_PTbinned::pt1800to2400] = "1800to2400";
  labels_xs_pt[QCD_xs_PTbinned::pt2400to3200] = "2400to3200";
  labels_xs_pt[QCD_xs_PTbinned::pt3200toInf] = "3200toInf";

  xs_pt[QCD_xs_PTbinned::pt300to470] = 7823;
  xs_pt[QCD_xs_PTbinned::pt470to600] = 648.2;
  xs_pt[QCD_xs_PTbinned::pt600to800] = 186.9;
  xs_pt[QCD_xs_PTbinned::pt800to1000] = 32.293;
  xs_pt[QCD_xs_PTbinned::pt1000to1400] = 9.4183;
  xs_pt[QCD_xs_PTbinned::pt1400to1800] = 0.84265;
  xs_pt[QCD_xs_PTbinned::pt1800to2400] = 0.12163;
  xs_pt[QCD_xs_PTbinned::pt2400to3200] = 0.00682981;
  xs_pt[QCD_xs_PTbinned::pt3200toInf] = 0.000165445;

  Nevents_pt[QCD_xs_PTbinned::pt300to470] = 15282856+2482816;
  Nevents_pt[QCD_xs_PTbinned::pt470to600] = 15458074+3959986;
  Nevents_pt[QCD_xs_PTbinned::pt600to800] = 9622896+3896412;
  Nevents_pt[QCD_xs_PTbinned::pt800to1000] = 15194720+3992112;
  Nevents_pt[QCD_xs_PTbinned::pt1000to1400] = 6229840+2999069;
  Nevents_pt[QCD_xs_PTbinned::pt1400to1800] = 2304684+396409;
  Nevents_pt[QCD_xs_PTbinned::pt1800to2400] = 1552064+397660;
  Nevents_pt[QCD_xs_PTbinned::pt2400to3200] = 399226+596904;
  Nevents_pt[QCD_xs_PTbinned::pt3200toInf] = 391735;
}
