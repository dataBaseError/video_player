/**
 * @file CVtest.cpp
 * @author Joseph Heron <joseph.heron@uoit.net>
 *
 * @version 1.0
 *
 * @section LICENSE
 * Copyright (C) 2015 Joseph Heron
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 * 
 */

#ifndef VIDEO_ADJUSTER_HPP_
#define VIDEO_ADJUSTER_HPP_

#include <string>
#include <iostream>

//#include <opencv2/gpu/gpu.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cv.hpp>

//#include <VideoBufferReader.hpp>

using namespace cv;
using namespace gpu;

class VideoAdjuster
{
	VideoCapture cap;

	std::string video_source;

	int current_frame;

	int brightness;

	int contrast;

	bool changed_pos;

public:

	static int mode;

	static const int DEFAULT_SCREEN = 0;
	static const int COLOR_SCREEN = 1;
	static const int B_N_C = 2;

	VideoAdjuster(std::string video_source);

	void setup(int max_frame_pos);

	bool run();

	static void set_pos(int position, void* data);

	static void my_button_cb(int state, void* userdata);

	bool read_frame(Mat &frame);

private:
	void move_frame_pos(int position);

};

#endif /* VIDEO_ADJUSTER_HPP_ */
