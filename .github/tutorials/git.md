So the common workflow/commands with git if you are working on a repo by yourself is

```bash
# show the files you've made changes to
git status
# it might also show you hint on what command you should use

# stage your changes
# add/stage a certain file or directory to be committed
git add ./path/to/directory/or/file
# or you can just add/stage ALL your changes by
git add .

# commit
# you can commit by either
git commit -m "commit message go here"
# or just
git commit
# which should open a commit file for you to write your changes

# push your changes to Github
git push
```

Now it's a bit more complicated when you are working in a group project.
Here's some useful command.


If you made changes to your local repo, and someone committed to the remote repo
you have 2 options
```bash
# Option 1: If you have not commit your changes.
# Preferable because it prevent the extra "Merge branch ..." commit
# you can do
git stash save
# then
git pull
# then to get your local changes back
git stash pop
# continue on as usual!
```
```bash
# Option 2: If you already committed you local changes
git pull
git push
# this would results in an extra commit "Merge branch something something..."
```
there might be a merge conflict when you do git pull
```
<<<<<<< HEAD
Your local changes
=======
Remote changes
>>>>>>> <commit-hash>
```
which you need to decide what to do.
manually edit the conflict file, keep/remove either or both.
The final file should not have conflict markers, then you can do the usual add-commit-push for the merge.

---

```bash
# if you want to un-commit/undo the last commit that was not pushed
git reset HEAD~1

# if the commit was pushed, you can also undo that, but it might cause issue for others
```

```bash
# if you git add some files or directory you didn't mean to
# you can do
git restore --staged ./path/to/directory/or/file
# or if you want to unstage all, do
git restore --staged
```


```bash
# discard changes & revert to the last commit for a directory or file
git restore ./path/to/directory/or/file

# reset your repo to match the remote repo (the one on Github)
git reset --hard origin

# git restore is basically a more precise git reset
# because you can target which directory or file to reset
```
