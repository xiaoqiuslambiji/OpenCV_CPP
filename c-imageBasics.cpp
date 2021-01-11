#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
  cv::Mat image; // 读取一张二维三通图像 新版本OpenCV中引入Mat类自动管理内存处理图像数据
  image = cv::imread("../ubuntu.png"); // cv::imread函数读取argv[1]指定路径下的图像
  if (image.data == nullptr) {
      std::cerr << "文件不存在" << std::endl;// 判断图像文件是否正确读取如果不能读取可能是文件不存在
      return 0; // 没有读取图片return 0终止函数
  }
  cv::imshow("image", image);
  cv::waitKey(0);

  std::cout << "image.size: " << image.size << std::endl; // image.size: 674 x 1200 高　宽
  std::cout << "image.rows: " << image.rows << std::endl; // image.rows: 674　高
  std::cout << "image.cols: " << image.cols << std::endl; // image.cols: 1200　宽
  std::cout << "image.rows/2: " << image.rows/2 << std::endl; // image.rows/2: 337　高/2 　注意高度是有多少行的像素　
  std::cout << "image.cols/2: " << image.cols/2 << std::endl; // image.cols/2: 600　宽/2　　注意宽度是有多少列的像素
  cv::Mat resize_image;
  cv::resize(image, resize_image, cv::Size(0,0),0.5,0.5,CV_INTER_LINEAR);
  /**
   * resize()函数
   * InputArray src, 输入原图像
   * OutputArray dst, 输出缩放后的图像
   * Size dsize, 输出图像的大小
   * 如果这个参数为0, 那么原图像缩放之后的大小就要通过下面的公式来计算
   * dsize = Size(round(fx*src.cols), round(fy*src.rows))
   * fx是fx:width方向的缩放比例,如果它是0,那么它就会按照(double)dsize给出的值来计算
   * fy是fy:height方向的缩放比例,如果它是0,那么它就会按照(double)dsize给出的值来计算
   * 如果这个参数不为0, 假如给出的是Size(width/2,height/2)代表将原图像在宽度和高度上缩小为原来的一半
   * fx=0.5 fy=0.5 和　Size(width/2,height/2)的缩放效果是一样的
   * 总结一下就是给出两种缩放比例参数的方法而已
   * 图像缩放之后像素要重新计算最后一个参数指定计算像素的方式有以下几种:
   * CV_INTER_NEAREST - 最邻近插值
   * CV_INTER_LINEAR - 双线性插值,如果最后一个参数你不指定,默认使用这种方法
   * CV_INTER_AREA - 基于局部像素的重采样
   * CV_INTER_CUBIC - 基于4x4像素邻域的3次插值法
   * CV_INTER_LANCZOS4 - 基于8x8像素邻域的Lanczos插值
   */
  cv::imshow("resize_image", resize_image);
  cv::waitKey(0);


  resize_image.copyTo(image(cv::Rect(0, 0, image.cols/2, image.rows/2)));
  resize_image.copyTo(image(cv::Rect(0, resize_image.rows, image.cols/2, image.rows/2)));
  resize_image.copyTo(image(cv::Rect(resize_image.cols, 0, image.cols/2, image.rows/2)));
  resize_image.copyTo(image(cv::Rect(resize_image.cols, resize_image.rows, image.cols/2, image.rows/2)));
  cv::imshow("image", image);
  cv::waitKey(0);
  /**
   * copyTo()函数的形式详解
   * image.copyTo(imageROI),作用是把image的内容复制粘贴到imageROI上
   * image.copyTo(imageROI,mask),作用是把mask和image重叠以后把mask中像素值为0（black）的点变为透明这样就会只显示image中的其它点了
   */

  cv::Mat mask;
  cv::resize(resize_image, mask, cv::Size(0,0),0.5,0.5,CV_INTER_LINEAR);
  cv::Mat mask_gray;
  cv::cvtColor(mask,mask_gray,CV_RGB2GRAY); // 加载掩模（必须是灰度图）
  mask.copyTo(resize_image(cv::Rect(0,0,mask.cols,mask.rows)),mask_gray); // 将掩膜拷贝到ROI
  cv::imshow("resize_image", resize_image);
  cv::waitKey(0);

  cv::rectangle(mask, cv::Rect(mask.cols-60, mask.rows-60, 60, 60), cv::Scalar(0, 0, 0), -1, 8);
  cv::Mat imageROI= resize_image(cv::Rect(0,0,mask.cols,mask.rows));
  cv::addWeighted(imageROI,0.5,mask,0.3,0.,imageROI);
  imshow("resize_image",resize_image);
  cv::waitKey(0);

  cv::destroyAllWindows();
  return 0;
}