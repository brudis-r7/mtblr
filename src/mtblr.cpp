#include <Rcpp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <mtbl.h>
#include "mtblr_types.h"

using namespace Rcpp;

//' @export
//[[Rcpp::export]]
XPtrReader read_mtbl(std::string path) {

  struct mtbl_reader *r = mtbl_reader_init(path.c_str(), NULL);
  return(XPtrReader(r));
}

//' @export
//[[Rcpp::export]]
NumericVector mtbl_length(XPtrReader x) {

  struct mtbl_reader *r = x.get();
  const struct mtbl_metadata *m = mtbl_reader_metadata(r);
  uint64_t count_entries = mtbl_metadata_count_entries(m);
  return(wrap(count_entries));

}

//' @export
//[[Rcpp::export]]
XPtrIter mtbl_map(XPtrReader x) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_iter(mtbl_reader_source(r));
  return(XPtrIter(it));

}

//' @export
//[[Rcpp::export]]
List mtbl_next(XPtrIter x) {

  struct mtbl_iter *it = x.get();

  const uint8_t *key, *val;
  size_t len_key, len_val;

  if (mtbl_iter_next(it, &key, &len_key, &val, &len_val)) {

    RawVector key_v = RawVector(len_key);
    RawVector val_v = RawVector(len_val);

    for(size_t j=0; j<len_key; j++) key_v[j] = key[j];
    for(size_t j=0; j<len_val; j++) val_v[j] = val[j];

    return(List::create(_("key")=key_v, _("value")=val_v));

  } else {
    mtbl_iter_destroy(&it);
    return(R_NilValue);
  }

}

//' @export
//[[Rcpp::export]]
std::vector < RawVector > mtbl_keys(XPtrReader x) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_iter(mtbl_reader_source(r));
  const struct mtbl_metadata *m = mtbl_reader_metadata(r);
  uint64_t count_entries = mtbl_metadata_count_entries(m);

  std::vector < RawVector > output(count_entries);

  uint64_t i = 0;
  const uint8_t *key;
  size_t len_key;

  while (mtbl_iter_next(it, &key, &len_key, &val, &len_val)) {
    output[i] = RawVector(len_key);
    for(size_t j=0; j<len_key; j++) {
      output[i][j] = key[j];
    }
    i++;
  }

  mtbl_iter_destroy(&it);

  return(output);

}

//' @export
//[[Rcpp::export]]
std::vector < RawVector > mtbl_values(XPtrReader x) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_iter(mtbl_reader_source(r));
  const struct mtbl_metadata *m = mtbl_reader_metadata(r);
  uint64_t count_entries = mtbl_metadata_count_entries(m);

  std::vector < RawVector > output(count_entries);

  uint64_t i = 0;
  const uint8_t *val;
  size_t len_val;

  while (mtbl_iter_next(it, &key, &len_key, &val, &len_val)) {
    output[i] = RawVector(len_val);
    for(size_t j=0; j<len_val; j++) {
      output[i][j] = val[j];
    }
    i++;
  }

  mtbl_iter_destroy(&it);

  return(output);

}

//' @export
//[[Rcpp::export]]
XPtrIter mtbl_get(XPtrReader x, std::string key) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_get(mtbl_reader_source(r),
                                         (const uint8_t *)key.c_str(),
                                         key.length());
  return(XPtrIter(it));

}

//' @export
//[[Rcpp::export]]
XPtrIter mtbl_get_prefix(XPtrReader x, std::string key) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_get_prefix(mtbl_reader_source(r),
                                                (const uint8_t *)key.c_str(),
                                                key.length());
  return(XPtrIter(it));

}

//' @export
//[[Rcpp::export]]
void mtbl_iter_close(XPtrIter x) {
  struct mtbl_iter *it = x.get();
  mtbl_iter_destroy(&it);
}

//' @export
//[[Rcpp::export]]
void close_mtbl(XPtrReader x) {
  struct mtbl_reader *r = x.get();
  mtbl_reader_destroy(&r);
}