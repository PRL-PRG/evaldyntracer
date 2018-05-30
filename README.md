# Eval Dynamic Tracer
[![Travis build status](https://travis-ci.org/PRL-PRG/evaldyntracer.svg?branch=master)](https://travis-ci.org/PRL-PRG/evaldyntracer)
 
 An R package for tracing eval.
 
First, you need to setup [R-dyntrace](https://github.com/PRL-PRG/R-dyntrace).

If you are not a developer, you can install `evaldyntracer` by running the 
following commands on the console:
```
$ R-dyntrace/bin/R

> library(devtools)
> install_github('PRL-PRG/evaldyntracer')
```

If you are a developer, fork the project and make changes to your copy. 
After you are done making your changes, push to your fork and send a pull request. 
Make sure your pull request passes all the tests.


## Install dependencies
To install all the package development dependencies, execute the following command -
```
$ make install-dependencies R_DYNTRACE_HOME = <R_DYNTRACE_HOME>
```

## Build
To build the source package, execute the following command -
```
$ make build R_DYNTRACE_HOME = <R_DYNTRACE_HOME>
```

## Install
To install the package, execute the following command -
```
$ make install R_DYNTRACE_HOME = <R_DYNTRACE_HOME>
```

## Document
To generate documentation for the package, execute the following command -
```
$ make document R_DYNTRACE_HOME = <R_DYNTRACE_HOME>
```

## Check
To perform all checks on the package, execute the following command -
```
$ make check R_DYNTRACE_HOME = <R_DYNTRACE_HOME>
```

## Test
To run tests on the package, execute the following command -
```
$ make test R_DYNTRACE_HOME = <R_DYNTRACE_HOME>
```
