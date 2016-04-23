// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "mtblr_types.h"
#include <Rcpp.h>

using namespace Rcpp;

// read_mtbl
XPtrReader read_mtbl(std::string path);
RcppExport SEXP mtblr_read_mtbl(SEXP pathSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< std::string >::type path(pathSEXP);
    __result = Rcpp::wrap(read_mtbl(path));
    return __result;
END_RCPP
}
// mtbl_length
NumericVector mtbl_length(XPtrReader x);
RcppExport SEXP mtblr_mtbl_length(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrReader >::type x(xSEXP);
    __result = Rcpp::wrap(mtbl_length(x));
    return __result;
END_RCPP
}
// mtbl_map
XPtrIter mtbl_map(XPtrReader x);
RcppExport SEXP mtblr_mtbl_map(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrReader >::type x(xSEXP);
    __result = Rcpp::wrap(mtbl_map(x));
    return __result;
END_RCPP
}
// mtbl_next
List mtbl_next(XPtrIter x);
RcppExport SEXP mtblr_mtbl_next(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrIter >::type x(xSEXP);
    __result = Rcpp::wrap(mtbl_next(x));
    return __result;
END_RCPP
}
// mtbl_keys
std::vector < RawVector > mtbl_keys(XPtrReader x);
RcppExport SEXP mtblr_mtbl_keys(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrReader >::type x(xSEXP);
    __result = Rcpp::wrap(mtbl_keys(x));
    return __result;
END_RCPP
}
// mtbl_values
std::vector < RawVector > mtbl_values(XPtrReader x);
RcppExport SEXP mtblr_mtbl_values(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrReader >::type x(xSEXP);
    __result = Rcpp::wrap(mtbl_values(x));
    return __result;
END_RCPP
}
// mtbl_get
XPtrIter mtbl_get(XPtrReader x, std::string key);
RcppExport SEXP mtblr_mtbl_get(SEXP xSEXP, SEXP keySEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrReader >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type key(keySEXP);
    __result = Rcpp::wrap(mtbl_get(x, key));
    return __result;
END_RCPP
}
// mtbl_get_prefix
XPtrIter mtbl_get_prefix(XPtrReader x, std::string key);
RcppExport SEXP mtblr_mtbl_get_prefix(SEXP xSEXP, SEXP keySEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrReader >::type x(xSEXP);
    Rcpp::traits::input_parameter< std::string >::type key(keySEXP);
    __result = Rcpp::wrap(mtbl_get_prefix(x, key));
    return __result;
END_RCPP
}
// mtbl_iter_close
void mtbl_iter_close(XPtrIter x);
RcppExport SEXP mtblr_mtbl_iter_close(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrIter >::type x(xSEXP);
    mtbl_iter_close(x);
    return R_NilValue;
END_RCPP
}
// close_mtbl
void close_mtbl(XPtrReader x);
RcppExport SEXP mtblr_close_mtbl(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< XPtrReader >::type x(xSEXP);
    close_mtbl(x);
    return R_NilValue;
END_RCPP
}