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

#include <string>

#include <VideoAdjuster.hpp>

using namespace cv;

int main(int argc, char *argv[]) {

	//Skip program name if any
	argc -= (argc > 0);
	argv += (argc > 0);

	std::string videoSource;
	unsigned long frameOffset = 0;
    //double fps = 30.0;

	if (argc != 1) {
		std::cout << "Invalid Parameters" << std::endl;
		return -1;
	} else {
		videoSource = std::string(argv[0]);
	}

	VideoAdjuster adjust(videoSource);

	adjust.run();

	return 0;
}
