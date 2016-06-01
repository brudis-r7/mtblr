// [[Rcpp::depends(RcppProgress)]]
#include <progress.hpp>

#include <Rcpp.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wordexp.h>
#include <fstream>
#include <iostream>

#include <mtbl.h>
#include "mtblr_types.h"

using namespace Rcpp;

//' Open an mtbl file
//'
//' @param path full path to mtbl file
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//[[Rcpp::export]]
XPtrReader read_mtbl(std::string path) {

  std::string fullPath(R_ExpandFileName(path.c_str()));

  struct mtbl_reader *r = mtbl_reader_init(fullPath.c_str(), NULL);
  if (r==NULL) stop("Cannot open file '%s'", path);
  return(XPtrReader(r));

}

//' Retrieve the number of records in an open mtbl file
//'
//' @param x mtbl file opened with \code{read_mtbl()}
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//' mtbl_length(mtbl)
//[[Rcpp::export]]
NumericVector mtbl_length(XPtrReader x) {

  struct mtbl_reader *r = x.get();
  const struct mtbl_metadata *m = mtbl_reader_metadata(r);
  uint64_t count_entries = mtbl_metadata_count_entries(m);
  return(wrap(count_entries));

}

//' Start an iterator over an mtbl file
//'
//' TODO add a parameter to pass in an R function to evaluate
//' just like in a real iterator
//'
//' @param x mtbl file opened with \code{read_mtbl()}
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//' mp <- mtbl_map(mtbl)
//' mtbl_iter_close(mp)
//[[Rcpp::export]]
XPtrIter mtbl_map(XPtrReader x) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_iter(mtbl_reader_source(r));
  return(XPtrIter(it));

}

//' Iterate over mtbl file entries
//'
//' Works with \code{mtbl_map()} and \code{mtbl_get()}
//'
//' If the number of available entries is less than \code{n}, a \code{list}
//' of the actual number of remaining entries is returned. Otherwise a \code{list}
//' of \code{n} entries is returned.
//'
//' @param x an iterator started with \code{mtbl_map()} or \code{mtbl_get()}
//' @param n number of records to return for this iteration. It's inefficient to
//'        sequentially iterate over large mtbl file but large values of \code{n}
//'        are also inefficent. \code{100} has been an optimal value in mtbl
//'        files used in Project Sonar. YMMV.
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//' mp <- mtbl_map(mtbl)
//' (mtbl_next(mp))
//' mtbl_iter_close(mp)
//[[Rcpp::export]]
List mtbl_next(XPtrIter x, size_t n=100) {

  struct mtbl_iter *it = x.get();

  const uint8_t *key, *val;
  size_t len_key, len_val;

  size_t ct = 0;
  std::vector<List> out(n);

  while((ct<n) && mtbl_iter_next(it, &key, &len_key, &val, &len_val)) {

    out[ct++] = List::create(_("key")=std::string(key, key+len_key),
                             _("value")=std::string(val, val+len_val));

  }

  out.resize(ct);

  return(wrap(out));

}

//' Return all the keys of an mtbl
//'
//' Remember that mtbl files are (in general) HUGE. This could take
//' a while and have a very large result.
//'
//' @param x an mtbl file opened with \code{read_mtbl()}
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//' head(mtbl_keys(mtbl))
//[[Rcpp::export]]
std::vector < std::string > mtbl_keys(XPtrReader x) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_iter(mtbl_reader_source(r));
  const struct mtbl_metadata *m = mtbl_reader_metadata(r);
  uint64_t count_entries = mtbl_metadata_count_entries(m);

  std::vector < std::string > output(count_entries);

  uint64_t i = 0;
  const uint8_t *key, *val;
  size_t len_key, len_val;

  while (mtbl_iter_next(it, &key, &len_key, &val, &len_val)) {
    output[i++] = std::string(key, key+len_key);
  }

  mtbl_iter_destroy(&it);

  return(output);

}

//' Return all the values of an mtbl
//'
//' Remember that mtbl files are (in general) HUGE. This could take
//' a while and have a very large result.
//'
//' @param x an mtbl file opened with \code{read_mtbl()}
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//' head(mtbl_values(mtbl))
//' @export
//[[Rcpp::export]]
CharacterVector mtbl_values(XPtrReader x) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_iter(mtbl_reader_source(r));
  const struct mtbl_metadata *m = mtbl_reader_metadata(r);
  uint64_t count_entries = mtbl_metadata_count_entries(m);

  std::vector < std::string > output(count_entries);

  uint64_t i = 0;
  const uint8_t *key, *val;
  size_t len_key, len_val;

  Progress p(count_entries, true);

  while (mtbl_iter_next(it, &key, &len_key, &val, &len_val)) {
    if ((i % 10000) == 0) {
      if (Progress::check_abort()) return(R_NilValue);
    }
    output[i++] = std::string(val, val+len_val);
    p.increment();
  }

  mtbl_iter_destroy(&it);

  return(wrap(output));

}

//' Export mtbl \emph{values} to a file
//'
//' Given an \code{mtbl} file opened with \code{read_mtbl()}, this function
//' will export each value from the mtbl key/value pair to \code{path} with
//' each value record terminated by a newline.
//'
//' The use-case driving this function is exporting the value side of
//' Project Sonar mtbl files since it would help in processing \code{jq}
//' pipelines.
//'
//' @param x an mtbl file opened with \code{read_mtbl()}
//' @param path full path to output file
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//' mtbl_export(mtbl, tempfile())
//[[Rcpp::export]]
void mtbl_export_values(XPtrReader x, std::string path) {

  std::string fullPath(R_ExpandFileName(path.c_str()));

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_iter(mtbl_reader_source(r));
  const struct mtbl_metadata *m = mtbl_reader_metadata(r);
  uint64_t count_entries = mtbl_metadata_count_entries(m);

  uint64_t i = 0;
  const uint8_t *key, *val;
  size_t len_key, len_val;

  std::ofstream output(fullPath);

  Progress p(count_entries, true);

  while (mtbl_iter_next(it, &key, &len_key, &val, &len_val)) {
    if ((i % 10000) == 0) {
      if (Progress::check_abort()) return;
    }
    output << std::string(val, val+len_val);
    output << "\n";
    i++;
    p.increment();
  }

  mtbl_iter_destroy(&it);

}

//' Retrieve a key/value pair from an mtbl by key
//'
//' In theory there are no duplicates, but this still
//' returs an iterator that you'll need to use \code{mtbl_next()} with.
//'
//' @param x an mtbl file opened with \code{read_mtbl()}
//' @param key string (exact) to look for in the keys
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//' mtbl_next(mtbl_get(mtbl, "aa"))
//[[Rcpp::export]]
XPtrIter mtbl_get(XPtrReader x, std::string key) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_get(mtbl_reader_source(r),
                                         (const uint8_t *)key.c_str(),
                                         key.length());
  return(XPtrIter(it));

}

//' Retrieve value(s) for a given key in an mtbl
//'
//' @param x an mtbl file opened with \code{read_mtbl()}
//' @param key string (prefix) to look for in the keys
//' @export
//' @examples
//' mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
//' mtbl_next(mtbl_get_prefix(mtbl, "a"))
//[[Rcpp::export]]
XPtrIter mtbl_get_prefix(XPtrReader x, std::string key) {

  struct mtbl_reader *r = x.get();
  struct mtbl_iter *it = mtbl_source_get_prefix(mtbl_reader_source(r),
                                                (const uint8_t *)key.c_str(),
                                                key.length());
  return(XPtrIter(it));

}

//' Close an iterator when finished
//'
//' Frees up memory.
//'
//' @param x an open iterator
//' @export
//[[Rcpp::export]]
void mtbl_iter_close(XPtrIter x) {
  struct mtbl_iter *it = x.get();
  mtbl_iter_destroy(&it);
}

//' Close an mtbl file
//'
//' Will be really useful if we ever implement the write components of the API.
//'
//' @param x an open mtbl file handle
//' @export
//[[Rcpp::export]]
void close_mtbl(XPtrReader x) {
  struct mtbl_reader *r = x.get();
  mtbl_reader_destroy(&r);
}