#!/bin/bash

./Test_GenerateMuonTracks $1 $2

# Capture the return value of the C++ executable
return_value=$?

echo "Return value captured in shell script: $return_value"

