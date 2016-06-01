
`mtblr` : Tools to work with [`mtbl`](https://github.com/farsightsec/mtbl) files in R

`mtbl` is a C library implementation of the Sorted String Table (SSTable) data structure, based on the SSTable implementation in the open source [Google LevelDB library](http://code.google.com/p/leveldb/). An SSTable is a file containing an immutable mapping of keys to values. Keys are stored in sorted order, with an index at the end of the file allowing keys to be located quickly.

`mtbl` is not a database library. It does not provide an updateable key-value data store, but rather exposes primitives for creating, searching and merging SSTable files. Unlike databases which use the SSTable data structure internally as part of their data store, management of SSTable files -- creation, merging, deletion, combining of search results from multiple SSTables -- is left to the discretion of the `mtbl` library user.

The following functions are implemented:

-   `read_mtbl`: Open an mtbl file
-   `mtbl_length`: Retrieve the number of records in an open mtbl file
-   `close_mtbl`: Close an mtbl file
-   `mtbl_map`: Start an iterator over an mtbl file
-   `mtbl_next`: Iterate over mtbl file entries
-   `mtbl_iter_close`: Close an iterator when finished
-   `mtbl_get`: Retrieve a key/value pair from an mtbl by key
-   `mtbl_get_prefix`: Retrieve value(s) for a given key in an mtbl
-   `mtbl_keys`: Return all the keys of an mtbl
-   `mtbl_values`: Return all the values of an mtbl
-   `mtbl_export_values`: Export mtbl values to a file

The following data sets are included:

-   `system.file("extdata/sample.mtbl", package="mtblr")`

### News

**0.3.0**

-   `mtbl_export_values()` to shunt values from mtbl files to a file
-   Progress bars!

**0.2.0**

-   Handles bad paths for `read_mtbl()`

**0.1.0**

-   Initial release

### Installation

``` r
devtools::install_github("brudis-r7/mtblr")
```

### Usage

``` r
library(mtblr)

# current verison
packageVersion("mtblr")
```

    ## [1] '0.3.0.9000'

``` r
mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))

mtbl_length(mtbl)
```

    ## [1] 676

``` r
head(mtbl_keys(mtbl))
```

    ## [1] "aa" "ab" "ac" "ad" "ae" "af"

``` r
head(mtbl_values(mtbl))
```

    ## [1] "1" "2" "3" "4" "5" "6"

``` r
mtbl_next(mtbl_map(mtbl))[99][[1]]$value
```

    ## [1] "99"

``` r
mtbl_next(mtbl_get(mtbl, "aa"))[[1]]$value
```

    ## [1] "1"

``` r
mtbl_next(mtbl_get_prefix(mtbl, "a"))[[10]]$value
```

    ## [1] "10"

### Test Results

``` r
library(mtblr)
library(testthat)

date()
```

    ## [1] "Wed Jun  1 15:18:18 2016"

``` r
test_dir("tests/")
```

    ## testthat results ========================================================================================================
    ## OK: 5 SKIPPED: 0 FAILED: 0
    ## 
    ## DONE ===================================================================================================================
