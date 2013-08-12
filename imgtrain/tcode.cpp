    if (1) {
    std::cout<< md.dims << md.channels() << (short)md.at<uchar>(0, 0) << md.total();
    for (int i = 0; i < md.rows; i ++) {
        for (int j = 0; j < md.cols; j ++) {
            if (i == 0 || i == md.rows-1 || j == 0 || j == md.cols-1) {
                md.at<uchar>(i, j) = 255;
            } else if ((short)md.at<uchar>(i, j) >= 237) {
                md.at<uchar>(i, j) = 255;
            } else if ((short)md.at<uchar>(i, j) < 237 ) {
                md.at<uchar>(i, j) = 0;
            }
        }
    }

    // row
    for (int i = 0; i < md.rows; i ++) {
        for (int j = 0; j < md.cols-1; j ++) {
            if ((short)md.at<uchar>(i, j) == 0) {
                int zcnt = 0;
                for (int k = j; k < md.cols; k++) {
                    if ((short)md.at<uchar>(i, k) > 0) break;
                    if ((short)md.at<uchar>(i, k) == 0) {
                        zcnt++;
                    }
                }
                if (zcnt <= 2) {
                    md.at<uchar>(i, j) = 255;
                    md.at<uchar>(i, j+1) = 255;
                    // md.at<uchar>(i, j+2) = 255;
                    // md.at<uchar>(i, j+3) = 255;
                    // md.at<uchar>(i, j+4) = 255;
                }
                j += zcnt;
            }
        }
    }

    if (1) {
    for (int j = 0; j < md.cols; j ++) {
        for (int i = 0; i < md.rows-1; i ++) {
            if ((short)md.at<uchar>(i, j) == 0) {
                int zcnt = 0;
                for (int k = i; k < md.rows-1; k++) {
                    if ((short)md.at<uchar>(k, j) > 0) break;
                    if ((short)md.at<uchar>(k, j) == 0) {
                        zcnt++;
                    }
                }
                if (zcnt <= 2) {
                    md.at<uchar>(i, j) = 255;
                    md.at<uchar>(i+1, j) = 255;
                    // md.at<uchar>(i, j+2) = 255;
                    // md.at<uchar>(i, j+3) = 255;
                    // md.at<uchar>(i, j+4) = 255;
                }
                i += zcnt;
            }
        }
    }
    }

    }

    cleared = md.clone();
    // write clear noise
    // std::cout<<clear_noise_tpl <<std::endl;
    memset(buff, 0, sizeof(buff));
    sprintf(buff, clear_noise_tpl, fname_start);
    cv::imwrite(buff, cleared);
    // std::cout<<buff <<std::endl;
