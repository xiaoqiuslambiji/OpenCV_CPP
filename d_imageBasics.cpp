#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main(int argc, char **argv) {
    cv::Mat image;// 读取一张二维三通道图像
    image = cv::imread("../ubuntu.png");
    if (image.data == nullptr) {
        std::cerr << "文件不存在" << std::endl;// 判断图像文件是否正确读取如果不能读取可能是文件不存在
        return 0; // 没有读取图片return 0 终止函数
    }
    cv::imshow("image", image);
    cv::waitKey(0);

    cv::Mat salt_pepper_image = image.clone();// 为图像添加椒盐噪声
    for (int k = 0; k < 3000; k++) {
        int i = rand() % salt_pepper_image.rows;
        int j = rand() % salt_pepper_image.cols; //随机取值行列
        if (salt_pepper_image.channels() == 1) {// 图像通道判定,如果是单通道,直接把像素变成白色
            salt_pepper_image.at<uchar>(i, j) = 255;// 行()索引 列[]索引 255 白色盐噪声
        }
        else {
            salt_pepper_image.at<cv::Vec3b>(i, j)[0] = 255;
            salt_pepper_image.at<cv::Vec3b>(i, j)[1] = 255;
            salt_pepper_image.at<cv::Vec3b>(i, j)[2] = 255;// 行()索引 列[]索引 白色盐噪声
        }
    }
    for (int k = 0; k < 3000; k++) {
        int i = rand() % salt_pepper_image.cols;
        int j = rand() % salt_pepper_image.rows;
        if (salt_pepper_image.channels() == 1) {
            salt_pepper_image.at<uchar>(j, i) = 0;
        }
        else if (salt_pepper_image.channels() == 3) {
            salt_pepper_image.at<cv::Vec3b>(j, i)[0] = 0;
            salt_pepper_image.at<cv::Vec3b>(j, i)[1] = 0;
            salt_pepper_image.at<cv::Vec3b>(j, i)[2] = 0;// 行()索引 列[]索引 黑色 椒噪声
        }
    }
    cv::imshow("salt_pepper_image", salt_pepper_image);
    cv::waitKey(0);

    cv::Mat gaussian_blur_image;
    cv::GaussianBlur(image, gaussian_blur_image, cv::Size(5, 5), 3, 3, 0);// 为图像添加高斯噪声
    /**
     函数原型:
     void GaussianBlur(InputArray src, OutputArray dst, Size ksize, double sigmaX, double sigmaY=0, int borderType=BORDER_DEFAULT);
     参数详解:
     src,输入源图像,图片深度应该为CV_8U,CV_16U, CV_16S, CV_32F,CV_64F之一
     dst,输出目标图像,需要和源图片有一样的尺寸和类型,比如可以用Mat::Clone,以源图片为模板来初始化目标图像
     ksize,高斯核的大小,其中ksize.width和ksize.height可以不同,但他们都必须为正数和奇数或者可以是零由sigma计算而来
     sigmaX,表示高斯核函数在X方向的的标准偏差
     sigmaY,表示高斯核函数在Y方向的的标准偏差,若sigmaY为零,就将它设为sigmaX,如果sigmaX和sigmaY都是0,那么就由ksize.width和ksize.height计算出来
     borderType,像素外插策略
     */
    cv::imshow("gaussian_blur_image", gaussian_blur_image);
    cv::waitKey(0);

    cv::Mat median_blur_image;
    cv::medianBlur(image, median_blur_image, 5);//中值滤波
    /**
    参数5表示选择附近5*5区域的像素值进行计算
    中值滤波将图像的每个像素用邻域(以当前像素为中心的正方形区域)像素的中值代替与邻域平均法类似,但计算的是中值
    函数原型:
    void medianBlur(InputArray src, OutputArray dst, int ksize)
    参数详解:
    InputArray类型的src,函数的输入参数,填1,3或者4通道的Mat类型的图像,当ksize为3或者5的时候,图像深度需为CV_8U,CV_16U,或CV_32F其中之一,而对于较大孔径尺寸的图片,它只能是CV_8U,
    OutputArray类型的dst,即目标图像,函数的输出参数,需要和源图片有一样的尺寸和类型,我们可以用Mat::Clone,以源图片为模板,来初始化得到如假包换的目标图,
    int类型的ksize,孔径的线性尺寸,注意这个参数必须是大于1的奇数,比如,3,5,7,9,
    中值滤波,是一种典型的非线性滤波技术,基本思想是用像素点邻域灰度值的中值来代替该像素点的灰度值,该方法在去除脉冲噪声,椒盐噪声的同时又能保留图像边缘细节,
    中值滤波是基于排序统计理论的一种能有效抑制噪声的非线性信号处理技术,
    其基本原理是把数字图像或数字序列中一点的值用该点的一个邻域中各点值的中值代替,让周围的像素值接近的真实值,
    从而消除孤立的噪声点,对于斑点噪声和椒盐噪声来说尤其有用,因为它不依赖于邻域内那些与典型值差别很大的值,中值滤波器在处理连续图像窗函数时与线性滤波器的工作方式类似,但滤波过程却不再是加权运算,
    中值滤波在一定的条件下可以克服常见线性滤波器如最小均方滤波,方框滤波器,均值滤波等带来的图像细节模糊,而且对滤除脉冲干扰及图像扫描噪声非常有效,
    也常用于保护边缘信息,保存边缘的特性使它在不希望出现边缘模糊的场合也很有用,是非常经典的平滑噪声处理方法,
    */
    cv::imshow("median_blur_image", median_blur_image);
    cv::waitKey(0);

    cv::Mat bilateral_filter_image;
    cv::bilateralFilter(image, bilateral_filter_image, 9, 175, 175);// 双边滤波
    /**
    双边滤波是一种非线性的滤波方法,是结合图像的空间邻近度和像素值相似度的一种折衷处理,
    同时考虑空间与信息和灰度相似性,达到保边去噪的目的,具有简单,非迭代,局部处理的特点,
    之所以能够达到保边去噪的滤波效果是因为滤波器由两个函数构成,
    一个函数是由几何空间距离决定滤波器系数,另一个是由像素差值决定滤波器系数,
    双边滤波器中,输出像素的值依赖于邻域像素的值的加权组合,
    函数原型:
    void bilateralFilter(InputArray src, OutputArray dst, int d, double sigmaColor, double sigmaSpace, int borderType=BORDER_DEFAULT )
    参数解释:
    InputArray src: 输入图像,可以是Mat类型,图像必须是8位或浮点型单通道,三通道的图像,
    OutputArray dst: 输出图像,和原图像有相同的尺寸和类型,
    int d: 表示在过滤过程中每个像素邻域的直径范围,如果这个值是非正数,则函数会从第五个参数sigmaSpace计算该值,
    double sigmaColor: 颜色空间过滤器的sigma值,这个参数的值越大,表明该像素邻域内有越宽广的颜色会被混合到一起,产生较大的半相等颜色区域,
    double sigmaSpace: 坐标空间中滤波器的sigma值,如果该值较大,则意味着颜色相近的较远的像素将相互影响,从而使更大的区域中足够相似的颜色获取相同的颜色,
                       当d>0时,d指定了邻域大小且与sigmaSpace无关,否则d正比于sigmaSpace,
    int borderType=BORDER_DEFAULT: 用于推断图像外部像素的某种边界模式,有默认值BORDER_DEFAULT,
    双边滤波器可以很好的保存图像边缘细节而滤除掉低频分量的噪音,但是双边滤波器的效率不是太高,花费的时间相较于其他滤波器而言也比较长,
    对于简单的滤波而言,可以将两个sigma值设置成相同的值,如果值<10则对滤波器影响很小,如果值>150则会对滤波器产生较大的影响,会使图片看起来像卡通,
     */
    cv::imshow("bilateral_filter_image", bilateral_filter_image);
    cv::waitKey(0);
    cv::destroyAllWindows();
    return 0;
}