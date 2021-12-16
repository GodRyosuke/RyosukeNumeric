#include <iostream>
// ルンゲクッタ法を用いて常微分方程式を解く

double pow(int a, int b)
{
    if (b == 0) {
        return 1;
    }
    if (b > 0) {
        int ans = 1;
        for (int i = 0; i < b; i++) {
            ans *= a;
        }
        return (double)ans;
    }
    if (b < 0) {
        double ans = 1;
        for (int i = 0; i < -b; i++) {
            ans /= (double)a;
        }
        return ans;
    }
}

// ルンゲクッタ法でネイピア数導出
// @param n: index
// @param h: 刻み幅
// @param yn: y(0)
double lead_e(int n, double h, double yn) {
    std::cout << yn << std::endl;
    if (n * h > 1) { // x = 1になったら終了
        return yn;
    }
    double k1 = yn;
    double k2 = yn + h * k1 / 2;
    double k3 = yn + h * k2 / 2;
    double k4 = yn + h * k3;
    double phi = (k1 + 2*k2 + 2*k3 + k4) / 6;
    double yn_next = yn + h * phi;

    lead_e(n + 1, h, yn_next);
}

int main(int argc, char** argv)
{
    double h = pow(2, -4); // <-euler法では、2^-13刻み幅でもイマイチだった
    double ans = lead_e(1, h, 1); // y(0) = 1
    std::cout << "answer: " << ans << std::endl;
    
    return 0;
}