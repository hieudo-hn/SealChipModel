#!/bin/bash

set -- Fold*
numFold="$#"

# Count the number of Fold folders, remember not to put any other folders/files' name
# to start with Fold
if [[ $numFold -gt 1 ]]
then
    for ((i = 1; i <= $numFold; i++))
    do
        # Remove the sync file from previous trainings
        rm -f mmod_sync*
        
        # Run the training
        curFold="Fold$i"
        ./trainModel ./$curFold

        # Move the output to its respective fold
        mv ./mmod_network.dat "./$curFold/${curFold}_model.dat"
    done
else
    echo "Please run \"./cv --cross-validation [dataFile] --fold [numFolds] first.\""
fi