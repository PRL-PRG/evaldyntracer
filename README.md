# Eval Dynamic Tracer
[![Travis build status](https://travis-ci.org/PRL-PRG/evaldyntracer.svg?branch=master)](https://travis-ci.org/PRL-PRG/evaldyntracer)
 
 An R package for tracing eval.
 
## Installation

First, you need to setup [R-dyntrace](https://github.com/PRL-PRG/R-dyntrace)
Then, install `evaldyntracer` for `R-dyntrace` by running the following command on the console:
```
$ R-dyntrace/bin/R

> library(devtools)
> install_github('PRL-PRG/evaldyntracer')
```
## Development

If you are a developer, fork the project and make changes to your copy.
Install your local copy by running the following command inside the
project root directory:

`R-dyntrace/bin/R CMD INSTALL --build --with-keep.source .`

After you are done making your changes, push to your fork and send a pull request.
Make sure your pull request passes all the tests.
