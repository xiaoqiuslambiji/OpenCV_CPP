#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
  cv::Mat image;
  image = cv::imread("../ubuntu.png");
  if (image.data == nullptr) {
      std::cerr << "文件不存在" << std::endl;
      return 0;
  }
  cv::imshow("image * 0.5", image);
  cv::waitKey(0);

  cv::Mat half_image;
  cv::resize(image, half_image, cv::Size(0,0),0.5,0.5,CV_INTER_LINEAR);
  cv::imshow("image * 0.5", half_image);
  cv::waitKey(0);

  cv::Mat line_image = half_image.clone();
  cv::line(line_image, cv::Point(0, 150), cv::Point(image.cols, 150), cv::Scalar(0,255,0), 2,8);
  /**
   cv::line, 给定一个图像img,连接点pt1和pt2的坐标,在图中画一条直线,color表明线的颜色cv.line()
   CvPoint pt1, 直线起点
   CvPoint pt2, 直线终点
   cv::Scalar(0,255,0), 直线的颜色
   int thickness=1, 线条粗细
   int lineType = 8, 线型默认8邻域
   */
  cv::imshow("line_image", line_image);
  cv::waitKey(0);


  std::string text = "slam";//设置待绘制的文本
  int font_face = cv::FONT_HERSHEY_TRIPLEX;// 字体
  double font_scale = 2;// 尺寸因子,值越大文字越大
  int thickness = 2;// 线条宽度
  int baseline;//获取文本框的长宽
  cv::Size text_size = cv::getTextSize(text, font_face, font_scale, thickness, &baseline);
  /**
   cv::getTextSize()获取待绘制文本框的大小,以便放置文本框
   cv::Size cv::getTextSize(const string& text,int fontFace, double fontScale, int thickness, int* baseLine);
   */
  cv::Point origin;// 设置文本框
  origin.x = half_image.cols / 2 - text_size.width / 2;
  origin.y = half_image.rows / 2 + text_size.height / 2;
  cv::Mat text_iamge = half_image.clone();
  cv::putText(text_iamge, text, origin, font_face, font_scale, cv::Scalar(0, 0, 255), thickness, 8, 0);
  /**
    void cv::putText(
    cv::Mat& img, 待绘制的图像
    const string& text, 待绘制的文字
    cv::Point origin, 文本框的左下角
    int fontFace, 字体
    double fontScale, 尺寸因子
    cv::Scalar color, 线条的颜色
    int thickness = 1, 线条宽度
    int lineType = 8, 线型默认8邻域
    bool bottomLeftOrigin = false 文字是正立的否则倒立
   */
  cv::imshow("text_iamge", text_iamge);//显示绘制结果
  cv::waitKey(0);

  cv::Point center_1(100, 100);
  cv::Point center_2(half_image.cols-100,half_image.rows-100);// 初始化圆心
  cv::Mat circle_ellipse_image = half_image.clone();
  circle(circle_ellipse_image, center_1, 50, cv::Scalar(0, 255, 0),3,8);// 画空心圈
  circle(circle_ellipse_image, center_2, 50, cv::Scalar(0,0,255),-1,8 );// 画实心圆　-1表明这是个实心圆
  /**
   * Opencv画点其实画的是小圆圈
   * void cvCircle( CvArr* img, CvPoint center, int radius, CvScalar color, int thickness=1, int line_type=8, int shift=0 );
   * img:图像
   * center:圆心坐标
   * radius:圆的半径
   * color:线条的颜色
   * thickness:如果是正数表示组成圆的线条的粗细程度,否则表示圆是否被填充.
   * line_type:线条的类型
   * shift:圆心坐标点和半径值的小数点位数
   */
  ellipse(circle_ellipse_image, cv::Point(circle_ellipse_image.cols/2, circle_ellipse_image.rows/2),
          cv::Size(circle_ellipse_image.cols/4, circle_ellipse_image.rows/4),
          0, 0, 360, cv::Scalar(0, 0, 255), 2, 8);// 画空心椭圆
  ellipse(circle_ellipse_image, cv::Point(circle_ellipse_image.cols/2, circle_ellipse_image.rows/2),
          cv::Size(circle_ellipse_image.cols/4, circle_ellipse_image.rows/4),
          90, 0, 360, cv::Scalar(0, 0, 255), -1, 8);// 画实心椭圆
  /**
   * void ellipse(
   * InputOutputArray img, 图像
   * Point center, 椭圆原心
   * Size axes, 椭圆x轴长度的一半, y轴长度的一半
   * double angle, 椭圆旋转角度
   * double startAngle, 椭圆起始角度
   * double endAngle, 椭圆终止角度
   * const Scalar& color, 椭圆颜色
   * int thickness = 1, 线宽
   * int lineType = LINE_8, 线型
   * int shift = 0); 坐标小数点位数
   */
  imshow("circle_ellipse_image", circle_ellipse_image);
  cv::waitKey(0);

  cv::Mat rectangle_iamge = half_image.clone();
  cv::rectangle(rectangle_iamge, cv::Rect(100, 100, 300, 200), cv::Scalar(255, 0, 0), 2, 8);
  cv::rectangle( rectangle_iamge ,cv::Point( 200, 200 ) ,cv::Point( rectangle_iamge.cols, rectangle_iamge.cols),
                 cv::Scalar( 0, 0, 255),  -1, 8 );
  /**
   * rectangle()
   Mat& img, 输出图像
   Rect rec, 矩形的位置和长宽
   const Scalar& color, 矩形颜色
   int thickness = 1, 线宽 取负值时,函数绘制填充了色彩的矩形
   int lineType = LINE_8, 直线类型
   int shift = 0 点坐标的小数点位数
   */
  imshow("rectangle_image", rectangle_iamge);
  cv::waitKey(0);

  line_image.copyTo(image(cv::Rect(0, 0, image.cols/2, image.rows/2)));
  text_iamge.copyTo(image(cv::Rect(half_image.cols, 0, image.cols/2, image.rows/2)));
  circle_ellipse_image.copyTo(image(cv::Rect(0, half_image.rows, image.cols/2, image.rows/2)));
  rectangle_iamge.copyTo(image(cv::Rect(half_image.cols, half_image.rows, image.cols/2, image.rows/2)));
  /**
   * Rect矩形类包括Point点类的成员x和y(表示矩形的左上角)以及size类的成员width和height(表示矩形状宽高大小)
   */
  imshow("merge_image", image);
  cv::waitKey(0);
  cv::destroyAllWindows();
  return 0;
}


