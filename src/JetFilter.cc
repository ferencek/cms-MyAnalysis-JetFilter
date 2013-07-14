// -*- C++ -*-
//
// Package:    JetFilter
// Class:      JetFilter
//
/**\class JetFilter JetFilter.cc MyAnalysis/JetFilter/src/JetFilter.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Dinko Ferencek
//         Created:  Sat Jul 13 20:28:18 CDT 2013
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Candidate/interface/Candidate.h"

//
// class declaration
//

class JetFilter : public edm::EDFilter {
   public:
      explicit JetFilter(const edm::ParameterSet&);
      ~JetFilter();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginJob() ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual bool beginRun(edm::Run&, edm::EventSetup const&);
      virtual bool endRun(edm::Run&, edm::EventSetup const&);
      virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
      virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);

      // ----------member data ---------------------------
      const edm::InputTag jetsInputTag_;
      const double        jetPtMin_, jetAbsEtaMax_;
      const int           jetsMin_, jetsMax_;
      const bool          enabled_;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
JetFilter::JetFilter(const edm::ParameterSet& iConfig) :

  jetsInputTag_(iConfig.getParameter<edm::InputTag>("JetsInputTag")),
  jetPtMin_(iConfig.getParameter<double>("JetPtMin")),
  jetAbsEtaMax_(iConfig.getParameter<double>("JetAbsEtaMax")),
  jetsMin_(iConfig.getParameter<int>("JetsMin")),
  jetsMax_(iConfig.getParameter<int>("JetsMax")),
  enabled_(iConfig.getParameter<bool>("Enabled"))

{
   //now do what ever initialization is needed

}


JetFilter::~JetFilter()
{

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
JetFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  if( !enabled_ )
    return true;

  // get jets
  edm::Handle<edm::View<reco::Candidate> > jets;
  iEvent.getByLabel(jetsInputTag_, jets);

  // count jets
  int njets=0;

  for(edm::View<reco::Candidate>::const_iterator it = jets->begin(); it != jets->end(); ++it)
  {
    if( it->pt()>jetPtMin_ && fabs(it->eta())<jetAbsEtaMax_ )
      ++njets;
  }

  if (jetsMin_>-1 && njets<jetsMin_) return false;
  if (jetsMax_>-1 && njets>jetsMax_) return false;

  return true;
}

// ------------ method called once each job just before starting event loop  ------------
void
JetFilter::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void
JetFilter::endJob() {
}

// ------------ method called when starting to processes a run  ------------
bool
JetFilter::beginRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool
JetFilter::endRun(edm::Run&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool
JetFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool
JetFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&)
{
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
JetFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(JetFilter);
