#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

class Image{
  private:
    std::vector<std::vector<cv::Point>> contoursList;
    cv::Mat detectedEdges;
    std::vector<cv::Vec4i> hierarchy;

  public:
      int thresh = 27;
      int max_thresh = 255;
      cv::Mat src;
      cv::Mat src_gray;

  private:
      cv::Point ComputeGravityCenter( std::vector<cv::Point> _pointsList );
      double ComputeCircleFittingRMS( std::vector<cv::Point> _pointsList, cv::Point _center );

  public:
      Image() = default;
      ~Image() = default;

      void ApplyFilters();
      bool IsCircle( std::vector<cv::Point> _pointsList );
      int LoadImage(char* fileName);
      void DetectContours();
      void CheckEachContour();
      void CheckAllContoursInOne();
};
