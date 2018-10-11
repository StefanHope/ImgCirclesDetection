#include "gtest/gtest_prod.h"
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
    const int thresholdCircleRMS = 2;
    const int thresholdCanny = 50;
    const unsigned int minimumCirclePtsNb = 50;
    cv::Mat sourceImage;
    cv::Mat greyImage;

  public:
    Image() = default;
    ~Image() = default;
    int LoadImage(char* fileName);
    int FindCircles();

  private:
    // For google tests accessibility
    FRIEND_TEST(Image_Test, ComputeGravityCenter01);
    FRIEND_TEST(Image_Test, ComputeGravityCenter02);
    FRIEND_TEST(Image_Test, ComputeGravityCenter03);

    cv::Point ComputeGravityCenter( std::vector<cv::Point> _pointsList );
    double ComputeCircleFittingRMS( std::vector<cv::Point> _pointsList, cv::Point _center );
    void ApplyFilters();
    bool IsCircle( std::vector<cv::Point> _pointsList );
    void DetectContours();
    void RemoveNoiseInContoursList();
    int CheckEachContour();
    bool CheckAllContoursInOne();
};
