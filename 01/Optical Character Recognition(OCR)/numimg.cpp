#include "digitblob.h"
#include "numimg.h"
#include "bmplib.h"
#include <algorithm> // for std::sort
#include <deque>
#include <iomanip>
#include <iostream>

using namespace std;

NumImg::NumImg(const char* bmp_filename)
{
    //  Note: readGSBMP dynamically allocates a 2D array 
    //    (i.e. array of pointers (1 per row/height) where each  
    //    point to an array of unsigned char (uint8_t) pixels)

    // call readGSBMP to initialize img_, h_, and w_;
    img_ = readGSBMP(bmp_filename, h_, w_);

    // Leave this check
    if(img_ == NULL) {
        throw std::logic_error("Could not read input file");
    }
    
    // Convert to Black and White using a fixed threshold 
    for(int i =0; i < h_; i++){
        for(int j = 0; j < w_; j++){
            if(img_[i][j] > 150){
                img_[i][j] = 255;
            }
            else {
                img_[i][j] = 0;
            }
        }
    }
}

NumImg::~NumImg()
{
    for(int i = 0; i < h_; i++){
      delete [] img_[i];
    }
    delete [] img_;
}

size_t NumImg::findAndCreateDigitBlobs()
{
    //Dynamically allocate the predecessor and explored arrays. 
    bool** explored = new bool*[h_];
    for(int i = 0; i < h_; i++){
      explored[i] = new bool[w_];
    }
    //explored should be all false at first time
    for(int i = 0; i < h_; i++){//Input bool values to the array
      for(int j = 0; j < w_; j++){
        explored[i][j] = false;
      }
    }
    for(int i = 0; i < h_; i++){//Input bool values to the array
      for(int j = 0; j < w_; j++){
        if(explored[i][j] == false){
            explored[i][j] = true;
            if(img_[i][j] == 0){
              DigitBlob b = createDigitBlob(explored, i, j);
              blobs_.push_back(b);
            }
        }
      }
    }

    sortDigitBlobs();

    for(int i = 0; i < h_; i++){
      delete [] explored[i];
    }
    delete [] explored;

    return blobs_.size();
}

std::string NumImg::classify(bool withDebug)
{
    std::string res;
    for(size_t i = 0; i < blobs_.size(); i++){
        blobs_[i].classify();
        if(withDebug){
            blobs_[i].printClassificationResults();
        }
        char c = blobs_[i].getClassification();
        res += c;
    }
    return res;
}

void NumImg::printBoundingBoxes() const
{
    cout << setw(2) << "i" << setw(6) << "ULRow" << setw(6) << "ULCol" << setw(4) << "Ht." << setw(4) << "Wi." << endl;
    for(size_t i = 0; i < blobs_.size(); i++){
        const DigitBlob& b = blobs_[i];
        cout << setw(2) << i << setw(6) << b.getUpperLeft().row << setw(6) << b.getUpperLeft().col 
        << setw(4) << b.getHeight() << setw(4) << b.getWidth()  << endl;
        // cout << "Blob " << i << " ul=(" << b.getUpperLeft().row << "," << b.getUpperLeft().col 
        //     << ") h=" << b.getHeight() << " w=" << b.getWidth() << endl;
    }

}

const DigitBlob& NumImg::getDigitBlob(size_t i) const
{
    if(i >= blobs_.size()){
        throw std::out_of_range("Index to getDigitBlob is out of range");
    }
    return blobs_[i];
}

size_t NumImg::numDigitBlobs() const
{
    return blobs_.size();
}

void NumImg::sortDigitBlobs()
{
    std::sort(blobs_.begin(), blobs_.end());
}

void NumImg::drawBoundingBoxesAndSave(const char* filename)
{
    for(size_t i=0; i < blobs_.size(); i++){
        Location ul = blobs_[i].getUpperLeft();
        int h = blobs_[i].getHeight();
        int w = blobs_[i].getWidth();
        for(int i = ul.row-1; i < ul.row + h + 1; i++){
            img_[i][ul.col-1] = 128;
            img_[i][ul.col+w] = 128;
        }
        for(int j = ul.col-1; j < ul.col + w + 1; j++){
            img_[ul.row-1][j] = 128;
            img_[ul.row+h][j] = 128;
        }
    }
    writeGSBMP(filename, img_, h_, w_);
}

// Add other (helper) function definitions
bool NumImg::checkforBound(Location n){
  if(0 <= n.row && n.row <= h_  && 0 <= n.col && n.col <= w_){
    return true;
  }
  return false;
}

DigitBlob NumImg::createDigitBlob(bool** explored, int pr, int pc)
{
  // Arrays to help produce neighbors easily in a loop
  // by encoding the **change** to the current location.
  // Goes in order N, NW, W, SW, S, SE, E, NE
  int neighbor_row[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
  int neighbor_col[8] = {0, -1, -1, -1, 0, 1, 1, 1};

  Location curr;
  Location start(pr,pc);
  deque<Location> d1;
  d1.push_back(start);
  
  //To check for bounds
  int maxrow = 0;
  int minrow = h_;
  int maxcol = 0;
  int mincol = w_;
  int height = 0;
  int width  = 0;

  while(d1.empty() == false){
    curr = d1.front();
    explored[curr.row][curr.col] = true;
    if(curr.row > maxrow){
      maxrow = curr.row;
    }
    if(curr.row < minrow){
      minrow = curr.row;
    }
    if(curr.col > maxcol){
      maxcol = curr.col;
    }
    if(curr.col < mincol){
      mincol = curr.col;
    }
    
    for(int i = 0; i < 8; i++){
      Location neighbors = curr;
      neighbors.row = curr.row + neighbor_row[i];
      neighbors.col = curr.col + neighbor_col[i];
      if(checkforBound(neighbors)){
        if(img_[neighbors.row][neighbors.col] == 0 && explored[neighbors.row][neighbors.col] == false){
          d1.push_back(neighbors);
          explored[neighbors.row][neighbors.col] = true;
        }
      }
    }
    d1.pop_front();
  }
  height = maxrow - minrow + 1;
  width  = maxcol - mincol + 1;

  Location ul(minrow, mincol);
  return DigitBlob(img_, ul, height, width);
}






