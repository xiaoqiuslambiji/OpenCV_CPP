#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <dirent.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;

void rgb_dataset_fr1_desk_with_rgb_txt(const string &strFile, const string &rgb_path, const string &rgb_outpath);

void rgb_dataset_fr1_desk_without_rgb_txt(const string &rgb_path, const string &rgb_outpath);

void CheckTarFilePath(const string &TarFilePath);

int main (int argc, char** argv) {
    string rgb_dataset_path = "/media/q/ba699ac6-3e7c-41f4-97e9-488e75766364/TUM_Dataset/rgbd_dataset_freiburg1_desk/";
    string strFile = rgb_dataset_path +"rgb.txt";
    string rgb_outpath_with_rgb_txt = rgb_dataset_path +"rgb_with/";
    CheckTarFilePath(rgb_outpath_with_rgb_txt);
    string rgb_outpath_without_rgb_txt = rgb_dataset_path +"rgb_without/";
    CheckTarFilePath(rgb_outpath_without_rgb_txt);
    rgb_dataset_fr1_desk_without_rgb_txt(rgb_dataset_path, rgb_outpath_without_rgb_txt);
    rgb_dataset_fr1_desk_with_rgb_txt(strFile, rgb_dataset_path, rgb_outpath_with_rgb_txt);
}

void CheckTarFilePath(const string &TarFilePath) {
    if(!opendir(TarFilePath.c_str())){
        string cmd;
        cmd = "mkdir " + TarFilePath;
        system(cmd.c_str());
        std::cout << "mkdir TarFilePath: " << TarFilePath << std::endl;
    }
    else {
        std::cout << "TarFilePath has mkdir: " << TarFilePath << std::endl;
    }
    closedir(opendir(TarFilePath.c_str()));
}


void rgb_dataset_fr1_desk_without_rgb_txt(const string &rgb_path, const string &rgb_outpath){
    vector<cv::String> vstrImageFilenames;
    cv::glob(rgb_path+"/rgb",vstrImageFilenames,false);
    int size = vstrImageFilenames.size();
    if(size == 0){
        cout<<"empty file."<<endl;
    }
    else {
        for (int i = 0; i < size; i++) {
            if (vstrImageFilenames[i].find("png") != cv::String::npos) {
                cv::Mat image = imread(vstrImageFilenames[i], CV_LOAD_IMAGE_UNCHANGED);
                if (image.data == NULL) {
                    cerr << "image.data == NULL \n" << vstrImageFilenames[i] << endl;
                }
                else {
                    cout << "\n" << endl;
                }
                imshow("image", image);
                cout << "\n" << endl;
                //cv::waitKey(0);

                char newName[10];
                sprintf(newName, "%06d.png", i);
                imwrite(rgb_outpath + newName, image);
                cv::Mat image_out = cv::imread(rgb_outpath + newName);
                if (image_out.data == NULL) {
                    cerr << "\n" << endl;
                }
                else{
                    cout << "\n" << rgb_outpath + newName<< endl;
                }
            }
            else {
                cout << "\n" << endl;
            }
        }
    }
    cv::destroyAllWindows();
}


void rgb_dataset_fr1_desk_with_rgb_txt(const string &strFile, const string &rgb_path, const string &rgb_outpath) {
    std::ifstream f;
    f.open(strFile.c_str());
    std::string s0;
    getline(f,s0);// skip first three lines
    getline(f,s0);
    getline(f,s0);
    int cnt = 1;
    while(!f.eof()) {
        std::string s;
        getline(f, s);
        if(!s.empty()){
            std::stringstream ss;
            ss << s;
            double t;
            std::string sRGB;
            ss >> t >> sRGB;
            std::string oldname = rgb_path + sRGB;
            int result;
            std::string newname;
            std::stringstream name_stream;
            name_stream << rgb_outpath << std::setw(4) << std::setfill('0') << cnt << ".png";
            name_stream >> newname;
            std::cout << newname << std::endl;
//            result = rename(oldname.c_str() , newname.c_str());
//            if ( result == 0 ){
//                puts ( "File successfully renamed" );
//            }
//            else{
//                perror( "Error renaming file ");
//            }


            cv::Mat image = cv::imread(oldname, CV_LOAD_IMAGE_UNCHANGED);
            cv::imwrite(newname, image);
            cv::Mat image_out = cv::imread(newname,CV_LOAD_IMAGE_UNCHANGED);
            if (image_out.data == NULL) {
                cerr << "\n" << newname << endl;
            }
            else{
                cout << "\n" <<  newname<< endl;
            }

        }
        cnt++;
    }
}
