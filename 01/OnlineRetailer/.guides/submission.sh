#!/bin/bash
#init wd is ~workspace

STARTER_FILES_DIR="hw2"
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

for F in .gitignore amazon.cpp book.cpp book.h clothing.cpp clothing.h database.txt datastore.h db_parser.cpp db_parser.h Makefile movie.cpp movie.h product.cpp product.h product_parser.cpp product_parser.h user.cpp user.h util.cpp util.h 
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
rm -rf $REPO_NAME.submission hw2.submission
mv $REPO_NAME hw2.submission
