#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

#include "Image.h"

int main( int, char** argv )
{
  Image image;

  if (image.LoadImage(argv[1]) != 0)
    return -1;

  image.FindCircles();
  
  return(0);
}
