#include "digitblob.h"
#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

bool Location::operator<(const Location& other) const
{
    Location temp = *this;
    if(temp.col < other.col){
      return true;
    }
    else if(temp.col > other.col){
      return false;
    }
    else{
      if(temp.row < other.row){
        return true;
      }
      else{
        return false;
      }
    }

    return false;
}

DigitBlob::DigitBlob()
{
    img_ = NULL;
    digit_ = '!'; // dummy value
    bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    euler_ = -2;

    // ul_'s Location default constructor already initializes it to -1,-1

    // Initilaize h_ and w_ and any other data members
    h_ = 0;
    w_ = 0;

}

DigitBlob::DigitBlob(uint8_t** img, Location upperleft, int height, int width)
{
    img_ = img;
    digit_ = '!'; // dummy value

    bq0_ = bq1_ = bq2_ = bq3_ = bq4_ = bqd_ = 0;
    euler_ = -2;

    // Initilaize ul_, h_ and w_ and any other data members
    ul_ = upperleft;
    h_ = height;
    w_ = width;

}

DigitBlob::~DigitBlob()
{
    

}

void DigitBlob::classify()
{
    calc_bit_quads();
    calc_euler_number();
    // Call helper functions to calculate features
    calc_centers_of_mass();
    calc_symmetry();
    //    Use the results of helper functions to calculate features
    //    Starting with the Euler number
    //    manage the value of through the abs to find the error bound.
    if(euler_ == 1){
       if((0.46 <= NVC && NVC <= 0.50) && 
                (0.44 <= NHC && NHC <= 0.52)&&
                (0.37 <= VS && VS <= 0.56)&& 
                (0.37 <= HS && HS <= 0.56)){
            digit_ = '5';
        }
        else if((0.49 <= NVC && NVC <= 0.52) && 
                (0.56 <= NHC && NHC <= 0.62)&&
                (0.62 <= VS && VS <= 0.88)&& 
                (0.62 <= HS && HS <=0.88)){
            digit_ = '3';
        }
        else if((0.52 <= NVC && NVC <= 0.55)&&
                (0.50 <= NHC && NHC <= 0.57)&&
                (0.58 <= VS && VS <= 0.63)&& 
                (0.58 <= HS && HS <= 0.63)){
            digit_ = '2';
        }
        else if((0.51 <= NVC && NVC <= 0.57)&&
           (0.44 <= NHC && NHC <= 0.64)&&
           (0.60 <= VS && VS <= 0.86)&& 
           (0.58 <= HS && HS <= 0.94)){
            digit_ = '1';
        }
        else{
            digit_ = '7';
        }
    }
    else if(euler_ == 0){
        if((0.50 <= NVC && NVC <= 0.57) && 
            (0.43 <= NHC && NHC <= 0.51)&&
            (0.52 <= VS && VS <= 0.7)&& 
            (0.52 <= HS && HS <= 0.7)){
            digit_ = '6';
        }
        else if((0.44 <= NVC && NVC <= 0.53)&&
                (0.53 <= NHC && NHC <= 0.57)&&
                (0.71 <= VS && VS <= 0.77)&& 
                (0.71 <= HS && HS <= 0.77)){
            digit_ = '4';
        }
        else if((0.48 <= NVC && NVC <= 0.52)&&
                (0.48 <= NHC && NHC <= 0.52)&&
                (0.8 <= VS && VS <= 1.0)&&  
                (0.8 <= HS && HS <= 1.0)){
            digit_ = '0';
        }
        else{
            digit_ = '9';
        }
    }
    else{//euler == -1
        digit_ = '8';
    }
    //printClassificationResults();
}

char DigitBlob::getClassification() const
{
    return digit_;
}

void DigitBlob::printClassificationResults() const
{
    cout << "Digit blob at " << ul_.row << "," << ul_.col << " h=" << h_ << " w=" << w_ << endl;
    cout << "Bit quads: 1, 2, D, 3, 4:";
    cout << " " << bq1_ << " " << bq2_ << " " << bqd_;
    cout << " " << bq3_ << " " << bq4_ << endl;
    cout << "Euler number is " << euler_ << endl;
    

    cout << "****Classified as: " << digit_ << "\n\n" << endl;
    cout << "Normal Vertical Centroid is " << NVC << endl;
    cout << "Normal Horizontal Centroid is " << NHC << endl; 
    cout << "Vertical Symetry is " << VS << endl;
    cout << "Horizontal Symetry is " << HS << endl;

}

const Location& DigitBlob::getUpperLeft() const
{
    return ul_;
}

int DigitBlob::getHeight() const
{
    return h_;
}

int DigitBlob::getWidth() const
{
    return w_;
}

bool DigitBlob::operator<(const DigitBlob& other)
{
    // Use Location's operator< for DigitBlob operator<
    return ul_ < other.ul_;
}

void DigitBlob::calc_euler_number()
{
    euler_ = (bq1_ - bq3_ - 2*bqd_) / 4;
}

void DigitBlob::calc_bit_quads()
{
    int blobrow = ul_.row - 1;
    int blobcol = ul_.col - 1;
    for(int i = blobrow; i < blobrow + h_ + 1; i++){
      for(int j = blobcol; j < blobcol + w_ +1; j++){
      //     //bqd
      //     if((img_[i][j] == 255 && img_[i][j+1] == 0 && 
      //         img_[i+1][j] == 0 && img_[i+1][j+1] == 255)||
      //         (img_[i][j] == 0 && img_[i][j+1] == 255 && 
      //         img_[i+1][j] == 255 && img_[i+1][j+1] == 0)){
      //             bqd_++;
      //     }
      //     //bq1
      //     else if((img_[i][j] == 0 && img_[i][j+1] == 255 && 
      //         img_[i+1][j] == 255 && img_[i+1][j+1] == 255)||
      //         (img_[i][j] == 255 && img_[i][j+1] == 0 && 
      //         img_[i+1][j] == 255 && img_[i+1][j+1] == 255)||
      //         (img_[i][j] == 255 && img_[i][j+1] == 255 && 
      //         img_[i+1][j] == 0 && img_[i+1][j+1] == 255)||
      //         (img_[i][j] == 255 && img_[i][j+1] == 255 && 
      //         img_[i+1][j] == 255 && img_[i+1][j+1] == 0)){
      //               bq1_++;
      //         }
      //     //bq3
      //     else if((img_[i][j] == 255 && img_[i][j+1] == 0 && 
      //         img_[i+1][j] == 0 && img_[i+1][j+1] == 0 )||
      //         (img_[i][j] == 0 && img_[i][j+1] == 255 && 
      //         img_[i+1][j] == 0 && img_[i+1][j+1] == 0 )||
      //         (img_[i][j] == 0 && img_[i][j+1] == 0 && 
      //         img_[i+1][j] == 255 && img_[i+1][j+1] == 0)||
      //         (img_[i][j] == 0 && img_[i][j+1] == 0 && 
      //         img_[i+1][j] == 0 && img_[i+1][j+1] == 255)){
      //               bq3_++;
      //     }
      //     else{}
      // }
      int count = 0;
      if(img_[i][j] == 0){
        count++;
      }
      if(img_[i][j+1] == 0){
        count++;
      }
      if(img_[i+1][j] == 0){
        count++;
      }
      if(img_[i+1][j+1] == 0){
        count++;
      }
      if(count == 1){
        bq1_++;
      }
      else if(count == 2 && (img_[i][j] == img_[i+1][j+1])){//considering both 0 and 255
        bqd_++;
      }
      else if(count == 3){
        bq3_++;
      }
      else{}
    }
  }
}

// Add more private helper function implementations
void DigitBlob::calc_centers_of_mass(){
    // VC(vertical centroid)/ (heights - 1)
    // HC(Horizontal centroid)/ (heights - 1)
    int sumVC = 0;
    int sumHC = 0;
    int countVC = 0;
    int countHC = 0;
    
    //vertical centroid
    for(int i = 0; i < h_; i++){
        for(int j = 0; j < w_; j++){
            if(img_[ul_.row+i][ul_.col+j] == 0){
                sumVC += i*1.0;
                countVC++;
            }
        }
    }
    double VC = (double)sumVC/countVC;
    //Horizontal centroid
    for(int i = 0; i < h_; i++){
        for(int j = 0; j < w_; j++){
            if(img_[ul_.row+i][ul_.col+j] == 0){
                sumHC += j*1.0;
                countHC++;
            }
        }
    }
    double HC = (double)sumHC/countHC;

    NVC = VC/(h_-1);
    NHC = HC/(w_-1);
}

void DigitBlob::calc_symmetry(){
    int countV = 0;
    int countH = 0;
    int totalV = 0;
    int totalH = 0;
    //vertical Symetry
    for(int i = ul_.row; i < ul_.row + h_/2; i++){
        for(int j = ul_.col; j < ul_.col + w_; j++){
            if((img_[i][j] == 0 && img_[2*ul_.row + h_-i-1][j] == 0)|| 
                (img_[i][j] == 255 && img_[2*ul_.row + h_-i-1][j] == 255)){
                    countV++;
            }
            totalV++;
        }
    }
    VS = (double)countV/totalV;
    //Horizontal Symetry
    for(int i = ul_.row; i < ul_.row + h_; i++){
        for(int j = ul_.col; j < ul_.col + w_/2; j++){
            if((img_[i][j] == 0 && img_[i][2*ul_.col + w_-j-1] == 0)|| 
                (img_[i][j] == 255 && img_[i][2*ul_.col + w_-j-1] == 255)){
                    countH++;
            }
            totalH++;
        }
    }
    HS = (double)countV/totalV;
}
