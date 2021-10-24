#include <sophus/se3.hpp>
#include <string>
#include <iostream>
#include <fstream>

// need pangolin for plotting trajectory
#include <pangolin/pangolin.h>

#include <unistd.h>

using namespace std;

// function for plotting trajectory, don't edit this code
// start point is red and end point is blue
void DrawTrajectory(vector<Sophus::SE3<double>, Eigen::aligned_allocator<Sophus::SE3<double>>>);

void DrawTrajectory(vector<Sophus::SE3<double>, Eigen::aligned_allocator<Sophus::SE3<double>>> truth_poses,
                    vector<Sophus::SE3<double>, Eigen::aligned_allocator<Sophus::SE3<double>>> estimated_poses) {
    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));


    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);
        for (size_t i = 0; i < truth_poses.size() - 1; i++) {
            // glColor3f(1 - (float) i / truth_poses.size(), 0.0f, (float) i / truth_poses.size());
            glColor3f(1.0f, 0.0f, 0.0f);
            glBegin(GL_LINES);
            auto p1 = truth_poses[i], p2 = truth_poses[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();

            glColor3f(0.0f, 0.0f, 1.0f);
            glBegin(GL_LINES);
            p1 = estimated_poses[i]; p2 = estimated_poses[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }
}

double CalculateRMSE(vector<Sophus::SE3<double>, Eigen::aligned_allocator<Sophus::SE3<double>>> truth_poses,
                   vector<Sophus::SE3<double>, Eigen::aligned_allocator<Sophus::SE3<double>>> etimated_poses) {
    Eigen::Matrix<double, 6, 1> se3;
    double rmse = 0.;
    for (int i = 0; i < truth_poses.size(); ++i) {
        se3 = (truth_poses[i].inverse() * etimated_poses[i]).log();
        rmse += se3.squaredNorm();
    }
    rmse = sqrt(rmse / truth_poses.size());
    return rmse;
}

void ReadPoses(string &trajectory_file, vector<Sophus::SE3<double>, Eigen::aligned_allocator<Sophus::SE3<double>>> &poses) {
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
            Sophus::SE3<double>(
                Eigen::Quaterniond(qw, qx, qy, qz),
                Eigen::Vector3d(tx, ty, tz)));
    }
    cout << "read " << poses.size() << " poses from " << trajectory_file << endl;
}

int main(int argc, char **argv) {
    // path to trajectory file
    string trajectory_file = "./trajectory.txt";

    vector<Sophus::SE3<double>, Eigen::aligned_allocator<Sophus::SE3<double>>> poses;

    /// implement pose reading code
    // start your code here (5~10 lines)

    ReadPoses(trajectory_file, poses);

    // end your code here

    // draw trajectory in pangolin
    DrawTrajectory(poses);
    return 0;
}

/*******************************************************************************************/
void DrawTrajectory(vector<Sophus::SE3<double>, Eigen::aligned_allocator<Sophus::SE3<double>>> poses) {
    if (poses.empty()) {
        cerr << "Trajectory is empty!" << endl;
        return;
    }

    // create pangolin window and plot the trajectory
    pangolin::CreateWindowAndBind("Trajectory Viewer", 1024, 768);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    pangolin::OpenGlRenderState s_cam(
            pangolin::ProjectionMatrix(1024, 768, 500, 500, 512, 389, 0.1, 1000),
            pangolin::ModelViewLookAt(0, -0.1, -1.8, 0, 0, 0, 0.0, -1.0, 0.0)
    );

    pangolin::View &d_cam = pangolin::CreateDisplay()
            .SetBounds(0.0, 1.0, pangolin::Attach::Pix(175), 1.0, -1024.0f / 768.0f)
            .SetHandler(new pangolin::Handler3D(s_cam));


    while (pangolin::ShouldQuit() == false) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        d_cam.Activate(s_cam);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glLineWidth(2);
        for (size_t i = 0; i < poses.size() - 1; i++) {
            glColor3f(1 - (float) i / poses.size(), 0.0f, (float) i / poses.size());
            glBegin(GL_LINES);
            auto p1 = poses[i], p2 = poses[i + 1];
            glVertex3d(p1.translation()[0], p1.translation()[1], p1.translation()[2]);
            glVertex3d(p2.translation()[0], p2.translation()[1], p2.translation()[2]);
            glEnd();
        }
        pangolin::FinishFrame();
        usleep(5000);   // sleep 5 ms
    }

}
