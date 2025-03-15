#!/bin/bash
#init wd is ~workspace

STARTER_FILES_DIR="hw3"
HIDDEN_DIR="/home/codio/workspace/grading/"

mkdir -p $HIDDEN_DIR

# clone student repo and checkout specified commit
cd $STARTER_FILES_DIR
REPO_URL=$(git remote get-url origin)
echo REPO_URL: $REPO_URL

#check for https url
if [[ "$REPO_URL" == *"https"* ]]; then
  echo "https URL found. Make sure remote git origin URL is ssh!"
  exit 1
fi

#does the SSH url end in .git?

if [[ "${REPO_URL: -4}" != ".git" ]]; then
  REPO_URL=$REPO_URL.git
fi

IFS='.''/' read -ra REPO_NAME_ARR <<< "$REPO_URL"
REPO_NAME=${REPO_NAME_ARR[-2]}
echo REPO_NAME: $REPO_NAME

cd $HIDDEN_DIR

echo $CODIO_FREE_TEXT_ANSWER > submission.sha

#pwd
#ls
rm -rf $REPO_NAME #delete old copy of repo if it exists
#ls
git clone --quiet $REPO_URL 2> /dev/null
#ls

if [[ ! -d $REPO_NAME ]] ;
then
echo "Unable to clone your repo. Please verify that you have connected your Codio to Github and that you have submitted a valid SHA."
exit 1
fi
#ls
cd $REPO_NAME

git checkout --quiet $CODIO_FREE_TEXT_ANSWER 2> /dev/null
retVal=$?
if [ $retVal -ne 0 ]; then
    echo "Unable to checkout the submitted SHA."
		exit $retVal
fi

for F in .gitignore llrec.h heap.h llrec-test1.in Makefile llrec.cpp llrec-test.cpp stack.h logicsim/and.png logicsim/circuit.h logicsim/exclusive_or.txt logicsim/gate.h logicsim/not.png logicsim/or.uml logicsim/single_not.txt logicsim/wire.h logicsim/and.uml logicsim/event.h logicsim/exclusive_or.uml logicsim/logicsim.cpp logicsim/not.uml logicsim/plantuml.jar logicsim/single_or.txt logicsim/circuit.cpp logicsim/exclusive_or.png logicsim/gate.cpp logicsim/Makefile logicsim/or.png logicsim/single_and.txt logicsim/wire.cpp
do

  if [[ ! -f $F ]] ;
  then
    echo "$F is not found in the repo. Did you 'git add $F' and 'git commit' and 'git push'?"
		exit -2
  else
    echo "$F has been checked in properly"
  fi
done

cd ..
rm -rf $REPO_NAME.submission $STARTER_FILES_DIR.submission
mv $REPO_NAME $STARTER_FILES_DIR.submission
