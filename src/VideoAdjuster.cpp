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

#include <VideoAdjuster.hpp>

int VideoAdjuster::mode = 0;

VideoAdjuster::VideoAdjuster(std::string video_source) 
    : video_source(video_source), current_frame(0),
    brightness(50), contrast(50), changed_pos(false){

}

void VideoAdjuster::set_pos(int position, void* data) {
    bool * ch = (bool *) data;
    *ch = true;
}

void VideoAdjuster::setup(int max_frame_pos) {
    namedWindow("Window", CV_GUI_EXPANDED);
    setWindowProperty("Window", CV_WND_PROP_ASPECTRATIO, CV_WINDOW_KEEPRATIO);
    setWindowProperty("Window", CV_WND_PROP_AUTOSIZE, CV_WINDOW_NORMAL);

    createTrackbar("Position", "Window", &current_frame, max_frame_pos, &set_pos, (void *) &changed_pos);

    createTrackbar("Brightness", "Window", &brightness, 100);

    createTrackbar("Contrast", "Window", &contrast, 100);

    createButton("Input", my_button_cb, (void *) DEFAULT_SCREEN, CV_RADIOBOX, true);
    createButton("Color", my_button_cb, (void *) COLOR_SCREEN, CV_RADIOBOX, false);
    createButton("B & C", my_button_cb, (void *) B_N_C, CV_RADIOBOX, false);
}

void VideoAdjuster::move_frame_pos(int position) {
	setTrackbarPos("Position", "Window", position);
}

bool VideoAdjuster::read_frame(Mat &frame) {
    bool result = cap.read(frame);
    move_frame_pos(++current_frame);

    return result && !frame.empty();
}


void VideoAdjuster::my_button_cb(int state, void* userdata) {

    if(state == 0) {
        // Off
    }
    else {
        // Find out what button was clicked and set mode to that.
        intptr_t value = (intptr_t) userdata;
        VideoAdjuster::mode = (int) value;
    }
}

bool VideoAdjuster::run() {
    cap.open(video_source);

    int frame_length = cap.get(CV_CAP_PROP_FRAME_COUNT);
    setup(frame_length);

    // File couldn't be opened
    if(!cap.isOpened()) {
        return false;
    }

    Mat frame;
    Mat output;
    int key = 0;
    cap.read(frame);
    bool pause = true;

    vector<Mat> colors;
    Mat color_test;


    while(true) {
        if(changed_pos) {
            changed_pos = false;
            cap.set(CV_CAP_PROP_POS_FRAMES, current_frame);
        }

        if(!pause) {
            // Play
            if(!read_frame(frame)) {
                return false;
            }
        }

        if(frame.empty()) {
        	break;
        }      

        if(mode == COLOR_SCREEN) {
            split(frame, colors);
            equalizeHist(colors[0], colors[0]);
            equalizeHist(colors[1], colors[1]);
            equalizeHist(colors[2], colors[2]);
            merge(colors, output);
        }
        else if(mode == B_N_C) {
            frame.convertTo(output, -1, contrast / 50.0, brightness-50);
        }
        else {
            frame.copyTo(output);
        }

        imshow("Window", output);

        key = waitKey(1);
        //std::cout << "key = " << key << std::endl;

        // Bind keys:
        //    - f, plays forward
        //    - r, plays backwards
        //    - space, pause video
        //    - Esc, end video
        //    - >, forward 1 frame
        //    - <, backward 1 frame
        if(key == 27)
        {
            break;
        }
        else if(key == 32) {
            pause = !pause;
        }
        else if(key == 62) {
            pause = true;
            if(!read_frame(frame)) {
                return false;
            }
        }
        else if(key == 60) {
            pause = true;

            if(current_frame > 0) {
                --current_frame;
                cap.set(CV_CAP_PROP_POS_FRAMES, current_frame);
                move_frame_pos(current_frame);
                cap.read(frame);
            }
        }
    }
    destroyAllWindows();

    return false;
}