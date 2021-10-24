# 第三节习题

## 群的性质

1. `{Z, +}` 是否为群？
`{Z, +}` 是群。满足封闭性、结合律、幺元、逆四条性质:
    - 封闭性：对任意 `a1, a2 ∈ Z`, 满足 `a1 + a2 ∈ Z`;
    - 结合律：对任意 `a1, a2, a3 ∈ Z`，满足 `a1 + a2 + a3 = a1 + (a2 + a3) ∈ Z`
    - 幺元：存在 `0 ∈ Z`，对任意 `a ∈ Z`, 满足 `a + 0 ∈ Z`
    - 逆：对任意 `a ∈ Z`, 存在 `-a ∈ Z`，使得 `a + (-a) = 0`

2. `{N, +}` 是否为群？
`{N, +}` 不是群，对任意 `a ∈ N, a ≠ 0`，因 `-a ∉ N`，所以不满足逆的性质要求。

## 验证向量叉乘的李代数性质

现取集合 `V = R3`，数域 `F = R`，李括号为: `[a, b] = a x b`, 请验证 `g = (R3, R, ×)` 构成李代数。

证明：
    - 封闭性：对任意 `X, Y ∈ R3`，`X x Y` 依然是一个向量，即 `X x Y ∈ R3`，因此满足封闭性条件
    - 双线性：对任意 `X，Y，Z ∈ R3, a, b ∈ R`，由于向量叉乘运算满足分配率和线性，因此有
        - `(aX + bY) x Z = aX x Z + bY x Z = a(X x Z) + b(Y x Z)`
        - `Z x (aX + bY) = a(Z x X) + b(Z x Y)`
    - 自反性：对任意 `X ∈ R3`， `|X x X| = |X||X|sin(0) = 0`, 因此 `X x X = 0`
    - 雅克比等价：
        - 对任意 `X, Y, Z ∈ R3`，因向量叉乘运算满足：
            - `(X x Y) x Z = (XZ)Y - (YZ)X`
            - `X x (Y x Z) = (XZ)Y - (XY)Z`
        - 因此 `X x (Y x Z) + Y x (Z x X) + Z x (X x Y) = X(YZ) - Z(XY) + (YX)Z - (YZ)X + (ZY)X - (ZX)Y = 0`

## 推导 SE(3) 的指数映射

见 [se3.png](se3.png)

## 伴随

见 [adjoint.png](adjoint.png)

## 轨迹的描绘

1. 事实上，`T_WC` 的平移部分即构成了机器人的轨迹。它的物理意义是什么？为何画出 `T_WC` 的平移 部分就得到了机器人的轨迹?
    - 物理意义：`T_WC` 指的是从相机中心到世界坐标系原点的平移向量
    - 世界坐标系不随相机运动而变化，因此可以认为 `T_WC` 是机器人相对于原点坐标在移动，移动可视化在观察者眼中就是机器人的运动轨迹

2. 代码见 [code](code)

    - 数据读取部分：[Line:88](code/draw_trajectory.cpp)

    ``` C++
        ifstream in(trajectory_file);
        double t, tx, ty, tz, qx, qy, qz, qw;
        while (!in.eof()) {
            in >> t;
            in >> tx;
            in >> ty;
            in >> tz;
            in >> qx;
            in >> qy;
            in >> qz;
            in >> qw;
            poses.emplace_back(
                Sophus:::SE3(
                    Eigen::Quaterniond(q_w,q_x,q_y,q_z),
                    Eigen::Vector3d(t_x,t_y,t_z)))
        }
    ```

    - [CMakelists.txt](code/CMakelists.txt)

## 轨迹的误差

- 误差计算：[Line:69](code/draw_trajectory.cpp)
- 可视化对比：[Line:18](code/draw_trajectory.cpp)
