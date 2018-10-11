#include "gtest/gtest.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "../src/Image.h"

class Image_Test : public ::testing::Test
{
  public:
    Image image;

  protected:
    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(Image_Test, FindCircles01)
{
  EXPECT_EQ(0, image.LoadImage("../unitTests/EntryData/EntryData01.jpg"));
  EXPECT_EQ(3, image.FindCircles());
}

TEST_F(Image_Test, ComputeGravityCenter01)
{
  std::vector<cv::Point> entryData;

  entryData.push_back(cv::Point(2.0, 2.0));
  entryData.push_back(cv::Point(2.0, 2.0));
  entryData.push_back(cv::Point(2.0, 2.0));
  entryData.push_back(cv::Point(2.0, 2.0));
  entryData.push_back(cv::Point(2.0, 2.0));
  cv::Point gravityCenter = image.ComputeGravityCenter(entryData);
  EXPECT_EQ(2.0, gravityCenter.x);
  EXPECT_EQ(2.0, gravityCenter.y);
}

TEST_F(Image_Test, ComputeGravityCenter02)
{
  std::vector<cv::Point> entryData;

  entryData.push_back(cv::Point(-2.0, 2.0));
  entryData.push_back(cv::Point(2.0, 2.0));
  cv::Point gravityCenter = image.ComputeGravityCenter(entryData);
  EXPECT_EQ(0.0, gravityCenter.x);
  EXPECT_EQ(2.0, gravityCenter.y);
}

TEST_F(Image_Test, ComputeGravityCenter03)
{
  std::vector<cv::Point> entryData;

  entryData.push_back(cv::Point(2.0, 5.2));
  entryData.push_back(cv::Point(2.0, -1.2));
  cv::Point gravityCenter = image.ComputeGravityCenter(entryData);
  EXPECT_EQ(2.0, gravityCenter.x);
  EXPECT_EQ(2.0, gravityCenter.y);
}
