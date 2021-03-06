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

#include <opencv2/highgui/highgui.hpp> // imread

#include <iostream>
using std::cout;


int main(int argc, char* argv[])
{
    if (argc != 2) {
        cout
            << "Usage: chilitags-detect <image>\n\n"
            << "Returns the list of detected tag id's in the image, one per line.\n";
        return 1;
    }

    cout << "Frame" << "\t" << "Tag" << "\t" 
    <<"TopLeftX" << "\t" <<"TopLeftY" << "\t" 
    << "TopRightX" << "\t" << "TopRightY" << "\t" 
    << "BottomRightX" << "\t" << "BottomRightY" << "\t" 
    << "BottomLeftX" << "\t" << "BottomLeftY" << "\n";

    cv::Mat image = cv::imread(argv[1]);
    if(image.data) {
        for (const auto &tag : chilitags::Chilitags().find(image)){
                const cv::Mat_<cv::Point2f> corners(tag.second);
                // frame
                cout << "1" << "\t";
                // Id
                cout << tag.first << "\t";
                // Top left
                cout << static_cast<int>(corners(0).x) << "\t";
                cout << static_cast<int>(corners(0).y) << "\t";
                // Top right
                cout << static_cast<int>(corners(1).x) << "\t";
                cout << static_cast<int>(corners(1).y) << "\t";
                // Bottom right
                cout << static_cast<int>(corners(2).x) << "\t";
                cout << static_cast<int>(corners(2).y) << "\t";
                // Bottom left
                cout << static_cast<int>(corners(3).x) << "\t";
                cout << static_cast<int>(corners(3).y) << "\n";
            }

        return 0;
    }
    return 1;
}
