
#!/bin/bash

# This lives in your project directory, alongside src/, bin/, config.make, etc

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR
make Debug && make RunDebug;