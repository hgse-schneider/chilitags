/*******************************************************************************
*   Copyright 2013-2014 EPFL                                                   *
*   Copyright 2013-2014 Quentin Bonnard                                        *
*                                                                              *
*   This file is part of chilitags.                                            *
*                                                                              *
*   Chilitags is free software: you can redistribute it and/or modify          *
*   it under the terms of the Lesser GNU General Public License as             *
*   published by the Free Software Foundation, either version 3 of the         *
*   License, or (at your option) any later version.                            *
*                                                                              *
*   Chilitags is distributed in the hope that it will be useful,               *
*   but WITHOUT ANY WARRANTY; without even the implied warranty of             *
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
*   GNU Lesser General Public License for more details.                        *
*                                                                              *
*   You should have received a copy of the GNU Lesser General Public License   *
*   along with Chilitags.  If not, see <http://www.gnu.org/licenses/>.         *
*******************************************************************************/

#include <chilitags.hpp>

#include <opencv2/highgui/highgui.hpp>

#include <iostream>
using std::cout;


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout << "Usage: detect-from-video <videofile>\n";
        return 1;
    }

    cv::VideoCapture capture(argv[1]);
    if (!capture.isOpened())
    {
        std::cerr << "Unable to read video file." << std::endl;
        return 1;
    }

    // The detection is not perfect, so if a tag is not detected during one frame,
    // the tag will shortly disappears, which results in flickering.
    // To address this, Chilitags "cheats" by keeping tags for n frames
    // at the same position. When tags disappear for more than 5 frames,
    // Chilitags actually removes it.
    // The following line disables this and get the raw results.
    chilitags::Chilitags chilitags;
    chilitags.setFilter(0, 0.0f);

    cv::Mat image;
    capture >> image;
    for (int frame = 0; image.data; ++frame) {
        const auto &tags = chilitags.find(image);
        if (!tags.empty()) {
            // Output frame number here for a semi-structured output
            for (const auto &tag : tags) {
                const cv::Mat_<cv::Point2f> corners(tag.second);
                cout << argv[1] << "\t";
                cout << frame << "\t";
                // Id
                cout << tag.first << "\t";
                // Top left
                cout << corners(0).x << "\t";
                cout << corners(0).y << "\t";
                // Top right
                cout << corners(1).x << "\t";
                cout << corners(1).y << "\t";
                // Bottom right
                cout << corners(2).x << "\t";
                cout << corners(2).y << "\t";
                // Bottom left
                cout << corners(3).x << "\t";
                cout << corners(3).y << "\n";
            }
        }
        capture >> image;
    }

    return 0;
}
