#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vitis/ai/facedetect.hpp>

using namespace std;

int main( int argc, char *argv[] )
{
  if (argc < 2)
  {
    cout << "Input source not specified" << endl;
    cout << "USAGE: ./face_detection <video source>" << endl;
    return -1;
  }

  cv::VideoCapture vid(argv[1]);

  auto face_detect = vitis::ai::FaceDetect::create("densebox_640_360");

  while (1)
  {
    cv::Mat frame;
    vid >> frame;

    auto detections = face_detect->run(frame);
    float width = frame.cols;
    float height = frame.rows;

    for (const auto &roi : detections.rects) {
      int xmin = std::min(std::max(roi.x * width, 0.0f), width);
      int ymin = std::min(std::max(roi.y * height, 0.0f), height);
      int xmax = std::min(std::max(xmin + (roi.width * width), 0.0f), width);
      int ymax = std::min(std::max(ymin + (roi.height * height), 0.0f), height);

      cv::rectangle( frame,
                     cv::Point(xmin, ymin),
                     cv::Point(xmax, ymax),
                     cv::Scalar(0,255,0),
                     1,
                     1,
                     0 );    }

    cv::imshow("Face Detection", frame);
    if (cv::waitKey(1) == 'q') break;
  }

  return 0;
}