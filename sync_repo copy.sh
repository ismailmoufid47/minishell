#!/bin/bash

REMOTE1="ismailmoufid47"
REMOTE2="jbelkerf"
BRANCH="main"

# Function to check if a rebase is already in progress
check_rebase_in_progress() {
    if [ -d ".git/rebase-apply" ] || [ -d ".git/rebase-merge" ]; then
        echo "A rebase is already in progress. Please resolve it first."
        exit 1
    fi
}

# Function to pull and rebase from a remote
pull_and_rebase() {
    local remote=$1
    git pull --rebase $remote $BRANCH
    if [ $? -ne 0 ]; then
        git rebase --interactive $remote/$BRANCH
        if [ $? -ne 0 ]; then
            git rebase --abort
            exit 1
        fi
    fi
}

# Function to push to a remote
push_to_remote() {
    local remote=$1
    echo "Pushing changes to $remote..."
    git push $remote $BRANCH
    if [ $? -ne 0 ]; then
        pull_and_rebase $remote
        git push $remote $BRANCH
        if [ $? -ne 0 ]; then
            exit 1
        fi
    fi
}

if [ "$1" == "push" ]; then
    check_rebase_in_progress

    git fetch $REMOTE1 $BRANCH
    git fetch $REMOTE2 $BRANCH

    pull_and_rebase $REMOTE1
    pull_and_rebase $REMOTE2

    push_to_remote $REMOTE1
    push_to_remote $REMOTE2

    echo "Sync complete!"

elif [ "$1" == "add" ]; then
    changed_files=$(git ls-files --modified --others --exclude-standard)
    if [ -n "$changed_files" ]; then
        git add $changed_files
        echo "Added files: $changed_files"
    else
        echo "No changed files to add."
    fi
else
    # Execute normal git commands
    git "$@"
fi
