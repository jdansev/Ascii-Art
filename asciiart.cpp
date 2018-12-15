#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>

#define WIDTH 1280*3/4
#define HEIGHT 720*3/4

using namespace cv;
using namespace std;

const int block_size = 5;
const float font_size = 0.4;
const std::string ch = "@#$&%*o+i;:-,.        ";

Mat frame;

int main() {

    bool pause = false;

    VideoCapture cap("/Users/Sevilla/Desktop/Videos/American Assassin (2017) [1080p] [YTS.AG]/American.Assassin.2017.1080p.BluRay.x264-[YTS.AG].mp4"); 

    // internal buffer stores only 3 frames
    cap.set(CV_CAP_PROP_BUFFERSIZE, 3);

    double fps = cap.get(CV_CAP_PROP_FPS);
    cout << fps << endl;

    if (!cap.isOpened()) {
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    while (1) {

        Mat resized;
        Mat output;

        if (!pause) {

            cap >> frame;

            if (frame.empty())
                break;

            resize(frame, resized, cv::Size(WIDTH, HEIGHT));
            imshow( "Frame", resized );

            output = resized;
            output.setTo(Scalar(255, 255, 255));

            for (float y = 0; y < HEIGHT/block_size; y++) {
                for (float x = 0; x < WIDTH/block_size; x++) {
                
                    float ix = x/(WIDTH/block_size)*(frame.cols/block_size);
                    float iy = y/(HEIGHT/block_size)*(frame.rows/block_size);

                    Vec3b color = frame.at<Vec3b>(Point(ix * block_size ,iy * block_size));

                    int R = color.val[0];
                    int G = color.val[1];
                    int B = color.val[2];

                    int Y = 0.299 * R + 0.587 * G + 0.114 * B;
                    float index = Y * ch.length() / 255;
                    char c = ch[(int) index];

                    putText(output, &c, Point(x * block_size, y * block_size), FONT_HERSHEY_PLAIN, font_size, Scalar(0, 0, 0), 1);

                }
            }

            imshow("Output",output);
        }
        
        char c = (char) waitKey(5);
        // Space to pause
        if (c == 32) {
            pause = !pause;
        }
        // ESC to exit
        else if (c == 27) {
            break;
        }

    }

    cap.release();
    destroyAllWindows();
        
    return 0;
}
