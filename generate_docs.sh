#!/bin/bash

# remove old docs if they exist
rm "docs/html" -d -r

# generate new docs
doxygen docs/doxygen.conf
