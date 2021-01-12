#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

int main() {
    cv::Mat image;// 读取一张二维三通道图像
    image = cv::imread("../ubuntu.png");
    cv::Size dst_image_size(image.cols, image.rows);// 设置旋转后图像的尺寸
    if (image.data == nullptr) {
        std::cerr << "文件读取失败" << std::endl;// 判断图像文件是否正确读取
        return 0;// 没有读取图片return 0终止 main 函数
    }
    cv::imshow("原始图像", image);
    cv::waitKey(0);

    cv::Point2f rotation_center(static_cast<float>(image.cols / 2.), static_cast<float>(image.rows / 2.));// 指定旋转中心
    std::cout << "旋转中心:\n" << rotation_center << std::endl;
    cv::Mat rotation_matrix = cv::getRotationMatrix2D(rotation_center, 45, 1.0); // 构造旋转矩阵
    std::cout << "旋转矩阵:\n" << rotation_matrix << std::endl;
    /**
     * 调用 cv::getRotationMatrix2D 获得图像绕着中心点旋转45度的旋转矩阵
     * 函数原型：
     * Mat getRotationMatrix2D(Point2f center, double angle, double scale)
     * 参数详解：
     * Point2f center：表示旋转的中心点
     * double angle：表示旋转的角度
     * double scale：图像缩放因子
     */
    cv::Mat rotation_image;// 旋转后的图像
    cv::warpAffine(image, rotation_image, rotation_matrix, dst_image_size,cv::INTER_LINEAR);
    /**
     * 仿射变换 warpAffine　简单来说就是:"线性变换"+"平移" 线性变换通过矩阵乘法来实现,变换前是直线的,变换后依然是直线,直线比例保持不变
     * 仿射变换是图像基于3个固定顶点的变换 在2D平面中应用较多 https://www.zhihu.com/question/20666664
     * void warpAffine( InputArray src, OutputArray dst, InputArray M, Size dsize, int flags = INTER_LINEAR,
     *                  int borderMode = BORDER_CONSTANT, const Scalar& borderValue = Scalar());
     * InputArray src, input image 输入变换前图像
     * OutputArray dst,output image that has the size dsize and the same type as src 输出变换后图像,需要初始化一个空矩阵用来保存结果,不用设定矩阵尺寸
     * InputArray M, transformation matrix 变换矩阵,生成方法有cv::getRotationMatrix2D()和getAffineTransform()函数
     * Size dsize, size of the output image 设置输出图像大小
     * int flags=INTER_LINEAR, INTER_NEAREST:最近邻插值, INTER_LINEAR:双线性插值, INTER_CUBIC:双三次样条插值, INTER_LANCZOS4:Lanczos插值
     * int borderMode=BORDER_CONSTANT, 表示目标图像中离群点(outliers)的像素值不会被此函数修改
     * const Scalar& borderValue=Scalar()) 边界填充值默认情况下为黑０
     */
    cv::imshow("旋转图像", rotation_image);
    cv::waitKey(0);

    cv::Mat translation_matrix =cv::Mat::zeros(2, 3, CV_32FC1);// 构造平移矩阵
    translation_matrix.at<float>(0, 0) = 1;
    translation_matrix.at<float>(0, 2) = 150;// 水平平移量
    translation_matrix.at<float>(1, 1) = 1;
    translation_matrix.at<float>(1, 2) = 150;// 竖直平移量
    std::cout << "平移矩阵:\n"<< translation_matrix << std::endl;
    cv::Mat translation_image;// 创建平移后的图像
    cv::warpAffine(image, translation_image, translation_matrix, dst_image_size);
    cv::imshow("平移图像", translation_image); // 显示平移效果
    cv::waitKey(0);

    cv::Point2f warpAffine_AffinePoints0[3] = { cv::Point2f(100, 50), cv::Point2f(100, 390), cv::Point2f(600, 50) };
    // 设置原图变换顶点
    cv::Point2f warpAffine_AffinePoints1[3] = { cv::Point2f(200, 100), cv::Point2f(200, 330), cv::Point2f(500, 50) };
    // 设置目标图像变换顶点
    cv::Mat affine_transform_matrix = cv::getAffineTransform(warpAffine_AffinePoints0, warpAffine_AffinePoints1);
    std::cout << "仿射变换矩阵:\n"<< affine_transform_matrix << std::endl;
    /**
     * 用函数Mat getAffineTransform( const Point2f src[], const Point2f dst[] );生成变换矩阵
     * 参数 const Point2f* src:原图的三个固定顶点
     * 参数 const Point2f* dst:目标图像的三个固定顶点
     * 返回值:Mat型变换矩阵,可直接用于warpAffine()函数
     * 注意:顶点数组长度超过3个,则会自动以前3个为变换顶点,数组可用Point2f[]或Point2f*表示
     */
    cv::Mat affine_transform_image;// 变换后的图像
    warpAffine(image, affine_transform_image, affine_transform_matrix, cv::Size(image.cols, image.rows));
    for (int i = 0; i <3; i++){
      circle(image, warpAffine_AffinePoints0[i], 2, cv::Scalar(0, 0, 255),2);
      circle(affine_transform_image, warpAffine_AffinePoints1[i], 2,cv::Scalar(0, 0, 255), 2);
    }
    imshow("仿射变换", affine_transform_image);// 显示affine_transform_image变换后的效果
    cv::waitKey(0);

    cv::Point2f Points0[4] = { cv::Point2f(100, 50), cv::Point2f(100, 390), cv::Point2f(600, 50), cv::Point2f(600, 390) };
    cv::Point2f Points1[4] = { cv::Point2f(200, 100), cv::Point2f(200, 330), cv::Point2f(500, 50), cv::Point2f(600, 390) };
    cv::Mat perspective_trans_matrix = getPerspectiveTransform(Points0, Points1);// 设定变换对应的几个点getPerspectiveTransform生成变换矩阵
    std::cout << "透视变换矩阵:\n"<< perspective_trans_matrix << std::endl;
    cv::Mat warp_perspective_image;
    warpPerspective(image, warp_perspective_image, perspective_trans_matrix,cv::Size(image.cols, image.rows), CV_INTER_CUBIC);
    /**
    透视变换是图像基于4个固定顶点3D平面的变换,主要作用是对图像进行变形,仿射等是透视变换的特殊形式,经过透视变换之后的图片通常不是平行四边形除非映射视平面和原来平面平行的
    函数原型:
    void warpPerspective(InputArray src, OutputArray dst, InputArray M, Size dsize, int flags=INTER_LINEAR, int borderMode=BORDER_CONSTANT,
     　　　　　　　　　　　　const Scalar& borderValue=Scalar())
    参数详解:
    InputArray　src:输入的图像
    OutputArray dst:输出的图像
    InputArray M:透视变换的矩阵
    Size dsize:输出图像的大小
    int flags=INTER_LINEAR:输出图像的插值方法
    int borderMode=BORDER_CONSTANT:图像边界的处理方式
    const Scalar& borderValue=Scalar():边界的颜色设置,一般默认是0
    */
    for (int i = 0; i < 4; i++){
      circle(image, Points0[i], 2, cv::Scalar(0, 0,255), 2);
      circle(warp_perspective_image, Points1[i], 2, cv::Scalar(0, 0, 255), 2);
    }
    imshow("透视变换", warp_perspective_image);
    cv::waitKey(0);// 暂停程序,等待一个按键输入,避免图像一闪而过

    cv::destroyAllWindows();
    return 0;
}
