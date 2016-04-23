#ifndef __MTBLR_TYPES__
#define __MTBLR_TYPES__

#include <mtbl.h>
#include <Rcpp.h>

inline void finaliseIter(mtbl_iter* node) {
  // do nothing
}

inline void finaliseReader(mtbl_reader* node) {
  // do nothing
}

typedef Rcpp::XPtr<mtbl_reader,Rcpp::PreserveStorage,finaliseReader> XPtrReader;
typedef Rcpp::XPtr<mtbl_iter,Rcpp::PreserveStorage,finaliseIter> XPtrIter;

#endif
