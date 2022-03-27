#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <vitis/ai/refinedet.hpp>

using namespace std;

int main( int argc, char *argv[] )
{
  if (argc < 2)
  {
    cout << "Input source not specified" << endl;
    cout << "USAGE: ./person_detection <video source>" << endl;
    return -1;
  }

  cv::VideoCapture vid(argv[1]);

  auto person_detect = vitis::ai::RefineDet::create("refinedet_pruned_0_96");

  while (1)
  {
    cv::Mat frame;
    vid >> frame;

    auto detections = person_detect->run(frame);
    float width = frame.cols;
    float height = frame.rows;

    for (auto &roi : detections.bboxes)
    {
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
                     0 );
    }

    cv::imshow("Person Detection", frame);
    if (cv::waitKey(1) == 'q') break;
  }

  return 0;
}