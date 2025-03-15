// Complete me
#include "customparser.h"
#include <iostream>
#include <sstream>

using namespace std;

const char* error_msg_1 = "Cannot read integer n";
const char* error_msg_2 = "Error in content parsing";
const char* error_msg_3 = "Error in user parsing";

void CustomFormatParser::parse(std::istream& is, std::vector<Content*>& content, std::vector<User*>& users)
{
    // Erase any old contents
    content.clear();
    users.clear();

    int count = 0;
    is >> count;
    if(is.fail()){
      throw ParserError(error_msg_1);
    }
    int id_; int type_;string firstWord_; string lastWord_;
    string title;int reviews_; int stars_;int ratings_;int episodes_;

    //recieving values from the file
    for(int i = 0; i < count; i++){
      is >> id_ >> type_;
      is >> firstWord_;
      getline(is, lastWord_);
      title = firstWord_ + lastWord_;
      is >> reviews_;
      is >> stars_;
      is >> ratings_;
      if(is.fail()){
        throw ParserError(error_msg_2);
      }
      if(type_ != 1){
        Movie* Tm = new Movie(id_, title, reviews_, stars_, ratings_);
        content.push_back(Tm);
        // string temp;
        // int tempRatings;
        // is >> temp >> tempRatings;
        // User* Tu = new User(temp, tempRatings);
        // users.push_back(Tu);  
        string temp;
        getline(is, temp); //Get rid of the \n character
        getline(is, temp);
        stringstream temp_ss;
        temp_ss << temp;
        while (temp_ss >> temp){
          Tm->addViewer(temp);
        }
      }
      else{
        is >> episodes_;
        Series* Ts = new Series(id_, title, reviews_, stars_,ratings_, episodes_);
        content.push_back(Ts);
        string temp;
        getline(is, temp); //Get rid of the \n character
        getline(is, temp);
        stringstream temp_ss;
        temp_ss << temp;
        while (temp_ss >> temp){
          Ts->addViewer(temp);
        }
      }
    }
    string temp;
    int tempRatings;
    is >> temp >> tempRatings;
    if(is.fail()){
        throw ParserError(error_msg_3);
    }
    //User* Tu = new User(temp, tempRatings);
    while(!is.fail()){
      User* Tu = new User(temp, tempRatings);
      // if(!is.fail()){
      //   break;
      // }
      // while(!is.fail()){
      //   int tempContentID;
      //   is >> tempContentID;
      //   Tu->addToHistory(tempContentID);
      // }
      getline(is, temp); //Get rid of the \n character
      getline(is, temp);
      stringstream temp_ss(temp);
      int tempContentID;
      while (temp_ss >> tempContentID){
        Tu->addToHistory(tempContentID);
      }
      users.push_back(Tu);

      is >> temp >> tempRatings;
    }
}

