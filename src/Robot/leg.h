#ifndef LEG_H
#define LEG_H

///klasa nogi z implementacja kinematyki odwrotnej opartej na
///https://oscarliang.com/inverse-kinematics-and-trigonometry-basics/
///https://oscarliang.com/inverse-kinematics-implementation-hexapod-robots/

#include <opencv2/core/core.hpp>
#include "util.h"
#include "Robot/servo.h"

class Leg
{
    private:
        joints legJoints; //joint A - przy podstawie, nastepne po koleji
        cv::Point3f angles;//katy na zgieciach x - kat przy polaczeniu A, y przy B, z przy C
        cv::Point3f initAngles;
        cv::Point3f lengths;//dlugosci poszczegolnych czesci nog x-AB y-BC z-CD
        cv::Mat R; //macierz obrotu tak aby obrócić część nóg o 180 stopni

        Servo servos[3];

        void calculateJointPoints(); //calculate joint points B, C, D relative to given point A with information about lentghs of leg parts and angles between them
        void sendServoSignals();
    public:
        Leg(){};
        Leg(cv::Point3f joint1, cv::Point3f angles1, cv::Point3f lengths1, cv::Point3i servos1, cv::Point3f signals1);

        joints getJoints() const {return legJoints;};

        void initialize();

        void setJointA(cv::Point3f joint1) {legJoints.A = joint1;};
        void setAngles(cv::Point3f angles1) {angles = angles1;};
        void setLengths(cv::Point3f lengths1) {lengths = lengths1;};
        void setR(cv::Mat R1) {R = R1;};
        
        void setServos(cv::Point3i servos1, cv::Point3f signals1);

        void restart(); //brings angles back to initial values

        void moveLeg(cv::Point3f t);
};

#endif // LEG_H
