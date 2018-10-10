#include "Image.h"

int Image::LoadImage(char* imageFile)
{
  sourceImage = cv::imread(imageFile);
  if (sourceImage.empty()){
    std::cerr << "No image supplied ..." << std::endl;
    return -1;
  }

  cv::imshow("SourceImage", sourceImage);
  cv::waitKey(0);
 
  return 0;
}

int Image::FindCircles()
{
  ApplyFilters();
  DetectContours();
  CheckEachContour();
  //  image.CheckAllContoursInOne();

  return 0;
}

void Image::ApplyFilters()
{
 
  // Converts image from one color space to another
  cvtColor(sourceImage, greyImage, cv::COLOR_BGR2GRAY);
  cv::imshow("greyImage", greyImage);
  cv::waitKey(0);

  // Image smoothing
  cv::blur(greyImage, greyImage, cv::Size(3,3));
}

void Image::DetectContours()
{
  Canny( greyImage, detectedEdges, thresh, thresh*2, 3 );
  findContours( detectedEdges, contoursList, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
}

void Image::CheckEachContour()
{
  cv::Mat drawing = cv::Mat::zeros( detectedEdges.size(), CV_8UC3 );

  cv::namedWindow("Contours", CV_WINDOW_AUTOSIZE );
  cv::Scalar color = cv::Scalar( 255, 255, 255);

  // Test each contour
  for( int contourId = 0; contourId < contoursList.size(); contourId++)
  {
    drawContours( drawing, contoursList, (int)contourId, color, 0.05, 8, hierarchy, 0, cv::Point() );
    if( (IsCircle(contoursList[contourId]) ) && (contoursList[contourId].size() > 20) )
      std::cout << "Figure n°" << contourId << " is a circle\n"; 
    else
      std::cout << "Figure n°" << contourId << " is NOT a circle\n";

    imshow( "Contours", drawing );   
    cv::waitKey(0);
  }
}

void Image::CheckAllContoursInOne()
{
  std::vector<cv::Point> contoursConcatenation;
  for( int contourId = 0; contourId < contoursList.size(); contourId++)
    for( int pointId = 0; pointId < contoursList[contourId].size(); pointId++)
      contoursConcatenation.push_back( contoursList[contourId][pointId] );

  if( IsCircle( contoursConcatenation ))
    std::cout << "Concatenation is a circle\n"; 
  else
    std::cout << "Concatenation is NOT a circle\n";

  cv::waitKey(0);
}

bool Image::IsCircle( std::vector<cv::Point> _pointsList ){
  cv::Point CG = ComputeGravityCenter( _pointsList );

  double errorRMS = ComputeCircleFittingRMS( _pointsList, CG );
  if( errorRMS < 5 )
    return true;
  return false;
}

cv::Point Image::ComputeGravityCenter( std::vector<cv::Point> _pointsList ){
  cv::Point gravityCenter;

  for( size_t point = 0; point < _pointsList.size(); point++){    
    gravityCenter.x = gravityCenter.x + _pointsList[point].x;
    gravityCenter.y = gravityCenter.y + _pointsList[point].y;
  }

  gravityCenter.x = gravityCenter.x/_pointsList.size();
  gravityCenter.y = gravityCenter.y/_pointsList.size();

  return gravityCenter;
}

double Image::ComputeCircleFittingRMS( std::vector<cv::Point> _pointsList, cv::Point _center ){

  double meanRadius = 0.0;
  std::vector<double> allRadius(_pointsList.size());

  for( size_t point = 0; point < _pointsList.size(); point++){
    allRadius[point] = sqrt( (_center.x-_pointsList[point].x)*(_center.x-_pointsList[point].x) + (_center.y-_pointsList[point].y)*(_center.y-_pointsList[point].y));
    meanRadius = meanRadius + allRadius[point];
  }

  meanRadius = meanRadius/_pointsList.size();

  double RMS = 0.0;
  for( size_t point = 0; point < _pointsList.size(); point++)
    RMS = RMS + (allRadius[point] - meanRadius) *  (allRadius[point] - meanRadius); 

  std::cout << "RMS error:\t" << std::setprecision(2) << std::fixed << sqrt(RMS/_pointsList.size()) <<"\t" ;

  return sqrt(RMS/_pointsList.size());
}
