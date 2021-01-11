#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
  // 本教程通过创建二维三通道图像,创建带alpha通道的透明图像和读取图像来讲解图像的维度,通道,深度,类型,四种遍历方式等相关内容
  /*****************************************************************************
 　* 创建一张二维三通道图像
 　*****************************************************************************/
  cv::Mat q_image(674, 1200, CV_8UC3, cv::Scalar(0,0,255));
  /**
   * cv::Mat定义一个矩阵行数/高为image.rows,列数/宽为image.cols
   * CV_(位数)+(数据类型)+(通道数)
   * 其中CV_后面紧接的数字表示位数,分别对应8bit,16bit
   * U表示Unsigned无符号整数类型,即其内部元素的值不可以为负数
   * S表示Signed有符号整数类型,其值存在负数
   * F则表示浮点数类型,即矩阵的内部元素值可以为小数(32对应单精度float类型,64对应双精度double类型)
   * C1~C4表示对应的通道数,即有1~4个通道
   *
   *【1】CV_8UC1---则可以创建----8位无符号的单通道---灰度图片------grayImg
   * #define CV_8UC1 CV_MAKETYPE(CV_8U,1)  type 预定义的常量 = 0
   *
   *【2】CV_8UC3---则可以创建----8位无符号的三通道---RGB彩色图像---colorImg
   * #define CV_8UC3 CV_MAKETYPE(CV_8U,3)  type 预定义的常量 = 16
   *
   *【3】CV_8UC4--则可以创建-----8位无符号的四通道---带透明色Alpha通道的RGB图像
   * #define CV_8UC4 CV_MAKETYPE(CV_8U,4)  type 预定义的常量 = 24
   *
   * cv::Scalar(0,0,255)每个像素由三个元素组成即三通道,初始化颜色值为(0,0,255)
   *
  */
  std::cout << "q_image.rows: " << q_image.rows << std::endl; // 674
  std::cout << "q_image.cols: " << q_image.cols << std::endl; // 1200
  std::cout << "q_image.dims: " << q_image.dims << std::endl; // 2
  std::cout << "q_image.channels(): " << q_image.channels() << std::endl; // 3
  std::cout << "q_image.type(): " << q_image.type() << std::endl; // 16
  /**
   * 类型表示了矩阵中元素的类型以及矩阵的通道个数
   * 它是一系列的预定义的常量,其命名规则为CV_(位数)+(数据类型)+(通道数)
   * CV_8UC3 = 16 , CV_16UC3 = 18
   */
  std::cout << "q_image.depth(): " << q_image.depth() << std::endl; // 0
  // depth用来度量每一个像素中每一个通道的精度,但它本身与图像的通道数无关,depth数值越大精度越高
  // Opencv中,Mat.depth()得到的是一个0~6的数字,分别代表不同的位数
  // 对应关系如下: enum{CV_8U=0, CV_8S=1, CV_16U=2, CV_16S=3, CV_32S=4, CV_32F=5, CV_64F=6}
  // 可见0和1都代表8位,2和3都代表16位,4和5代表32位,6代表64位
  // 其中U是unsigned无符号数的意思,S表示signed有符号数的意思
  std::cout << "q_image.elemSize(): " << q_image.elemSize() << std::endl; // 3(通道)
  // 矩阵中元素的个数为image.rows*image.cols=674*1200
  // elemSize以8位(一个字节)为单位表示矩阵中每一个元素的字节数
  // 数据类型是CV_8UC1,elemSize==1
  // 数据类型是CV_8UC3或CV_8SC3,elemSize==3
  // 数据类型是CV_16UC3或CV_16SC3,elemSize==6
  std::cout << "q_image.elemSize1(): " << q_image.elemSize1() << std::endl; // 1(字节)
  // elemSize加上一个"1"构成了elemSize1这个属性,可认为是元素内1个通道的意思
  // 表示Mat矩阵中每一个元素单个通道的数据大小,以字节为单位,所以eleSize1==elemSize/channels
  std::cout << "q_image.step: " << q_image.step << std::endl; // 3600
  // step可以理解为Mat矩阵中每一行的"步长",以字节为单位,step=elemSize()*cols=3*1200=3600
  // 每一行中所有元素的字节总量,累计了一行中所有元素,所有通道,所有通道的elemSize1之后的值
  cv::namedWindow( "q_image", CV_WINDOW_AUTOSIZE );
  imshow( "q_image", q_image);
  cv::waitKey(0);


  /*****************************************************************************
 　* 创建一张alpha通道的Mat图像
 　*****************************************************************************/

  //创建带alpha通道的Mat
  cv::Mat mat(480, 640, CV_8UC4);
  for(int i = 0; i < mat.rows; ++i) {
    for(int j = 0; j < mat.cols; ++j) {
      auto &rgba = mat.at<cv::Vec4b>(i, j);
      /**
       * OpenCV源代码中的定义 typedef Vec <uchar, 2> Vec2b
       * Vec2b 表示每个Vec2b对象可以存储2个char(字符型)数据
       * vec3b 表示每个Vec3b对象可以存储3个char(字符型)数据,比如可以用这样的对象,去存储RGB图像中的
       * vec4b 表示每个Vec4b对象可以存储4个字符型数据,可以用这样的类对象去存储—4通道RGB+Alpha的图
       * mat.at<cv::Vec4b>(i, j);
　　　　* 从mat中取出一个像素,像素的类型是Vec4b该类型含义是,有4个UCHAR类型的元素
　　　　* 其中rgba[0],rgba[1],rgba[2]代表像素三原色BGR,即为蓝色Blue,Green绿色,红色Red,rgba[3]代表像素的Alpha值表示像素透明度
       */
      rgba[0]= UCHAR_MAX;
      rgba[1]= cv::saturate_cast<uchar>((float (mat.cols - j)) / ((float)mat.cols) *UCHAR_MAX);
      rgba[2]= cv::saturate_cast<uchar>((float (mat.rows - i)) / ((float)mat.rows) *UCHAR_MAX);
      rgba[3]= cv::saturate_cast<uchar>(0.5 * (rgba[1] + rgba[2]));
    }
  }
  imshow("带alpha通道的图像",mat);
  cv::waitKey(0);


  /*****************************************************************************
   * 读取一张二维三通道图像
   *****************************************************************************/
  cv::Mat image;
  // 新版本OpenCV中引入Mat类自动管理内存处理图像数据 读入一张图片
  image = cv::imread("../ubuntu.png",-1);
  /**
   * flag=-1   8位深度  原通道 按照图像原样读取 保留Alpha通道（第4通道）
   * flag=0    8位深度  1通道 将图像转成单通道灰度图像后读取
   * flag=1    8位深度  3通道 将图像转换成3通道BGR彩色图像
   * CV_LOAD_IMAGE_UNCHANGED = -1
   * CV_LOAD_IMAGE_GRAYSCALE = 0
   * CV_LOAD_IMAGE_COLOR     = 1
   */
  // cv::imread函数读取argv[1]指定路径下的图像
  if (image.data == nullptr) {
    std::cerr << "文件" << argv[1] << "不存在." << std::endl;
    // 判断图像文件是否正确读取如果不能读取可能是文件不存在
    return 0;
    // 没有读取图片return 0终止函数
  }
  cv::namedWindow( "image", CV_WINDOW_AUTOSIZE );
  // OpenCV创建显示图像窗口"image"
  imshow( "image", image);
  // 在窗口"image"显示图像image
  cv::waitKey(0);
  // 等待任意按键按下退出,不加这一句窗口会一闪而过
  // 等待6000 ms后窗口自动关闭 waitKey(6000);
  std::cout << "image.rows: " << image.rows << std::endl;
  // image.rows图像的行数是: 674
  std::cout << "image.cols: " << image.cols << std::endl;
  // image.cols图像的列数是: 1200
  std::cout << "image.dims: " << image.dims << std::endl;
  // image.dims图像的维度是: 2
  std::cout << "image.channels(): " << image.channels() << std::endl;
  // image.channels()图像的通道是: 3
  std::cout << "image.type(): " << image.type() << std::endl;
  // image.type()图像的类型是: 16
  std::cout << "image.depth(): " << image.depth() << std::endl;
  // image.depth()图像的深度是: 0
  std::cout << "image.elemSize(): " << image.elemSize() << std::endl;
  // image.elemSize()图像的elemSize是: 3
  std::cout << "image.elemSize1(): " << image.elemSize1() << std::endl;
  // image.elemSize1()图像的elemSize1是: 1

  // 转换为灰度图像
  cv::Mat gray_image;
  cv::cvtColor(image, gray_image, cv::COLOR_BGR2GRAY);
  imshow( "gray_image", gray_image);
  // 在窗口"gray_image"显示图像gray_image
  cv::waitKey(0);
  // 按任意键退出,不加这一句窗口会一闪而过
  std::cout << "gray_image.rows: " << gray_image.rows << std::endl;
  // gray_image.rows图像的行数是: 674
  std::cout << "gray_image.cols: " << gray_image.cols << std::endl;
  // gray_image.cols图像的列数是: 1200
  std::cout << "gray_image.dims: " << gray_image.dims << std::endl;
  // gray_image.dims图像的维度是: 2
  std::cout << "gray_image.channels(): " << gray_image.channels() << std::endl;
  // gray_image.channels()图像的通道是: 1
  std::cout << "gray_image.type(): " << gray_image.type() << std::endl;
  // gray_image.type()图像的类型是: 0
  std::cout << "gray_image.depth(): " << gray_image.depth() << std::endl;
  // gray_image.depth()图像的深度是: 0
  std::cout << "gray_image.elemSize(): " << gray_image.elemSize() << std::endl;
  // gray_image.elemSize()图像的elemSize是: 1
  std::cout << "gray_image.elemSize1(): " << gray_image.elemSize1() << std::endl;
  // gray_image.elemSize1()图像的elemSize1是: 1

  /*****************************************************************************
   * 常用Mat类矩阵元素读取方式有:通过at方法进行读取,通过指针ptr进行读取,通过迭代器进行读取,
   * 通过矩阵元素的地址定位方式进行读取,接下来将详细的介绍这四种读取方式.
   *****************************************************************************/
  // 通过at方法读取单通道Mat矩阵类中的元素
  cv::Mat M4 = (cv::Mat_<double>(3, 3) << 0, -1, 0, -1, 0, 0, 0, 0, 1);
  // 创建自定义数据的矩阵Mat
  std::cout << "M4 = " << std::endl << M4 << std::endl;
  double value = M4.at<double>(0,1); // -1
  // 通过at方法读取元素需要在后面跟上<数据类型>以坐标的形式给出需要读取的元素坐标(行数,列数)
  std::cout << "value = " << value << std::endl;

  // at 方法读取三通道Mat矩阵类中的元素
  /**
   * Mat类中获取或改变该像素点的灰度值或者RGB值，可以通过image.at<uchar>(i,j)的方式。
   * 单通道图像image.at<uchar>(i, j) i对应的是点的y坐标，j对应的是点的x坐标，而不是我们习惯的（x,y）
   * RGB
   * image.at<Vec3b>(i, j)[0]
   * image.at<Vec3b>(i, j)[1]
   * image.at<Vec3b>(i, j)[2]
   */
  cv::Mat M5(3, 4, CV_8UC3, cv::Scalar(0, 0, 255));
  // 读取彩色图像像素
  for(int i = 0;i < M5.rows;i++){
    for(int j = 0;j < M5.cols;j++){
      std::cout << "M5.at<cv::Vec3b>(i,j)[0]: " << int(M5.at<cv::Vec3b>(i,j)[0]) << std::endl;  //蓝色通道
      std::cout << "M5.at<cv::Vec3b>(i,j)[0]: " << int(M5.at<cv::Vec3b>(i,j)[1]) << std::endl;  //绿色通道
      std::cout << "M5.at<cv::Vec3b>(i,j)[0]: " << int(M5.at<cv::Vec3b>(i,j)[2]) << std::endl;  //红是通道
      // 通过at方法读取多通道Mat矩阵类中的元素,多通道矩阵每一个元素坐标处都是多个数据,因此引入一个变量用于表示同一元素多个数据
      // OpenCV中定义cv::Vec3b,cv::Vec3s,cv::Vec3w,cv::Vec3d,cv::Vec3f,cv::Vec3i六种类型表示同一个元素的三个通道数据
      // 数字表示通道的个数,最后一位是数据类型的缩写,b是uchar类型的缩写,s是short类型的缩写,w是ushort类型的缩写,
      // d是double类型的缩写,f是float类型的缩写,i是int类型的缩写
    }
  }

  // 通过指针ptr读取Mat类矩阵中的元素
  cv::Mat M6(3, 4, CV_8UC3, cv::Scalar(0, 0, 1));
  for (int i = 0; i < M6.rows; i++){
    // 循环遍历图像的每一行
    uchar* row_ptr = M5.ptr(i);
    // 用cv::Mat::ptr获得图像的行头指针,再定义一个uchar类型的row_ptr指向第i行的头指针
    for (int j = 0; j < M6.cols*M6.channels(); j++){
      // 循环遍历图像矩阵中每一行所有通道的数据
      // Mat类矩阵矩阵中每一行中的每个元素都是挨着存放,每一行中存储的数据数量为列数与通道数的乘积
      // 即代码中指针向后移动cols*channels()-1位,当读取第2行数据中第3个数据时,可以直接用M6.ptr(1)[2]访问
      std::cout << "row_ptr[" << j << "]: " << (int)row_ptr[j] << std::endl;
      // 循环输出每一个通道中的数值
    }
  }


  // 通过迭代器访问Mat类矩阵中的元素
  // Mat类变量同时也是一个容器变量,所以Mat类变量拥有迭代器,用于访问Mat类变量中的数据,通过迭代器可以实现对矩阵中每一个元素的遍历
  cv::Mat M7(3, 4, CV_8UC3, cv::Scalar(0, 1, 2));
  cv::MatIterator_<uchar> it = M7.begin<uchar>();
  // 初始位置的迭代器
  cv::MatIterator_<uchar> it_end = M7.end<uchar>();
  // 终止位置的迭代器
  // Mat类的迭代器变量类型是cv::MatIterator_< >,在定义时同样需要在括号中声明数据的变量类型
  // Mat类迭代器的起始是Mat.begin< >(),结束是Mat.end< >(),与其他迭代器用法相同,通过"++"运算实现指针位置向下迭代
  // 数据的读取方式是先读取第一个元素的每一个通道,之后再读取第二个元素的每一个通道,直到最后一个元素的最后一个通道
  for(; it != it_end; it++){
    std::cout << (int)(*it) << " ";
    std::cout << std::endl;
  }
  cv::destroyAllWindows();
  return 0;
}
