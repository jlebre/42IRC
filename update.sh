#!/bin/bash

# This script is used to update the git repository

# Add all files to the repository
git add .

# Commit the changes
# If a commit message is provided, use it
# Otherwise, use a default message
if (( $# == 1 )); then
    git commit -m "$1"
else
    git commit -m "update"
fi

# Push the changes to the remote repository
git push

##########
# jlebre #
##########