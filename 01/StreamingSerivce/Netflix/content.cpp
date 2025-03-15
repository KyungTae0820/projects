#include "content.h"
#include <iostream>
#include <iomanip>

using namespace std;

Content::Content(int id, std::string name, int nr, int ts, int rating)
{
    id_ = id;
    name_ = name;
    numReviews_ = nr;
    totalStars_ = ts;
    rating_ = rating;
    //std::vector<std::string> usersWhoViewed_;
}

Content::~Content()
{
//   while(usersWhoViewed_.size() != 0){
//     usersWhoViewed_.pop_back();
//   }
}

void Content::display(std::ostream& ostr) const
{
    ostr << "========" << endl;
    ostr << "ID: " << id_ << endl;
    ostr << "Name: " << name_ << endl;
    ostr << "Views: " << usersWhoViewed_.size() << endl;
    ostr << "Average review: " << setprecision(1) << fixed << getStarAverage() << endl;
    
    if(0 >= rating_ && rating_ < 5) {
        const char** ratingMapping = this->ratingStrings();
        ostr << "Rating: " << ratingMapping[rating_] << endl;
    }
}

int Content::id() const
{
    return id_;
}

std::string Content::name() const
{
    return name_;
}

int Content::rating() const
{
    return rating_;
}

void Content::review(int numStars) 
{
    numReviews_++;
    totalStars_ += numStars;
}

void Content::addViewer(const std::string& username)
{
    usersWhoViewed_.push_back(username);
}

const std::vector<std::string>& Content::getViewers() const
{
    return usersWhoViewed_;
}

bool Content::hasViewed(const std::string& uname) const
{
    for(size_t m = 0; m < usersWhoViewed_.size(); m++){
        if(usersWhoViewed_[m] == uname){
            return true;
        }
    }
    return false;
}

const char** Movie::ratingStrings() const
{
    // Global variable of movie rating mappings that you can use for 
    //  displaying Movie objects. We use "G" for rating 0 and 1.
    static const char* movierating[] = {"G", "G", "PG", "PG-13", "R"};
    return movierating;
}

const char** Series::ratingStrings() const
{
    // DEFAULT TO THE SERIES / TV Rating Mappings
    
    // Global variable of series rating mapping (0 = "TVY", 1 = "TVG", etc.)
    static const char* tvrating[] = {"TVY", "TVG", "TVPG", "TV14", "TVMA"};
    return tvrating;
}

double Content::getStarAverage() const 
{
    if(numReviews_ == 0){
      return 0;
    }
    else{
      double starAverage = (double)totalStars_/numReviews_;
      return starAverage;
    }
}

int Series::numEpisodes() const
{
    // Should return the number of episodes in the series
    return numEpisodes_;

}

// Complete the other derived class member constructors and member functions
//What I have to add more?
Movie::Movie(int id, std::string name, int nr, int ts, int rating)
   : Content(id, name, nr, ts, rating)
    {

    }

Movie::~Movie(){
//   while(usersWhoViewed_.size() != 0){
//     usersWhoViewed_.pop_back();
//   }
}
void Movie:: display(std::ostream& outfile) const{
    Content::display(outfile);
}

Series::Series(int id, std::string name, int nr, int ts, int rating, int numEpisodes)
    : Content(id, name, nr, ts, rating)
    {
        numEpisodes_ = numEpisodes;
        //std::vector<std::string> usersWhoViewed_
    }
Series::~Series(){
//   while(usersWhoViewed_.size() != 0){
//     usersWhoViewed_.pop_back();
//   }
}
// int Series::numEpisodes(){
//     return numEpisodes_;
// }
void Series::display(std::ostream& outfile) const
{
    Content::display(outfile);
    outfile << "Episodes: " << numEpisodes_ << endl;
}