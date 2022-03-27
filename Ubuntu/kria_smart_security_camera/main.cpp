#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vitis/ai/refinedet.hpp>
#include <vitis/ai/facedetect.hpp>

using namespace std;

cv::String windowName1 = "Kria Detection";
//cv::String windowName2 = "Face Detection";
cv::VideoCapture vid("/dev/video0");  // WebCam

//cv::namedWindow(windowName1);
//cv::moveWindow(windowName1, 900,0);

auto person_detect = vitis::ai::RefineDet::create("refinedet_pruned_0_96");
auto face_detect = vitis::ai::FaceDetect::create("densebox_640_360");

void person_detection()
{
  while(1) {
    cv::Mat frame;
    vid >> frame;
	int xthreshold = 380;
	int xdelta;
	
	cv::namedWindow(windowName1);
	cv::moveWindow(windowName1, 900,0);

	auto detections = person_detect->run(frame);
    float width = frame.cols;
    float height = frame.rows;

    for (auto &roi : detections.bboxes)
    {
      int xmin = std::min(std::max(roi.x * width, 0.0f), width);
      int ymin = std::min(std::max(roi.y * height, 0.0f), height);
      int xmax = std::min(std::max(xmin + (roi.width * width), 0.0f), width);
      int ymax = std::min(std::max(ymin + (roi.height * height), 0.0f), height);
	  
      xdelta = xmax - xmin;

      cv::rectangle( frame,
                     cv::Point(xmin, ymin),
                     cv::Point(xmax, ymax),
                     cv::Scalar(0,255,0),
                     1,
                     1,
                     0 );
    }

    cv::imshow(windowName1, frame);
	if ((xdelta > xthreshold)) break;
    if (cv::waitKey(10) == 'q') break;
  }
//  cv::destroyWindow(windowName1);
}

void face_detection()
{
  while(1) {
    cv::Mat frame;
    vid >> frame;
    int xthreshold = 100;
	int xdelta;
	
	cv::namedWindow(windowName1);
    cv::moveWindow(windowName1, 900,0);
	
    auto detections = face_detect->run(frame);
    float width = frame.cols;
    float height = frame.rows;

    for (const auto &roi : detections.rects) {
      int xmin = std::min(std::max(roi.x * width, 0.0f), width);
      int ymin = std::min(std::max(roi.y * height, 0.0f), height);
      int xmax = std::min(std::max(xmin + (roi.width * width), 0.0f), width);
      int ymax = std::min(std::max(ymin + (roi.height * height), 0.0f), height);

      xdelta = xmax - xmin;
	  
      cv::rectangle( frame,
                     cv::Point(xmin, ymin),
                     cv::Point(xmax, ymax),
                     cv::Scalar(0,0,255),
                     1,
                     1,
                     0 );    }

    cv::imshow(windowName1, frame);
	if ((xdelta < xthreshold)) break;
    if (cv::waitKey(10) == 'q') break;
  }
//  cv::destroyWindow(windowName2);  
}

int main()
{
//  for (int i = 0; i<5; i++)
  while(1)
  {
    person_detection();

    face_detection();
	
  }
  
  return 0;
}