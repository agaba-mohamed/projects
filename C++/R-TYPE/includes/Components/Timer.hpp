/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-zyad.othman
** File description:
** Timer
*/

#include "Render.hpp"

#ifndef TIMER_HPP_
#define TIMER_HPP_

class Timer : public AComponents{
    public:
        Timer() {};
        ~Timer() {};

        void startTimer() {
            if (!isReset)
                startTime = std::chrono::high_resolution_clock::now();
        };

        bool checkTimer(double cooldown) {
            currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed_seconds = currentTime - startTime;
            double seconds = elapsed_seconds.count();
            if (seconds > cooldown) {
                needReset = true;
                return true;
            }
            return false;
        };

        void ResetTimer() {
            if (needReset) {
                isReset = true;
                startTime = std::chrono::high_resolution_clock::now();
            }
        };

    protected:
    private:
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point currentTime;
        bool isReset = false;
        bool needReset = false;
};

#endif /* !TIMER_HPP_ */
