#include <iostream>
// euler法を用いて常微分方程式を解く

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

// euler法でネイピア数を導出
double lead_e(int n, double yn, double h)
{
    std::cout << yn << std::endl;
    // 刻み幅hより、x=1となるnの値は、nh=1より、n = 1/h
    if (n * h > 1) { // e^xでは、x = 1のときy=eとなるから。
        return yn;
    }
    lead_e(n + 1, (1 + h) * yn, h);
}

int main(int argc, char** argv)
{
    double h = pow(2, -13);
    std::cout << "h: " << h << std::endl;
    int max_N = 100;
    double leaded_e = lead_e(1, 1, h);
    std::cout << "answer: " << leaded_e << std::endl;
    return 0;
}