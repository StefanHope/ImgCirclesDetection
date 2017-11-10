//#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 27;
int max_thresh = 255;
RNG rng(12345);
void detectContour( vector<vector<Point> >& contours );
Point computeGravityCenter( vector<Point> _pointsList );
double computeCircleFittingRMS( vector<Point> _pointsList, Point _center );
bool IsCircle( vector<Point> _pointsList );

int main( int, char** argv )
{
  src = imread(argv[1]);
  if (src.empty()){
    cerr << "No image supplied ..." << endl;
    return -1;
  }

  // Converts image from one color space to another
  cvtColor( src, src_gray, COLOR_BGR2GRAY );
  imshow( "DisplayImage", src_gray );
  waitKey(0);

  // Image smoothing
  blur( src_gray, src_gray, Size(3,3) );

  // Pop-up box
  //  const char* source_window = "Source";
  //  namedWindow( source_window, WINDOW_AUTOSIZE );
  //  imshow( source_window, src );
  //  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );

  // Contour  
  vector<vector<Point> > contoursList;
  //detectContour( contoursList );

  // Find circles
  // Test each contour
  Mat canny_output;
  vector<Vec4i> hierarchy;

  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  findContours( canny_output, contoursList, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );

  namedWindow("Contours", CV_WINDOW_AUTOSIZE );
  for( int contourId = 0; contourId < contoursList.size(); contourId++){
    Scalar color = Scalar( 255, 255, 255); //rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing, contoursList, (int)contourId, color, 0.05, 8, hierarchy, 0, Point() );
    if( ( IsCircle(contoursList[contourId]) ) && (contoursList[contourId].size() > 20) )
      std::cout << "Figure n°" << contourId << " is a circle\n"; 
    else
      std::cout << "Figure n°" << contourId << " is NOT a circle\n";

    imshow( "Contours", drawing );   
    waitKey(0);
  }

  // Use all contours in one
  vector<Point> contoursConcatenation;
  for( int contourId = 0; contourId < contoursList.size(); contourId++)
    for( int pointId = 0; pointId < contoursList[contourId].size(); pointId++)
      contoursConcatenation.push_back( contoursList[contourId][pointId] );

  if( IsCircle( contoursConcatenation ))
    std::cout << "Concatenation is a circle\n"; 
  else
    std::cout << "Concatenation is NOT a circle\n";

  waitKey(0);
  return(0);
}

bool IsCircle( vector<Point> _pointsList ){
 Point CG = computeGravityCenter( _pointsList );

  double errorRMS = computeCircleFittingRMS( _pointsList, CG );
  if( errorRMS < 5 )
    return true;
  return false;
}

Point computeGravityCenter( vector<Point> _pointsList ){
  Point gravityCenter;

  //for( auto& it : _pointsList ){
  for( size_t point = 0; point < _pointsList.size(); point++){    
    gravityCenter.x = gravityCenter.x + _pointsList[point].x;
    gravityCenter.y = gravityCenter.y + _pointsList[point].y;
  }

  gravityCenter.x = gravityCenter.x/_pointsList.size();
  gravityCenter.y = gravityCenter.y/_pointsList.size();

  return gravityCenter;
}

double computeCircleFittingRMS( vector<Point> _pointsList, Point _center ){
  
  double meanRadius = 0.0;
  vector<double> allRadius(_pointsList.size());

  for( size_t point = 0; point < _pointsList.size(); point++){
    allRadius[point] = sqrt( (_center.x-_pointsList[point].x)*(_center.x-_pointsList[point].x) + (_center.y-_pointsList[point].y)*(_center.y-_pointsList[point].y));
    meanRadius = meanRadius + allRadius[point];
  }

  meanRadius = meanRadius/_pointsList.size();

  double RMS = 0.0;
  for( size_t point = 0; point < _pointsList.size(); point++)
    RMS = RMS + (allRadius[point] - meanRadius) *  (allRadius[point] - meanRadius); 

  std::cout << "RMS error:\t" << setprecision(2) << std::fixed << sqrt(RMS/_pointsList.size()) <<"\t" ;

  return sqrt(RMS/_pointsList.size());
}
void detectContour( vector<vector<Point> >& contours )
{
  Mat canny_output;
  vector<Vec4i> hierarchy;

  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  findContours( canny_output, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );

  for( size_t i = 0; i< contours.size(); i++ )
  {
    Scalar color = Scalar( 255, 255, 255); //rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
    drawContours( drawing, contours, (int)i, color, 0.05, 8, hierarchy, 0, Point() );
  }
}
