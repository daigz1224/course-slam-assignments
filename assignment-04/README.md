# 第四节习题

## 图像去畸变

见 [code/undistort_image.cpp](code/undistort_image.cpp), 解畸变的图见[assets/test_undistort.png](assets/test_undistort.png)

``` c++
    double x = (u - cx) / fx, y = (v - cy) / fy;  // 获取该像素对应的相机坐标系下的单位坐标
    double r2 = x * x + y * y;
    double x_distorted = x * (1 + k1 * r2 + k2 * r2 * r2) + 2 * p1 * x * y + p2 * (r2 + 2 * x * x);
    double y_distorted = y * (1 + k1 * r2 + k2 * r2 * r2) + 2 * p2 * x * y + p1 * (r2 + 2 * y * y);
    u_distorted = x_distorted * fx + cx;          // 将解畸变后的相机坐标系下的单位坐标转回像素坐标
    v_distorted = y_distorted * fy + cy;
```

## 双目视差的使用

见 [code/disparity.cpp](code/disparity.cpp), 核心代码如下：

``` c++
    double x = (u - cx) / fx, y = (v - cy) / fy;  // 获取该像素对应的相机坐标系下的单位坐标
    float disp = disparity.at<uchar>(v, u);       // 获取 uchar 格式的视差
    double depth = fx * d / disp;                 // 计算深度
    point[0] = x * depth;                         // 将单位坐标通过深度还原
    point[1] = y * depth;
    point[2] = depth;
    pointcloud.push_back(point);
```

## 矩阵运算微分

1. 证明如图 [differential-01.jpg](differential-01.jpg)
2. 证明如图 [differential-02.jpg](differential-02.jpg)
3. 证明如图 [differential-03.jpg](differential-03.jpg)

## 高斯牛顿法的曲线拟合实验

见 [code/gaussnewton.cpp](code/gaussnewton.cpp)

``` c++11
    double error = 0;   // 第i个数据点的计算误差
    error = yi - exp(ae * xi * xi + be * xi + ce); // 填写计算error的表达式
    Vector3d J; // 雅可比矩阵
    J[0] = -exp(ae * xi * xi + be * xi + ce) * xi * xi;  // de/da
    J[1] = -exp(ae * xi * xi + be * xi + ce) * xi;       // de/db
    J[2] = -exp(ae * xi * xi + be * xi + ce);            // de/dc

    H += J * J.transpose(); // GN近似的H
    b += -error * J;
    // ...
    Vector3d dx;
    dx = H.ldlt().solve(b);  // 求解 Hx=b
```

## 批量最大似然估计

见 [batch_MLE.jpg](batch_MLE.jpg)
