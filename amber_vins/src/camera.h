#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <iostream>
#include <Eigen/Dense>
using namespace Eigen;
using namespace std;

class Camera
{
public:
    //
    // Camera calibration
    //
    /* Projection */
    double ox, oy,  // principal point [px,px]
           fx, fy, // focal length [px,px]
           k1, k2, k3,   // radial distortion parameters [n/u,n/u]
           t1, t2;   // tangential distortion parameters [n/u,n/u]
    
    Camera();
    void setDistortionParam(double _k1, double _k2, double _t1, double _t2, double _k3);
    void setIntrinsicParam(double _fx, double _fy, double _ox, double _oy);

    Vector2d cameraProject(const Vector3d &p);
    Matrix<double, 2, 3> jacobianH(const Vector3d &p);
    Vector3d triangulateGNInverseDepth(const Matrix4Xd& CG_q, const Matrix3Xd& G_p_C, const Matrix2Xd& z, const Vector3d& guess = Vector3d(0, 0, 0));
    Vector3d triangulateGN(const Matrix4Xd& CG_q, const Matrix3Xd& G_p_C, const Matrix2Xd& z, const Vector3d& guess = Vector3d(0, 0, 0));
    Vector3d triangulateLMInverseDepth(const Matrix4Xd& CG_q, const Matrix3Xd& G_p_C, const Matrix2Xd& z, const Vector3d& guess = Vector3d(0, 0, 0));
    Vector3d triangulateLM(const Matrix4Xd& CG_q, const Matrix3Xd& G_p_C, const Matrix2Xd& z, const Vector3d& guess = Vector3d(0, 0, 0));

    Vector3d triangulateFromTwoView(const Quaterniond& CiG_q, const Vector3d& G_p_Ci, const Vector2d& zi,
                                    const Quaterniond& CjG_q, const Vector3d& G_p_Cj, const Vector2d& zj);
    Vector3d triangulate(const Matrix4Xd& CG_q, const Matrix3Xd& G_p_C, const Matrix2Xd& z, double* r_norm = NULL);

    friend ostream& operator<<(ostream& out, const Camera& camera);
};


#endif //_CAMERA_H_
