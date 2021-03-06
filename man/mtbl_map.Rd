% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/RcppExports.R
\name{mtbl_map}
\alias{mtbl_map}
\title{Start an iterator over an mtbl file}
\usage{
mtbl_map(x)
}
\arguments{
\item{x}{mtbl file opened with \code{read_mtbl()}}
}
\description{
TODO add a parameter to pass in an R function to evaluate
just like in a real iterator
}
\examples{
mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
mp <- mtbl_map(mtbl)
mtbl_iter_close(mp)
}

