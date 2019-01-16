# script to update bomberman
# from matteyeux/bomberman

# Specify a new remote upstream repository that will be synced with the fork
git remote add upstream https://github.com/matteyeux/bomberman

# Verify the new upstream repository you've specified for your fork
git remote -v

# Fetch the branches and their respective commits from the upstream repository
git fetch upstream

# Check out your fork's local master branch.
git checkout master

# Merge the changes from upstream/master into your local master branch.
git merge upstream/master