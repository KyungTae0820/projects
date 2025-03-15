#include "strmsrv.h"
#include <iostream>
#include <fstream>
using namespace std;

StreamService::StreamService()
{
    // Update as needed
    cUser_ = NULL;
}

StreamService::~StreamService()
{   
    // int i = 0;
    // while(users_.size()-1 != 0){
    //     int uindex = users_.size() - i-1;
    //     delete users_[uindex];
    //     users_.pop_back();
    //     i++;
    // }
    // int j = 0;
    // while(content_.size()-1 != 0){
    //     int cindex = content_.size() - j-1;
    //     delete content_[cindex];
    //     content_.pop_back();
    //     j++;
    // }
    for(unsigned int i = 0; i < users_.size(); i++){
        delete users_[i];
    }
    for(unsigned int i = 0; i < content_.size(); i++){
        delete content_[i];
    }
}

void StreamService::readAndParseData(std::istream& is, Parser& p)
{
    p.parse(is, content_, users_);
    cout << "Read " << content_.size() << " content items." << endl;
    cout << "Read " << users_.size() << " users." << endl;
}

void StreamService::userLogin(const std::string& uname)
{
    if(cUser_ != NULL){
      throw runtime_error("No user logged in");
    }
    int index = getUserIndexByName(uname);
    if(index == -1){
        //throw UserNotLoggedInError("No user is logged in");
        throw std::invalid_argument("No user logged in");
    }
    else{
        cUser_ = users_[index]; 
    }
}

void StreamService::userLogout()
{
    cUser_ = NULL;
}

std::vector<CID_T> StreamService::searchContent(const std::string& partial) const
{
    std::vector<CID_T> results;
    for(size_t i = 0; i < content_.size(); i++){
        //  Modify this to also push back when the string 'partial'
        //  is contained in the name of the current content. Lookup the string
        //  class documentation to find an appropriate function that can be used
        //  to do this simply.
        if(partial == "*" || content_[i]->name().find(partial)!= string::npos){
            results.push_back(i);
        }
    }        
    return results;
}

std::vector<CID_T> StreamService::getUserHistory() const
{
    throwIfNoCurrentUser();
    return cUser_->history;
}

void StreamService::watch(CID_T contentID)
{
    throwIfNoCurrentUser();//1st one
    bool index = isValidContentID(contentID);//2nd
    if(index == false){
        throw range_error("watch range Error");
    }
    if(content_[contentID]->rating() > cUser_->ratingLimit){
        throw RatingLimitError("Rating Limit Error");
    }
    //add the user to content viewers 
    content_[contentID]->addViewer(cUser_->uname);
    //add content to user history
    cUser_->addToHistory(contentID);
}

void StreamService::reviewShow(CID_T contentID, int numStars)
{ 
  throwIfNoCurrentUser();
  if(numStars < 0 || numStars > 5){//ReviewRangeError
      throw ReviewRangeError("ReviewRangeError");
  }
  content_[contentID]->review(numStars);
}

CID_T StreamService::suggestBestSimilarContent(CID_T contentID) const
{
    // dummy implementation
    //return -1;
    throwIfNoCurrentUser();
    vector<User*> Uj;//vector that holds the User who whatched contentID
    vector<Content*> Cj;//Vector that holds the repeated content
    int maxcountContent = 0;
    //int maxContentidx = 0;
    for(unsigned int i = 0; i < users_.size(); i++){//find and put the users in the
        if(users_[i]->haveWatched(contentID) == true && cUser_ != users_[i]){
            Uj.push_back(users_[i]);
        }
    }
    for(unsigned int i = 0; i < content_.size(); i++){//check the content count
        int countContent = 0;//count variable to check how many times the content repeated
        for(unsigned int j = 0; j < Uj.size(); j++){
            if(Uj[j]->haveWatched(content_[i]->id())){
                countContent++;
            }
        }
        if(countContent >= maxcountContent){
            maxcountContent = countContent;
            //maxContentidx = i;
            Cj.push_back(content_[i]);
        }
    }
    //CID_T a = Cj[maxContentidx]->id();
    for(unsigned int i = Cj.size()-1; i >=0; i--){
        if(cUser_->haveWatched(Cj[i]->id())==true){//애초에 안되는 경우
            if(i == 0){
                return -1;//when there are no sugesstion
            }
        }
        else{//되는경우 에서 content ID랑 달라야지
            if(contentID != Cj[i]->id()){
                return Cj[i]->id();//suggest the content id
            }
        }
    }
}

void StreamService::displayContentInfo(CID_T contentID) const
{
    if(! isValidContentID(contentID)){
        throw std::invalid_argument("Watch: invalid contentID");
    }

    // Call the display abitlity of the appropriate content object



}

bool StreamService::isValidContentID(CID_T contentID) const
{
    return (contentID >= 0) && (contentID < (int) content_.size());
}

void StreamService::throwIfNoCurrentUser() const
{
    if(cUser_ == NULL){
        throw UserNotLoggedInError("No user logged in");
    }
}

int StreamService::getUserIndexByName(const std::string& uname) const
{
    for(size_t i = 0; i < users_.size(); i++){
        if(uname == users_[i]->uname) {
            return (int)i;
        }
    }
    return -1;
}
