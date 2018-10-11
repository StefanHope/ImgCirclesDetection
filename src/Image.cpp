#include "Image.h"

// #define DISPLAY true

#ifdef DISPLAY
void DisplayImage(std::string winName, cv::Mat imgName)
{
  cv::imshow(winName, imgName);
  cv::waitKey(0);
}
#else
void DisplayImage(std::string winName, cv::Mat imgName){}
#endif

int Image::LoadImage(char* imageFile)
{
  sourceImage = cv::imread(imageFile);
  if (sourceImage.empty()){
    std::cerr << "No image supplied ..." << std::endl;
    return -1;
  }

  DisplayImage("SourceImage", sourceImage);
 
  return 0;
}

int Image::FindCircles()
{
  ApplyFilters();
  DetectContours();

  return CheckEachContour();
}

void Image::ApplyFilters()
{
 
  // Converts image from one color space to another
  cvtColor(sourceImage, greyImage, cv::COLOR_BGR2GRAY);

  // Image smoothing
  // cv::blur(greyImage, greyImage, cv::Size(3, 3));
}

void Image::DetectContours()
{
  Canny( greyImage, detectedEdges, thresholdCanny, thresholdCanny*2, 3 );
  findContours( detectedEdges, contoursList, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE, cv::Point(0, 0) );
}

int Image::CheckEachContour()
{
  int circlesNb = 0;

  cv::Mat drawing = cv::Mat::zeros( detectedEdges.size(), CV_8UC3 );
  for(unsigned int contourId = 0; contourId < contoursList.size(); contourId++)
  {
    cv:: Scalar color = cv::Scalar(255, 255, 255);
    drawContours( drawing, contoursList, (int)contourId, color, 0.05, 8, hierarchy, 0, cv::Point() );

    if (IsCircle(contoursList[contourId]))
    {
      std::cout << "Figure n°" << contourId << " is a circle\n";
      circlesNb++;
    }
    else
    {
      std::cout << "Figure n°" << contourId << " is NOT a circle\n";
    }

    contourId++;
    DisplayImage("Contours", drawing);
  }

  return circlesNb;
}

bool Image::IsCircle( std::vector<cv::Point> _pointsList ){
  if (_pointsList.size() < minimumCirclePtsNb)
    return false;
  
  cv::Point CG = ComputeGravityCenter( _pointsList );

  double errorRMS = ComputeCircleFittingRMS( _pointsList, CG );
  std::cout << "RMS error:\t" << std::setprecision(2) << std::fixed << errorRMS <<"\t" ;
  if( errorRMS < thresholdCircleRMS )
    return true;
  return false;
}

cv::Point Image::ComputeGravityCenter( std::vector<cv::Point> _pointsList ){
  cv::Point gravityCenter;

  for (auto& point : _pointsList){    
    gravityCenter.x += point.x;
    gravityCenter.y += point.y;
  }

  gravityCenter.x /= _pointsList.size();
  gravityCenter.y /= _pointsList.size();

  return gravityCenter;
}

double Image::ComputeCircleFittingRMS( std::vector<cv::Point> _pointsList, cv::Point _center ){

  double meanRadius = 0.0;
  std::vector<double> allRadius;

  for(auto& point : _pointsList){
    double newRadius = sqrt( (_center.x - point.x)*(_center.x - point.x) + (_center.y -
          point.y)*(_center.y - point.y));
    meanRadius += newRadius;
    allRadius.push_back(newRadius);
  }

  meanRadius /= _pointsList.size();

  double errorRMS = 0.0;
  for (auto& radius : allRadius)
    errorRMS += (radius - meanRadius)*(radius - meanRadius); 


  return sqrt(errorRMS/_pointsList.size());
}
