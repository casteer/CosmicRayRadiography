/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: RooGaussian.rdl,v 1.14 2005/02/25 14:25:06 wverkerke Exp $
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef SamplePDGCosmic
#define SamplePDGCosmic

#include "RooFitCore/RooAbsPdf.hh"
#include "RooFitCore/RooRealProxy.hh"

class RooRealVar;

class SamplePDGCosmic : public RooAbsPdf {

public:

  SamplePDGCosmic(const char *name, const char *title,
	      RooAbsReal& _x, RooAbsReal& _mean, RooAbsReal& _sigma);
  SamplePDGCosmic(const RooGaussian& other, const char* name=0) ;

  virtual TObject* clone(const char* newname) const { return new RooGaussian(*this,newname); }
  inline virtual ~SamplePDGCosmic() { }

  Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t staticInitOK=kTRUE) const;
  void generateEvent(Int_t code);

protected:

  RooRealProxy E ;
  RooRealProxy Theta ;
  
  Double_t evaluate() const ;

private:

  ClassDef(SamplePDGCosmic,0) // Gaussian PDF
};

#endif
