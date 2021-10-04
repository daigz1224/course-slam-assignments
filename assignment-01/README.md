# 第一章作业

## 熟悉 Linux

1. 如何在 Ubuntu 中安装软件(命令行界面)?它们通常被安装在什么地方？
    - install package

    ``` bash
    # apt or apt-get
    sudo apt install {{package}}

    # deb
    sudo dpkg -i {{package.deb}}

    # rpm
    sudo alien {{package.rpm}} && sudo dpkg -i {{package.deb}}

    # AppImage and others
    chmod u+x {{package.AppImage}} && ./{{package.AppImage}}
    ```

    - 一般安装在 /usr 或 /usr/local 下

2. linux 的环境变量是什么?我如何定义新的环境变量?
    - 环境变量是在操作系统中一个具有特定名字的对象，它包含了一个或者多个应用程序所将使用到的信息。譬如 PATH，决定了 shell 将到哪些目录寻找命令或程序
    - 定义新的环境变量

    ``` bash
    # 仅当前终端生效
    export MY_ENV_VARIABLE=BLABLABLA

    # 针对所有用户生效
    echo "export MY_ENV_VARIABLE=BLABLABLA" >> /etc/profile

    # 针对当前用户生效(以 bash 为例)
    echo "export MY_ENV_VARIABLE=BLABLABLA" >> ~/.bashrc
    ```

3. linux 根目录下面的目录结构是什么样的?至少说出 3 个目录的用途。
    - /bin: 用户二进制文件，系统全部用户可执行文件
    - /sbin: 系统二进制文件，只能由系统管理员运行
    - /etc: 配置文件，包含全部程序配置文件，也包含了用于启动/中止单个程序的启动和关闭shell脚本
    - /dev: 设备文件
    - /proc: 进程信息
    - /var: 变量文件
    - /tmp: 临时文件，当系统重新启动时，这个目录下的文件都将被删除
    - /usr: 用户程序，包含二进制文件、库文件、文档和二级程序的源代码。
    - /home: 用户 HOME 目录
    - /boot: 引导加载程序文件，包含引导加载程序相关的文件，譬如内核的 initrd、vmlinux、grub 文件
    - /lib: 系统库，包含支持位于 /bin 和 /sbin 下的二进制文件的库文件
    - /opt: 可选的附加应用程序
    - /mnt: 挂载目录
    - /media: 可移动媒体设备
    - /srv: 服务数据

4. 假设我要给 a.sh 加上可执行权限，该输入什么命令?

    ``` bash
    chmod +x a.sh
    ```

5. 假设我要将 a.sh 文件的所有者改成 xiang:xiang，该输入什么命令？

    ``` bash
    chown xiang:xiang a.sh
    ```

## SLAM 综述文献阅读

1. SLAM 会在哪些场合中用到？至少列举三个方向。
    - 自动驾驶，AR，VR, 自主机器人，无人机等
2. SLAM 中定位与建图是什么关系？为什么在定位的同时需要建图？
    - 定位和建图是相互依赖的，准确的定位依赖正确的地图，而构建正确的地图需要准确的定位。
    - SLAM 是在未知的环境下进行定位和建图，有地图的定位和有定位的地图创建都是容易解决的，但无地图的定位和未解决定位的地图创建需要一个迭代、相辅相成的过程。
3. SLAM 发展历史如何？我们可以将它划分成哪几个阶段？
    SLAM 最早由 Smith、Self 和 Cheeseman 于 1988 年提出。 由于其重要的理论与应用价值，被很多学者认为是实现真正全自主移动机器人的关键。SLAM 的发展可以大致分为三个阶段：
    - 朴素时期：classical age（1986-2004）。classical age 出现了 SLAM 最基本的概率公式，包括基于扩展卡尔曼滤波器（EKF），Rao-Blackwellised 粒子滤波器和最大似然估计的方法。此外，它还剔除了与效率以及鲁棒数据等相关的基本问题，这也是日后的发展方向。
    - 算法分析时期：algorithmic-analysis age（2004-2015），这一时期研究了 SLAM 的基本特性，包括可观察性，收敛性，一致性以及稀疏性对 SLAM 高效求解的关键作用，主要的开源 SLAM 库在这个时期得到了开发。
    - 鲁棒性-预测性时代: robust-perception（2015-至今）：这一时期主要探索 SLAM 在位置环境中对鲁棒性、高级别的场景理解，计算资源优化，任务驱动的环境感知等。
4. 列举三篇在 SLAM 领域的经典文献。
    - [On the Representation and Estimation of Spatial Uncertainty](https://frc.ri.cmu.edu/~hpm/project.archive/reference.file/Smith&Cheeseman.pdf): 1986 年的开山之作
    - [ORB-SLAM2: an Open-Source SLAM System for Monocular, Stereo and RGB-D Cameras](https://arxiv.org/pdf/1610.06475.pdf): 2016 年的开源系统框架，当前在定位上应用最多的稀疏建图框架
    - [SuperPoint: Self-Supervised Interest Point Detection and Description](https://arxiv.org/pdf/1712.07629.pdf): 2018 年的基于深度学习提取特征和描述子的开山之作

## CMake 练习

作业见: [hello/CMakeLists.txt](hello/CMakeLists.txt), 另修改了源码文件的后缀（.c -> .cc）来适配 `#include <iostream>`

## 理解 ORB-SLAM2 框架

1. 截图见 [ORB_SLAM2-clone.png](ORB_SLAM2-clone.png)
2. 问题：
    - ORB-SLAM2 将编译出什么结果?有几个库文件和可执行文件?
        - 1 个库文件：lib/libORB_SLAM2.so
        - 6 个可执行文件：
            - ./Examples/Monocular/mono_euroc
            - ./Examples/Monocular/mono_kitti
            - ./Examples/Monocular/mono_tum
            - ./Examples/Stereo/stereo_euroc
            - ./Examples/Stereo/stereo_kitti
            - ./Examples/RGB-D/rgbd_tum
    - ORB-SLAM2 中的 include, src, Examples 三个文件夹中都含有什么内容?
        - include 包含头文件
        - src 包含源文件
        - Examples 包含 Monocular，RGB-D，ROS，Stereo 四个文件夹，有对应 EuRoC, KITTI, TUM 的数据集运行示例
    - ORB-SLAM2 中的可执行文件链接到了哪些库?它们的名字是什么?
        - 链接了 OpenCV，Eigen，Pangolin，DBoW2，g2o

## 使用摄像头或视频运行 ORB-SLAM2

1. 截图见 [ORB_SLAM2-build.png](ORB_SLAM2-build.png)
2. CMakelists.txt 添加 executable 并链接库即可

    ``` cmake
    add_executable(myvideo myvideo.cpp)
    target_link_libraries(myvideo ${PROJECT_NAME})
    ```

3. 截图见 [ORB_SLAM2-video.png](ORB_SLAM2-video.png)
