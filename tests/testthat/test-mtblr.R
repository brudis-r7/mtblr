context("basic functionality")
test_that("we can do something", {

  mtbl <- read_mtbl("/Users/bob/Desktop/2016-04-04-1459771861-udp_bacnet_rpm_47808-processed.mtbl")
  expect_that(length(mtbl_keys(mtbl)), equals(18788))
  expect_that(length(mtbl_values(mtbl)), equals(18788))

})
