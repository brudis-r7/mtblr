context("basic functionality")
test_that("we can do something", {

  mtbl <- read_mtbl(system.file("extdata/sample.mtbl", package="mtblr"))
  expect_that(length(mtbl_keys(mtbl)), equals(676))
  expect_that(length(mtbl_values(mtbl)), equals(676))
  expect_that(mtbl_next(mtbl_map(mtbl))[99][[1]]$value, equals("99"))
  expect_that(mtbl_next(mtbl_get(mtbl, "aa"))[[1]]$value, equals("1"))
  expect_that(mtbl_next(mtbl_get_prefix(mtbl, "a"))[[10]]$value, equals("10"))

})
