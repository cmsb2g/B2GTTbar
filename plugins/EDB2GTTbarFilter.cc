
#include "FWCore/Framework/interface/EDFilter.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include <vector>


template< typename T, typename TC=T >
class EDB2GTTbarVectorFilter : public edm::EDFilter {
public:


  EDB2GTTbarVectorFilter( edm::ParameterSet const & params ) :
    edm::EDFilter( ),
    min_( params.getParameter<TC>( "minVal" ) ),
    token_ (consumes<typename std::vector<T> >( params.getParameter<edm::InputTag>("src") ) ) 
  {
  }
  virtual ~EDB2GTTbarVectorFilter() {}

  virtual void beginJob() {}
  virtual void endJob() {}

  virtual bool filter(edm::Event& iEvent, const edm::EventSetup& iSetup) override {

    edm::Handle< std::vector<T> > h_pt;


    bool pass = true; 

    iEvent.getByToken( token_, h_pt );
    if ( h_pt->size() < 1 ) {
      pass = false; 	
    }
    else {
      auto pt0 = (*h_pt)[0];
      if ( pt0 < min_ ){
	pass = false;
      }
    }

    return pass;
  }

protected:
  T min_;
  edm::EDGetTokenT<std::vector<T> > token_;
};


typedef EDB2GTTbarVectorFilter<double> EDB2GTTbarVectorFilterDouble;
typedef EDB2GTTbarVectorFilter<float,double> EDB2GTTbarVectorFilterFloat;


DEFINE_FWK_MODULE(EDB2GTTbarVectorFilterFloat);
DEFINE_FWK_MODULE(EDB2GTTbarVectorFilterDouble);

